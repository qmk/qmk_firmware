// Copyright 2023 Kyle McCreery
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

typedef union {
    uint32_t raw;
    struct {
        uint8_t dpi_config;
        int16_t dt_term_config;
    };
} keyboard_config_t;

extern keyboard_config_t keyboard_config;
extern uint16_t dpi_array[];

enum keyboard_keycodes {
    DPI_UP = QK_KB,
    DPI_DN,
    DPI_FINE,
    TAP_UP,
    TAP_DN,
    TAP_ON,
    TAP_OFF,
    TAP_TOG
};
