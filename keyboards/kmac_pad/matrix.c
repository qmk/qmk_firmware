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

#include <stdint.h>
#include <stdbool.h>
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"


#if (MATRIX_COLS <= 8)
#    define print_matrix_header() print("\nr/c 01234567\n")
#    define print_matrix_row(row) print_bin_reverse8(matrix_get_row(row))
#    define matrix_bitpop(i) bitpop(matrix[i])
#    define ROW_SHIFTER ((uint8_t)1)
#elif (MATRIX_COLS <= 16)
#    define print_matrix_header() print("\nr/c 0123456789ABCDEF\n")
#    define print_matrix_row(row) print_bin_reverse16(matrix_get_row(row))
#    define matrix_bitpop(i) bitpop16(matrix[i])
#    define ROW_SHIFTER ((uint16_t)1)
#elif (MATRIX_COLS <= 32)
#    define print_matrix_header() print("\nr/c 0123456789ABCDEF0123456789ABCDEF\n")
#    define print_matrix_row(row) print_bin_reverse32(matrix_get_row(row))
#    define matrix_bitpop(i) bitpop32(matrix[i])
#    define ROW_SHIFTER ((uint32_t)1)
#endif

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

/* matrix state(1:on, 0:off) */
static matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
static matrix_row_t matrix[MATRIX_ROWS];      // debounced values


__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

inline matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

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
            current_matrix[0] |= (ROW_SHIFTER << current_col);
        } else {
            // Pin HI, clear col bit
            current_matrix[0] &= ~(ROW_SHIFTER << current_col);
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
            current_matrix[row_index] &= ~(ROW_SHIFTER << current_col);
        } else {
            // Pin LO, set col bit
            current_matrix[row_index] |= (ROW_SHIFTER << current_col);
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

void matrix_print(void) {
    print_matrix_header();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row);
        print(": ");
        print_matrix_row(row);
        print("\n");
    }
}

void matrix_init(void) {
    // initialize hardware and global matrix state here
    unselect_cols();

    // initialize key pins
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        setPinInputHigh(row_pins[row_index]);
    }

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    // Unless hardware debouncing - Init the configured debounce routine
    debounce_init(MATRIX_ROWS);

    // This *must* be called for correct keyboard behavior
    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    bool changed = false;

    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        changed |= read_rows_on_col(raw_matrix, current_col);
    }

    // Unless hardware debouncing - use the configured debounce routine
    debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

    // This *must* be called for correct keyboard behavior
    matrix_scan_quantum();

    return changed;
}
