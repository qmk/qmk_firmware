/* Copyright 2023 RephlexZero (@RephlexZero)
SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once
#include "analogkeys.h"
#include <stdint.h>
#include "quantum.h"
#include "lut.h"

void update_extremum(key_t *key);

void register_key(matrix_row_t *current_row, uint8_t current_col);

void deregister_key(matrix_row_t *current_row, uint8_t current_col);

void get_sensor_offsets(void);

void matrix_read_cols_dynamic_actuation(matrix_row_t *current_row, uint8_t current_col, key_t *key);

void matrix_read_cols_continuous_dynamic_actuation(matrix_row_t *current_row, uint8_t current_col, key_t *key);

void matrix_read_cols_static_actuation(matrix_row_t *current_row, uint8_t current_col, key_t *key);