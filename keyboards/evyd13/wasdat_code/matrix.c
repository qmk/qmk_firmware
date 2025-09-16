/*
Copyright 2012-2018 Jun Wako, Jack Humbert, Yiancar

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "matrix.h"
#include "sn74x138.h"

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

/* Columns 6 and 9-15 use a 74HC138 3-to-8 demultiplexer.
 * D4 is the enable pin, must be set high to use it.
 *
 * 0:  F7
 * 1:  F5
 * 2:  F6
 * 3:  F1
 * 4:  F4
 * 5:  F0
 *
 *     A2   A1   A0
 *     D0   D1   D2
 * 6:   1    1    1
 *
 * 7:  D5
 * 8:  D3
 *
 * 9:   1    1    0
 * 10:  1    0    1
 * 11:  1    0    0
 * 12:  0    1    1
 * 13:  0    1    0
 * 14:  0    0    1
 * 15:  0    0    0
 */
static void select_col(uint8_t col) {
    if (col_pins[col] != NO_PIN) {
        gpio_write_pin_low(col_pins[col]);
    } else {
        sn74x138_set_addr((col == 6) ? 7 : 15 - col);
        sn74x138_set_enabled(true);
    }
}

static void unselect_col(uint8_t col) {
    if (col_pins[col] != NO_PIN) {
        gpio_set_pin_output(col_pins[col]);
        gpio_write_pin_high(col_pins[col]);
    } else {
        sn74x138_set_enabled(false);
    }
}

static void unselect_cols(void) {
    // Native
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        if (col_pins[x] != NO_PIN) {
            gpio_set_pin_output(col_pins[x]);
            gpio_write_pin_high(col_pins[x]);
        }
    }

    // Demultiplexer
    sn74x138_set_enabled(false);
}

static void init_pins(void) {
    unselect_cols();
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        gpio_set_pin_input_high(row_pins[x]);
    }
}

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    bool matrix_changed = false;

    // Select col and wait for col selection to stabilize
    select_col(current_col);
    matrix_io_delay();

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[row_index];

        // Check row pin state
        if (gpio_read_pin(row_pins[row_index]) == 0) {
            // Pin LO, set col bit
            current_matrix[row_index] |= (MATRIX_ROW_SHIFTER << current_col);
        } else {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~(MATRIX_ROW_SHIFTER << current_col);
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_matrix[row_index]) && !(matrix_changed)) {
            matrix_changed = true;
        }
    }

    // Unselect col
    unselect_col(current_col);

    return matrix_changed;
}

void matrix_init_custom(void) {
    // initialize demultiplexer
    sn74x138_init();
    // initialize key pins
    init_pins();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    // Set col, read rows
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        changed |= read_rows_on_col(current_matrix, current_col);
    }

    return changed;
}
