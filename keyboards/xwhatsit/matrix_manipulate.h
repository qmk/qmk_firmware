/* Copyright 2020 Purdea Andrei
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MATRIX_MANIPULATE_H
#define MATRIX_MANIPULATE_H

#include "quantum.h"

// Contains stuff used to manipulate the matrix using the util.
// These are defined in matrix.c. This file is not called matrix.h to avoid conflict with qmk-native matrix.h

extern bool keyboard_scan_enabled;
void matrix_scan_raw(matrix_row_t current_matrix[]);
extern uint16_t cal_thresholds[CAPSENSE_CAL_BINS];
extern matrix_row_t assigned_to_threshold[CAPSENSE_CAL_BINS][MATRIX_CAPSENSE_ROWS];
uint16_t measure_middle_keymap_coords(uint8_t col, uint8_t row, uint8_t time, uint8_t reps);
void shift_data(uint32_t data, int data_idle, int shcp_idle, int stcp_idle);
void dac_write_threshold(uint16_t value);
uint8_t test_single(uint8_t col, uint16_t time, uint8_t *interference_ptr);

#endif

