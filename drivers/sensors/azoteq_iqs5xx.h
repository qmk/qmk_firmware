// Copyright 2023 Dasky (@daskygit)
// Copyright 2023 George Norton (@george-norton)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "i2c_master.h"
#include "pointing_device.h"
#include "util.h"

typedef enum {
    AZOTEQ_IQS5XX_UNKNOWN,
    AZOTEQ_IQS550 = 40,
    AZOTEQ_IQS525 = 52,
    AZOTEQ_IQS572 = 58,
} azoteq_iqs5xx_product_numbers_t;
typedef enum {
    AZOTEQ_IQS5XX_ACTIVE,
    AZOTEQ_IQS5XX_IDLE_TOUCH,
    AZOTEQ_IQS5XX_IDLE,
    AZOTEQ_IQS5XX_LP1,
    AZOTEQ_IQS5XX_LP2,
} azoteq_iqs5xx_charging_modes_t;

typedef struct {
    uint8_t h : 8;
    uint8_t l : 8;
} azoteq_iqs5xx_report_rate_t;

typedef struct PACKED {
    bool    single_tap : 1;     // Single tap gesture status
    bool    press_and_hold : 1; // Press and hold gesture status
    bool    swipe_x_neg : 1;    // Swipe in negative X direction status
    bool    swipe_x_pos : 1;    // Swipe in positive X direction status
    bool    swipe_y_pos : 1;    // Swipe in positive Y direction status
    bool    swipe_y_neg : 1;    // Swipe in negative Y direction status
    uint8_t _unused : 2;        // unused
} azoteq_iqs5xx_gesture_events_0_t;

typedef struct PACKED {
    bool    two_finger_tap : 1; // Two finger tap gesture status
    bool    scroll : 1;         // Scroll status
    bool    zoom : 1;           // Zoom gesture status
    uint8_t _unused : 5;        // unused
} azoteq_iqs5xx_gesture_events_1_t;

typedef struct PACKED {
    azoteq_iqs5xx_charging_modes_t charging_mode : 3;      // Indicates current mode
    bool                           ati_error : 1;          //
    bool                           reati_occurred : 1;     //
    bool                           alp_ati_error : 1;      //
    bool                           alp_reati_occurred : 1; //
    bool                           show_reset : 1;         //
} azoteq_iqs5xx_system_info_0_t;

typedef struct PACKED {
    bool    tp_movement : 1;      //
    bool    palm_detect : 1;      //  Palm detect status
    bool    too_many_fingers : 1; // Total finger status
    bool    rr_missed : 1;        // Report rate status
    bool    snap_toggle : 1;      // Change in any snap channel status
    bool    switch_state : 1;     // Status of input pin SW_IN
    uint8_t _unused : 2;          // unused
} azoteq_iqs5xx_system_info_1_t;

typedef struct {
    uint8_t h : 8;
    uint8_t l : 8;
} azoteq_iqs5xx_relative_xy_t;

typedef struct {
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

typedef struct {
    uint8_t                     number_of_fingers;
    azoteq_iqs5xx_relative_xy_t x;
    azoteq_iqs5xx_relative_xy_t y;
} azoteq_iqs5xx_report_data_t;

_Static_assert(sizeof(azoteq_iqs5xx_report_data_t) == 5, "azoteq_iqs5xx_report_data_t should be 5 bytes");

typedef struct PACKED {
    bool sw_input : 1;
    bool sw_input_select : 1;
    bool reati : 1;
    bool alp_reati : 1;
    bool sw_input_event : 1;
    bool wdt : 1;
    bool setup_complete : 1;
    bool manual_control : 1;
} azoteq_iqs5xx_system_config_0_t;

typedef struct PACKED {
    bool event_mode : 1;
    bool gesture_event : 1;
    bool tp_event : 1;
    bool reati_event : 1;
    bool alp_prox_event : 1;
    bool snap_event : 1;
    bool touch_event : 1;
    bool prox_event : 1;
} azoteq_iqs5xx_system_config_1_t;

typedef struct PACKED {
    bool    flip_x : 1;
    bool    flip_y : 1;
    bool    switch_xy_axis : 1;
    bool    palm_reject : 1;
    uint8_t _unused : 4;
} azoteq_iqs5xx_xy_config_0_t;

typedef struct PACKED {
    bool   suspend : 1;
    bool   reset : 1;
    int8_t _unused : 6;
} azoteq_iqs5xx_system_control_1_t;

typedef struct PACKED {
    bool   single_tap : 1;
    bool   press_and_hold : 1;
    bool   swipe_x_minus : 1;
    bool   swipe_x_plus : 1;
    bool   swipe_y_plus : 1;
    bool   swipe_y_minus : 1;
    int8_t _unused : 2;
} azoteq_iqs5xx_single_finger_gesture_enable_t;

typedef struct PACKED {
    bool   two_finger_tap : 1;
    bool   scroll : 1;
    bool   zoom : 1;
    int8_t _unused : 5;
} azoteq_iqs5xx_multi_finger_gesture_enable_t;

typedef struct PACKED {
    azoteq_iqs5xx_single_finger_gesture_enable_t single_finger_gestures;
    azoteq_iqs5xx_multi_finger_gesture_enable_t  multi_finger_gestures;
    uint16_t                                     tap_time;
    uint16_t                                     tap_distance;
    uint16_t                                     hold_time;
    uint16_t                                     swipe_initial_time;
    uint16_t                                     swipe_initial_distance;
    uint16_t                                     swipe_consecutive_time;
    uint16_t                                     swipe_consecutive_distance;
    int8_t                                       swipe_angle;
    uint16_t                                     scroll_initial_distance;
    int8_t                                       scroll_angle;
    uint16_t                                     zoom_initial_distance;
    uint16_t                                     zoom_consecutive_distance;
} azoteq_iqs5xx_gesture_config_t;

_Static_assert(sizeof(azoteq_iqs5xx_gesture_config_t) == 24, "azoteq_iqs5xx_gesture_config_t should be 24 bytes");

typedef struct {
    uint16_t x_resolution;
    uint16_t y_resolution;
} azoteq_iqs5xx_resolution_t;

#define AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(h, l) ((int16_t)(h << 8) | l)
#define AZOTEQ_IQS5XX_SWAP_H_L_BYTES(b) ((uint16_t)((b & 0xff) << 8) | (b >> 8))

#ifndef AZOTEQ_IQS5XX_REPORT_RATE
#    define AZOTEQ_IQS5XX_REPORT_RATE 10
#endif
#if !defined(POINTING_DEVICE_TASK_THROTTLE_MS) && !defined(POINTING_DEVICE_MOTION_PIN)
// Polling the Azoteq isn't recommended, ensuring we only poll after the report is ready stops any unexpected NACKs
#    define POINTING_DEVICE_TASK_THROTTLE_MS AZOTEQ_IQS5XX_REPORT_RATE + 1
#endif

const pointing_device_driver_t azoteq_iqs5xx_pointing_device_driver;

void           azoteq_iqs5xx_init(void);
i2c_status_t   azoteq_iqs5xx_wake(void);
report_mouse_t azoteq_iqs5xx_get_report(report_mouse_t mouse_report);
i2c_status_t   azoteq_iqs5xx_get_report_rate(azoteq_iqs5xx_report_rate_t *report_rate, azoteq_iqs5xx_charging_modes_t mode, bool end_session);
i2c_status_t   azoteq_iqs5xx_set_report_rate(uint16_t report_rate_ms, azoteq_iqs5xx_charging_modes_t mode, bool end_session);
i2c_status_t   azoteq_iqs5xx_set_event_mode(bool enabled, bool end_session);
i2c_status_t   azoteq_iqs5xx_set_reati(bool enabled, bool end_session);
i2c_status_t   azoteq_iqs5xx_set_gesture_config(bool end_session);
i2c_status_t   azoteq_iqs5xx_set_xy_config(bool flip_x, bool flip_y, bool switch_xy, bool palm_reject, bool end_session);
i2c_status_t   azoteq_iqs5xx_reset_suspend(bool reset, bool suspend, bool end_session);
i2c_status_t   azoteq_iqs5xx_get_base_data(azoteq_iqs5xx_base_data_t *base_data);
void           azoteq_iqs5xx_set_cpi(uint16_t cpi);
uint16_t       azoteq_iqs5xx_get_cpi(void);
uint16_t       azoteq_iqs5xx_get_product(void);
void           azoteq_iqs5xx_setup_resolution(void);
