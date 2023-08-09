/* Copyright 2023 RephlexZero (@RephlexZero)
SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

#include <stdint.h>
#include "quantum.h"

/* global struct to save keypress logic params */
typedef struct {
    uint8_t mode;
    uint8_t actuation_point;
    uint8_t press_sensitivity;
    uint8_t release_sensitivity;
    uint8_t press_hysteresis;
    uint8_t release_hysteresis;
} analog_config; /* 6 bytes */
_Static_assert(sizeof(analog_config) == VIA_EEPROM_CUSTOM_CONFIG_SIZE, "Size mismatch");
extern analog_config g_config;

typedef struct {
    /* For individual analog key data */
    uint8_t value;
    uint8_t extremum;
    int16_t offset;
    bool    continuous_dynamic_actuation;
} key_t;
extern key_t keys[MATRIX_ROWS][MATRIX_COLS];

void via_config_set_value(uint8_t *data);

void via_config_get_value(uint8_t *data);