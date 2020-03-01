/*
Copyright 2017-2019 Mathias Andersson <wraul@dbox.se>

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

__attribute__((weak)) void matrix_init_kb(void) {}

__attribute__((weak)) void matrix_scan_kb(void) {}

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

inline uint8_t matrix_rows(void) { return MATRIX_ROWS; }

inline uint8_t matrix_cols(void) { return MATRIX_COLS; }

inline bool matrix_is_on(uint8_t row, uint8_t col) { return (matrix[row] & ((matrix_row_t)1 << col)); }

inline matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void) {
    print_matrix_header();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row);
        print(": ");
        print_matrix_row(row);
        print("\n");
    }
}

uint8_t matrix_key_count(void) {
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += matrix_bitpop(i);
    }
    return count;
}

/* Columns 0 - 15
 * These columns uses two 74HC237D 3 to 8 bit demultiplexers.
 * col / pin:    PB6  PC6  PC7  PF1  PF0
 * 0:             0    1    0    0    0
 * 1:             0    1    0    0    1
 * 2:             0    1    0    1    0
 * 3:             0    1    0    1    1
 * 4:             0    1    1    0    0
 * 5:             0    1    1    0    1
 * 6:             0    1    1    1    0
 * 7:             0    1    1    1    1
 * 8:             1    0    0    0    0
 * 9:             1    0    0    0    1
 * 10:            1    0    0    1    0
 * 11:            1    0    0    1    1
 * 12:            1    0    1    0    0
 * 13:            1    0    1    0    1
 * 14:            1    0    1    1    0
 * 15:            1    0    1    1    1
 *
 * col: 16
 * pin: PB5
 */
static void unselect_cols(void) {
    for (uint8_t x = 0; x < 6; x++) {
        setPinOutput(col_pins[x]);
        writePinLow(col_pins[x]);
    }
}

static void select_col(uint8_t col) {
    if (col < 16) {
        uint8_t c = col + 8;

        writePin(B6, c & 0b10000);
        writePin(C6, c & 0b01000);
        writePin(C7, c & 0b00100);
        writePin(F1, c & 0b00010);
        writePin(F0, c & 0b00001);
    } else {
        writePinHigh(B5);
    }
}

/* Row pin configuration
 * row: 0   1   2   3   4   5
 * pin: D0  D1  D2  D3  D5  B7
 *
 * Caps lock uses its own pin E2
 */
static void init_pins(void) {
    unselect_cols();
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInputHigh(row_pins[x]);
    }

    setPinInputHigh(E2);
}

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    bool matrix_changed = false;

    // Select col and wait for col selecton to stabilize
    select_col(current_col);
    wait_us(30);

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[row_index];

        // Check row pin state
        // Use the otherwise unused row: 3, col: 0 for caps lock
        if (row_index == 3 && current_col == 0) {
            if (readPin(E2) == 0) {
                // Pin LO, set col bit
                current_matrix[row_index] |= (ROW_SHIFTER << current_col);
            } else {
                // Pin HI, clear col bit
                current_matrix[row_index] &= ~(ROW_SHIFTER << current_col);
            }
        } else {
            if (readPin(row_pins[row_index]) == 0) {
                // Pin HI, clear col bit
                current_matrix[row_index] &= ~(ROW_SHIFTER << current_col);
            } else {
                // Pin LO, set col bit
                current_matrix[row_index] |= (ROW_SHIFTER << current_col);
            }
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
    bool changed = false;

    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        changed |= read_rows_on_col(raw_matrix, current_col);
    }

    debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

    matrix_scan_quantum();

    return (uint8_t)changed;
}
