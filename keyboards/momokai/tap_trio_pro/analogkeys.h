/* Copyright 2023 RephlexZero (@RephlexZero)
             2024 peepeetee (@peepeetee)
             2024 minisbett (@minisbett)
             2025 Jenna Fligor (@Ex-32)
SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#include <stdint.h>
#include <stdbool.h>

enum analog_key_modes {
    dynamic_actuation = 0,
    continuous_dynamic_actuation = 1,
    static_actuation = 2,
    flashing = 3,
};

/* global struct to save keypress logic params */
typedef struct {
    uint8_t mode;
    uint8_t actuation_point;
    uint8_t press_sensitivity;
    uint8_t release_sensitivity;
    uint8_t press_hysteresis;
    uint8_t release_hysteresis;
} analog_config; /* 6 bytes */
//size defined in config.h
_Static_assert(sizeof(analog_config) == EECONFIG_KB_DATA_SIZE, "Size mismatch");
extern analog_config g_config;

typedef struct {
    /* For individual analog key data */
    uint16_t value;
    uint16_t extremum;
    int16_t offset;
    bool    is_analog;
    bool    continuous_dynamic_actuation;
} hybrid_key_t;
extern hybrid_key_t keys[MATRIX_ROWS][MATRIX_COLS];
