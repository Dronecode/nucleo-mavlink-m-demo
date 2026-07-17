// Nucleo-F103RB MAVLink peripheral, MAVLink-M dialect.
//
// Stands in for a MAVLink component (an ESAD / munition device) so we can verify
// that PX4 can exchange common + MAVLink-M messages with real hardware. The
// dialect here is the full MAVLink-M spec (mavlink-military was replaced by it),
// so the ESAD messages carry the new IDs (ESAD_STATE 53030, ESAD_ARMING 53031)
// and the MAVLINK_M_ESAD_* enum names.
//
// Behaviour:
//   - Emits HEARTBEAT at 1 Hz  (common dialect, proves the TX path + link).
//   - On receiving ESAD_ARMING (MAVLink-M), replies with ESAD_STATE (MAVLink-M),
//     echoing the arming request back as the new arming_status.
//   - LD2 (green, PA5) solid on when armed, off when disarmed.
//
// Links:
//   - USART1 (PA9 TX / PA10 RX, Arduino D8 / D2): MAVLink to the PX4 flight
//     controller's TELEM2. Wired crossed, with a common GND. See FCLink below.
//   - USART2 (PA2/PA3): the ST-Link virtual COM port to the host, used here
//     only as a debug console (DBG below).

#include "mavlink_config.h"
#include "mavlink/military/mavlink.h"

// MAVLink link to the PX4 flight controller (Tropic TELEM2).
// This is a SEPARATE UART from the ST-Link/Mac console.
//   USART1: TX=PA9 (Arduino D8), RX=PA10 (Arduino D2).
// Wire it crossed to the Tropic TELEM2: Nucleo PA9(TX)->Tropic RX,
// Nucleo PA10(RX)->Tropic TX, plus a common GND.
HardwareSerial FCLink(PA10, PA9);   // (RX, TX)
static const uint32_t FC_BAUD = 57600;

// ST-Link virtual COM port (USART2, PA2/PA3) -> /dev/cu.usbmodem* on the Mac.
// Used only as a human-readable debug console now, not for MAVLink.
#define DBG Serial
static const uint32_t DBG_BAUD = 115200;

// This payload's identity on the bus. It is its OWN system, distinct from the
// autopilot (PX4 is usually system 1), so PX4 routes/forwards it as a separate
// node rather than mistaking it for one of its own components.
static const uint8_t SYS_ID  = 2;    // the ESAD payload, a separate system
static const uint8_t COMP_ID = 190;  // arming/payload component slot

// LD2 on the Nucleo-64 (PA5, green). Solid on when armed, off when disarmed.
static const uint8_t LED = LED_BUILTIN;

// Mirror of the last arming request we were told to apply.
static uint8_t g_arming_status = MAVLINK_M_ESAD_ARMING_DISARMED;

static void send_heartbeat()
{
	mavlink_message_t msg;
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];

	// A generic onboard controller. Not an autopilot: this is a peripheral.
	mavlink_msg_heartbeat_pack(
		SYS_ID, COMP_ID, &msg,
		MAV_TYPE_GENERIC,
		MAV_AUTOPILOT_INVALID,
		0,                      // base_mode
		0,                      // custom_mode
		MAV_STATE_ACTIVE);

	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	FCLink.write(buf, len);
}

static void send_esad_state()
{
	mavlink_message_t msg;
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
	const uint8_t sw_hash[8] = { 'n','u','c','1','0','3','r','b' };
	// No engagement association on this demo payload: all-zero track UID.
	const uint8_t track_uid[16] = { 0 };

	mavlink_msg_esad_state_pack(
		SYS_ID, COMP_ID, &msg,
		(uint64_t)micros(),               // time_usec (board-relative, no RTC)
		1,                                // esad_id (instance 1; 0 is invalid for ESAD_STATE)
		0,                                // arming_challenge_hash
		0,                                // fault_flags
		0.0f,                             // input_1
		0.0f,                             // input_2
		sw_hash,                          // sw_version_hash[8]
		g_arming_status,                  // arming_status  <- echoes the request
		MAVLINK_M_ESAD_MUNITION_PRESENT,  // munition_status
		MAVLINK_M_ESAD_IGNITION_OPEN,     // ignition_status
		0,                                // munition_type
		0,                                // store_id (single store)
		MAVLINK_M_ESAD_PIN_PRESENT,       // pin_state
		MAVLINK_M_ESAD_ARM_DELAY_UNKNOWN, // arm_delay_setting
		-1,                               // arm_delay_remaining_s (not counting)
		MAVLINK_M_ESAD_TRIG_DIST_UNKNOWN, // trigger_distance_mode
		track_uid);                       // track_uid[16] (all-zero, no track)

	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	FCLink.write(buf, len);
}

static void handle_message(const mavlink_message_t *msg)
{
	switch (msg->msgid) {
	case MAVLINK_MSG_ID_ESAD_ARMING: {
		mavlink_esad_arming_t in;
		mavlink_msg_esad_arming_decode(msg, &in);

		// Only act on requests addressed to us: this instance (esad_id == 1) or
		// the broadcast selector (esad_id == 0). The decode also yields store_id,
		// which we ignore on this single-store demo payload.
		if (in.esad_id != 0 && in.esad_id != 1) {
			break;
		}

		// arming_request: 0 = disarm (MAVLINK_M_ESAD_REQUEST_DISARM),
		// 1 = arm (MAVLINK_M_ESAD_REQUEST_ARM). Map straight to the state enum.
		g_arming_status = in.arming_request ? MAVLINK_M_ESAD_ARMING_ARMED
		                                    : MAVLINK_M_ESAD_ARMING_DISARMED;
		send_esad_state();
		// LD2 (green, PA5) tracks arming state: solid on when armed, off when
		// disarmed. Single-color GPIO LED, no colour control on this board.
		digitalWrite(LED, g_arming_status == MAVLINK_M_ESAD_ARMING_ARMED ? HIGH : LOW);
		DBG.print("ESAD_ARMING rx, request=");
		DBG.print(in.arming_request);
		DBG.println(" -> replied ESAD_STATE");
		break;
	}
	default:
		// Everything else (HEARTBEAT from the GCS, etc.) is parsed and ignored.
		break;
	}
}

void setup()
{
	pinMode(LED, OUTPUT);
	DBG.begin(DBG_BAUD);       // Mac console (ST-Link VCP)
	FCLink.begin(FC_BAUD);     // MAVLink to the Tropic (USART1)
	DBG.println("nucleo esad payload up: HB on USART1 @57600, sys=2 comp=190");
}

void loop()
{
	static uint32_t last_hb = 0;
	static mavlink_message_t msg;
	static mavlink_status_t status;

	// Drain the FC UART, feeding the incremental parser one byte at a time.
	while (FCLink.available() > 0) {
		uint8_t c = (uint8_t)FCLink.read();
		if (mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status)) {
			handle_message(&msg);
		}
	}

	uint32_t now = millis();
	if (now - last_hb >= 1000) {
		last_hb = now;
		send_heartbeat();
		// LED is not touched here: it reflects arming state, not the heartbeat.
	}
}
