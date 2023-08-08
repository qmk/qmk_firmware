// Copyright 2023 RephlexZero (@RephlexZero)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

void update_extremum(key_t *key);

void register_key(matrix_row_t *current_row, uint8_t current_col);

void deregister_key(matrix_row_t *current_row, uint8_t current_col);

void get_sensor_offsets(uint16_t rest_adc_value);

int min(int a, int b);

int max(int a, int b);

void matrix_read_cols_dynamic_actuation(matrix_row_t *current_row, uint8_t current_col, key_t *key);

void matrix_read_cols_continuous_dynamic_actuation(matrix_row_t *current_row, uint8_t current_col, key_t *key);

void matrix_read_cols_static_actuation(matrix_row_t *current_row, uint8_t current_col, key_t *key);