#!/usr/bin/env python3
"""Diagnose why a host script cannot talk to the board. Read-only, safe to run.

Answers, in one pass and without needing the dialect generated:
  * which serial ports exist, and which one looks like the board
  * whether the port is openable at all, and who is holding it if not
  * whether ModemManager is interfering (Linux)
  * what the board is actually emitting, at every plausible baud
  * whether those bytes are MAVLink v1, MAVLink v2, or a text debug console

The last one matters most. Current firmware serves MAVLink on both the USB VCP
and USART1, so USB should always answer. If a port yields only text, the board
is running an **older build** that kept MAVLink on USART1 (D8/D2) and left USB
as a 115200 text console. No host-side fix helps in that case: reflash.

Run:  python3 diagnose_link.py [--port /dev/ttyACM0]
"""
from __future__ import annotations

import argparse
import glob
import os
import platform
import subprocess
import sys
import time

BAUDS = [57600, 115200, 9600, 38400, 230400, 921600]
MAVLINK_V2 = 0xFD
MAVLINK_V1 = 0xFE


def hdr(s: str) -> None:
    print(f"\n=== {s} ===")


def list_ports_report():
    hdr("serial ports")
    try:
        from serial.tools import list_ports
    except ImportError:
        sys.exit("pyserial not installed: python3 -m pip install -r requirements.txt")
    ports = list(list_ports.comports())
    if not ports:
        print("  none found. Is the board plugged in?")
    for p in ports:
        vid = f"{p.vid:#06x}" if p.vid else "-"
        pid = f"{p.pid:#06x}" if p.pid else "-"
        tag = ""
        if p.vid == 0x0483:
            tag = "  <- ST-Link (the Nucleo)"
        elif p.vid == 0x3643 or "px4" in (p.description or "").lower():
            tag = "  <- PX4 flight controller"
        print(f"  {p.device:22s} vid={vid} pid={pid}  {p.description}{tag}")
    return ports


def pick_port(ports, explicit):
    if explicit:
        return explicit
    for p in ports:
        if p.vid == 0x0483:                      # ST-Link first
            return p.device
    for p in ports:
        if "usbmodem" in p.device or "ttyACM" in p.device:
            return p.device
    return None


def linux_checks(port: str) -> None:
    if platform.system() != "Linux":
        return
    hdr("linux host checks")

    # ModemManager AT-probes new ttyACM devices and corrupts the stream.
    try:
        out = subprocess.run(["systemctl", "is-active", "ModemManager"],
                             capture_output=True, text=True, timeout=5)
        state = out.stdout.strip() or out.stderr.strip()
        if state == "active":
            print("  ModemManager: ACTIVE  <- likely interfering")
            print("      sudo systemctl stop ModemManager")
        else:
            print(f"  ModemManager: {state}")
    except Exception:
        print("  ModemManager: could not query (systemctl unavailable)")

    # dialout membership; without it the open fails outright.
    try:
        groups = subprocess.run(["id", "-nG"], capture_output=True,
                                text=True, timeout=5).stdout.split()
        if "dialout" in groups:
            print("  dialout group: yes")
        else:
            print("  dialout group: NO  <- cannot open the port")
            print(f"      sudo usermod -aG dialout {os.environ.get('USER','$USER')}")
            print("      then log out and back in")
    except Exception:
        print("  dialout group: could not query")

    # Anything else holding the port.
    holders = []
    for fd in glob.glob("/proc/[0-9]*/fd/*"):
        try:
            if os.path.realpath(fd) == os.path.realpath(port):
                holders.append(fd.split("/")[2])
        except OSError:
            continue
    if holders:
        print(f"  port held by PID(s): {sorted(set(holders))}  <- close them")
    else:
        print("  port not held by another process (as far as /proc shows)")


def count_frames(raw: bytes, magic: int) -> int:
    """Longest run of back-to-back well-formed frames starting at each offset.

    Counting stray magic bytes is not good enough: at the wrong baud, random
    noise contains 0xFD often enough to look like MAVLink. A real stream has
    frames whose declared length lands exactly on the next frame's magic byte,
    so walk the chain and require that to hold.
    """
    best = 0
    for start in range(min(len(raw), 64)):
        i, n = start, 0
        while i < len(raw) and raw[i] == magic:
            if magic == MAVLINK_V2:
                if i + 12 > len(raw):
                    break
                plen, incompat = raw[i + 1], raw[i + 2]
                total = 12 + plen + (13 if incompat & 0x01 else 0)
            else:
                if i + 8 > len(raw):
                    break
                total = 8 + raw[i + 1]
            i += total
            n += 1
        best = max(best, n)
    return best


def classify(raw: bytes) -> str:
    if not raw:
        return "silence"
    printable = sum(1 for b in raw if 32 <= b < 127 or b in (9, 10, 13))
    pct = 100 * printable / len(raw)
    # Two chained frames is enough to be certain; noise essentially never
    # produces a length field that lands on another magic byte twice running.
    if count_frames(raw, MAVLINK_V2) >= 2:
        return "looks like MAVLink v2"
    if count_frames(raw, MAVLINK_V1) >= 2:
        return "looks like MAVLink v1"
    if pct > 85:
        return "text (debug console?)"
    return "noise / wrong baud"


def sweep(port: str):
    import serial
    hdr(f"listening on {port}")
    results = {}
    open_errors = []
    for baud in BAUDS:
        try:
            s = serial.Serial(port, baud, timeout=0.4)
        except Exception as e:
            print(f"  {baud:7d}  OPEN FAILED: {e}")
            open_errors.append(str(e))
            if "Permission denied" in str(e):
                print("           -> add yourself to the dialout group")
            elif "Device or resource busy" in str(e):
                print("           -> something else holds the port (ModemManager?)")
            results[baud] = None
            continue
        raw = b""
        t = time.time()
        while time.time() - t < 2.5:
            raw += s.read(512)
        s.close()
        kind = classify(raw)
        results[baud] = (raw, kind)
        print(f"  {baud:7d}  {len(raw):6d} bytes  {kind}")
        if raw:
            print(f"           hex: {raw[:24].hex(' ')}")
            if kind.startswith("text"):
                txt = raw[:120].decode("utf-8", errors="replace")
                for line in txt.splitlines():
                    if line.strip():
                        print(f"           txt: {line.strip()}")
    return results, open_errors


def verdict(results: dict, open_errors: list) -> None:
    hdr("verdict")
    mav = [b for b, r in results.items() if r and "MAVLink" in r[1]]
    text = [b for b, r in results.items() if r and r[1].startswith("text")]
    anything = [b for b, r in results.items() if r and r[0]]

    # Never opened at all: that is a host/permissions/path problem, and saying
    # "silence" here would send you off debugging firmware for no reason.
    if not results or all(r is None for r in results.values()):
        why = open_errors[0] if open_errors else ""
        print("  The port could not be opened at all, so nothing was measured.")
        if "No such file" in why:
            print("  It does not exist. Re-check the device name in the list above;")
            print("  unplug and replug and watch: dmesg | tail -20 | grep -i tty")
        elif "Permission denied" in why:
            print("  Permission denied. Add yourself to dialout and re-login:")
            print(f"      sudo usermod -aG dialout {os.environ.get('USER','$USER')}")
        elif "busy" in why.lower():
            print("  Something else holds it. On Ubuntu that is usually ModemManager:")
            print("      sudo systemctl stop ModemManager")
        else:
            print(f"  Error was: {why}")
        return

    if mav:
        b = mav[0]
        print(f"  MAVLink found at {b} baud.")
        if b != 57600:
            print(f"  The host scripts default to 57600. Run with --baud {b}.")
        else:
            print("  The link is healthy. If a host script still fails, the fault")
            print("  is in the script's identity/timeout logic, not the link.")
        return

    if text:
        print(f"  Only human-readable text found (at {text[0]} baud), no MAVLink.")
        print("  That is a text debug console, which current firmware does not have.")
        print()
        print("  So this board is running an OLD build: one that kept MAVLink on")
        print("  USART1 (D8/D2) and left USB as a 115200 console. Nothing you do")
        print("  host-side will make that port speak MAVLink. Reflash it:")
        print("      FQBN='STMicroelectronics:stm32:Nucleo_64:pnum=NUCLEO_F103RB'")
        print("      arduino-cli compile -b \"$FQBN\" nucleo_mavlink_m")
        print("      arduino-cli upload  -b \"$FQBN\" -p <port> nucleo_mavlink_m")
        print("  Current firmware serves MAVLink on USB and USART1 at once.")
        return

    if anything:
        print("  Bytes arrived but nothing parsed at any baud. Likely a baud the")
        print("  sweep did not cover, or a half-broken wire. Check the hex above.")
        return

    print("  Total silence at every baud. In order:")
    print("    1. Is the sketch actually flashed and running? (press RESET and")
    print("       re-run: a boot banner should appear on the debug console)")
    print("    2. ModemManager holding the port (see above)")
    print("    3. Wrong port: try the others listed at the top")


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", default=None)
    args = ap.parse_args()

    print(f"platform: {platform.platform()}")
    ports = list_ports_report()
    port = pick_port(ports, args.port)
    if not port:
        print("\nNo candidate port. Plug the board in, or pass --port.")
        return 1
    print(f"\nusing port: {port}")
    if not args.port:
        print("  (override with --port if that is the wrong board)")

    linux_checks(port)
    results, open_errors = sweep(port)
    verdict(results, open_errors)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
