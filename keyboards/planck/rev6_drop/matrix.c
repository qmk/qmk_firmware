/*
 * Copyright 2018-2023 Jack Humbert <jack.humb@gmail.com>
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

#include "quantum.h"

/* matrix state(1:on, 0:off) */
static pin_t matrix_row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static pin_t matrix_col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

static matrix_row_t matrix_inverted[MATRIX_COLS];

void matrix_init_custom(void) {
    // actual matrix setup - cols
    for (int i = 0; i < MATRIX_COLS; i++) {
        setPinOutput(matrix_col_pins[i]);
        writePinLow(matrix_col_pins[i]);
    }

    // rows
    for (int i = 0; i < MATRIX_ROWS; i++) {
        setPinInputLow(matrix_row_pins[i]);
    }
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    // actual matrix
    for (int col = 0; col < MATRIX_COLS; col++) {
        matrix_row_t data = 0;

        // strobe col
        writePinHigh(matrix_col_pins[col]);

        // need wait to settle pin state
        wait_us(20);

        // read row data
        for (int row = 0; row < MATRIX_ROWS; row++) {
            data |= (readPin(matrix_row_pins[row]) << row);
        }

        // unstrobe col
        writePinLow(matrix_col_pins[col]);

        if (matrix_inverted[col] != data) {
            matrix_inverted[col] = data;
        }
    }

    for (int row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t old = current_matrix[row];
        current_matrix[row] = 0;
        for (int col = 0; col < MATRIX_COLS; col++) {
            current_matrix[row] |= ((matrix_inverted[col] & (1 << row) ? 1 : 0) << col);
        }
        changed |= old != current_matrix[row];
    }

    return changed;
}
