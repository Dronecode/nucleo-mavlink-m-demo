# Wiring

This matters only for **topology B** (Mac ↔ PX4 ↔ Nucleo). Topology A uses the
onboard ST-Link USB and needs no external wiring — see the note at the bottom.

## The pin trap: use D8/D2, not D0/D1

> **On the Nucleo-64, the Arduino `D0`/`D1` pins are USART2 (PA3/PA2) — the
> ST-Link debug port — NOT USART1.** Wiring TELEM2 to D0/D1 is the single most
> common mistake and it will look like a dead link. The MAVLink link to PX4 is
> **USART1**, which is **D8 (PA9, TX)** and **D2 (PA10, RX)**.

The firmware makes this explicit:

```cpp
HardwareSerial FCLink(PA10, PA9);   // (RX, TX)  -> USART1, Arduino D2 / D8
#define DBG Serial                  //            -> USART2, ST-Link VCP (debug)
```

USART2 stays as a human-readable debug console at 115200 over the ST-Link VCP;
USART1 carries the MAVLink traffic to the Tropic at 57600.

## The link is crossed (TX ↔ RX)

Serial is point-to-point and crossed: each side's TX goes to the other side's RX.
Plus a common ground. Three wires total, no flow control.

| Nucleo pin | Arduino label | Function      | → | Tropic TELEM2 | Notes                    |
|------------|---------------|---------------|---|---------------|--------------------------|
| PA9        | D8            | USART1 TX     | → | TELEM2 **RX** | Nucleo transmit          |
| PA10       | D2            | USART1 RX     | ← | TELEM2 **TX** | Nucleo receive           |
| GND        | GND           | ground        | — | TELEM2 GND    | common reference, required |

So:

```
  Nucleo PA9  (D8, TX) ------------> Tropic TELEM2 RX
  Nucleo PA10 (D2, RX) <------------ Tropic TELEM2 TX
  Nucleo GND           <----------->  Tropic TELEM2 GND
```

Get the TX/RX crossing wrong and you get exactly the same symptom as the D0/D1
mistake: no payload heartbeat at the GCS. If nothing comes through, verify the
crossing before touching params.

### Flow control

The link is 3-wire. There are no CTS/RTS lines, so PX4's TELEM2 flow control
**must** be forced off (`MAV_1_FLOW_CTRL=0`, see
[SETUP.md](SETUP.md#5-configure-px4-telem2)). With flow control left on auto, PX4
may wait on a CTS that is never asserted and send nothing.

### Baud

Both ends are **57600 8N1**. On PX4 that is `SER_TEL2_BAUD 57600`; on the Nucleo
it is `FC_BAUD` in the sketch. They must match — the USB CDC baud to the Mac is
irrelevant (CDC ignores it), but the TELEM2 ↔ Nucleo baud is real UART and must
agree.

## Topology A (direct) — no wiring

For the direct Mac ↔ Nucleo test (`host/fake_pixhawk.py`), the MAVLink link runs
over the Nucleo's onboard ST-Link virtual COM port (USART2, PA2/PA3), which
appears as `/dev/cu.usbmodem1103` on the Mac. No jumper wires, no external
adapter.

Note the firmware as shipped puts the MAVLink link on USART1 for topology B. To
run topology A over the ST-Link VCP without any wiring, point the sketch's FC
link at `Serial` (USART2) instead of USART1, or attach a USB-serial adapter to
USART1 (D8/D2/GND) and open that adapter's port.
