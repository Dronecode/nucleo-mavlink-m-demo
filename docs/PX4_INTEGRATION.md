# Adding the mavlink-military dialect to PX4

How to build a PX4 firmware for **any board** that can parse and forward the
military dialect from
[Dronecode/mavlink-military](https://github.com/Dronecode/mavlink-military). This
is a general guide; it is not specific to this project or to any one board. The
NXP MR-Tropic is used only as a worked example.

None of this lives in the `nucleo-mavlink-m` repo — every change described here
is made in your **PX4-Autopilot** checkout.

## Why the board has to be rebuilt, not just configured

PX4 forwards any MAVLink message that **parses**. There is no per-message-ID
allowlist: if a frame's ID, length, and CRC-extra byte are known to the running
firmware, PX4 will route and forward it; if they are not, the frame fails the
CRC-extra check and is dropped silently.

The `ESAD_*` (and every other military) message ID is only known to a firmware
that had the military dialect **compiled in**. So configuring a param at runtime
is not enough — the dialect is generated at build time and baked into the binary.
A board that was not built with it will pass heartbeats (common dialect) while
dropping every military message, which looks like a forwarding bug but is not.

## How PX4 selects a dialect

The dialect is a per-board, build-time choice.

- `src/modules/mavlink/Kconfig` defines a string param `MAVLINK_DIALECT`,
  default `"common"`.
- A board opts into a different dialect by setting `CONFIG_MAVLINK_DIALECT` in
  its `.px4board` file. As of this writing, 12 boards already set a dialect this
  way, so it is the canonical, supported mechanism — you are not doing anything
  unusual.
- At configure time, `src/modules/mavlink/CMakeLists.txt` feeds mavgen the file
  `${MAVLINK_GIT_DIR}/message_definitions/v1.0/${CONFIG_MAVLINK_DIALECT}.xml`:

  ```cmake
  ${PYTHON_EXECUTABLE} ${MAVLINK_GIT_DIR}/pymavlink/tools/mavgen.py
      --lang C --wire-protocol 2.0
      --output ${MAVLINK_LIBRARY_DIR}
      ${MAVLINK_GIT_DIR}/message_definitions/v1.0/${CONFIG_MAVLINK_DIALECT}.xml
  ```

**The dialect name in `.px4board` must match the XML filename.** `military`
generates from `military.xml`. Get this wrong and CMake looks for a file that
does not exist and the build fails at generation.

### Step 1: set the dialect in the board's `.px4board`

Add one line to the board config you intend to build. For the mr-tropic example,
that is `boards/nxp/mr-tropic/default.px4board`:

```
CONFIG_MAVLINK_DIALECT="military"
```

Use whichever `.px4board` variant you build (`default.px4board`,
`mavlink-dev.px4board`, etc.). The line is the same for any board.

### Step 2: put military.xml where CMake looks for it

`military.xml` must exist in the mavlink submodule at:

```
src/modules/mavlink/mavlink/message_definitions/v1.0/military.xml
```

It `<include>`s `common.xml`, so a firmware built with the military dialect ends
up with **both** dialects — you do not lose the common messages. `military.xml`
is the full **MAVLink-M** spec — 26 messages in the 53000 block, not the earlier
preliminary set.

The repo also ships a `military_extensions.xml` template (a private-extension
dialect, dialect 3, that `<include>`s `military.xml` and adds example messages in
the 53900+ range). It is for vendor-private messages; the demo uses the standard
military dialect and does not need it.

There are two ways to get the file in place.

**(a) Quick / local — drop it into the submodule directory.** Copy or symlink
`military.xml` straight into
`src/modules/mavlink/mavlink/message_definitions/v1.0/`. Fast, good for a demo or
a bring-up session. The catch: it lives inside the mavlink submodule, so it is
**lost on any submodule reset** (`git submodule update`, a clean checkout, a
branch switch that touches the submodule pointer). Fine for throwaway work, not
for anything you need to reproduce later.

**(b) Durable — vendor it in the PX4 tree, or fork mavlink.** For anything beyond
a throwaway, keep `military.xml` under version control in your PX4 tree (for
example under a `boards/.../military/` or a dedicated vendored directory) and have
CMake **copy it into** the definitions directory before mavgen runs, so a
submodule reset can never wipe it. Alternatively, maintain a mavlink fork that
carries `military.xml` in `message_definitions/v1.0/` and point the submodule at
it. Either way the file survives resets and the build is reproducible. Prefer
this for any board you will build more than once.

### Step 3: build

```sh
make <board>_default          # e.g. make nxp_mr-tropic_default
```

### Step 4: verify the dialect was generated

The generated C headers land under `build/<board>/mavlink/<dialect>/`. Confirm the
military headers exist:

```sh
ls build/nxp_mr-tropic_default/mavlink/military/
# expect mavlink.h plus per-message headers, including:
#   mavlink_msg_esad_arming.h
#   mavlink_msg_esad_state.h
```

If that directory is missing or empty, the dialect did not generate — recheck the
`.px4board` line (name must match the XML) and that `military.xml` is actually in
the definitions directory (Step 2). Check
`build/<board>/mavgen_military.log` for the generator output.

## i.MXRT boards only: R_ARM_PREL31 link error

This section applies **only** if your board is an NXP i.MXRT board and the build
fails at link with a relocation error. STM32-class boards do not use the ITCM
placement scheme described here and will not hit this. If your build links fine,
skip this section.

The affected boards are the i.MXRT family that force functions into ITCM:
`nxp/mr-tropic`, `nxp/tropic-community`, and `px4/fmu-v6xrt`. You can tell a board
uses this scheme by the presence of
`boards/<vendor>/<board>/nuttx-config/scripts/itcm_functions_includes.ld`.

### Symptom

The link fails with:

```
relocation truncated to fit: R_ARM_PREL31 against ...
```

often naming `__udivmoddi4`, `__aeabi_uldivmod`, or `__aeabi_ldivmod`, or an
`.ARM.exidx` section. **Flash usage is not the problem** — on mr-tropic the image
was around 58% flash when this hit.

### Cause

These boards' linker scripts force selected hot functions into ITCM at address
`0x0` (via `nuttx-config/scripts/itcm_functions_includes.ld`), while the ARM
stack-unwind tables (`.ARM.exidx` / `.ARM.extab`) sit in flash at `0x60xxxxxx`.

The military messages carry `uint64_t time_usec` fields, which pull 64-bit
division helpers (`__udivmoddi4` / `__aeabi_uldivmod` / `__aeabi_ldivmod`) into
the link. Those helpers get placed into ITCM at `0x0`. Their `.ARM.exidx` unwind
entries remain in flash, and `R_ARM_PREL31` is a signed 31-bit PC-relative
relocation — it cannot span the ~1.6 GB gap between an unwind entry in flash and
the code it points at in ITCM. Hence the truncated relocation.

### Fix

PX4 builds with `-fno-exceptions`, so the ARM unwind tables are dead code.
Discard them, keeping empty `__exidx_start` / `__exidx_end` symbols for any
references. Edit `boards/<vendor>/<board>/nuttx-config/scripts/script.ld`.

**Before** (the tables are emitted into flash — this is what triggers the error):

```ld
    .ARM.extab :
    {
        *(.ARM.extab*)
    } > flash

    .ARM.exidx :
    {
        __exidx_start = ABSOLUTE(.);
        *(.ARM.exidx*)
        __exidx_end = ABSOLUTE(.);
    } > flash
```

**After** (tables discarded, symbols kept):

```ld
    /* PX4 builds with -fno-exceptions, so the ARM unwind tables are dead code.
     * Keeping them here also breaks the link: functions force-placed into ITCM
     * (0x0) via itcm_functions_includes.ld cannot be reached from their exidx
     * entries in flash (0x60xxxxxx) with a 31-bit R_ARM_PREL31 relocation.
     * Discard the tables; keep empty start/end symbols for any references. */
    __exidx_start = ABSOLUTE(.);
    __exidx_end = ABSOLUTE(.);

    /DISCARD/ :
    {
        *(.ARM.extab*)
        *(.ARM.exidx*)
    }
```

This is safe under `-fno-exceptions`. It only affects the i.MXRT/ITCM boards; do
not apply it to STM32 boards, where it is unnecessary and the section layout
differs.

## Recap

1. `CONFIG_MAVLINK_DIALECT="military"` in the board's `.px4board`.
2. `military.xml` in `src/modules/mavlink/mavlink/message_definitions/v1.0/`
   (quick: drop it in; durable: vendor + copy, or fork mavlink).
3. `make <board>_default`.
4. Confirm `build/<board>/mavlink/military/mavlink_msg_esad_*.h` exist.
5. i.MXRT board with an `R_ARM_PREL31` link error? Discard `.ARM.exidx`/`.extab`
   in that board's `script.ld`.
