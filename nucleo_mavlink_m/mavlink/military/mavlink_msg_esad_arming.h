#pragma once
// MESSAGE ESAD_ARMING PACKING

#define MAVLINK_MSG_ID_ESAD_ARMING 53008


typedef struct __mavlink_esad_arming_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch, microseconds UTC).*/
 uint32_t arming_challenge_hash; /*<  Challenge hash matching the active ESAD_STATE hash.*/
 uint8_t arming_request; /*<  Requested arming state change.*/
} mavlink_esad_arming_t;

#define MAVLINK_MSG_ID_ESAD_ARMING_LEN 13
#define MAVLINK_MSG_ID_ESAD_ARMING_MIN_LEN 13
#define MAVLINK_MSG_ID_53008_LEN 13
#define MAVLINK_MSG_ID_53008_MIN_LEN 13

#define MAVLINK_MSG_ID_ESAD_ARMING_CRC 169
#define MAVLINK_MSG_ID_53008_CRC 169



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ESAD_ARMING { \
    53008, \
    "ESAD_ARMING", \
    3, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_esad_arming_t, time_usec) }, \
         { "arming_challenge_hash", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_esad_arming_t, arming_challenge_hash) }, \
         { "arming_request", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_esad_arming_t, arming_request) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ESAD_ARMING { \
    "ESAD_ARMING", \
    3, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_esad_arming_t, time_usec) }, \
         { "arming_challenge_hash", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_esad_arming_t, arming_challenge_hash) }, \
         { "arming_request", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_esad_arming_t, arming_request) }, \
         } \
}
#endif

/**
 * @brief Pack a esad_arming message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param arming_challenge_hash  Challenge hash matching the active ESAD_STATE hash.
 * @param arming_request  Requested arming state change.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_esad_arming_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, uint32_t arming_challenge_hash, uint8_t arming_request)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ESAD_ARMING_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, arming_challenge_hash);
    _mav_put_uint8_t(buf, 12, arming_request);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ESAD_ARMING_LEN);
#else
    mavlink_esad_arming_t packet;
    packet.time_usec = time_usec;
    packet.arming_challenge_hash = arming_challenge_hash;
    packet.arming_request = arming_request;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ESAD_ARMING_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ESAD_ARMING;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ESAD_ARMING_MIN_LEN, MAVLINK_MSG_ID_ESAD_ARMING_LEN, MAVLINK_MSG_ID_ESAD_ARMING_CRC);
}

/**
 * @brief Pack a esad_arming message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param arming_challenge_hash  Challenge hash matching the active ESAD_STATE hash.
 * @param arming_request  Requested arming state change.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_esad_arming_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, uint32_t arming_challenge_hash, uint8_t arming_request)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ESAD_ARMING_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, arming_challenge_hash);
    _mav_put_uint8_t(buf, 12, arming_request);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ESAD_ARMING_LEN);
#else
    mavlink_esad_arming_t packet;
    packet.time_usec = time_usec;
    packet.arming_challenge_hash = arming_challenge_hash;
    packet.arming_request = arming_request;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ESAD_ARMING_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ESAD_ARMING;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ESAD_ARMING_MIN_LEN, MAVLINK_MSG_ID_ESAD_ARMING_LEN, MAVLINK_MSG_ID_ESAD_ARMING_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ESAD_ARMING_MIN_LEN, MAVLINK_MSG_ID_ESAD_ARMING_LEN);
#endif
}

/**
 * @brief Pack a esad_arming message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param arming_challenge_hash  Challenge hash matching the active ESAD_STATE hash.
 * @param arming_request  Requested arming state change.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_esad_arming_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,uint32_t arming_challenge_hash,uint8_t arming_request)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ESAD_ARMING_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, arming_challenge_hash);
    _mav_put_uint8_t(buf, 12, arming_request);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ESAD_ARMING_LEN);
#else
    mavlink_esad_arming_t packet;
    packet.time_usec = time_usec;
    packet.arming_challenge_hash = arming_challenge_hash;
    packet.arming_request = arming_request;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ESAD_ARMING_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ESAD_ARMING;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ESAD_ARMING_MIN_LEN, MAVLINK_MSG_ID_ESAD_ARMING_LEN, MAVLINK_MSG_ID_ESAD_ARMING_CRC);
}

/**
 * @brief Encode a esad_arming struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param esad_arming C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_esad_arming_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_esad_arming_t* esad_arming)
{
    return mavlink_msg_esad_arming_pack(system_id, component_id, msg, esad_arming->time_usec, esad_arming->arming_challenge_hash, esad_arming->arming_request);
}

/**
 * @brief Encode a esad_arming struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param esad_arming C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_esad_arming_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_esad_arming_t* esad_arming)
{
    return mavlink_msg_esad_arming_pack_chan(system_id, component_id, chan, msg, esad_arming->time_usec, esad_arming->arming_challenge_hash, esad_arming->arming_request);
}

/**
 * @brief Encode a esad_arming struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param esad_arming C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_esad_arming_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_esad_arming_t* esad_arming)
{
    return mavlink_msg_esad_arming_pack_status(system_id, component_id, _status, msg,  esad_arming->time_usec, esad_arming->arming_challenge_hash, esad_arming->arming_request);
}

/**
 * @brief Send a esad_arming message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param arming_challenge_hash  Challenge hash matching the active ESAD_STATE hash.
 * @param arming_request  Requested arming state change.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_esad_arming_send(mavlink_channel_t chan, uint64_t time_usec, uint32_t arming_challenge_hash, uint8_t arming_request)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ESAD_ARMING_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, arming_challenge_hash);
    _mav_put_uint8_t(buf, 12, arming_request);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ESAD_ARMING, buf, MAVLINK_MSG_ID_ESAD_ARMING_MIN_LEN, MAVLINK_MSG_ID_ESAD_ARMING_LEN, MAVLINK_MSG_ID_ESAD_ARMING_CRC);
#else
    mavlink_esad_arming_t packet;
    packet.time_usec = time_usec;
    packet.arming_challenge_hash = arming_challenge_hash;
    packet.arming_request = arming_request;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ESAD_ARMING, (const char *)&packet, MAVLINK_MSG_ID_ESAD_ARMING_MIN_LEN, MAVLINK_MSG_ID_ESAD_ARMING_LEN, MAVLINK_MSG_ID_ESAD_ARMING_CRC);
#endif
}

/**
 * @brief Send a esad_arming message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_esad_arming_send_struct(mavlink_channel_t chan, const mavlink_esad_arming_t* esad_arming)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_esad_arming_send(chan, esad_arming->time_usec, esad_arming->arming_challenge_hash, esad_arming->arming_request);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ESAD_ARMING, (const char *)esad_arming, MAVLINK_MSG_ID_ESAD_ARMING_MIN_LEN, MAVLINK_MSG_ID_ESAD_ARMING_LEN, MAVLINK_MSG_ID_ESAD_ARMING_CRC);
#endif
}

#if MAVLINK_MSG_ID_ESAD_ARMING_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_esad_arming_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, uint32_t arming_challenge_hash, uint8_t arming_request)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, arming_challenge_hash);
    _mav_put_uint8_t(buf, 12, arming_request);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ESAD_ARMING, buf, MAVLINK_MSG_ID_ESAD_ARMING_MIN_LEN, MAVLINK_MSG_ID_ESAD_ARMING_LEN, MAVLINK_MSG_ID_ESAD_ARMING_CRC);
#else
    mavlink_esad_arming_t *packet = (mavlink_esad_arming_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->arming_challenge_hash = arming_challenge_hash;
    packet->arming_request = arming_request;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ESAD_ARMING, (const char *)packet, MAVLINK_MSG_ID_ESAD_ARMING_MIN_LEN, MAVLINK_MSG_ID_ESAD_ARMING_LEN, MAVLINK_MSG_ID_ESAD_ARMING_CRC);
#endif
}
#endif

#endif

// MESSAGE ESAD_ARMING UNPACKING


/**
 * @brief Get field time_usec from esad_arming message
 *
 * @return [us] Timestamp (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_esad_arming_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field arming_challenge_hash from esad_arming message
 *
 * @return  Challenge hash matching the active ESAD_STATE hash.
 */
static inline uint32_t mavlink_msg_esad_arming_get_arming_challenge_hash(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field arming_request from esad_arming message
 *
 * @return  Requested arming state change.
 */
static inline uint8_t mavlink_msg_esad_arming_get_arming_request(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Decode a esad_arming message into a struct
 *
 * @param msg The message to decode
 * @param esad_arming C-struct to decode the message contents into
 */
static inline void mavlink_msg_esad_arming_decode(const mavlink_message_t* msg, mavlink_esad_arming_t* esad_arming)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    esad_arming->time_usec = mavlink_msg_esad_arming_get_time_usec(msg);
    esad_arming->arming_challenge_hash = mavlink_msg_esad_arming_get_arming_challenge_hash(msg);
    esad_arming->arming_request = mavlink_msg_esad_arming_get_arming_request(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ESAD_ARMING_LEN? msg->len : MAVLINK_MSG_ID_ESAD_ARMING_LEN;
        memset(esad_arming, 0, MAVLINK_MSG_ID_ESAD_ARMING_LEN);
    memcpy(esad_arming, _MAV_PAYLOAD(msg), len);
#endif
}
