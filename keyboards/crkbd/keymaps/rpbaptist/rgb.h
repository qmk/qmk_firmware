// Copyright 2023 Your Name (@rpbaptist)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "transactions.h"

typedef union {
    uint32_t raw;
    struct {
        bool     rgb_layer_indicator : 1;
        bool     rgb_matrix_idle_anim : 1;
        uint8_t  rgb_matrix_active_mode : 4;
        uint8_t  rgb_matrix_idle_mode : 4;
        uint8_t  rgb_matrix_active_speed : 2;
        uint8_t  rgb_matrix_idle_speed : 2;
        uint32_t rgb_matrix_idle_timeout : 18;
    };
} user_config_t;

extern user_config_t user_config;

_Static_assert(sizeof(user_config_t) == sizeof(uint32_t), "Userspace EECONFIG out of spec.");

const char *rgb_matrix_anim_oled_text(uint8_t mode);
void        rgb_matrix_set_gaming_defaults(void);
void        rgb_matrix_set_typing_defaults(void);
bool        process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t *record);
