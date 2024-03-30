/*
Copyright 2022 somepin

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

static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

/* All rows use a 74HC138 3 to 8 bit demultiplexer.
 *
 *     A2   A1   A0
 *     D0   D1   D2
 * 0:   0    0    0
 * 1:   0    0    1
 * 2:   0    1    0
 * 3:   0    1    1
 * 4:   1    0    0
 * 5:   1    0    1
 * 6:   1    1    0
 */
static void select_row(uint8_t row) {
    sn74x138_set_addr(row);
}

static void init_pins(void) {
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinInputHigh(col_pins[x]);
    }
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    bool matrix_changed = false;

    // Store last value of row prior to reading
    matrix_row_t last_row_value = current_matrix[current_row];

    // Start with a clear matrix row
    current_matrix[current_row] = 0;

    // Select row and wait for row selection to stabilize
    select_row(current_row);
    matrix_io_delay();

    // For each col...
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {

        // Select the col pin to read (active low)
        uint8_t pin_state = readPin(col_pins[col_index]);

        // Populate the matrix row with the state of the col pin
        current_matrix[current_row] |=  pin_state ? 0 : (row_shifter << col_index);
    }
    
    // Determine if matrix changed state
    if ((last_row_value != current_matrix[current_row]) && !(matrix_changed)) {
        matrix_changed = true;
    }

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

    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        changed |= read_cols_on_row(current_matrix, current_row);
    }

    return changed;
}
