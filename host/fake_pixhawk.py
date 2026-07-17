#!/usr/bin/env python3
"""Fake Pixhawk / GCS that talks to the Nucleo over the ST-Link virtual COM port.

Speaks the military dialect (which includes common). It:
  1. Waits for the Nucleo's HEARTBEAT so we know the link and common dialect work.
  2. Sends ESAD_ARMING (military) with a chosen arming_request.
  3. Waits for the ESAD_STATE (military) reply and prints the echoed arming_status.

Usage:
    python3 fake_pixhawk.py [--port /dev/cu.usbmodem1103] [--baud 57600] [--arm 1]

The military dialect module is generated on first run from the mavlink submodule
in the PX4 worktree (see generate_dialect.sh), and dropped next to this file.
"""
import argparse
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)  # so the generated military_dialect.py is importable

try:
    import military_dialect as mil
except ImportError:
    sys.exit(
        "military_dialect.py not found. Run ./generate_dialect.sh first "
        "to generate the pymavlink military dialect."
    )

from pymavlink import mavutil

# Force pymavlink to use our generated military dialect for all encode/decode.
mavutil.mavlink = mil


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", default="/dev/cu.usbmodem1103")
    ap.add_argument("--baud", type=int, default=57600)
    ap.add_argument("--arm", type=int, default=1, choices=(0, 1),
                    help="arming_request to send: 1=arm, 0=disarm")
    ap.add_argument("--timeout", type=float, default=10.0)
    args = ap.parse_args()

    print(f"opening {args.port} @ {args.baud}")
    m = mavutil.mavlink_connection(args.port, baud=args.baud, dialect=None)
    m.mav = mil.MAVLink(m, srcSystem=255, srcComponent=190)  # GCS identity

    print("waiting for HEARTBEAT from the Nucleo...")
    hb = m.wait_heartbeat(timeout=args.timeout)
    if hb is None:
        print("FAIL: no heartbeat (is the sketch flashed and the port right?)")
        return 1
    print(f"  HEARTBEAT ok: sys={m.target_system} comp={m.target_component} "
          f"type={hb.type} autopilot={hb.autopilot}")

    print(f"sending ESAD_ARMING arming_request={args.arm} (military)...")
    m.mav.esad_arming_send(
        time_usec=int(time.time() * 1e6),
        arming_challenge_hash=0xDEADBEEF,
        arming_request=args.arm,
    )

    print("waiting for ESAD_STATE reply (military)...")
    deadline = time.time() + args.timeout
    while time.time() < deadline:
        msg = m.recv_match(type="ESAD_STATE", blocking=True, timeout=1)
        if msg is None:
            continue
        state_name = {0: "DISARMED", 1: "ARMED", 2: "FAULT"}.get(
            msg.arming_status, str(msg.arming_status))
        sw = bytes(msg.sw_version_hash).rstrip(b"\x00").decode(errors="replace")
        print(f"  ESAD_STATE ok: arming_status={msg.arming_status} ({state_name}) "
              f"munition_status={msg.munition_status} sw_hash={sw!r}")
        expected = args.arm  # 1->ARMED(1), 0->DISARMED(0)
        if msg.arming_status == expected:
            print("PASS: Nucleo echoed the arming request over the military dialect.")
            return 0
        print(f"WARN: expected arming_status={expected}, got {msg.arming_status}")
        return 2

    print("FAIL: no ESAD_STATE reply within timeout")
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
