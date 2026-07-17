#pragma once
// MESSAGE ESAD_STATE PACKING

#define MAVLINK_MSG_ID_ESAD_STATE 53007


typedef struct __mavlink_esad_state_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch, microseconds UTC).*/
 uint32_t arming_challenge_hash; /*<  Challenge hash for arming authentication.*/
 uint32_t fault_flags; /*<  Active fault flag bitmask.*/
 float input_1; /*<  Analog/digital input 1 (implementation-defined).*/
 float input_2; /*<  Analog/digital input 2 (implementation-defined).*/
 uint8_t sw_version_hash[8]; /*<  Software version as 8-byte short Git hash.*/
 uint8_t arming_status; /*<  Current arming state.*/
 uint8_t munition_status; /*<  Current munition state.*/
 uint8_t ignition_status; /*<  Current ignition circuit state.*/
 uint8_t munition_type; /*<  Munition type identifier (implementation-defined).*/
} mavlink_esad_state_t;

#define MAVLINK_MSG_ID_ESAD_STATE_LEN 36
#define MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN 36
#define MAVLINK_MSG_ID_53007_LEN 36
#define MAVLINK_MSG_ID_53007_MIN_LEN 36

#define MAVLINK_MSG_ID_ESAD_STATE_CRC 194
#define MAVLINK_MSG_ID_53007_CRC 194

#define MAVLINK_MSG_ESAD_STATE_FIELD_SW_VERSION_HASH_LEN 8

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ESAD_STATE { \
    53007, \
    "ESAD_STATE", \
    10, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_esad_state_t, time_usec) }, \
         { "arming_challenge_hash", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_esad_state_t, arming_challenge_hash) }, \
         { "fault_flags", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_esad_state_t, fault_flags) }, \
         { "input_1", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_esad_state_t, input_1) }, \
         { "input_2", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_esad_state_t, input_2) }, \
         { "sw_version_hash", NULL, MAVLINK_TYPE_UINT8_T, 8, 24, offsetof(mavlink_esad_state_t, sw_version_hash) }, \
         { "arming_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 32, offsetof(mavlink_esad_state_t, arming_status) }, \
         { "munition_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 33, offsetof(mavlink_esad_state_t, munition_status) }, \
         { "ignition_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 34, offsetof(mavlink_esad_state_t, ignition_status) }, \
         { "munition_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 35, offsetof(mavlink_esad_state_t, munition_type) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ESAD_STATE { \
    "ESAD_STATE", \
    10, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_esad_state_t, time_usec) }, \
         { "arming_challenge_hash", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_esad_state_t, arming_challenge_hash) }, \
         { "fault_flags", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_esad_state_t, fault_flags) }, \
         { "input_1", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_esad_state_t, input_1) }, \
         { "input_2", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_esad_state_t, input_2) }, \
         { "sw_version_hash", NULL, MAVLINK_TYPE_UINT8_T, 8, 24, offsetof(mavlink_esad_state_t, sw_version_hash) }, \
         { "arming_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 32, offsetof(mavlink_esad_state_t, arming_status) }, \
         { "munition_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 33, offsetof(mavlink_esad_state_t, munition_status) }, \
         { "ignition_status", NULL, MAVLINK_TYPE_UINT8_T, 0, 34, offsetof(mavlink_esad_state_t, ignition_status) }, \
         { "munition_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 35, offsetof(mavlink_esad_state_t, munition_type) }, \
         } \
}
#endif

/**
 * @brief Pack a esad_state message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param arming_challenge_hash  Challenge hash for arming authentication.
 * @param fault_flags  Active fault flag bitmask.
 * @param input_1  Analog/digital input 1 (implementation-defined).
 * @param input_2  Analog/digital input 2 (implementation-defined).
 * @param sw_version_hash  Software version as 8-byte short Git hash.
 * @param arming_status  Current arming state.
 * @param munition_status  Current munition state.
 * @param ignition_status  Current ignition circuit state.
 * @param munition_type  Munition type identifier (implementation-defined).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_esad_state_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, uint32_t arming_challenge_hash, uint32_t fault_flags, float input_1, float input_2, const uint8_t *sw_version_hash, uint8_t arming_status, uint8_t munition_status, uint8_t ignition_status, uint8_t munition_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ESAD_STATE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, arming_challenge_hash);
    _mav_put_uint32_t(buf, 12, fault_flags);
    _mav_put_float(buf, 16, input_1);
    _mav_put_float(buf, 20, input_2);
    _mav_put_uint8_t(buf, 32, arming_status);
    _mav_put_uint8_t(buf, 33, munition_status);
    _mav_put_uint8_t(buf, 34, ignition_status);
    _mav_put_uint8_t(buf, 35, munition_type);
    _mav_put_uint8_t_array(buf, 24, sw_version_hash, 8);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ESAD_STATE_LEN);
#else
    mavlink_esad_state_t packet;
    packet.time_usec = time_usec;
    packet.arming_challenge_hash = arming_challenge_hash;
    packet.fault_flags = fault_flags;
    packet.input_1 = input_1;
    packet.input_2 = input_2;
    packet.arming_status = arming_status;
    packet.munition_status = munition_status;
    packet.ignition_status = ignition_status;
    packet.munition_type = munition_type;
    mav_array_memcpy(packet.sw_version_hash, sw_version_hash, sizeof(uint8_t)*8);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ESAD_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ESAD_STATE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN, MAVLINK_MSG_ID_ESAD_STATE_LEN, MAVLINK_MSG_ID_ESAD_STATE_CRC);
}

/**
 * @brief Pack a esad_state message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param arming_challenge_hash  Challenge hash for arming authentication.
 * @param fault_flags  Active fault flag bitmask.
 * @param input_1  Analog/digital input 1 (implementation-defined).
 * @param input_2  Analog/digital input 2 (implementation-defined).
 * @param sw_version_hash  Software version as 8-byte short Git hash.
 * @param arming_status  Current arming state.
 * @param munition_status  Current munition state.
 * @param ignition_status  Current ignition circuit state.
 * @param munition_type  Munition type identifier (implementation-defined).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_esad_state_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, uint32_t arming_challenge_hash, uint32_t fault_flags, float input_1, float input_2, const uint8_t *sw_version_hash, uint8_t arming_status, uint8_t munition_status, uint8_t ignition_status, uint8_t munition_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ESAD_STATE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, arming_challenge_hash);
    _mav_put_uint32_t(buf, 12, fault_flags);
    _mav_put_float(buf, 16, input_1);
    _mav_put_float(buf, 20, input_2);
    _mav_put_uint8_t(buf, 32, arming_status);
    _mav_put_uint8_t(buf, 33, munition_status);
    _mav_put_uint8_t(buf, 34, ignition_status);
    _mav_put_uint8_t(buf, 35, munition_type);
    _mav_put_uint8_t_array(buf, 24, sw_version_hash, 8);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ESAD_STATE_LEN);
#else
    mavlink_esad_state_t packet;
    packet.time_usec = time_usec;
    packet.arming_challenge_hash = arming_challenge_hash;
    packet.fault_flags = fault_flags;
    packet.input_1 = input_1;
    packet.input_2 = input_2;
    packet.arming_status = arming_status;
    packet.munition_status = munition_status;
    packet.ignition_status = ignition_status;
    packet.munition_type = munition_type;
    mav_array_memcpy(packet.sw_version_hash, sw_version_hash, sizeof(uint8_t)*8);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ESAD_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ESAD_STATE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN, MAVLINK_MSG_ID_ESAD_STATE_LEN, MAVLINK_MSG_ID_ESAD_STATE_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN, MAVLINK_MSG_ID_ESAD_STATE_LEN);
#endif
}

/**
 * @brief Pack a esad_state message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param arming_challenge_hash  Challenge hash for arming authentication.
 * @param fault_flags  Active fault flag bitmask.
 * @param input_1  Analog/digital input 1 (implementation-defined).
 * @param input_2  Analog/digital input 2 (implementation-defined).
 * @param sw_version_hash  Software version as 8-byte short Git hash.
 * @param arming_status  Current arming state.
 * @param munition_status  Current munition state.
 * @param ignition_status  Current ignition circuit state.
 * @param munition_type  Munition type identifier (implementation-defined).
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_esad_state_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,uint32_t arming_challenge_hash,uint32_t fault_flags,float input_1,float input_2,const uint8_t *sw_version_hash,uint8_t arming_status,uint8_t munition_status,uint8_t ignition_status,uint8_t munition_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ESAD_STATE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, arming_challenge_hash);
    _mav_put_uint32_t(buf, 12, fault_flags);
    _mav_put_float(buf, 16, input_1);
    _mav_put_float(buf, 20, input_2);
    _mav_put_uint8_t(buf, 32, arming_status);
    _mav_put_uint8_t(buf, 33, munition_status);
    _mav_put_uint8_t(buf, 34, ignition_status);
    _mav_put_uint8_t(buf, 35, munition_type);
    _mav_put_uint8_t_array(buf, 24, sw_version_hash, 8);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ESAD_STATE_LEN);
#else
    mavlink_esad_state_t packet;
    packet.time_usec = time_usec;
    packet.arming_challenge_hash = arming_challenge_hash;
    packet.fault_flags = fault_flags;
    packet.input_1 = input_1;
    packet.input_2 = input_2;
    packet.arming_status = arming_status;
    packet.munition_status = munition_status;
    packet.ignition_status = ignition_status;
    packet.munition_type = munition_type;
    mav_array_memcpy(packet.sw_version_hash, sw_version_hash, sizeof(uint8_t)*8);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ESAD_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ESAD_STATE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN, MAVLINK_MSG_ID_ESAD_STATE_LEN, MAVLINK_MSG_ID_ESAD_STATE_CRC);
}

/**
 * @brief Encode a esad_state struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param esad_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_esad_state_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_esad_state_t* esad_state)
{
    return mavlink_msg_esad_state_pack(system_id, component_id, msg, esad_state->time_usec, esad_state->arming_challenge_hash, esad_state->fault_flags, esad_state->input_1, esad_state->input_2, esad_state->sw_version_hash, esad_state->arming_status, esad_state->munition_status, esad_state->ignition_status, esad_state->munition_type);
}

/**
 * @brief Encode a esad_state struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param esad_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_esad_state_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_esad_state_t* esad_state)
{
    return mavlink_msg_esad_state_pack_chan(system_id, component_id, chan, msg, esad_state->time_usec, esad_state->arming_challenge_hash, esad_state->fault_flags, esad_state->input_1, esad_state->input_2, esad_state->sw_version_hash, esad_state->arming_status, esad_state->munition_status, esad_state->ignition_status, esad_state->munition_type);
}

/**
 * @brief Encode a esad_state struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param esad_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_esad_state_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_esad_state_t* esad_state)
{
    return mavlink_msg_esad_state_pack_status(system_id, component_id, _status, msg,  esad_state->time_usec, esad_state->arming_challenge_hash, esad_state->fault_flags, esad_state->input_1, esad_state->input_2, esad_state->sw_version_hash, esad_state->arming_status, esad_state->munition_status, esad_state->ignition_status, esad_state->munition_type);
}

/**
 * @brief Send a esad_state message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param arming_challenge_hash  Challenge hash for arming authentication.
 * @param fault_flags  Active fault flag bitmask.
 * @param input_1  Analog/digital input 1 (implementation-defined).
 * @param input_2  Analog/digital input 2 (implementation-defined).
 * @param sw_version_hash  Software version as 8-byte short Git hash.
 * @param arming_status  Current arming state.
 * @param munition_status  Current munition state.
 * @param ignition_status  Current ignition circuit state.
 * @param munition_type  Munition type identifier (implementation-defined).
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_esad_state_send(mavlink_channel_t chan, uint64_t time_usec, uint32_t arming_challenge_hash, uint32_t fault_flags, float input_1, float input_2, const uint8_t *sw_version_hash, uint8_t arming_status, uint8_t munition_status, uint8_t ignition_status, uint8_t munition_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ESAD_STATE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, arming_challenge_hash);
    _mav_put_uint32_t(buf, 12, fault_flags);
    _mav_put_float(buf, 16, input_1);
    _mav_put_float(buf, 20, input_2);
    _mav_put_uint8_t(buf, 32, arming_status);
    _mav_put_uint8_t(buf, 33, munition_status);
    _mav_put_uint8_t(buf, 34, ignition_status);
    _mav_put_uint8_t(buf, 35, munition_type);
    _mav_put_uint8_t_array(buf, 24, sw_version_hash, 8);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ESAD_STATE, buf, MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN, MAVLINK_MSG_ID_ESAD_STATE_LEN, MAVLINK_MSG_ID_ESAD_STATE_CRC);
#else
    mavlink_esad_state_t packet;
    packet.time_usec = time_usec;
    packet.arming_challenge_hash = arming_challenge_hash;
    packet.fault_flags = fault_flags;
    packet.input_1 = input_1;
    packet.input_2 = input_2;
    packet.arming_status = arming_status;
    packet.munition_status = munition_status;
    packet.ignition_status = ignition_status;
    packet.munition_type = munition_type;
    mav_array_memcpy(packet.sw_version_hash, sw_version_hash, sizeof(uint8_t)*8);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ESAD_STATE, (const char *)&packet, MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN, MAVLINK_MSG_ID_ESAD_STATE_LEN, MAVLINK_MSG_ID_ESAD_STATE_CRC);
#endif
}

/**
 * @brief Send a esad_state message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_esad_state_send_struct(mavlink_channel_t chan, const mavlink_esad_state_t* esad_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_esad_state_send(chan, esad_state->time_usec, esad_state->arming_challenge_hash, esad_state->fault_flags, esad_state->input_1, esad_state->input_2, esad_state->sw_version_hash, esad_state->arming_status, esad_state->munition_status, esad_state->ignition_status, esad_state->munition_type);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ESAD_STATE, (const char *)esad_state, MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN, MAVLINK_MSG_ID_ESAD_STATE_LEN, MAVLINK_MSG_ID_ESAD_STATE_CRC);
#endif
}

#if MAVLINK_MSG_ID_ESAD_STATE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_esad_state_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, uint32_t arming_challenge_hash, uint32_t fault_flags, float input_1, float input_2, const uint8_t *sw_version_hash, uint8_t arming_status, uint8_t munition_status, uint8_t ignition_status, uint8_t munition_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, arming_challenge_hash);
    _mav_put_uint32_t(buf, 12, fault_flags);
    _mav_put_float(buf, 16, input_1);
    _mav_put_float(buf, 20, input_2);
    _mav_put_uint8_t(buf, 32, arming_status);
    _mav_put_uint8_t(buf, 33, munition_status);
    _mav_put_uint8_t(buf, 34, ignition_status);
    _mav_put_uint8_t(buf, 35, munition_type);
    _mav_put_uint8_t_array(buf, 24, sw_version_hash, 8);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ESAD_STATE, buf, MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN, MAVLINK_MSG_ID_ESAD_STATE_LEN, MAVLINK_MSG_ID_ESAD_STATE_CRC);
#else
    mavlink_esad_state_t *packet = (mavlink_esad_state_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->arming_challenge_hash = arming_challenge_hash;
    packet->fault_flags = fault_flags;
    packet->input_1 = input_1;
    packet->input_2 = input_2;
    packet->arming_status = arming_status;
    packet->munition_status = munition_status;
    packet->ignition_status = ignition_status;
    packet->munition_type = munition_type;
    mav_array_memcpy(packet->sw_version_hash, sw_version_hash, sizeof(uint8_t)*8);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ESAD_STATE, (const char *)packet, MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN, MAVLINK_MSG_ID_ESAD_STATE_LEN, MAVLINK_MSG_ID_ESAD_STATE_CRC);
#endif
}
#endif

#endif

// MESSAGE ESAD_STATE UNPACKING


/**
 * @brief Get field time_usec from esad_state message
 *
 * @return [us] Timestamp (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_esad_state_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field arming_challenge_hash from esad_state message
 *
 * @return  Challenge hash for arming authentication.
 */
static inline uint32_t mavlink_msg_esad_state_get_arming_challenge_hash(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field fault_flags from esad_state message
 *
 * @return  Active fault flag bitmask.
 */
static inline uint32_t mavlink_msg_esad_state_get_fault_flags(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  12);
}

/**
 * @brief Get field input_1 from esad_state message
 *
 * @return  Analog/digital input 1 (implementation-defined).
 */
static inline float mavlink_msg_esad_state_get_input_1(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field input_2 from esad_state message
 *
 * @return  Analog/digital input 2 (implementation-defined).
 */
static inline float mavlink_msg_esad_state_get_input_2(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field sw_version_hash from esad_state message
 *
 * @return  Software version as 8-byte short Git hash.
 */
static inline uint16_t mavlink_msg_esad_state_get_sw_version_hash(const mavlink_message_t* msg, uint8_t *sw_version_hash)
{
    return _MAV_RETURN_uint8_t_array(msg, sw_version_hash, 8,  24);
}

/**
 * @brief Get field arming_status from esad_state message
 *
 * @return  Current arming state.
 */
static inline uint8_t mavlink_msg_esad_state_get_arming_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  32);
}

/**
 * @brief Get field munition_status from esad_state message
 *
 * @return  Current munition state.
 */
static inline uint8_t mavlink_msg_esad_state_get_munition_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  33);
}

/**
 * @brief Get field ignition_status from esad_state message
 *
 * @return  Current ignition circuit state.
 */
static inline uint8_t mavlink_msg_esad_state_get_ignition_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  34);
}

/**
 * @brief Get field munition_type from esad_state message
 *
 * @return  Munition type identifier (implementation-defined).
 */
static inline uint8_t mavlink_msg_esad_state_get_munition_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  35);
}

/**
 * @brief Decode a esad_state message into a struct
 *
 * @param msg The message to decode
 * @param esad_state C-struct to decode the message contents into
 */
static inline void mavlink_msg_esad_state_decode(const mavlink_message_t* msg, mavlink_esad_state_t* esad_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    esad_state->time_usec = mavlink_msg_esad_state_get_time_usec(msg);
    esad_state->arming_challenge_hash = mavlink_msg_esad_state_get_arming_challenge_hash(msg);
    esad_state->fault_flags = mavlink_msg_esad_state_get_fault_flags(msg);
    esad_state->input_1 = mavlink_msg_esad_state_get_input_1(msg);
    esad_state->input_2 = mavlink_msg_esad_state_get_input_2(msg);
    mavlink_msg_esad_state_get_sw_version_hash(msg, esad_state->sw_version_hash);
    esad_state->arming_status = mavlink_msg_esad_state_get_arming_status(msg);
    esad_state->munition_status = mavlink_msg_esad_state_get_munition_status(msg);
    esad_state->ignition_status = mavlink_msg_esad_state_get_ignition_status(msg);
    esad_state->munition_type = mavlink_msg_esad_state_get_munition_type(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ESAD_STATE_LEN? msg->len : MAVLINK_MSG_ID_ESAD_STATE_LEN;
        memset(esad_state, 0, MAVLINK_MSG_ID_ESAD_STATE_LEN);
    memcpy(esad_state, _MAV_PAYLOAD(msg), len);
#endif
}
