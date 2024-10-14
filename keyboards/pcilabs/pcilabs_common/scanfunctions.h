/*
Copyright 2023 RephlexZero (@RephlexZero)
Copyright 2024 Mkass420 (@Mkass420)
SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "analogkeys.h"
#include <stdint.h>
#include "quantum.h"

void update_extremum(analog_key_t *key);

void register_key(matrix_row_t *current_row, uint8_t current_col);

void deregister_key(matrix_row_t *current_row, uint8_t current_col);

void get_sensor_offsets(void);

void matrix_read_cols_dynamic_actuation(matrix_row_t *current_row, uint8_t current_col, analog_key_t *key);

void matrix_read_cols_continuous_dynamic_actuation(matrix_row_t *current_row, uint8_t current_col, analog_key_t *key);

void matrix_read_cols_static_actuation(matrix_row_t *current_row, uint8_t current_col, analog_key_t *key);

void lut_init(void);

void key_init(void);

extern void (*matrix_read_mode_array[7])(matrix_row_t*, uint8_t, analog_key_t*); // 3 bits for modes
