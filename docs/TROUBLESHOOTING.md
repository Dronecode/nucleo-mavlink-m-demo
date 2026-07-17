# Troubleshooting

Symptoms and fixes, most-common first. Topology B (Mac ↔ PX4 ↔ Nucleo) has the
most moving parts, so most of this is about it.

Topology B is **confirmed working on real hardware**: the full loop
Mac → PX4 → Nucleo → PX4 → Mac passes for both arm and disarm, and LD2 tracks
the arming state. Everything below was hit and resolved during that bring-up, so
if you are seeing one of these symptoms it is a known issue with a known fix, not
a dead end.

## No payload heartbeat via PX4

**Symptom:** `gcs_via_px4.py` sees PX4's own heartbeat (sys 1) but never the
payload's (`sys=2 comp=190`), and prints:

```
FAIL: never saw the payload heartbeat via PX4.
```

The Nucleo is heartbeating fine on its own, but the frames are not reaching the
GCS through PX4. Work down this list:

1. **First, confirm the params actually took.** In the PX4 shell run
   `mavlink status`. The TELEM2 instance must show a **serial** device
   `/dev/ttyS4` at `57600`:

   ```
   mavlink status
   ...
   instance #1:
       GCS heartbeat ...
       mavlink chan: #1
       type: GENERIC LINK OR PROTOCOL
       device: /dev/ttyS4  <-- must be the serial port, not UDP
       baudrate: 57600
   ```

   If instance #1 shows a **UDP** port (an IP/port pair) instead of
   `/dev/ttyS4`, the params did **not** take — most often because `MAV_1_CONFIG`
   was written as garbage over MAVLink `PARAM_SET` (see the INT32 section below),
   or because you never rebooted after `param save`. Fix the params and reboot
   before chasing wiring.
2. **Wiring: crossed and on the right pins.** The MAVLink link is **USART1**
   (PA9 = D8 = TX, PA10 = D2 = RX), crossed to the Tropic's TELEM2, plus GND.
   The `D0`/`D1` pins are USART2 (the ST-Link debug port), **not** the FC link —
   wiring there is the classic dead-link mistake. See [WIRING.md](WIRING.md).
   Confirm the Nucleo is actually transmitting: the debug console (USART2 /
   ST-Link VCP, 115200) prints `HB tx on USART1, N bytes` once a second.
3. **`MAV_1_CONFIG=102`** so TELEM2 is a MAVLink instance at all.
4. **`SER_TEL2_BAUD=57600`** matching the Nucleo. A baud mismatch gives silence
   or garbage, never clean frames.
5. **`MAV_1_FLOW_CTRL=0`.** The link is 3-wire; with flow control on auto, PX4
   can wait forever on a CTS that is never asserted.
6. **`MAV_1_FORWARD=1`.** This is the one people miss — PX4 forwarding is **off
   by default**. Without it, TELEM2 frames never cross to the USB/GCS link.
7. **Reboot after `param save`.** These take effect on reboot, not immediately.

Confirm on the Nucleo debug console first (step 2). If the Nucleo is transmitting
but PX4 still shows nothing, the problem is params/wiring on the PX4 side, not
the firmware.

## Wrong pins: PX4 receives zero bytes on TELEM2

**Symptom:** the Nucleo is provably transmitting (its debug console prints
`HB tx on USART1, N bytes` every second), TELEM2 shows up correctly in
`mavlink status` as `/dev/ttyS4` at 57600, yet PX4 receives **zero bytes** on
TELEM2. Swapping the two data wires makes no difference — still zero bytes in
**both** orientations.

**Cause:** you are wired to the wrong UART. On the Nucleo-64, the Arduino
`D0`/`D1` pins are **USART2** (PA3/PA2) — the ST-Link debug port — **not**
USART1. The firmware's MAVLink link (`FCLink`) is on **USART1**, which is
**D8 (PA9, TX)** and **D2 (PA10, RX)**. If you land on D0/D1 you are tapping the
debug console UART, which is not connected to the Tropic, so no orientation of
the two wires will ever carry a byte. That "dead in both orientations" symptom is
the tell that it is a wrong-UART problem, not a TX/RX swap.

**Fix:** move to USART1 and cross it:

- Nucleo **PA9 (D8, TX)** → Tropic TELEM2 **RX**
- Nucleo **PA10 (D2, RX)** → Tropic TELEM2 **TX**
- common **GND**

Full pinout in [WIRING.md](WIRING.md). If bytes still do not arrive after moving
to D8/D2, *then* try swapping TX/RX — a plain TX/RX swap gives the same zero-byte
symptom but is fixed by the swap, whereas the wrong-UART case is not.

## INT32 PARAM_SET stores garbage

**Symptom:** you set the TELEM2 params from a script over MAVLink `PARAM_SET`
instead of the shell, everything "succeeds", but TELEM2 behaves as if
unconfigured — wrong config, wrong baud, no forwarding.

**Cause:** MAVLink `PARAM_SET` carries the value in a `float param_value` field.
PX4's INT32 params (`MAV_1_CONFIG`, `MAV_1_MODE`, `MAV_1_FORWARD`, …) expect the
integer's **bit pattern** reinterpreted as a float, not the numeric value.
Sending `float(102)` writes the IEEE-754 encoding of 102.0, whose raw bits PX4
reads back as the integer **1120665600** — that exact readback is the fingerprint
of this bug. (`struct.unpack('<i', struct.pack('<f', 102.0))[0] == 1120665600`.)

**Fix:** pack the int and reinterpret its bytes as a float on the way out:

```python
import struct
def int_as_float(i):
    return struct.unpack('<f', struct.pack('<i', i))[0]

# e.g. MAV_1_CONFIG = 102
m.mav.param_set_send(target_system, target_component,
                     b"MAV_1_CONFIG",
                     int_as_float(102),
                     mavutil.mavlink.MAV_PARAM_TYPE_INT32)
```

**Verifying the readback:** the `PARAM_VALUE` PX4 returns is *also* a float
carrying the int's bit pattern, so you must reinterpret it the other way to
check it. Do **not** compare `param_value` to `102` directly — it will read as
`102.0`-shaped garbage. Convert back:

```python
def float_as_int(f):
    return struct.unpack('<i', struct.pack('<f', f))[0]

# msg is the returned PARAM_VALUE for MAV_1_CONFIG
assert float_as_int(msg.param_value) == 102
```

Simplest of all: use the PX4 MAVLink shell (`Tools/mavlink_shell.py`) and
`param set MAV_1_CONFIG 102`, then `param show MAV_1_CONFIG` to confirm. The shell
does the encoding and readback correctly, which is why
[`px4_telem2_setup.txt`](../host/px4_telem2_setup.txt) uses `param set` rather
than scripted `PARAM_SET`.

## The GCS sees the payload but ESAD_ARMING gets no reply

**Symptom:** the payload heartbeat comes through, but after sending
`ESAD_ARMING` the GCS never gets a matching `ESAD_STATE`:

```
FAIL: no matching ESAD_STATE returned.
```

Two likely causes:

### component_was_seen timing gate

PX4 only forwards to a component it has actually **seen**. Two conditions:

- The **GCS must announce itself** — send at least one packet so PX4 marks the
  USB/GCS component "seen" and will forward to it. Both host scripts send a GCS
  `HEARTBEAT` on connect for exactly this reason.
- Let the **Nucleo heartbeat for a second** before sending `ESAD_ARMING`, so PX4
  has registered the payload as a node. Firing the arming request the instant
  the script connects can beat this gate.

If you script your own GCS, replicate both: heartbeat on connect, and wait for
the payload heartbeat before arming.

### Dialect not compiled into PX4

If PX4 was **not** built with `CONFIG_MAVLINK_DIALECT="military"`, it cannot
parse `ESAD_*` (the CRC-extra byte is unknown), so it drops those frames
silently. Heartbeats still flow, which makes this look like a forwarding problem.
Rebuild PX4 with the military dialect (see [SETUP.md](SETUP.md#4-build-and-flash-the-tropic-px4-topology-b)).

## robust_parsing / junk on connect

**Symptom:** the host script raises `invalid MAVLink prefix` right after opening
the port, or locks onto the wrong node.

**Fix (already in the scripts):** open the connection with `robust_parsing=True`
so pymavlink resyncs past connect-time junk and partial frames instead of raising
`invalid MAVLink prefix` on the first non-magic byte. Both host scripts set it on
the connection **and** on `m.mav`. Also, `wait_heartbeat()` locks onto the
*first* heartbeat of *any*
node — and the payload's `MAV_TYPE_GENERIC` is not filtered out, so it can win
the lock over PX4. `gcs_via_px4.py` explicitly requires `srcSystem == 1` when
waiting for PX4. If you write your own client, do the same: filter heartbeats by
system ID rather than trusting the first one.

Related: the very first `HEARTBEAT` right after a flash/reset can report `sys=0`.
That is partial-frame noise from the board re-enumerating, not a firmware bug;
subsequent frames are clean (`sys=2 comp=190`).

## PX4 build fails: R_ARM_PREL31 relocation out of range

**Symptom:** building `nxp_mr-tropic_default` with the military dialect fails to
link with a relocation truncated / `R_ARM_PREL31` out-of-range error, referencing
`__udivmoddi4` or an `.ARM.exidx` section.

**Cause:** the military dialect pulls 64-bit division (`__udivmoddi4`) into the
mr-tropic link. The board's linker script force-places that routine in ITCM at
`0x0`, while its ARM stack-unwind entry (`.ARM.exidx`) lands in flash at
`0x60xxxxxx`. `R_ARM_PREL31` is a signed 31-bit PC-relative relocation and cannot
span that ~1.6 GB gap between the code and its unwind entry.

**Fix:** discard the unwind tables. They are unused under `-fno-exceptions`, so
this is safe. In
`boards/nxp/mr-tropic/nuttx-config/scripts/script.ld`, add to the `SECTIONS`
block:

```ld
/DISCARD/ : {
    *(.ARM.exidx*)
    *(.ARM.extab*)
}
```

This change lives in the **PX4 tree**, not this repo, and applies only to i.MXRT
boards. Full context, including the before/after linker snippet and which boards
are affected, in
[PX4_INTEGRATION.md](PX4_INTEGRATION.md#imxrt-boards-only-r_arm_prel31-link-error).

## Nucleo flashes but nothing happens

- **Wrong port for upload.** `arduino-cli upload` targets the ST-Link VCP
  (`/dev/cu.usbmodem1103` here), and copies the `.bin` onto the ST-Link
  mass-storage drive (`/Volumes/NOD_F103RB`). If the drive is not mounted, the
  upload cannot complete — re-plug the Nucleo's ST-Link USB.
- **Nothing on the debug console.** The debug console is USART2 over the ST-Link
  VCP at **115200** (not 57600 — that is the FC link baud). Open the right port
  at the right baud.

## Quick checklist for topology B

This is the sequence that produced a passing run on hardware:

1. Nucleo flashed; debug console prints `HB tx on USART1, N bytes` at 1 Hz.
2. TELEM2 wired to USART1 (D8/D2), crossed, with GND. Not D0/D1.
3. PX4 built with `CONFIG_MAVLINK_DIALECT="military"` + the linker fix.
4. TELEM2 params set (`MAV_1_CONFIG=102`, `SER_TEL2_BAUD=57600`, `MAV_1_MODE=2`,
   `MAV_1_FORWARD=1`, `MAV_1_FLOW_CTRL=0`), saved, **rebooted**.
5. `mavlink status` shows instance #1 on `/dev/ttyS4` @ 57600 (serial, not UDP).
6. `python3 gcs_via_px4.py --arm 1` → `PASS`, LD2 solid on.
7. `python3 gcs_via_px4.py --arm 0` → `PASS`, LD2 off.
