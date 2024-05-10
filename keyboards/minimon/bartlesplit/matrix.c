/*
Copyright 2012-2023 Jun Wako <wakojun@gmail.com> Kyrremann <kyrremann@gmail.com>
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

 Copied from here: https://github.com/e3w2q/qmk_firmware/blob/762fe3e0a7cbea768245a75520f06ff5a2f00b9f/keyboards/2x3test/matrix.c
*/

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include "wait.h"
#include "util.h"
#include "matrix.h"
#include "quantum.h"

#define ROW_SHIFTER ((uint16_t)1)

static const pin_t row_pins[] = MATRIX_ROW_PINS;
static const pin_t col_pins[] = MATRIX_COL_PINS;

static void select_row(uint8_t row) {
    setPinOutput(row_pins[row]);
    writePinLow(row_pins[row]);
}

static void unselect_row(uint8_t row) {
    setPinInputHigh(row_pins[row]);
}

static void unselect_rows(void) {
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInputHigh(row_pins[x]);
    }
}

static void select_col(uint8_t col) {
    setPinOutput(col_pins[col]);
    writePinLow(col_pins[col]);
}

static void unselect_col(uint8_t col) {
    setPinInputHigh(col_pins[col]);
}

static void unselect_cols(void) {
    for (uint8_t x = 0; x < MATRIX_COLS/2; x++) {
        setPinInputHigh(col_pins[x*2]);
    }
}

static void init_pins(void) {
    unselect_cols();
    unselect_rows();
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Store last value of row prior to reading
    matrix_row_t last_row_value = current_matrix[current_row];

    // Select row and wait for row selection to stabilize
    select_row(current_row);
    wait_us(30);

    // For each col...
    for (uint8_t col_index = 0; col_index < MATRIX_COLS / 2; col_index++) {
        uint16_t column_index_bitmask = ROW_SHIFTER << ((col_index * 2) + 1);
        // Check row pin state
        if (readPin(col_pins[col_index*2])) {
            // Pin HI, clear col bit
            current_matrix[current_row] &= ~column_index_bitmask;
        } else {
            // Pin LO, set col bit
            current_matrix[current_row] |= column_index_bitmask;
        }
    }

    // Unselect row
    unselect_row(current_row);

    return (last_row_value != current_matrix[current_row]);
}

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    bool matrix_changed = false;

    // Select col and wait for col selection to stabilize
    select_col(current_col*2);
    wait_us(30);

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[row_index];

        uint16_t column_index_bitmask = ROW_SHIFTER << (current_col * 2);
        // Check row pin state
        if (readPin(row_pins[row_index])) {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~column_index_bitmask;
        } else {
            // Pin LO, set col bit
            current_matrix[row_index] |= column_index_bitmask;
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_matrix[row_index]) && !(matrix_changed)) {
                   matrix_changed = true;
        }
    }

    // Unselect col
    unselect_col(current_col*2);

    return matrix_changed;
}


void matrix_init_custom(void) {
    // initialize key pins
    init_pins();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {

    bool changed = false;

    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        changed |= read_cols_on_row(current_matrix, current_row);
    }
    // Set col, read rows
    for (uint8_t current_col = 0; current_col < MATRIX_COLS/2; current_col++) {
        changed |= read_rows_on_col(current_matrix, current_col);
    }

    return changed;
}
