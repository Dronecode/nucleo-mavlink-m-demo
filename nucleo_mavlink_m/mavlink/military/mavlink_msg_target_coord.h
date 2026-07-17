#pragma once
// MESSAGE TARGET_COORD PACKING

#define MAVLINK_MSG_ID_TARGET_COORD 53002


typedef struct __mavlink_target_coord_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX epoch, microseconds UTC).*/
 uint32_t target_set_id; /*<  Parent target set identifier.*/
 int32_t lat; /*< [degE7] Target latitude, WGS84.*/
 int32_t lon; /*< [degE7] Target longitude, WGS84.*/
 float alt; /*< [m] Target altitude, MSL.*/
 float vx; /*< [m/s] Velocity north component (NED).*/
 float vy; /*< [m/s] Velocity east component (NED).*/
 float vz; /*< [m/s] Velocity down component (NED).*/
 float cov_pos_x; /*< [m^2] Position covariance, north axis.*/
 float cov_pos_y; /*< [m^2] Position covariance, east axis.*/
 float cov_pos_z; /*< [m^2] Position covariance, down axis.*/
 float cov_vel_x; /*< [m^2/s^2] Velocity covariance, north axis.*/
 float cov_vel_y; /*< [m^2/s^2] Velocity covariance, east axis.*/
 float cov_vel_z; /*< [m^2/s^2] Velocity covariance, down axis.*/
 float cep_desired; /*< [m] Desired circular error probable.*/
 float cep_max; /*< [m] Maximum acceptable circular error probable.*/
 char target_name[50]; /*<  Human-readable target name (null-terminated).*/
 uint8_t target_class; /*<  Target classification.*/
 uint8_t target_force; /*<  Force affiliation.*/
} mavlink_target_coord_t;

#define MAVLINK_MSG_ID_TARGET_COORD_LEN 120
#define MAVLINK_MSG_ID_TARGET_COORD_MIN_LEN 120
#define MAVLINK_MSG_ID_53002_LEN 120
#define MAVLINK_MSG_ID_53002_MIN_LEN 120

#define MAVLINK_MSG_ID_TARGET_COORD_CRC 247
#define MAVLINK_MSG_ID_53002_CRC 247

#define MAVLINK_MSG_TARGET_COORD_FIELD_TARGET_NAME_LEN 50

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TARGET_COORD { \
    53002, \
    "TARGET_COORD", \
    19, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_target_coord_t, time_usec) }, \
         { "target_set_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_target_coord_t, target_set_id) }, \
         { "target_name", NULL, MAVLINK_TYPE_CHAR, 50, 68, offsetof(mavlink_target_coord_t, target_name) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_target_coord_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 16, offsetof(mavlink_target_coord_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_target_coord_t, alt) }, \
         { "vx", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_target_coord_t, vx) }, \
         { "vy", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_target_coord_t, vy) }, \
         { "vz", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_target_coord_t, vz) }, \
         { "cov_pos_x", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_target_coord_t, cov_pos_x) }, \
         { "cov_pos_y", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_target_coord_t, cov_pos_y) }, \
         { "cov_pos_z", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_target_coord_t, cov_pos_z) }, \
         { "cov_vel_x", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_target_coord_t, cov_vel_x) }, \
         { "cov_vel_y", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_target_coord_t, cov_vel_y) }, \
         { "cov_vel_z", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_target_coord_t, cov_vel_z) }, \
         { "cep_desired", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_target_coord_t, cep_desired) }, \
         { "cep_max", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_target_coord_t, cep_max) }, \
         { "target_class", NULL, MAVLINK_TYPE_UINT8_T, 0, 118, offsetof(mavlink_target_coord_t, target_class) }, \
         { "target_force", NULL, MAVLINK_TYPE_UINT8_T, 0, 119, offsetof(mavlink_target_coord_t, target_force) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TARGET_COORD { \
    "TARGET_COORD", \
    19, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_target_coord_t, time_usec) }, \
         { "target_set_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_target_coord_t, target_set_id) }, \
         { "target_name", NULL, MAVLINK_TYPE_CHAR, 50, 68, offsetof(mavlink_target_coord_t, target_name) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_target_coord_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 16, offsetof(mavlink_target_coord_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_target_coord_t, alt) }, \
         { "vx", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_target_coord_t, vx) }, \
         { "vy", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_target_coord_t, vy) }, \
         { "vz", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_target_coord_t, vz) }, \
         { "cov_pos_x", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_target_coord_t, cov_pos_x) }, \
         { "cov_pos_y", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_target_coord_t, cov_pos_y) }, \
         { "cov_pos_z", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_target_coord_t, cov_pos_z) }, \
         { "cov_vel_x", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_target_coord_t, cov_vel_x) }, \
         { "cov_vel_y", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_target_coord_t, cov_vel_y) }, \
         { "cov_vel_z", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_target_coord_t, cov_vel_z) }, \
         { "cep_desired", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_target_coord_t, cep_desired) }, \
         { "cep_max", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_target_coord_t, cep_max) }, \
         { "target_class", NULL, MAVLINK_TYPE_UINT8_T, 0, 118, offsetof(mavlink_target_coord_t, target_class) }, \
         { "target_force", NULL, MAVLINK_TYPE_UINT8_T, 0, 119, offsetof(mavlink_target_coord_t, target_force) }, \
         } \
}
#endif

/**
 * @brief Pack a target_coord message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param target_set_id  Parent target set identifier.
 * @param target_name  Human-readable target name (null-terminated).
 * @param lat [degE7] Target latitude, WGS84.
 * @param lon [degE7] Target longitude, WGS84.
 * @param alt [m] Target altitude, MSL.
 * @param vx [m/s] Velocity north component (NED).
 * @param vy [m/s] Velocity east component (NED).
 * @param vz [m/s] Velocity down component (NED).
 * @param cov_pos_x [m^2] Position covariance, north axis.
 * @param cov_pos_y [m^2] Position covariance, east axis.
 * @param cov_pos_z [m^2] Position covariance, down axis.
 * @param cov_vel_x [m^2/s^2] Velocity covariance, north axis.
 * @param cov_vel_y [m^2/s^2] Velocity covariance, east axis.
 * @param cov_vel_z [m^2/s^2] Velocity covariance, down axis.
 * @param cep_desired [m] Desired circular error probable.
 * @param cep_max [m] Maximum acceptable circular error probable.
 * @param target_class  Target classification.
 * @param target_force  Force affiliation.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_target_coord_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, uint32_t target_set_id, const char *target_name, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float cov_pos_x, float cov_pos_y, float cov_pos_z, float cov_vel_x, float cov_vel_y, float cov_vel_z, float cep_desired, float cep_max, uint8_t target_class, uint8_t target_force)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_COORD_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, target_set_id);
    _mav_put_int32_t(buf, 12, lat);
    _mav_put_int32_t(buf, 16, lon);
    _mav_put_float(buf, 20, alt);
    _mav_put_float(buf, 24, vx);
    _mav_put_float(buf, 28, vy);
    _mav_put_float(buf, 32, vz);
    _mav_put_float(buf, 36, cov_pos_x);
    _mav_put_float(buf, 40, cov_pos_y);
    _mav_put_float(buf, 44, cov_pos_z);
    _mav_put_float(buf, 48, cov_vel_x);
    _mav_put_float(buf, 52, cov_vel_y);
    _mav_put_float(buf, 56, cov_vel_z);
    _mav_put_float(buf, 60, cep_desired);
    _mav_put_float(buf, 64, cep_max);
    _mav_put_uint8_t(buf, 118, target_class);
    _mav_put_uint8_t(buf, 119, target_force);
    _mav_put_char_array(buf, 68, target_name, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TARGET_COORD_LEN);
#else
    mavlink_target_coord_t packet;
    packet.time_usec = time_usec;
    packet.target_set_id = target_set_id;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.vx = vx;
    packet.vy = vy;
    packet.vz = vz;
    packet.cov_pos_x = cov_pos_x;
    packet.cov_pos_y = cov_pos_y;
    packet.cov_pos_z = cov_pos_z;
    packet.cov_vel_x = cov_vel_x;
    packet.cov_vel_y = cov_vel_y;
    packet.cov_vel_z = cov_vel_z;
    packet.cep_desired = cep_desired;
    packet.cep_max = cep_max;
    packet.target_class = target_class;
    packet.target_force = target_force;
    mav_array_memcpy(packet.target_name, target_name, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TARGET_COORD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TARGET_COORD;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TARGET_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_COORD_LEN, MAVLINK_MSG_ID_TARGET_COORD_CRC);
}

/**
 * @brief Pack a target_coord message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param target_set_id  Parent target set identifier.
 * @param target_name  Human-readable target name (null-terminated).
 * @param lat [degE7] Target latitude, WGS84.
 * @param lon [degE7] Target longitude, WGS84.
 * @param alt [m] Target altitude, MSL.
 * @param vx [m/s] Velocity north component (NED).
 * @param vy [m/s] Velocity east component (NED).
 * @param vz [m/s] Velocity down component (NED).
 * @param cov_pos_x [m^2] Position covariance, north axis.
 * @param cov_pos_y [m^2] Position covariance, east axis.
 * @param cov_pos_z [m^2] Position covariance, down axis.
 * @param cov_vel_x [m^2/s^2] Velocity covariance, north axis.
 * @param cov_vel_y [m^2/s^2] Velocity covariance, east axis.
 * @param cov_vel_z [m^2/s^2] Velocity covariance, down axis.
 * @param cep_desired [m] Desired circular error probable.
 * @param cep_max [m] Maximum acceptable circular error probable.
 * @param target_class  Target classification.
 * @param target_force  Force affiliation.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_target_coord_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t time_usec, uint32_t target_set_id, const char *target_name, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float cov_pos_x, float cov_pos_y, float cov_pos_z, float cov_vel_x, float cov_vel_y, float cov_vel_z, float cep_desired, float cep_max, uint8_t target_class, uint8_t target_force)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_COORD_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, target_set_id);
    _mav_put_int32_t(buf, 12, lat);
    _mav_put_int32_t(buf, 16, lon);
    _mav_put_float(buf, 20, alt);
    _mav_put_float(buf, 24, vx);
    _mav_put_float(buf, 28, vy);
    _mav_put_float(buf, 32, vz);
    _mav_put_float(buf, 36, cov_pos_x);
    _mav_put_float(buf, 40, cov_pos_y);
    _mav_put_float(buf, 44, cov_pos_z);
    _mav_put_float(buf, 48, cov_vel_x);
    _mav_put_float(buf, 52, cov_vel_y);
    _mav_put_float(buf, 56, cov_vel_z);
    _mav_put_float(buf, 60, cep_desired);
    _mav_put_float(buf, 64, cep_max);
    _mav_put_uint8_t(buf, 118, target_class);
    _mav_put_uint8_t(buf, 119, target_force);
    _mav_put_char_array(buf, 68, target_name, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TARGET_COORD_LEN);
#else
    mavlink_target_coord_t packet;
    packet.time_usec = time_usec;
    packet.target_set_id = target_set_id;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.vx = vx;
    packet.vy = vy;
    packet.vz = vz;
    packet.cov_pos_x = cov_pos_x;
    packet.cov_pos_y = cov_pos_y;
    packet.cov_pos_z = cov_pos_z;
    packet.cov_vel_x = cov_vel_x;
    packet.cov_vel_y = cov_vel_y;
    packet.cov_vel_z = cov_vel_z;
    packet.cep_desired = cep_desired;
    packet.cep_max = cep_max;
    packet.target_class = target_class;
    packet.target_force = target_force;
    mav_array_memcpy(packet.target_name, target_name, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TARGET_COORD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TARGET_COORD;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TARGET_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_COORD_LEN, MAVLINK_MSG_ID_TARGET_COORD_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TARGET_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_COORD_LEN);
#endif
}

/**
 * @brief Pack a target_coord message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param target_set_id  Parent target set identifier.
 * @param target_name  Human-readable target name (null-terminated).
 * @param lat [degE7] Target latitude, WGS84.
 * @param lon [degE7] Target longitude, WGS84.
 * @param alt [m] Target altitude, MSL.
 * @param vx [m/s] Velocity north component (NED).
 * @param vy [m/s] Velocity east component (NED).
 * @param vz [m/s] Velocity down component (NED).
 * @param cov_pos_x [m^2] Position covariance, north axis.
 * @param cov_pos_y [m^2] Position covariance, east axis.
 * @param cov_pos_z [m^2] Position covariance, down axis.
 * @param cov_vel_x [m^2/s^2] Velocity covariance, north axis.
 * @param cov_vel_y [m^2/s^2] Velocity covariance, east axis.
 * @param cov_vel_z [m^2/s^2] Velocity covariance, down axis.
 * @param cep_desired [m] Desired circular error probable.
 * @param cep_max [m] Maximum acceptable circular error probable.
 * @param target_class  Target classification.
 * @param target_force  Force affiliation.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_target_coord_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,uint32_t target_set_id,const char *target_name,int32_t lat,int32_t lon,float alt,float vx,float vy,float vz,float cov_pos_x,float cov_pos_y,float cov_pos_z,float cov_vel_x,float cov_vel_y,float cov_vel_z,float cep_desired,float cep_max,uint8_t target_class,uint8_t target_force)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_COORD_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, target_set_id);
    _mav_put_int32_t(buf, 12, lat);
    _mav_put_int32_t(buf, 16, lon);
    _mav_put_float(buf, 20, alt);
    _mav_put_float(buf, 24, vx);
    _mav_put_float(buf, 28, vy);
    _mav_put_float(buf, 32, vz);
    _mav_put_float(buf, 36, cov_pos_x);
    _mav_put_float(buf, 40, cov_pos_y);
    _mav_put_float(buf, 44, cov_pos_z);
    _mav_put_float(buf, 48, cov_vel_x);
    _mav_put_float(buf, 52, cov_vel_y);
    _mav_put_float(buf, 56, cov_vel_z);
    _mav_put_float(buf, 60, cep_desired);
    _mav_put_float(buf, 64, cep_max);
    _mav_put_uint8_t(buf, 118, target_class);
    _mav_put_uint8_t(buf, 119, target_force);
    _mav_put_char_array(buf, 68, target_name, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TARGET_COORD_LEN);
#else
    mavlink_target_coord_t packet;
    packet.time_usec = time_usec;
    packet.target_set_id = target_set_id;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.vx = vx;
    packet.vy = vy;
    packet.vz = vz;
    packet.cov_pos_x = cov_pos_x;
    packet.cov_pos_y = cov_pos_y;
    packet.cov_pos_z = cov_pos_z;
    packet.cov_vel_x = cov_vel_x;
    packet.cov_vel_y = cov_vel_y;
    packet.cov_vel_z = cov_vel_z;
    packet.cep_desired = cep_desired;
    packet.cep_max = cep_max;
    packet.target_class = target_class;
    packet.target_force = target_force;
    mav_array_memcpy(packet.target_name, target_name, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TARGET_COORD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TARGET_COORD;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TARGET_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_COORD_LEN, MAVLINK_MSG_ID_TARGET_COORD_CRC);
}

/**
 * @brief Encode a target_coord struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param target_coord C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_target_coord_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_target_coord_t* target_coord)
{
    return mavlink_msg_target_coord_pack(system_id, component_id, msg, target_coord->time_usec, target_coord->target_set_id, target_coord->target_name, target_coord->lat, target_coord->lon, target_coord->alt, target_coord->vx, target_coord->vy, target_coord->vz, target_coord->cov_pos_x, target_coord->cov_pos_y, target_coord->cov_pos_z, target_coord->cov_vel_x, target_coord->cov_vel_y, target_coord->cov_vel_z, target_coord->cep_desired, target_coord->cep_max, target_coord->target_class, target_coord->target_force);
}

/**
 * @brief Encode a target_coord struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_coord C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_target_coord_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_target_coord_t* target_coord)
{
    return mavlink_msg_target_coord_pack_chan(system_id, component_id, chan, msg, target_coord->time_usec, target_coord->target_set_id, target_coord->target_name, target_coord->lat, target_coord->lon, target_coord->alt, target_coord->vx, target_coord->vy, target_coord->vz, target_coord->cov_pos_x, target_coord->cov_pos_y, target_coord->cov_pos_z, target_coord->cov_vel_x, target_coord->cov_vel_y, target_coord->cov_vel_z, target_coord->cep_desired, target_coord->cep_max, target_coord->target_class, target_coord->target_force);
}

/**
 * @brief Encode a target_coord struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param target_coord C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_target_coord_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_target_coord_t* target_coord)
{
    return mavlink_msg_target_coord_pack_status(system_id, component_id, _status, msg,  target_coord->time_usec, target_coord->target_set_id, target_coord->target_name, target_coord->lat, target_coord->lon, target_coord->alt, target_coord->vx, target_coord->vy, target_coord->vz, target_coord->cov_pos_x, target_coord->cov_pos_y, target_coord->cov_pos_z, target_coord->cov_vel_x, target_coord->cov_vel_y, target_coord->cov_vel_z, target_coord->cep_desired, target_coord->cep_max, target_coord->target_class, target_coord->target_force);
}

/**
 * @brief Send a target_coord message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec [us] Timestamp (UNIX epoch, microseconds UTC).
 * @param target_set_id  Parent target set identifier.
 * @param target_name  Human-readable target name (null-terminated).
 * @param lat [degE7] Target latitude, WGS84.
 * @param lon [degE7] Target longitude, WGS84.
 * @param alt [m] Target altitude, MSL.
 * @param vx [m/s] Velocity north component (NED).
 * @param vy [m/s] Velocity east component (NED).
 * @param vz [m/s] Velocity down component (NED).
 * @param cov_pos_x [m^2] Position covariance, north axis.
 * @param cov_pos_y [m^2] Position covariance, east axis.
 * @param cov_pos_z [m^2] Position covariance, down axis.
 * @param cov_vel_x [m^2/s^2] Velocity covariance, north axis.
 * @param cov_vel_y [m^2/s^2] Velocity covariance, east axis.
 * @param cov_vel_z [m^2/s^2] Velocity covariance, down axis.
 * @param cep_desired [m] Desired circular error probable.
 * @param cep_max [m] Maximum acceptable circular error probable.
 * @param target_class  Target classification.
 * @param target_force  Force affiliation.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_target_coord_send(mavlink_channel_t chan, uint64_t time_usec, uint32_t target_set_id, const char *target_name, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float cov_pos_x, float cov_pos_y, float cov_pos_z, float cov_vel_x, float cov_vel_y, float cov_vel_z, float cep_desired, float cep_max, uint8_t target_class, uint8_t target_force)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_COORD_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, target_set_id);
    _mav_put_int32_t(buf, 12, lat);
    _mav_put_int32_t(buf, 16, lon);
    _mav_put_float(buf, 20, alt);
    _mav_put_float(buf, 24, vx);
    _mav_put_float(buf, 28, vy);
    _mav_put_float(buf, 32, vz);
    _mav_put_float(buf, 36, cov_pos_x);
    _mav_put_float(buf, 40, cov_pos_y);
    _mav_put_float(buf, 44, cov_pos_z);
    _mav_put_float(buf, 48, cov_vel_x);
    _mav_put_float(buf, 52, cov_vel_y);
    _mav_put_float(buf, 56, cov_vel_z);
    _mav_put_float(buf, 60, cep_desired);
    _mav_put_float(buf, 64, cep_max);
    _mav_put_uint8_t(buf, 118, target_class);
    _mav_put_uint8_t(buf, 119, target_force);
    _mav_put_char_array(buf, 68, target_name, 50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_COORD, buf, MAVLINK_MSG_ID_TARGET_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_COORD_LEN, MAVLINK_MSG_ID_TARGET_COORD_CRC);
#else
    mavlink_target_coord_t packet;
    packet.time_usec = time_usec;
    packet.target_set_id = target_set_id;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.vx = vx;
    packet.vy = vy;
    packet.vz = vz;
    packet.cov_pos_x = cov_pos_x;
    packet.cov_pos_y = cov_pos_y;
    packet.cov_pos_z = cov_pos_z;
    packet.cov_vel_x = cov_vel_x;
    packet.cov_vel_y = cov_vel_y;
    packet.cov_vel_z = cov_vel_z;
    packet.cep_desired = cep_desired;
    packet.cep_max = cep_max;
    packet.target_class = target_class;
    packet.target_force = target_force;
    mav_array_memcpy(packet.target_name, target_name, sizeof(char)*50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_COORD, (const char *)&packet, MAVLINK_MSG_ID_TARGET_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_COORD_LEN, MAVLINK_MSG_ID_TARGET_COORD_CRC);
#endif
}

/**
 * @brief Send a target_coord message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_target_coord_send_struct(mavlink_channel_t chan, const mavlink_target_coord_t* target_coord)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_target_coord_send(chan, target_coord->time_usec, target_coord->target_set_id, target_coord->target_name, target_coord->lat, target_coord->lon, target_coord->alt, target_coord->vx, target_coord->vy, target_coord->vz, target_coord->cov_pos_x, target_coord->cov_pos_y, target_coord->cov_pos_z, target_coord->cov_vel_x, target_coord->cov_vel_y, target_coord->cov_vel_z, target_coord->cep_desired, target_coord->cep_max, target_coord->target_class, target_coord->target_force);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_COORD, (const char *)target_coord, MAVLINK_MSG_ID_TARGET_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_COORD_LEN, MAVLINK_MSG_ID_TARGET_COORD_CRC);
#endif
}

#if MAVLINK_MSG_ID_TARGET_COORD_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_target_coord_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, uint32_t target_set_id, const char *target_name, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz, float cov_pos_x, float cov_pos_y, float cov_pos_z, float cov_vel_x, float cov_vel_y, float cov_vel_z, float cep_desired, float cep_max, uint8_t target_class, uint8_t target_force)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, target_set_id);
    _mav_put_int32_t(buf, 12, lat);
    _mav_put_int32_t(buf, 16, lon);
    _mav_put_float(buf, 20, alt);
    _mav_put_float(buf, 24, vx);
    _mav_put_float(buf, 28, vy);
    _mav_put_float(buf, 32, vz);
    _mav_put_float(buf, 36, cov_pos_x);
    _mav_put_float(buf, 40, cov_pos_y);
    _mav_put_float(buf, 44, cov_pos_z);
    _mav_put_float(buf, 48, cov_vel_x);
    _mav_put_float(buf, 52, cov_vel_y);
    _mav_put_float(buf, 56, cov_vel_z);
    _mav_put_float(buf, 60, cep_desired);
    _mav_put_float(buf, 64, cep_max);
    _mav_put_uint8_t(buf, 118, target_class);
    _mav_put_uint8_t(buf, 119, target_force);
    _mav_put_char_array(buf, 68, target_name, 50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_COORD, buf, MAVLINK_MSG_ID_TARGET_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_COORD_LEN, MAVLINK_MSG_ID_TARGET_COORD_CRC);
#else
    mavlink_target_coord_t *packet = (mavlink_target_coord_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->target_set_id = target_set_id;
    packet->lat = lat;
    packet->lon = lon;
    packet->alt = alt;
    packet->vx = vx;
    packet->vy = vy;
    packet->vz = vz;
    packet->cov_pos_x = cov_pos_x;
    packet->cov_pos_y = cov_pos_y;
    packet->cov_pos_z = cov_pos_z;
    packet->cov_vel_x = cov_vel_x;
    packet->cov_vel_y = cov_vel_y;
    packet->cov_vel_z = cov_vel_z;
    packet->cep_desired = cep_desired;
    packet->cep_max = cep_max;
    packet->target_class = target_class;
    packet->target_force = target_force;
    mav_array_memcpy(packet->target_name, target_name, sizeof(char)*50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_COORD, (const char *)packet, MAVLINK_MSG_ID_TARGET_COORD_MIN_LEN, MAVLINK_MSG_ID_TARGET_COORD_LEN, MAVLINK_MSG_ID_TARGET_COORD_CRC);
#endif
}
#endif

#endif

// MESSAGE TARGET_COORD UNPACKING


/**
 * @brief Get field time_usec from target_coord message
 *
 * @return [us] Timestamp (UNIX epoch, microseconds UTC).
 */
static inline uint64_t mavlink_msg_target_coord_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field target_set_id from target_coord message
 *
 * @return  Parent target set identifier.
 */
static inline uint32_t mavlink_msg_target_coord_get_target_set_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field target_name from target_coord message
 *
 * @return  Human-readable target name (null-terminated).
 */
static inline uint16_t mavlink_msg_target_coord_get_target_name(const mavlink_message_t* msg, char *target_name)
{
    return _MAV_RETURN_char_array(msg, target_name, 50,  68);
}

/**
 * @brief Get field lat from target_coord message
 *
 * @return [degE7] Target latitude, WGS84.
 */
static inline int32_t mavlink_msg_target_coord_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  12);
}

/**
 * @brief Get field lon from target_coord message
 *
 * @return [degE7] Target longitude, WGS84.
 */
static inline int32_t mavlink_msg_target_coord_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  16);
}

/**
 * @brief Get field alt from target_coord message
 *
 * @return [m] Target altitude, MSL.
 */
static inline float mavlink_msg_target_coord_get_alt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field vx from target_coord message
 *
 * @return [m/s] Velocity north component (NED).
 */
static inline float mavlink_msg_target_coord_get_vx(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field vy from target_coord message
 *
 * @return [m/s] Velocity east component (NED).
 */
static inline float mavlink_msg_target_coord_get_vy(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field vz from target_coord message
 *
 * @return [m/s] Velocity down component (NED).
 */
static inline float mavlink_msg_target_coord_get_vz(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field cov_pos_x from target_coord message
 *
 * @return [m^2] Position covariance, north axis.
 */
static inline float mavlink_msg_target_coord_get_cov_pos_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field cov_pos_y from target_coord message
 *
 * @return [m^2] Position covariance, east axis.
 */
static inline float mavlink_msg_target_coord_get_cov_pos_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field cov_pos_z from target_coord message
 *
 * @return [m^2] Position covariance, down axis.
 */
static inline float mavlink_msg_target_coord_get_cov_pos_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field cov_vel_x from target_coord message
 *
 * @return [m^2/s^2] Velocity covariance, north axis.
 */
static inline float mavlink_msg_target_coord_get_cov_vel_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field cov_vel_y from target_coord message
 *
 * @return [m^2/s^2] Velocity covariance, east axis.
 */
static inline float mavlink_msg_target_coord_get_cov_vel_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  52);
}

/**
 * @brief Get field cov_vel_z from target_coord message
 *
 * @return [m^2/s^2] Velocity covariance, down axis.
 */
static inline float mavlink_msg_target_coord_get_cov_vel_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  56);
}

/**
 * @brief Get field cep_desired from target_coord message
 *
 * @return [m] Desired circular error probable.
 */
static inline float mavlink_msg_target_coord_get_cep_desired(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  60);
}

/**
 * @brief Get field cep_max from target_coord message
 *
 * @return [m] Maximum acceptable circular error probable.
 */
static inline float mavlink_msg_target_coord_get_cep_max(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  64);
}

/**
 * @brief Get field target_class from target_coord message
 *
 * @return  Target classification.
 */
static inline uint8_t mavlink_msg_target_coord_get_target_class(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  118);
}

/**
 * @brief Get field target_force from target_coord message
 *
 * @return  Force affiliation.
 */
static inline uint8_t mavlink_msg_target_coord_get_target_force(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  119);
}

/**
 * @brief Decode a target_coord message into a struct
 *
 * @param msg The message to decode
 * @param target_coord C-struct to decode the message contents into
 */
static inline void mavlink_msg_target_coord_decode(const mavlink_message_t* msg, mavlink_target_coord_t* target_coord)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    target_coord->time_usec = mavlink_msg_target_coord_get_time_usec(msg);
    target_coord->target_set_id = mavlink_msg_target_coord_get_target_set_id(msg);
    target_coord->lat = mavlink_msg_target_coord_get_lat(msg);
    target_coord->lon = mavlink_msg_target_coord_get_lon(msg);
    target_coord->alt = mavlink_msg_target_coord_get_alt(msg);
    target_coord->vx = mavlink_msg_target_coord_get_vx(msg);
    target_coord->vy = mavlink_msg_target_coord_get_vy(msg);
    target_coord->vz = mavlink_msg_target_coord_get_vz(msg);
    target_coord->cov_pos_x = mavlink_msg_target_coord_get_cov_pos_x(msg);
    target_coord->cov_pos_y = mavlink_msg_target_coord_get_cov_pos_y(msg);
    target_coord->cov_pos_z = mavlink_msg_target_coord_get_cov_pos_z(msg);
    target_coord->cov_vel_x = mavlink_msg_target_coord_get_cov_vel_x(msg);
    target_coord->cov_vel_y = mavlink_msg_target_coord_get_cov_vel_y(msg);
    target_coord->cov_vel_z = mavlink_msg_target_coord_get_cov_vel_z(msg);
    target_coord->cep_desired = mavlink_msg_target_coord_get_cep_desired(msg);
    target_coord->cep_max = mavlink_msg_target_coord_get_cep_max(msg);
    mavlink_msg_target_coord_get_target_name(msg, target_coord->target_name);
    target_coord->target_class = mavlink_msg_target_coord_get_target_class(msg);
    target_coord->target_force = mavlink_msg_target_coord_get_target_force(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TARGET_COORD_LEN? msg->len : MAVLINK_MSG_ID_TARGET_COORD_LEN;
        memset(target_coord, 0, MAVLINK_MSG_ID_TARGET_COORD_LEN);
    memcpy(target_coord, _MAV_PAYLOAD(msg), len);
#endif
}
