/*
Copyright 2023 RephlexZero (@RephlexZero)
Copyright 2024 Mkass420 (@Mkass420)
SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "config.h"

typedef enum __attribute__((__packed__)) { static_actuation, dynamic_actuation, continuous_dynamic_actuation, dynamic_keystroke } analog_mode_t;
typedef enum __attribute__((__packed__)) { latenpow, KS_20 } switch_type_t;
static const uint16_t switch_ranges[] = {[latenpow] = 400, [KS_20] = 410};

typedef union {
    struct {
        analog_mode_t mode : 3;             // up to 7 modes
        switch_type_t switch_type : 3;      // up to 7 switch types
        uint16_t      actuation_point : 10; // actually 9, but im afraid of padding issues
        uint8_t       press_sensitivity;
        uint8_t       release_sensitivity;
        uint8_t       press_hysteresis;
        uint8_t       release_hysteresis;
        // uint16_t      dks_actuation_point;
    };
    uint8_t config_raw[EECONFIG_KEY_DATA_SIZE];
} key_config_t;
_Static_assert(sizeof(key_config_t) == EECONFIG_KEY_DATA_SIZE, "Size mismatch");

typedef struct {
    uint16_t value;
    uint16_t extremum;
    int32_t  offset;
    bool     continuous_dynamic_actuation;
    uint16_t raw;
    uint16_t (*lut)[ADC_RESOLUTION_MAX];
    key_config_t; // gcc extension, use -fplan9-extensions
    struct {
        uint32_t sum;
        uint32_t buf[SMA_SAMPLE_SIZE];
        uint8_t  index;
    } SMA;
} analog_key_t;

extern analog_key_t keys[MATRIX_ROWS][MATRIX_COLS];

static const uint8_t eeconfig_magic_const = 0x69; // change with every eeconfig change

typedef union {
    struct __attribute__((__packed__)){
        uint8_t magic;
        key_config_t key_configs[MATRIX_ROWS][MATRIX_COLS];
    };
    uint8_t config_raw[EECONFIG_KB_DATA_SIZE];
} eeconfig_kb_t;
_Static_assert(sizeof(eeconfig_kb_t) == EECONFIG_KB_DATA_SIZE, "Size mismatch");

static const key_config_t key_config_default = {
    .mode                = static_actuation,
    .switch_type         = KS_20,
    .actuation_point     = 120,
    .press_sensitivity   = 32,
    .release_sensitivity = 32,
    .press_hysteresis    = 10,
    .release_hysteresis  = 10,
    //.dks_actuation_point = 0
};
