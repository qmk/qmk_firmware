// Copyright 2024 Hyojin Bak (@eerraa)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef VIA_ENABLE
#include "quantum.h"

// struct to save things
typedef struct {
    uint8_t backlight_bright;                 // 1 byte
    uint8_t backlight_effect;                 // 1 byte
    uint8_t breathing_period;                 // 1 byte
    uint8_t blink_speed;                      // 1 byte
} blink_settings_config;                      // total 4 bytes

// via value id declaration
enum n87s_custom_value_id {
    id_custom_backlight_brightness = 0,
    id_custom_backlight_effect,
    id_custom_breathing_period,
    id_custom_blink_speed
};

// function declaration
void indicator_config_set_value( uint8_t *data );
void indicator_config_get_value( uint8_t *data );
void indicator_config_save ( void );
#endif