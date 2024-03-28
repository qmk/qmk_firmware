/*
Copyright 2021 talsu <talsu84@gmail.com>

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

#include "wait.h"
#include "matrix.h"

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

/* Columns 0 - 3
 * col / pin:
 * 0: C7
 * 1: C6
 * 2: B6
 * 3: B5
 */
static void unselect_cols(void) {
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        setPinOutput(col_pins[col]);
        writePinLow(col_pins[col]);
    }
}

static void select_col(uint8_t col) {
    writePinHigh(col_pins[col]);
}

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    bool matrix_changed = false;

    // Select col and wait for col selecton to stabilize
    select_col(current_col);
    wait_us(30);

    // row:0 , col:0 FN key is DIRECT_PIN
    if (current_col == 0) {

        matrix_row_t last_row_value = current_matrix[0];
        if (readPin(row_pins[0]) == 0) {
            // Pin LO, set col bit
            current_matrix[0] |= (1 << current_col);
        } else {
            // Pin HI, clear col bit
            current_matrix[0] &= ~(1 << current_col);
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_matrix[0]) && !(matrix_changed)) {
            matrix_changed = true;
        }
    }

    // other row use MATRIX
    for (uint8_t row_index = 1; row_index < MATRIX_ROWS; row_index++) {

        matrix_row_t last_row_value = current_matrix[row_index];
        if (readPin(row_pins[row_index]) == 0) {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~(1 << current_col);
        } else {
            // Pin LO, set col bit
            current_matrix[row_index] |= (1 << current_col);
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_matrix[row_index]) && !(matrix_changed)) {
            matrix_changed = true;
        }
    }


    // Unselect cols
    unselect_cols();

    return matrix_changed;
}

void matrix_init_custom(void) {
    // initialize hardware and global matrix state here
    unselect_cols();

    // initialize key pins
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        setPinInputHigh(row_pins[row_index]);
    }
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        changed |= read_rows_on_col(current_matrix, current_col);
    }

    return changed;
}
