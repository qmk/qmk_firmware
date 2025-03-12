// Copyright 2025 esplo
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "quantum.h"

#ifdef OLED_ENABLE
typedef enum _DisplayMode { DisplayMode_Layer, DisplayMode_EEPROM, DisplayMode_MAX } DisplayMode;
#endif

#ifdef POINTING_DEVICE_ENABLE
#    include "drivers/modular_adns5050.h"
#    define NUM_MODULAR_ADNS5050 ARRAY_SIZE(((pin_t[])MODULAR_ADNS5050_SCLK_PINS))
#endif

typedef union {
    uint32_t raw;
    struct {
        // Angle adjustment per 2 degrees for trackballs.
        // 2^8*2=512 to represent 360 degrees
        uint16_t angle1 : 8;
        uint16_t angle2 : 8;
        // delay time in ms (* 100ms).
        // 2^6=64 to represent 0 ms - 4000 ms
        uint16_t mouse_layer_ms : 6;
        // pointer speed magnification
        // x0.5, x1 (default), x2, x4
        uint16_t pointer_speed_magnification : 2;
        // dummy
        uint16_t _ : 8;
    };
} user_config_t;

user_config_t user_config;
