/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
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
#include "config.h"
#include "quantum.h"
#include "cheapino.h"

// How long the scanning code waits for changed io to settle.
#ifndef MATRIX_IO_DELAY
#    define MATRIX_IO_DELAY 30
#endif

// Rows that are actually scanned. Rows after these only hold keys the
// revision code fills in (like the v1 encoder press).
#ifndef CHEAPINO_SCANNED_ROWS
#    define CHEAPINO_SCANNED_ROWS MATRIX_ROWS
#endif

#define COL_SHIFTER ((uint16_t)1)

static const pin_t row_pins[] = MATRIX_ROW_PINS;
static const pin_t col_pins[] = MATRIX_COL_PINS;
static matrix_row_t previous_matrix[MATRIX_ROWS];

static void select_row(uint8_t row) {
    gpio_set_pin_output(row_pins[row]);
    gpio_write_pin_low(row_pins[row]);
}

static void unselect_row(uint8_t row) { gpio_set_pin_input_high(row_pins[row]); }

static void unselect_rows(void) {
    for (uint8_t x = 0; x < CHEAPINO_SCANNED_ROWS; x++) {
        gpio_set_pin_input_high(row_pins[x]);
    }
    for (uint8_t x = CHEAPINO_SCANNED_ROWS; x < MATRIX_ROWS; x++) {
        gpio_set_pin_input(row_pins[x]);
    }
}

static void select_col(uint8_t col) {
    gpio_set_pin_output(col_pins[col]);
    gpio_write_pin_low(col_pins[col]);
}

static void unselect_col(uint8_t col) {
    gpio_set_pin_input_high(col_pins[col]);
}

static void unselect_cols(void) {
    for (uint8_t x = 0; x < MATRIX_COLS/2; x++) {
        gpio_set_pin_input_high(col_pins[x*2]);
    }
}

static void read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Select row and wait for row selection to stabilize
    select_row(current_row);
    wait_us(MATRIX_IO_DELAY);

    // For each col...
    for (uint8_t col_index = 0; col_index < MATRIX_COLS / 2; col_index++) {
        uint16_t column_index_bitmask = COL_SHIFTER << ((col_index * 2) + 1);
        // Check row pin state
        if (gpio_read_pin(col_pins[col_index*2])) {
            // Pin HI, clear col bit
            current_matrix[current_row] &= ~column_index_bitmask;
        } else {
            // Pin LO, set col bit
            current_matrix[current_row] |= column_index_bitmask;
        }
    }

    // Unselect row
    unselect_row(current_row);
}

static void read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    // Select col and wait for col selection to stabilize
    select_col(current_col*2);
    wait_us(MATRIX_IO_DELAY);

    uint16_t column_index_bitmask = COL_SHIFTER << (current_col * 2);
    // For each row...
    for (uint8_t row_index = 0; row_index < CHEAPINO_SCANNED_ROWS; row_index++) {
        // Check row pin state
        if (gpio_read_pin(row_pins[row_index])) {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~column_index_bitmask;
        } else {
            // Pin LO, set col bit
            current_matrix[row_index] |= column_index_bitmask;
        }
    }
    // Unselect col
    unselect_col(current_col*2);
}


void matrix_init_custom(void) {
    // initialize key pins
    unselect_cols();
    unselect_rows();
}

void store_old_matrix(matrix_row_t current_matrix[]) {
    memcpy(previous_matrix, current_matrix, MATRIX_ROWS * sizeof(matrix_row_t));
}

bool has_matrix_changed(matrix_row_t current_matrix[]) {
    return memcmp(previous_matrix, current_matrix, MATRIX_ROWS * sizeof(matrix_row_t)) != 0;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    store_old_matrix(current_matrix);
    // Set row, read cols
    for (uint8_t current_row = 0; current_row < CHEAPINO_SCANNED_ROWS; current_row++) {
        read_cols_on_row(current_matrix, current_row);
    }
    // Set col, read rows
    for (uint8_t current_col = 0; current_col < MATRIX_COLS/2; current_col++) {
        read_rows_on_col(current_matrix, current_col);
    }

    cheapino_read_encoder(current_matrix);
    cheapino_fix_ghosting(current_matrix);

    return has_matrix_changed(current_matrix);
}

