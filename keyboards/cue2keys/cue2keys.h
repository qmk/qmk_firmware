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
        // angle adjustment per 2 degrees for trackballs
        // 2^8*2=512 to represent 360 degrees
        uint16_t angle1 : 8;
        uint16_t angle2 : 8;
        // auto mouse layer off delay time
        // 2^4=16 to represent 200+50x<value> ms (250-1000 ms)
        uint16_t mouse_layer_off_delay_ms : 4;
        // pointer speed magnification
        // 2^2=4 to represent x0.5, x1 (default), x2, x4
        uint16_t pointer_speed_magnification : 2;
        // dummy
        uint16_t _ : 8;
    };
} kb_config_t;

extern kb_config_t kb_config;
