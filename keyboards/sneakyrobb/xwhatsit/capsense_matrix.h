/* Copyright 2020 Purdea Andrei
 * Copyright 2021 Matthew J Wolf
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
#pragma once

#define nSHDN_BIT 12
#define MCP_DAC_GAIN_2X 0
#define MCP_DAC_GAIN_1X 1
#define nGA_BIT 13
#define BUF_BIT 14

#define TRACKING_TEST_TIME 4
// Key 1 is the always non-pressed key under the space bar to the right.
#define TRACKING_KEY_1_COL 6
#define TRACKING_KEY_1_ROW 4
// Key 2 is the always-pressed calibration pad to the far right-bottom of the keyboard. (both on F62 and F77)
#define TRACKING_KEY_2_COL 15
#define TRACKING_KEY_2_ROW 6
// Key 3 is the F key
#define TRACKING_KEY_3_COL 2
#define TRACKING_KEY_3_ROW 5
// Key 4 is the half of the split backspace that is unused if the user has a normal backspace.
#define TRACKING_KEY_4_COL 7
#define TRACKING_KEY_4_ROW 3
// Key 5 is hidden key next to the left shift, which is only used in ISO layouts.
#define TRACKING_KEY_5_COL 0
#define TRACKING_KEY_5_ROW 7

#define TRACKING_REPS 16

#ifndef NO_PRINT
#define NRTIMES 64
#define TESTATONCE 8
#define REPS_V2 15
#endif

#ifndef MATRIX_MANIPULATE_H
#define MATRIX_MANIPULATE_H

#include "quantum.h"

// Contains stuff used to manipulate the matrix using the util.
// These are defined in capsense_matrix.c. This file is not called matrix.h to avoid conflict with qmk-native matrix.h

extern bool keyboard_scan_enabled;
void matrix_scan_raw(matrix_row_t current_matrix[]);
extern uint16_t cal_thresholds[CAPSENSE_CAL_BINS];
extern matrix_row_t assigned_to_threshold[CAPSENSE_CAL_BINS][MATRIX_CAPSENSE_ROWS];
uint16_t measure_middle_keymap_coords(uint8_t col, uint8_t row, uint8_t time, uint8_t reps);
void shift_data(uint32_t data, int data_idle, int shcp_idle, int stcp_idle);
void dac_write_threshold(uint16_t value);
uint8_t test_single(uint8_t col, uint16_t time, uint8_t *interference_ptr);
void shift_select_col_no_strobe(uint8_t col);
void shift_select_nothing(void);

#endif
