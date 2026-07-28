#!/usr/bin/env python3
"""GCS that talks to the ESAD payload *through* PX4.

Topology:
    Mac (this script)  <--USB-->  Tropic (PX4)  <--TELEM2-->  Nucleo (ESAD)

PX4 is the router. It must be flashed with the military dialect so it can parse
and forward the ESAD messages. This script:
  1. Connects to PX4 over USB and confirms PX4's own HEARTBEAT (system 1).
  2. Watches for the payload's HEARTBEAT (system 2, comp 190) forwarded from
     TELEM2, proving PX4 sees the Nucleo.
  3. Sends ESAD_ARMING addressed to the payload; PX4 forwards it out TELEM2.
  4. Waits for the payload's ESAD_STATE reply, forwarded back.

Usage:
    python3 gcs_via_px4.py [--port /dev/ttyACM0] [--baud 57600] [--arm 1]

The flight controller port is autodetected on macOS (`/dev/cu.usbmodem*`) and
Linux (`/dev/ttyACM*`); it identifies the FC by its USB strings so it does not
grab the Nucleo's ST-Link by mistake. Pass `--port` to override.

USB CDC ignores the baud value, but PX4's TELEM2 link to the Nucleo must match
the Nucleo's 57600 8N1 no-flow (set via PX4 params, see README).
"""
import argparse
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

try:
    import military_dialect as mil
except ImportError:
    sys.exit("military_dialect.py not found. Run ./generate_dialect.sh first.")

import pymavlink_compat
from pymavlink import mavutil

pymavlink_compat.apply()   # pymavlink instance-message crash in recv_match()
mavutil.mavlink = mil

PAYLOAD_SYS = 2      # the Nucleo ESAD identifies as system 2
PAYLOAD_COMP = 190


def _autodetect_fc_port() -> str:
    """The flight controller's USB CDC port, across macOS and Linux.

    macOS names it `/dev/cu.usbmodem*`, Linux `/dev/ttyACM*`, so a hardcoded
    default for one is broken on the other. Unlike the Nucleo scripts we must
    pick the *FC* here, and on a bench both boards are plugged in at once, so
    identify it rather than taking the first CDC port:

      * PX4 firmware reports itself as e.g. "PX4 FMU v6XRT.x" with vendor
        "Dronecode Project, Inc." (USB VID 0x3643).
      * The Nucleo's ST-Link is VID 0x0483 and must never be chosen here.

    Returns "" if nothing plausible is attached.
    """
    from serial.tools import list_ports
    ST_LINK_VID = 0x0483
    cands = [p for p in list_ports.comports()
             if "usbmodem" in p.device or "ttyACM" in p.device]
    for p in cands:
        blob = f"{p.description or ''} {p.manufacturer or ''} " \
               f"{p.product or ''}".lower()
        if p.vid == 0x3643 or "px4" in blob or "pixhawk" in blob:
            return p.device
    # Nothing self-identified as PX4: fall back to any CDC port that is not the
    # ST-Link, so a board with unusual USB strings still works.
    for p in cands:
        if p.vid != ST_LINK_VID:
            return p.device
    return ""


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", default=None,
                    help="flight controller serial port; default: autodetect")
    ap.add_argument("--baud", type=int, default=57600)
    ap.add_argument("--arm", type=int, default=1, choices=(0, 1))
    ap.add_argument("--timeout", type=float, default=15.0)
    args = ap.parse_args()

    port = args.port or _autodetect_fc_port()
    if not port:
        from serial.tools import list_ports
        print("FAIL: no flight controller port found. Pass --port explicitly.")
        print("  ports seen: "
              + (", ".join(p.device for p in list_ports.comports()) or "(none)"))
        return 1

    print(f"opening PX4 at {port}")
    # robust_parsing resyncs past connect-time junk / partial frames instead of
    # raising on a bad magic byte.
    m = mavutil.mavlink_connection(port, baud=args.baud, dialect=None,
                                   robust_parsing=True)
    m.mav = mil.MAVLink(m, srcSystem=255, srcComponent=190)  # GCS identity
    m.mav.robust_parsing = True
    # Announce ourselves so PX4 marks the USB component "seen" and forwards to it.
    m.mav.heartbeat_send(mil.MAV_TYPE_GCS, mil.MAV_AUTOPILOT_INVALID, 0, 0, 0)

    # Must be PX4 (sys 1), not the payload (sys 2). wait_heartbeat() locks onto
    # the first heartbeat of any node, and the payload's MAV_TYPE_GENERIC is not
    # filtered out, so it could win the lock. Explicitly require srcSystem==1.
    print("waiting for PX4 HEARTBEAT (sys=1)...")
    hb = None
    deadline = time.time() + args.timeout
    while time.time() < deadline:
        cand = m.recv_match(type="HEARTBEAT", blocking=True, timeout=1)
        if cand and cand.get_srcSystem() == 1:
            hb = cand
            break
    if hb is None:
        print("FAIL: no PX4 heartbeat (sys=1)"); return 1
    print(f"  PX4 up: sys={hb.get_srcSystem()} autopilot={hb.autopilot} type={hb.type}")

    # 2. See the payload's heartbeat come through PX4 from TELEM2.
    print(f"watching for payload HEARTBEAT (sys={PAYLOAD_SYS} comp={PAYLOAD_COMP}) "
          "forwarded from TELEM2...")
    seen_payload = False
    deadline = time.time() + args.timeout
    while time.time() < deadline:
        msg = m.recv_match(type="HEARTBEAT", blocking=True, timeout=1)
        if msg and msg.get_srcSystem() == PAYLOAD_SYS \
                and msg.get_srcComponent() == PAYLOAD_COMP:
            print(f"  payload seen through PX4: sys={msg.get_srcSystem()} "
                  f"comp={msg.get_srcComponent()} type={msg.type}")
            seen_payload = True
            break
    if not seen_payload:
        print("FAIL: never saw the payload heartbeat via PX4.")
        print("  check: TELEM2 baud/flow params, MAV_x_CONFIG=TELEM2, wiring, "
              "MAV_x_FORWARD=1")
        return 1

    # 3. Send ESAD_ARMING to the payload; PX4 routes it out TELEM2.
    # Drain any ESAD_STATE already buffered (e.g. from a prior run) so the reply
    # we match below is genuinely a response to THIS request. The Nucleo stamps
    # ESAD_STATE.time_usec with board uptime (micros()), not wall-clock, so we
    # cannot gate on a wall-clock timestamp; draining is the reliable approach.
    while m.recv_match(type="ESAD_STATE", blocking=False) is not None:
        pass

    # ESAD_ARMING has no target_system/target_component fields, so this is a
    # broadcast: PX4 forwards it out TELEM2 based on MAV_x_FORWARD, not routing.
    print(f"sending ESAD_ARMING arming_request={args.arm} to payload...")
    m.mav.esad_arming_send(
        time_usec=int(time.time() * 1e6),
        esad_id=1,          # target ESAD instance 1 (0 = all instances)
        arming_challenge_hash=0xDEADBEEF,
        arming_request=args.arm,
        store_id=0,         # 0 = all stores / broadcast
    )

    # 4. Wait for the ESAD_STATE forwarded back from the payload.
    print("waiting for ESAD_STATE from payload (forwarded back through PX4)...")
    deadline = time.time() + args.timeout
    while time.time() < deadline:
        msg = m.recv_match(type="ESAD_STATE", blocking=True, timeout=1)
        if msg is None:
            continue
        name = {0: "DISARMED", 1: "ARMED", 2: "FAULT"}.get(
            msg.arming_status, str(msg.arming_status))
        print(f"  ESAD_STATE from sys={msg.get_srcSystem()}: "
              f"arming_status={msg.arming_status} ({name})")
        # arming_status is ESAD_ARMING_STATUS (DISARMED=0/ARMED=1); args.arm is
        # ESAD_ARMING_REQUEST (DISARM=0/ARM=1). They line up on 0/1 by design.
        if msg.arming_status == args.arm:
            print("PASS: full loop Mac -> PX4 -> Nucleo -> PX4 -> Mac over the "
                  "military dialect.")
            return 0
        # A non-matching (stale/transitional) state is not a failure; keep
        # waiting for the matching reply until the deadline.
        print(f"  (ignoring arming_status={msg.arming_status}, want {args.arm})")

    print("FAIL: no matching ESAD_STATE returned. The arming request may not have "
          "reached the payload (forwarding / wiring / baud).")
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
