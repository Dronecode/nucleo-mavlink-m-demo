/** @file
 *    @brief MAVLink comm protocol testsuite generated from military.xml
 *    @see https://mavlink.io/en/
 */
#pragma once
#ifndef MILITARY_TESTSUITE_H
#define MILITARY_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL
static void mavlink_test_common(uint8_t, uint8_t, mavlink_message_t *last_msg);
static void mavlink_test_military(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_common(system_id, component_id, last_msg);
    mavlink_test_military(system_id, component_id, last_msg);
}
#endif

#include "../common/testsuite.h"


static void mavlink_test_target_set_coord(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TARGET_SET_COORD >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_target_set_coord_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,93372036854776815ULL,963498712,963498920,963499128,269.0,297.0,"STUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNO"
    };
    mavlink_target_set_coord_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.time_start = packet_in.time_start;
        packet1.time_end = packet_in.time_end;
        packet1.target_set_id = packet_in.target_set_id;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.radius = packet_in.radius;
        
        mav_array_memcpy(packet1.target_set_name, packet_in.target_set_name, sizeof(char)*50);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TARGET_SET_COORD_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TARGET_SET_COORD_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_set_coord_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_target_set_coord_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_set_coord_pack(system_id, component_id, &msg , packet1.time_usec , packet1.target_set_id , packet1.target_set_name , packet1.lat , packet1.lon , packet1.alt , packet1.radius , packet1.time_start , packet1.time_end );
    mavlink_msg_target_set_coord_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_set_coord_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.target_set_id , packet1.target_set_name , packet1.lat , packet1.lon , packet1.alt , packet1.radius , packet1.time_start , packet1.time_end );
    mavlink_msg_target_set_coord_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_target_set_coord_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_set_coord_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.target_set_id , packet1.target_set_name , packet1.lat , packet1.lon , packet1.alt , packet1.radius , packet1.time_start , packet1.time_end );
    mavlink_msg_target_set_coord_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("TARGET_SET_COORD") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_TARGET_SET_COORD) != NULL);
#endif
}

static void mavlink_test_target_box_coord(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TARGET_BOX_COORD >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_target_box_coord_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,93372036854776815ULL,963498712,{ 963498920, 963498921, 963498922, 963498923 },{ 963499752, 963499753, 963499754, 963499755 },{ 437.0, 438.0, 439.0, 440.0 },"YZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTU"
    };
    mavlink_target_box_coord_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.time_start = packet_in.time_start;
        packet1.time_end = packet_in.time_end;
        packet1.target_set_id = packet_in.target_set_id;
        
        mav_array_memcpy(packet1.lat, packet_in.lat, sizeof(int32_t)*4);
        mav_array_memcpy(packet1.lon, packet_in.lon, sizeof(int32_t)*4);
        mav_array_memcpy(packet1.alt, packet_in.alt, sizeof(float)*4);
        mav_array_memcpy(packet1.target_set_name, packet_in.target_set_name, sizeof(char)*50);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TARGET_BOX_COORD_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TARGET_BOX_COORD_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_box_coord_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_target_box_coord_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_box_coord_pack(system_id, component_id, &msg , packet1.time_usec , packet1.target_set_id , packet1.target_set_name , packet1.lat , packet1.lon , packet1.alt , packet1.time_start , packet1.time_end );
    mavlink_msg_target_box_coord_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_box_coord_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.target_set_id , packet1.target_set_name , packet1.lat , packet1.lon , packet1.alt , packet1.time_start , packet1.time_end );
    mavlink_msg_target_box_coord_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_target_box_coord_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_box_coord_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.target_set_id , packet1.target_set_name , packet1.lat , packet1.lon , packet1.alt , packet1.time_start , packet1.time_end );
    mavlink_msg_target_box_coord_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("TARGET_BOX_COORD") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_TARGET_BOX_COORD) != NULL);
#endif
}

static void mavlink_test_target_coord(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TARGET_COORD >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_target_coord_t packet_in = {
        93372036854775807ULL,963497880,963498088,963498296,157.0,185.0,213.0,241.0,269.0,297.0,325.0,353.0,381.0,409.0,437.0,465.0,"QRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLM",231,42
    };
    mavlink_target_coord_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.target_set_id = packet_in.target_set_id;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.vx = packet_in.vx;
        packet1.vy = packet_in.vy;
        packet1.vz = packet_in.vz;
        packet1.cov_pos_x = packet_in.cov_pos_x;
        packet1.cov_pos_y = packet_in.cov_pos_y;
        packet1.cov_pos_z = packet_in.cov_pos_z;
        packet1.cov_vel_x = packet_in.cov_vel_x;
        packet1.cov_vel_y = packet_in.cov_vel_y;
        packet1.cov_vel_z = packet_in.cov_vel_z;
        packet1.cep_desired = packet_in.cep_desired;
        packet1.cep_max = packet_in.cep_max;
        packet1.target_class = packet_in.target_class;
        packet1.target_force = packet_in.target_force;
        
        mav_array_memcpy(packet1.target_name, packet_in.target_name, sizeof(char)*50);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TARGET_COORD_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TARGET_COORD_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_coord_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_target_coord_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_coord_pack(system_id, component_id, &msg , packet1.time_usec , packet1.target_set_id , packet1.target_name , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.cep_desired , packet1.cep_max , packet1.target_class , packet1.target_force );
    mavlink_msg_target_coord_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_coord_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.target_set_id , packet1.target_name , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.cep_desired , packet1.cep_max , packet1.target_class , packet1.target_force );
    mavlink_msg_target_coord_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_target_coord_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_coord_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.target_set_id , packet1.target_name , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.cep_desired , packet1.cep_max , packet1.target_class , packet1.target_force );
    mavlink_msg_target_coord_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("TARGET_COORD") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_TARGET_COORD) != NULL);
#endif
}

static void mavlink_test_fires(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_FIRES >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_fires_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,963498296,963498504,185.0,963498920,241.0,19107
    };
    mavlink_fires_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.time_impact_usec = packet_in.time_impact_usec;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.effector_id = packet_in.effector_id;
        packet1.cep_expected = packet_in.cep_expected;
        packet1.sequence = packet_in.sequence;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_FIRES_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_FIRES_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fires_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_fires_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fires_pack(system_id, component_id, &msg , packet1.time_usec , packet1.time_impact_usec , packet1.lat , packet1.lon , packet1.alt , packet1.effector_id , packet1.sequence , packet1.cep_expected );
    mavlink_msg_fires_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fires_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.time_impact_usec , packet1.lat , packet1.lon , packet1.alt , packet1.effector_id , packet1.sequence , packet1.cep_expected );
    mavlink_msg_fires_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_fires_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fires_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.time_impact_usec , packet1.lat , packet1.lon , packet1.alt , packet1.effector_id , packet1.sequence , packet1.cep_expected );
    mavlink_msg_fires_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("FIRES") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_FIRES) != NULL);
#endif
}

static void mavlink_test_splash_correction(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SPLASH_CORRECTION >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_splash_correction_t packet_in = {
        93372036854775807ULL,963497880,963498088,129.0,157.0,18483,211
    };
    mavlink_splash_correction_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.cep_expected = packet_in.cep_expected;
        packet1.sequence = packet_in.sequence;
        packet1.type_detected = packet_in.type_detected;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SPLASH_CORRECTION_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SPLASH_CORRECTION_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_splash_correction_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_splash_correction_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_splash_correction_pack(system_id, component_id, &msg , packet1.time_usec , packet1.lat , packet1.lon , packet1.alt , packet1.sequence , packet1.type_detected , packet1.cep_expected );
    mavlink_msg_splash_correction_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_splash_correction_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.lat , packet1.lon , packet1.alt , packet1.sequence , packet1.type_detected , packet1.cep_expected );
    mavlink_msg_splash_correction_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_splash_correction_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_splash_correction_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.lat , packet1.lon , packet1.alt , packet1.sequence , packet1.type_detected , packet1.cep_expected );
    mavlink_msg_splash_correction_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SPLASH_CORRECTION") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SPLASH_CORRECTION) != NULL);
#endif
}

static void mavlink_test_target_handover(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TARGET_HANDOVER >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_target_handover_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,93372036854776815ULL,963498712,963498920,241.0,269.0,297.0,325.0,353.0,381.0,409.0,437.0,465.0,493.0,963501208,549.0,"CDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXY","ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVW",{ 33, 34, 35, 36, 37, 38, 39, 40 },57,124,191
    };
    mavlink_target_handover_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.detected_first_usec = packet_in.detected_first_usec;
        packet1.valid_until_usec = packet_in.valid_until_usec;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.vx = packet_in.vx;
        packet1.vy = packet_in.vy;
        packet1.vz = packet_in.vz;
        packet1.cov_pos_x = packet_in.cov_pos_x;
        packet1.cov_pos_y = packet_in.cov_pos_y;
        packet1.cov_pos_z = packet_in.cov_pos_z;
        packet1.cov_vel_x = packet_in.cov_vel_x;
        packet1.cov_vel_y = packet_in.cov_vel_y;
        packet1.cov_vel_z = packet_in.cov_vel_z;
        packet1.target_set_id = packet_in.target_set_id;
        packet1.confidence_score = packet_in.confidence_score;
        packet1.target_class = packet_in.target_class;
        packet1.target_force = packet_in.target_force;
        packet1.match_media_type = packet_in.match_media_type;
        
        mav_array_memcpy(packet1.target_name, packet_in.target_name, sizeof(char)*50);
        mav_array_memcpy(packet1.match_media_url, packet_in.match_media_url, sizeof(char)*50);
        mav_array_memcpy(packet1.authorization, packet_in.authorization, sizeof(uint8_t)*8);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TARGET_HANDOVER_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TARGET_HANDOVER_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_handover_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_target_handover_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_handover_pack(system_id, component_id, &msg , packet1.time_usec , packet1.detected_first_usec , packet1.valid_until_usec , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.target_set_id , packet1.target_name , packet1.match_media_url , packet1.confidence_score , packet1.authorization , packet1.target_class , packet1.target_force , packet1.match_media_type );
    mavlink_msg_target_handover_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_handover_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.detected_first_usec , packet1.valid_until_usec , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.target_set_id , packet1.target_name , packet1.match_media_url , packet1.confidence_score , packet1.authorization , packet1.target_class , packet1.target_force , packet1.match_media_type );
    mavlink_msg_target_handover_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_target_handover_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_target_handover_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.detected_first_usec , packet1.valid_until_usec , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.target_set_id , packet1.target_name , packet1.match_media_url , packet1.confidence_score , packet1.authorization , packet1.target_class , packet1.target_force , packet1.match_media_type );
    mavlink_msg_target_handover_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("TARGET_HANDOVER") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_TARGET_HANDOVER) != NULL);
#endif
}

static void mavlink_test_battle_damage_assessment(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_battle_damage_assessment_t packet_in = {
        93372036854775807ULL,963497880,963498088,129.0,157.0,185.0,213.0,241.0,269.0,297.0,325.0,353.0,381.0,963500376,"IJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDE",{ 207, 208, 209, 210, 211, 212, 213, 214 },231,42,109,176
    };
    mavlink_battle_damage_assessment_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.vx = packet_in.vx;
        packet1.vy = packet_in.vy;
        packet1.vz = packet_in.vz;
        packet1.cov_pos_x = packet_in.cov_pos_x;
        packet1.cov_pos_y = packet_in.cov_pos_y;
        packet1.cov_pos_z = packet_in.cov_pos_z;
        packet1.cov_vel_x = packet_in.cov_vel_x;
        packet1.cov_vel_y = packet_in.cov_vel_y;
        packet1.cov_vel_z = packet_in.cov_vel_z;
        packet1.target_set_id = packet_in.target_set_id;
        packet1.destruction_pct = packet_in.destruction_pct;
        packet1.confidence_pct = packet_in.confidence_pct;
        packet1.target_class = packet_in.target_class;
        packet1.target_force = packet_in.target_force;
        
        mav_array_memcpy(packet1.target_name, packet_in.target_name, sizeof(char)*50);
        mav_array_memcpy(packet1.authorization, packet_in.authorization, sizeof(uint8_t)*8);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_battle_damage_assessment_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_battle_damage_assessment_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_battle_damage_assessment_pack(system_id, component_id, &msg , packet1.time_usec , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.target_set_id , packet1.target_name , packet1.authorization , packet1.destruction_pct , packet1.confidence_pct , packet1.target_class , packet1.target_force );
    mavlink_msg_battle_damage_assessment_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_battle_damage_assessment_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.target_set_id , packet1.target_name , packet1.authorization , packet1.destruction_pct , packet1.confidence_pct , packet1.target_class , packet1.target_force );
    mavlink_msg_battle_damage_assessment_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_battle_damage_assessment_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_battle_damage_assessment_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.target_set_id , packet1.target_name , packet1.authorization , packet1.destruction_pct , packet1.confidence_pct , packet1.target_class , packet1.target_force );
    mavlink_msg_battle_damage_assessment_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("BATTLE_DAMAGE_ASSESSMENT") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_BATTLE_DAMAGE_ASSESSMENT) != NULL);
#endif
}

static void mavlink_test_esad_state(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ESAD_STATE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_esad_state_t packet_in = {
        93372036854775807ULL,963497880,963498088,129.0,157.0,{ 77, 78, 79, 80, 81, 82, 83, 84 },101,168,235,46
    };
    mavlink_esad_state_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.arming_challenge_hash = packet_in.arming_challenge_hash;
        packet1.fault_flags = packet_in.fault_flags;
        packet1.input_1 = packet_in.input_1;
        packet1.input_2 = packet_in.input_2;
        packet1.arming_status = packet_in.arming_status;
        packet1.munition_status = packet_in.munition_status;
        packet1.ignition_status = packet_in.ignition_status;
        packet1.munition_type = packet_in.munition_type;
        
        mav_array_memcpy(packet1.sw_version_hash, packet_in.sw_version_hash, sizeof(uint8_t)*8);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ESAD_STATE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_esad_state_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_esad_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_esad_state_pack(system_id, component_id, &msg , packet1.time_usec , packet1.arming_challenge_hash , packet1.fault_flags , packet1.input_1 , packet1.input_2 , packet1.sw_version_hash , packet1.arming_status , packet1.munition_status , packet1.ignition_status , packet1.munition_type );
    mavlink_msg_esad_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_esad_state_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.arming_challenge_hash , packet1.fault_flags , packet1.input_1 , packet1.input_2 , packet1.sw_version_hash , packet1.arming_status , packet1.munition_status , packet1.ignition_status , packet1.munition_type );
    mavlink_msg_esad_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_esad_state_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_esad_state_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.arming_challenge_hash , packet1.fault_flags , packet1.input_1 , packet1.input_2 , packet1.sw_version_hash , packet1.arming_status , packet1.munition_status , packet1.ignition_status , packet1.munition_type );
    mavlink_msg_esad_state_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ESAD_STATE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ESAD_STATE) != NULL);
#endif
}

static void mavlink_test_esad_arming(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ESAD_ARMING >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_esad_arming_t packet_in = {
        93372036854775807ULL,963497880,41
    };
    mavlink_esad_arming_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.arming_challenge_hash = packet_in.arming_challenge_hash;
        packet1.arming_request = packet_in.arming_request;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ESAD_ARMING_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ESAD_ARMING_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_esad_arming_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_esad_arming_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_esad_arming_pack(system_id, component_id, &msg , packet1.time_usec , packet1.arming_challenge_hash , packet1.arming_request );
    mavlink_msg_esad_arming_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_esad_arming_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.arming_challenge_hash , packet1.arming_request );
    mavlink_msg_esad_arming_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_esad_arming_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_esad_arming_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.arming_challenge_hash , packet1.arming_request );
    mavlink_msg_esad_arming_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ESAD_ARMING") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ESAD_ARMING) != NULL);
#endif
}

static void mavlink_test_rws_pose(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_RWS_POSE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_rws_pose_t packet_in = {
        93372036854775807ULL,963497880,963498088,129.0,157.0,185.0,213.0,241.0,269.0,297.0,325.0,353.0,381.0,409.0,437.0,465.0,{ 493.0, 494.0, 495.0, 496.0 },605.0,633.0,661.0,37
    };
    mavlink_rws_pose_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.vx = packet_in.vx;
        packet1.vy = packet_in.vy;
        packet1.vz = packet_in.vz;
        packet1.cov_pos_x = packet_in.cov_pos_x;
        packet1.cov_pos_y = packet_in.cov_pos_y;
        packet1.cov_pos_z = packet_in.cov_pos_z;
        packet1.cov_vel_x = packet_in.cov_vel_x;
        packet1.cov_vel_y = packet_in.cov_vel_y;
        packet1.cov_vel_z = packet_in.cov_vel_z;
        packet1.offset_x = packet_in.offset_x;
        packet1.offset_y = packet_in.offset_y;
        packet1.offset_z = packet_in.offset_z;
        packet1.accuracy_roll = packet_in.accuracy_roll;
        packet1.accuracy_pitch = packet_in.accuracy_pitch;
        packet1.accuracy_yaw = packet_in.accuracy_yaw;
        packet1.coordinate_frame = packet_in.coordinate_frame;
        
        mav_array_memcpy(packet1.q, packet_in.q, sizeof(float)*4);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_RWS_POSE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_RWS_POSE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rws_pose_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_rws_pose_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rws_pose_pack(system_id, component_id, &msg , packet1.time_usec , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.offset_x , packet1.offset_y , packet1.offset_z , packet1.q , packet1.accuracy_roll , packet1.accuracy_pitch , packet1.accuracy_yaw , packet1.coordinate_frame );
    mavlink_msg_rws_pose_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rws_pose_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.offset_x , packet1.offset_y , packet1.offset_z , packet1.q , packet1.accuracy_roll , packet1.accuracy_pitch , packet1.accuracy_yaw , packet1.coordinate_frame );
    mavlink_msg_rws_pose_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_rws_pose_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rws_pose_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz , packet1.cov_pos_x , packet1.cov_pos_y , packet1.cov_pos_z , packet1.cov_vel_x , packet1.cov_vel_y , packet1.cov_vel_z , packet1.offset_x , packet1.offset_y , packet1.offset_z , packet1.q , packet1.accuracy_roll , packet1.accuracy_pitch , packet1.accuracy_yaw , packet1.coordinate_frame );
    mavlink_msg_rws_pose_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("RWS_POSE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_RWS_POSE) != NULL);
#endif
}

static void mavlink_test_rws_state(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_RWS_STATE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_rws_state_t packet_in = {
        93372036854775807ULL,"IJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDE",51,118
    };
    mavlink_rws_state_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.arming_state = packet_in.arming_state;
        packet1.weapon_type = packet_in.weapon_type;
        
        mav_array_memcpy(packet1.weapon_string, packet_in.weapon_string, sizeof(char)*50);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_RWS_STATE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_RWS_STATE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rws_state_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_rws_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rws_state_pack(system_id, component_id, &msg , packet1.time_usec , packet1.weapon_string , packet1.arming_state , packet1.weapon_type );
    mavlink_msg_rws_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rws_state_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time_usec , packet1.weapon_string , packet1.arming_state , packet1.weapon_type );
    mavlink_msg_rws_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_rws_state_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_rws_state_send(MAVLINK_COMM_1 , packet1.time_usec , packet1.weapon_string , packet1.arming_state , packet1.weapon_type );
    mavlink_msg_rws_state_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("RWS_STATE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_RWS_STATE) != NULL);
#endif
}

static void mavlink_test_military(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_target_set_coord(system_id, component_id, last_msg);
    mavlink_test_target_box_coord(system_id, component_id, last_msg);
    mavlink_test_target_coord(system_id, component_id, last_msg);
    mavlink_test_fires(system_id, component_id, last_msg);
    mavlink_test_splash_correction(system_id, component_id, last_msg);
    mavlink_test_target_handover(system_id, component_id, last_msg);
    mavlink_test_battle_damage_assessment(system_id, component_id, last_msg);
    mavlink_test_esad_state(system_id, component_id, last_msg);
    mavlink_test_esad_arming(system_id, component_id, last_msg);
    mavlink_test_rws_pose(system_id, component_id, last_msg);
    mavlink_test_rws_state(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MILITARY_TESTSUITE_H
