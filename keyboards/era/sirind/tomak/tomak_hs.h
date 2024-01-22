// Copyright 2023 Hyojin Bak (@eerraa)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#ifdef VIA_ENABLE
// struct to save things
typedef struct {
    bool enable_ind:1;                   // | byte
    bool ind_override:1;                 // 1 byte
    HSV indicator_color;      // 3 bytes
    uint8_t ind_index_1;      // 1 byte
    uint8_t ind_index_2;      // 1 byte
    uint8_t ind_index_3;      // 1 byte
} indicator_settings_config;
// total 7 bytes

// via value id declaration
enum tomak_custom_value_id {
    id_custom_indicator_toggle = 0,
    id_custom_indicator_override,
    id_custom_indicator_brightness,
    id_custom_indicator_color
};

// function declaration
void indicator_config_set_value( uint8_t *data );
void indicator_config_get_value( uint8_t *data );
void indicator_config_save ( void );
void _set_color(HSV *color, uint8_t *data);
void _get_color(HSV *color, uint8_t *data);
#endif