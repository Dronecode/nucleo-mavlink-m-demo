# Building a custom PX4 with the MAVLink-M dialect

A recipe for putting the military dialect into a **custom PX4 build**: your own
board variant, your own port assignment, your own peripheral. It covers the two
halves people trip over, in order:

1. **Build time.** Getting `military.xml` compiled into the binary, including how
   board *variants* (`.px4board` labels) work, since that is where a custom build
   differs from the stock one.
2. **Run time.** Getting the parsed messages to actually reach your peripheral.
   Compiling the dialect in is necessary but **not sufficient**, and the runtime
   half is not documented anywhere else in this repo.

Read **[PX4_INTEGRATION.md](PX4_INTEGRATION.md)** first for *why* the board must
be rebuilt at all (the short version: PX4 forwards any message that parses, and a
message only parses if its ID and CRC-extra were compiled in). This guide assumes
you accept that and want the mechanics for a non-default build.

Everything here was exercised on an **NXP/Pixhawk FMUv6X-RT** running PX4 1.18.0,
driving a Nucleo-F103RB ESAD over TELEM1. Where something was *not* verified in
that session it says so explicitly.

## Part 1: build time

### Pick your target

PX4 build targets are `<vendor>_<board>_<label>`, derived directly from the
`.px4board` files on disk:

```sh
find boards -mindepth 3 -maxdepth 3 -name '*.px4board'
# boards/px4/fmu-v6xrt/default.px4board  -> make px4_fmu-v6xrt_default
# boards/px4/fmu-v6xrt/bench.px4board    -> make px4_fmu-v6xrt_bench
# boards/nxp/mr-tropic/default.px4board  -> make nxp_mr-tropic_default
```

List them all with `make list_config_targets`.

### How variants merge (this is the part that surprises people)

A non-default label is **not** a standalone config. It is a *delta* applied on
top of the board's `default.px4board`. From `cmake/kconfig.cmake`:

```cmake
# Non-default labels merge default.px4board + {label}.px4board,
# so reconfigure must also trigger on changes to default.px4board.
...
merge_config.py Kconfig ${BOARD_CONFIG} ${PX4_BOARD_DIR}/default.px4board ${BOARD_DEFCONFIG}
```

So `bench.px4board` being four lines long does not mean the bench build has four
options. It means "everything in `default.px4board`, plus these four". Two
consequences:

- You only put in a variant file what **differs** from default.
- Editing `default.px4board` changes every variant of that board. If you want the
  dialect on one variant only, put the line in the **variant** file.

### Set the dialect

Add one line to whichever `.px4board` you actually build:

```
CONFIG_MAVLINK_DIALECT="military"
```

The string must match the XML filename: `military` generates from `military.xml`.
Get it wrong and CMake looks for a file that does not exist and the build fails
at generation time, not at link time.

To create a **new** variant rather than modifying an existing one, drop a new
file next to the others. A minimal military variant of a board:

```sh
# boards/px4/fmu-v6xrt/military.px4board  -> make px4_fmu-v6xrt_military
CONFIG_MAVLINK_DIALECT="military"
```

That single line inherits the entire `default.px4board` and changes only the
dialect. It is the cleanest way to keep a dialect build from disturbing the
board's normal targets.

### Put military.xml where mavgen looks

CMake feeds mavgen this exact path:

```
src/modules/mavlink/mavlink/message_definitions/v1.0/${CONFIG_MAVLINK_DIALECT}.xml
```

> **`v1.0` here is the XML schema version, not the wire protocol.** It is a
> historical directory name in the mavlink repo and it is the *only* one that has
> ever existed, so every dialect lives there, `common.xml` and
> `development.xml` included. It has nothing to do with MAVLink 1 vs 2.
>
> The wire protocol is chosen by mavgen's flag, and PX4 hardcodes v2 in
> `src/modules/mavlink/CMakeLists.txt`:
>
> ```cmake
> mavgen.py --lang C --wire-protocol 2.0 ...
> ```
>
> MAVLink-M **requires** v2 and cannot work otherwise: the v1 frame carries a
> single-byte message ID, so it can only address IDs 0-255, while the MAVLink-M
> block starts at 53000. `ESAD_STATE` (53030) is not representable in a v1 frame
> at all. If anything in your chain falls back to v1, the entire 53000 block
> silently disappears while common-dialect traffic keeps flowing, which looks
> exactly like the "dialect not compiled in" symptom. Keep `MAV_PROTO_VER` at
> `0` (auto) or `2`, never `1`, and generate host dialects with
> `--wire-protocol=2.0`.
>
> To confirm what is actually on the wire, check the first byte of a frame:
> **`0xFD` is v2, `0xFE` is v1.**

That directory is inside the **mavlink submodule**, which is the whole problem.
Three ways to populate it, worst to best for reproducibility:

**(a) Drop it in.** Copy `military.xml` straight into the submodule.

```sh
cp /path/to/mavlink-military/military.xml \
   src/modules/mavlink/mavlink/message_definitions/v1.0/
```

This is what the FMUv6X-RT session used, and it builds immediately. It is also
**destroyed by any submodule reset**: `git submodule update`, a fresh clone, or a
branch switch that moves the submodule pointer. Fine for a bring-up session, not
for CI or for a board you will rebuild next month. If a build that worked
yesterday suddenly cannot find the dialect, this is why.

**(b) Point the submodule at a fork.** Maintain a mavlink fork carrying
`military.xml` in `message_definitions/v1.0/` and update the submodule to it. The
file then survives resets because it *is* the submodule content, and no build
system changes are needed. Best option if you control a fork.

**(c) Vendor it in the PX4 tree and copy it in at configure time.** Keep the file
under version control somewhere in the PX4 tree and have CMake copy it into the
definitions directory before mavgen runs. This keeps everything in one repo.
*This variant was not exercised in the session above*, so treat any snippet as a
starting point and confirm the copy lands before mavgen runs, not after.

### Build

```sh
make px4_fmu-v6xrt_bench            # or your target
```

If your board is an **i.MXRT** part (`px4/fmu-v6xrt`, `nxp/mr-tropic`,
`nxp/tropic-community`) the link will fail with `R_ARM_PREL31` relocation
truncated until you discard the ARM unwind tables in that board's `script.ld`.
The military messages carry `uint64_t time_usec` fields, which pull 64-bit
division helpers into ITCM at `0x0` while their `.ARM.exidx` entries stay in
flash at `0x60xxxxxx`, and a signed 31-bit PC-relative relocation cannot span
that gap. Full before/after snippet and reasoning:
[PX4_INTEGRATION.md](PX4_INTEGRATION.md#imxrt-boards-only-r_arm_prel31-link-error).

This is a **per-board file**, so a custom variant does not get you out of it. It
applies to the board, not the label.

### Verify the dialect compiled in

Check the generated headers, not just a successful build:

```sh
ls build/px4_fmu-v6xrt_bench/mavlink/military/mavlink_msg_esad_*.h
# mavlink_msg_esad_arming.h
# mavlink_msg_esad_config.h
# mavlink_msg_esad_state.h

ls build/<target>/mavlink/military/mavlink_msg_*.h | wc -l    # 26 for MAVLink-M
```

Empty or missing means the dialect did not generate. Check
`build/<target>/mavgen_military.log`, then recheck the `.px4board` line and that
`military.xml` is really in the definitions directory.

## Part 2: run time

A correctly built binary still will not deliver anything to your peripheral until
routing is configured. On the FMUv6X-RT session, the firmware was right and the
loop still failed, so do not skip this half.

### Map the port to a MAVLink instance

`MAV_<i>_CONFIG` selects which physical port instance `i` binds to. The values
come from `Tools/serial/generate_config.py`:

| Value | Port | Default baud |
|---|---|---|
| 101 | TELEM 1 | 57600 |
| 102 | TELEM 2 | 921600 |
| 103 | TELEM 3 | 57600 |
| 104 | TELEM/SERIAL 4 | 57600 |
| 201 | GPS 1 | 0 (auto) |
| 202 | GPS 2 | 0 (auto) |

**The instance number and the port number are unrelated.** `MAV_0_*` is not
"TELEM1"; it is whatever `MAV_0_CONFIG` points at. Pick a free instance and set
its config. Use `MAV_1_*` and up if `MAV_0_*` is already carrying your GCS
telemetry.

The device path behind each label is per board, from that board's
`default.px4board`:

```sh
grep SERIAL_ boards/px4/fmu-v6xrt/default.px4board
# CONFIG_BOARD_SERIAL_TEL1="/dev/ttyS2"     <- differs per board!
# CONFIG_BOARD_SERIAL_TEL2="/dev/ttyS5"
```

On FMUv6X-RT, TELEM1 is `/dev/ttyS2`. On mr-tropic, TELEM2 is `/dev/ttyS4`. Do
not copy a device path from another board's instructions.

### Forwarding: both ends, not one

This is the gate that is missing from the rest of this repo's docs. PX4 forwards a
message only if the **receiving** instance has forwarding on, *and* the
**destination** instance has forwarding on. From `Mavlink::forward_message()` and
its caller in `src/modules/mavlink/mavlink_main.cpp`:

```cpp
if (get_forwarding_on()) {                 // the instance that RECEIVED the message
    Mavlink::forward_message(msg, this);
}
...
for (Mavlink *inst : mavlink_module_instances) {
    if (inst && (inst != self) && (inst->get_forwarding_on())) {   // the DESTINATION
        if (inst->_receiver.component_was_seen(target_system_id, target_component_id)) {
            inst->pass_message(msg);
        }
    }
}
```

Practical rules that fall out of this:

- **Set `MAV_<i>_FORWARD=1` on your peripheral's instance.** It is off by default
  and it is needed for *both* directions, because that instance is the receiver
  for replies and the destination for commands.
- **You do not need to configure the USB/GCS instance.** PX4 hardcodes it:

  ```cpp
  // Always forward messages to/from the USB instance.
  _forwarding_on = true;
  ```

  So a GCS on USB is covered automatically. A GCS on a *serial* link is not, and
  needs its own `MAV_<i>_FORWARD=1`.
- **`component_was_seen` is a real gate.** For a broadcast message (no
  `target_system` field, which is the case for `ESAD_ARMING`) it returns true as
  soon as the destination instance has seen *any* component. In practice: let the
  peripheral heartbeat for a second before sending commands, and have your GCS
  send a heartbeat on connect.

### Flow control on a 3-wire link

If your peripheral is wired with only TX, RX, and GND, force flow control off:

```
param set MAV_<i>_FLOW_CTRL 0
```

The default is `2` (auto). On auto, PX4 can decide flow control is on and then
wait on a CTS that a 3-wire link never asserts. The tell is brutal to diagnose
because it is **asymmetric**: your peripheral's frames arrive at PX4 with zero
loss, because that direction does not need CTS, while nothing goes back out.
Confirm with `mavlink status`, which prints `flow control: ON|OFF` per instance.

### Worked parameter set

For a peripheral on TELEM1 at 57600, 3-wire, using instance 0:

```
param set MAV_0_CONFIG 101      # 101 = TELEM1
param set SER_TEL1_BAUD 57600   # match the peripheral
param set MAV_0_MODE 2          # Onboard
param set MAV_0_FORWARD 1       # REQUIRED, off by default
param set MAV_0_FLOW_CTRL 0     # 3-wire, no CTS/RTS
param set MAV_0_RATE 0          # auto
param save
reboot
```

Substitute the instance and port for your build. A reboot is required.

Set these from the **PX4 MAVLink shell**, not scripted `PARAM_SET`. PX4's INT32
params expect the integer's bit pattern packed into the float `param_value`
field, and sending `float(101)` silently stores garbage. See
[TROUBLESHOOTING.md](TROUBLESHOOTING.md#int32-param_set-stores-garbage).

## Verifying it end to end

### Is the link alive?

```
mavlink status
```

For your peripheral's instance, confirm all four:

```
instance #0:
    flow control: OFF                              <- OFF on a 3-wire link
    Received Messages:
      sysid:  2, compid:190, Total: 122 (lost: 0)  <- peripheral is heard
    Forwarding: On                                 <- MAV_x_FORWARD took
    transport protocol: serial (/dev/ttyS2 @57600) <- serial, not UDP
```

A **UDP** transport where you expected serial means `MAV_<i>_CONFIG` did not take
(garbage `PARAM_SET`, or no reboot after `param save`).

### Is PX4 actually parsing your dialect?

There is a neat trick here that does not require any instrumentation. The
`Received Messages` counters only count frames that **parsed**, so they are a
direct test of whether the dialect is live in the running firmware:

1. Note the count for your GCS's `sysid`/`compid` on the USB instance.
2. Send exactly one dialect message from the GCS.
3. Re-read `mavlink status`.

If the counter advanced, PX4 parsed your MAVLink-M message and the dialect is
compiled in. If it did not, the frame failed CRC-extra and you are running a
`common`-only binary regardless of what you think you flashed. A frame that fails
CRC is never counted.

This cleanly separates "PX4 cannot understand the message" from "PX4 understands
it but is not delivering it", which are otherwise identical from the GCS.

### Does the peripheral hear it?

Whatever your peripheral is, give it a side channel: a debug UART, an LED, a
counter. On the reference setup the Nucleo prints to a separate USART and drives
LD2 on arm. Without that you cannot distinguish "PX4 never sent it" from "the
peripheral got it and its reply was lost", and those have completely different
fixes.

## Failure modes, by symptom

All of these produce **exactly the same** GCS-visible symptom: heartbeats flow,
your dialect messages get no reply. They stack, so fixing one can reveal the next.

| Symptom | Cause | Fix |
|---|---|---|
| Peripheral heartbeat forwards, dialect messages vanish | Binary built `common`-only | `CONFIG_MAVLINK_DIALECT` + rebuild. Confirm with the counter test above |
| Peripheral heard with 0 loss, nothing reaches it | Flow control waiting on absent CTS | `MAV_<i>_FLOW_CTRL 0` |
| Peripheral heard with 0 loss, nothing reaches it | Missing/miswired FC-TX to peripheral-RX | The asymmetry is the tell. Check the return wire |
| Nothing crosses between links at all | `MAV_<i>_FORWARD` unset | Set it to 1 on the peripheral's instance, reboot |
| Commands work, replies do not | GCS on a serial link with forwarding off | `MAV_<i>_FORWARD=1` on the GCS instance too. USB is automatic |
| Instance shows UDP, not serial | `MAV_<i>_CONFIG` never took | Set via shell, `param save`, reboot |
| Build cannot find the dialect after previously working | Submodule reset ate `military.xml` | Placement option (b) or (c) |
| Common messages flow, entire 53000 block missing | A link fell back to MAVLink **v1**, whose 1-byte msgid cannot address 53000+ | `MAV_PROTO_VER` 0 or 2. Check the frame magic: `0xFD` = v2, `0xFE` = v1 |
| Link fails, `R_ARM_PREL31` truncated | i.MXRT ITCM vs `.ARM.exidx` | Discard unwind tables in that board's `script.ld` |

## Host-side gotcha

pymavlink up to and including **2.4.49** has a latent crash in
`mavutil.add_message()`. A message type first cached without its instance field
set leaves `_instances` as `None`; the next copy that carries an instance value
raises

```
TypeError: 'NoneType' object does not support item assignment
```

from inside `recv_match()`, killing the caller. It is intermittent because it
depends on connect-time resync ordering, and it takes down
`Tools/mavlink_shell.py` the same way, which blocks the `param set` workflow
above. This repo ships a guard in
[`host/pymavlink_compat.py`](../host/pymavlink_compat.py); call
`pymavlink_compat.apply()` before opening any connection. For `mavlink_shell.py`,
import it first or run the shell from a wrapper that does.

## Recap

Build time:

1. Pick the target: `make list_config_targets`.
2. `CONFIG_MAVLINK_DIALECT="military"` in the `.px4board` you build. Variants
   merge on top of `default.px4board`, so a one-line variant file is enough.
3. `military.xml` into `src/modules/mavlink/mavlink/message_definitions/v1.0/`,
   ideally in a way that survives a submodule reset.
4. i.MXRT board? Discard `.ARM.exidx`/`.extab` in its `script.ld`.
5. Confirm `build/<target>/mavlink/military/mavlink_msg_esad_*.h` exist.

Run time:

6. `MAV_<i>_CONFIG` to the port (101 = TELEM1, 102 = TELEM2), matching
   `SER_TEL<n>_BAUD`.
7. `MAV_<i>_FORWARD=1`. Off by default, needed in both directions. USB is
   automatic.
8. `MAV_<i>_FLOW_CTRL=0` on a 3-wire link.
9. `param save`, **reboot**.
10. Verify with `mavlink status` and the received-message counter test.
