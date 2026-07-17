// MAVLink build-time configuration for the STM32F103RB (128KB flash / 20KB RAM).
// Included before any mavlink header. Keeps the footprint small enough to fit.
#pragma once

// One logical comm channel (USART2 <-> ST-Link VCP). Shrinks the per-channel
// parse/status buffers that mavlink_helpers.h allocates.
#define MAVLINK_COMM_NUM_BUFFERS 1

// F103 is little-endian, so no byte swap; unaligned struct access is fine on
// Cortex-M3 for the packed accessors mavgen emits. Leaving both at defaults is
// safe, but pinning them avoids pulling the conversion-heavy slow path.
#define MAVLINK_ALIGNED_FIELDS 0

// We hand-feed bytes through mavlink_parse_char(), no CRC callback indirection.
#define MAVLINK_USE_MESSAGE_INFO 0
