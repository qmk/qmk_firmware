// Copyright 2023 Wilhelm Schuster
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

typedef union {
    uint32_t raw;
    struct {
        int8_t actuation_point_value;
    };
} keyboard_config_t;

void fc980c_matrix_init_kb(void);

void fc980c_eeconfig_update_kb(void);

void fc980c_eeconfig_init_kb(void);

void fc980c_keyboard_post_init_kb(void);
