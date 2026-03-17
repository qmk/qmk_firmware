// Copyright 2026 HorrorTroll <https://github.com/HorrorTroll>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

typedef union {
    uint32_t raw;
    struct {
        uint8_t rgb_mode :8;
    };
} user_config_t;

extern user_config_t user_config;

enum custom_keycodes {
    CLR_CYC = QK_KB_0,
    RGB_ESC
};

enum user_rgb_mode {
    RGB_MODE_ALL,
    RGB_MODE_NONE,
};
