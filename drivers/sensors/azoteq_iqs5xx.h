// Copyright 2023 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "i2c_master.h"

typedef struct __attribute__((packed)) {
    uint8_t h : 8;
    uint8_t l : 8;
} azoteq_iqs5xx_report_rate_t;

typedef enum { ACTIVE, IDLE_TOUCH, IDLE, LP1, LP2 } azoteq_charging_modes_t;

typedef struct __attribute__((packed)) {
    bool    single_tap : 1;     // Single tap gesture status
    bool    press_and_hold : 1; // Press and hold gesture status
    bool    swipe_x_neg : 1;    // Swipe in negative X direction status
    bool    swipe_x_pos : 1;    // Swipe in positive X direction status
    bool    swipe_y_pos : 1;    // Swipe in positive Y direction status
    bool    swipe_y_neg : 1;    // Swipe in negative Y direction status
    uint8_t _unused : 2;        // unused
} azoteq_iqs5xx_gesture_events_0_t;

typedef struct __attribute__((packed)) {
    bool    two_finger_tap : 1; // Two finger tap gesture status
    bool    scroll : 1;         // Scroll status
    bool    zoom : 1;           // Zoom gesture status
    uint8_t _unused : 5;        // unused
} azoteq_iqs5xx_gesture_events_1_t;

typedef struct __attribute__((packed)) {
    azoteq_charging_modes_t charging_mode : 3;      // Indicates current mode
    bool                    ati_error : 1;          //
    bool                    reati_occurred : 1;     //
    bool                    alp_ati_error : 1;      //
    bool                    alp_reati_occurred : 1; //
    bool                    show_reset : 1;         //
} azoteq_iqs5xx_system_info_0_t;

typedef struct __attribute__((packed)) {
    bool    tp_movement : 1;      //
    bool    palm_detect : 1;      //  Palm detect status
    bool    too_many_fingers : 1; // Total finger status
    bool    rr_missed : 1;        // Report rate status
    bool    snap_toggle : 1;      // Change in any snap channel status
    bool    switch_state : 1;     // Status of input pin SW_IN
    uint8_t _unused : 2;          // unused
} azoteq_iqs5xx_system_info_1_t;

typedef struct __attribute__((packed)) {
    uint8_t h : 8;
    uint8_t l : 8;
} azoteq_iqs5xx_relative_xy_t;

typedef struct __attribute__((packed)) {
    uint8_t                          previous_cycle_time;
    azoteq_iqs5xx_gesture_events_0_t gesture_events_0;
    azoteq_iqs5xx_gesture_events_1_t gesture_events_1;
    azoteq_iqs5xx_system_info_0_t    system_info_0;
    azoteq_iqs5xx_system_info_1_t    system_info_1;
    uint8_t                          number_of_fingers;
    azoteq_iqs5xx_relative_xy_t      x;
    azoteq_iqs5xx_relative_xy_t      y;
} azoteq_iqs5xx_base_data_t;

_Static_assert(sizeof(azoteq_iqs5xx_base_data_t) == 10, "azoteq_iqs5xx_basic_report_t should be 10 bytes");

#define AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(h, l) ((h << 8) | l)

i2c_status_t azoteq_iqs5xx_get_base_data(azoteq_iqs5xx_base_data_t *base_data);

i2c_status_t azoteq_iqs5xx_end_session(void);

i2c_status_t azoteq_iqs5xx_get_report_rate(azoteq_iqs5xx_report_rate_t *report_rate, azoteq_charging_modes_t mode, bool END_SESSION);

i2c_status_t azoteq_iqs5xx_set_report_rate(uint16_t report_rate_ms, azoteq_charging_modes_t mode, bool END_SESSION);