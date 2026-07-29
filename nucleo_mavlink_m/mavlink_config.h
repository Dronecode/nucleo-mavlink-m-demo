// MAVLink build-time configuration for the STM32F103RB (128KB flash / 20KB RAM).
// Included before any mavlink header. Keeps the footprint small enough to fit.
#pragma once

// Two logical comm channels, because we serve MAVLink on both links at once:
//   MAVLINK_COMM_0 = USART1 (PA9/PA10, D8/D2)  -> flight controller TELEM
//   MAVLINK_COMM_1 = USART2 (ST-Link USB VCP)  -> host GCS
// This MUST be >= the number of links. Each channel owns its own
// mavlink_message_t/mavlink_status_t inside mavlink_helpers.h; feeding two
// interleaved byte streams through one channel corrupts both parsers.
#define MAVLINK_COMM_NUM_BUFFERS 2

// F103 is little-endian, so no byte swap; unaligned struct access is fine on
// Cortex-M3 for the packed accessors mavgen emits. Leaving both at defaults is
// safe, but pinning them avoids pulling the conversion-heavy slow path.
#define MAVLINK_ALIGNED_FIELDS 0

// We hand-feed bytes through mavlink_parse_char(), no CRC callback indirection.
#define MAVLINK_USE_MESSAGE_INFO 0
