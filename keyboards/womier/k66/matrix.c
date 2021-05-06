/*
 * Copyright 2011 Jun Wako <wakojun@gmail.com>
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
 *
 * Ported to QMK by Stephen Peery <https://github.com/smp4488/>
 */

#include <stdint.h>
#include <stdbool.h>
#include "ch.h"
#include "hal.h"

#include "wait.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"
#include "led_matrix.h"

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

// static const pin_t led_row_pins[MATRIX_ROWS][3] = LED_MATRIX_ROW_PINS;
// static const pin_t led_row_pins[LED_MATRIX_ROWS] = LED_MATRIX_ROW_PINS;

// LED COL pins are the same as the keyboard matrix

volatile matrix_row_t raw_matrix[MATRIX_ROWS]  = {0};  // raw values
matrix_row_t          last_matrix[MATRIX_ROWS] = {0};  // raw values
matrix_row_t          matrix[MATRIX_ROWS]      = {0};  // debounced values
volatile bool         matrix_changed           = false;

void matrix_scan_kb(void) {}

inline matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void) {}

// static void select_col(uint8_t col) {
//     setPinOutput(col_pins[col]);
//     writePinLow(col_pins[col]);
// }

static void unselect_col(uint8_t col) { setPinInputHigh(col_pins[col]); }

static void unselect_cols(void) {
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinInputHigh(col_pins[x]);
    }
}

static void init_pins(void) {
    unselect_cols();
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInputHigh(row_pins[x]);
    }
}

void matrix_init(void) {
    // initialize key pins
    init_pins();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    debounce_init(MATRIX_ROWS);

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    matrix_changed = false;

    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
            // Determine if the matrix changed state
            if ((last_matrix[row_index] != raw_matrix[row_index])) {
                matrix_changed         = true;
                last_matrix[row_index] = raw_matrix[row_index];
            }
        }
    }

    debounce(last_matrix, matrix, MATRIX_ROWS, matrix_changed);

    matrix_scan_quantum();

    return (uint8_t)matrix_changed;
}
