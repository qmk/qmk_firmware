// Copyright 2025 esplo
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "quantum.h"

enum my_keycodes {
    // Next OLED Page
    NEXT_OLED_PAGE = QK_KB_0,
    // drag scroll feature for trackball
    DRAG_SCROLL,
    // kb_config modification
    AUTO_MOUSE_LAYER_P1,
    AUTO_MOUSE_LAYER_OFF_DELAY_P1,
    AUTO_MOUSE_LAYER_OFF_DELAY_M1,
    ANGLE_L_ADJUSTMENT_P1,
    ANGLE_L_ADJUSTMENT_M1,
    ANGLE_L_ADJUSTMENT_P30,
    ANGLE_L_ADJUSTMENT_M30,
    ANGLE_R_ADJUSTMENT_P1,
    ANGLE_R_ADJUSTMENT_M1,
    ANGLE_R_ADJUSTMENT_P30,
    ANGLE_R_ADJUSTMENT_M30,
    POINTER_SPEED_MAGNIFICATION_P1,
    POINTER_SPEED_MAGNIFICATION_M1,
    INVERT_DRAG_SCROLL_X_P1,
    INVERT_DRAG_SCROLL_Y_P1,
    DRAG_SCROLL_SPEED_MAGNIFICATION_P1,
    DRAG_SCROLL_SPEED_MAGNIFICATION_M1,
    TRACKBALL_LED_OFF_TIMEOUT_P1,
    TRACKBALL_LED_OFF_TIMEOUT_M1,
    ROTARY_ENCODER_1_RESOLUTION_P1,
    ROTARY_ENCODER_2_RESOLUTION_P1,
    ROTARY_ENCODER_3_RESOLUTION_P1,
    ROTARY_ENCODER_4_RESOLUTION_P1,
    ROTARY_ENCODER_5_RESOLUTION_P1,
    ROTARY_ENCODER_6_RESOLUTION_P1,
    ROTARY_ENCODER_7_RESOLUTION_P1,
    ROTARY_ENCODER_8_RESOLUTION_P1,
    ROTARY_ENCODER_9_RESOLUTION_P1,
    ROTARY_ENCODER_10_RESOLUTION_P1,
    ROTARY_ENCODER_11_RESOLUTION_P1,
    ROTARY_ENCODER_12_RESOLUTION_P1,
    ROTARY_ENCODER_13_RESOLUTION_P1,
    ROTARY_ENCODER_14_RESOLUTION_P1,
    ROTARY_ENCODER_15_RESOLUTION_P1,
    ROTARY_ENCODER_16_RESOLUTION_P1,
};

typedef union {
    uint8_t raw[EECONFIG_KB_DATA_SIZE]; // 1KB
    struct {
        // Auto mouse layer (true/false)
        // 2^1=2, default: 1, max: 1
        uint32_t mouse_layer_on : 1;
        // Auto mouse layer off delay time in ms (0-6300 ms)
        // 2^6=64, default: 13, max: 63
        uint32_t mouse_layer_off_delay_ms : 6;
        // Angle adjustment per 2 degrees for trackballs (left)
        // 2^9=512, default: 0, max: 359
        uint32_t angle_L : 9;
        // Angle adjustment per 2 degrees for trackballs (right)
        // 2^9=512, default: 0, max: 359
        uint32_t angle_R : 9;
        // Pointer speed magnification (0.25 * value)
        // 2^4=16, default: 4, max: 15
        uint32_t pointer_speed_magnification : 4;
        // Invert drag scroll X-axis direction (true/false)
        // 2^1=2, default: 0, max: 1
        uint32_t invert_drag_scroll_x : 1;
        // Invert drag scroll Y-axis direction (true/false)
        // 2^1=2, default: 0, max: 1
        uint32_t invert_drag_scroll_y : 1;
        // Drag scroll speed magnification (0.25 * value)
        // 2^4=16, default: 4, max: 15
        uint32_t drag_scroll_speed_magnification : 4;
        // Trackball LED off timeout (never, 5min, 10min, 15 min)
        // 2^2=4, default: 1, max: 3
        uint32_t trackball_led_off_timeout : 2;
        // Dummy value
        // 2^32=4294967296, default: 0, max: 0
        uint32_t _dummy_tb : 32;
        // Rotary encoder 1 resolution (restart needed to reflect)
        // 2^2=4, default: 2, max: 3
        uint32_t re_resolution_1 : 2;
        // Rotary encoder 2 resolution (restart needed to reflect)
        // 2^2=4, default: 2, max: 3
        uint32_t re_resolution_2 : 2;
        // Rotary encoder 3 resolution (restart needed to reflect)
        // 2^2=4, default: 2, max: 3
        uint32_t re_resolution_3 : 2;
        // Rotary encoder 4 resolution (restart needed to reflect)
        // 2^2=4, default: 2, max: 3
        uint32_t re_resolution_4 : 2;
        // Rotary encoder 5 resolution (restart needed to reflect)
        // 2^2=4, default: 2, max: 3
        uint32_t re_resolution_5 : 2;
        // Rotary encoder 6 resolution (restart needed to reflect)
        // 2^2=4, default: 2, max: 3
        uint32_t re_resolution_6 : 2;
        // Rotary encoder 7 resolution (restart needed to reflect)
        // 2^2=4, default: 2, max: 3
        uint32_t re_resolution_7 : 2;
        // Rotary encoder 8 resolution (restart needed to reflect)
        // 2^2=4, default: 2, max: 3
        uint32_t re_resolution_8 : 2;
        // Rotary encoder 9 resolution (restart needed to reflect)
        // 2^2=4, default: 2, max: 3
        uint32_t re_resolution_9 : 2;
        // Rotary encoder 10 resolution (restart needed to reflect)
        // 2^2=4, default: 2, max: 3
        uint32_t re_resolution_10 : 2;
        // Rotary encoder 11 resolution (restart needed to reflect)
        // 2^2=4, default: 2, max: 3
        uint32_t re_resolution_11 : 2;
        // Rotary encoder 12 resolution (restart needed to reflect)
        // 2^2=4, default: 2, max: 3
        uint32_t re_resolution_12 : 2;
        // Rotary encoder 13 resolution (restart needed to reflect)
        // 2^2=4, default: 2, max: 3
        uint32_t re_resolution_13 : 2;
        // Rotary encoder 14 resolution (restart needed to reflect)
        // 2^2=4, default: 2, max: 3
        uint32_t re_resolution_14 : 2;
        // Rotary encoder 15 resolution (restart needed to reflect)
        // 2^2=4, default: 2, max: 3
        uint32_t re_resolution_15 : 2;
        // Rotary encoder 16 resolution (restart needed to reflect)
        // 2^2=4, default: 2, max: 3
        uint32_t re_resolution_16 : 2;
    };
} kb_config_t;

extern kb_config_t kb_config;

void my_kb_config_init(kb_config_t* kb_config);
void debug_output_kb_config(kb_config_t* kb_config);
bool process_kb_config_modification(kb_config_t* kb_config, uint16_t keycode, keyrecord_t* record);
void oled_kb_config_output(kb_config_t* kb_config, uint8_t page);
