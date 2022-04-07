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

#include <stdint.h>
#include <stdbool.h>
#include "matrix.h"
#include "quantum.h"
#include "sn74x138.h"

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

/* col 0: C7
 * col 1: B6
 * col 2: C6
 * col 3: B4
 * col 4: B5
 * col 5: D7
 *
 * These columns use a 74HC138 3 to 8 bit demultiplexer.
 *                A2   A1   A0
 * col / pin:    PD0  PD1  PD2
 * 6:              1    1    1
 * 7:              1    1    0
 * 8:              1    0    1
 * 9:              1    0    0
 * 10:             0    1    1
 * 11:             0    1    0
 * 12:             0    0    1
 *
 * col 13: D3
 * col 14: B7
 * col 15: B3
 */
static void select_col(uint8_t col) {
    if (col_pins[col] != NO_PIN) {
        writePinLow(col_pins[col]);
    } else {
        sn74x138_set_addr(13 - col);
    }
}

static void unselect_col(uint8_t col) {
    if (col_pins[col] != NO_PIN) {
        setPinOutput(col_pins[col]);
        writePinHigh(col_pins[col]);
    } else {
        sn74x138_set_addr(0);
    }
}

static void unselect_cols(void) {
    // Native
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        if (col_pins[x] != NO_PIN) {
            setPinOutput(col_pins[x]);
            writePinHigh(col_pins[x]);
        }
    }

    // Demultiplexer
    sn74x138_set_addr(0);
}

static void init_pins(void) {
    unselect_cols();
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInputHigh(row_pins[x]);
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
        if (readPin(row_pins[row_index]) == 0) {
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
    // initialize key pins
    init_pins();
    // initialize demultiplexer
    sn74x138_init();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    // Set col, read rows
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        changed |= read_rows_on_col(current_matrix, current_col);
    }

    return changed;
}
