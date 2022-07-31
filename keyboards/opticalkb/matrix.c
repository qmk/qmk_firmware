/*
Copyright 2022 Girish Palya <girishji@gmail.com>

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

/*
 * scan matrix
 * https://github.com/qmk/qmk_firmware/blob/master/docs/custom_matrix.md
 */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "util.h"
#include "matrix.h"
#include "quantum.h"
#include "print.h"
#include "wait.h"
#include "debug.h"
#include "util.h"
#include "config.h"
#include "timer.h"

#ifdef MATRIX_ROW_PINS
static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
#endif
#ifdef MATRIX_COL_PINS
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
#endif

/* matrix state(1:on, 0:off) */
// static matrix_row_t matrix[MATRIX_ROWS];
matrix_row_t matrix[MATRIX_ROWS];

void matrix_init(void) {
    // initialize matrix state: all keys off
    memset(matrix, 0, sizeof(matrix));

    // https://github.com/qmk/qmk_firmware/blob/master/docs/gpio_control.md
    //
    // initialize column pins to be Output and set them Low
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        pin_t pin = col_pins[col];
        if (pin != NO_PIN) {
            ATOMIC_BLOCK_FORCEON {
                setPinOutput(pin);
                writePinHigh(pin);
            }
        }
    }

    // initialize row pins to be Input
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        pin_t pin = row_pins[row];
        if (pin != NO_PIN) {
            ATOMIC_BLOCK_FORCEON {
#ifdef PT_INPUT_USE_PULLUP
                setPinInputHigh(pin);
#else
                setPinInput(pin);
#endif
            }
        }
    }

    // This *must* be called for correct keyboard behavior
    matrix_init_quantum();
}

static bool select_col(uint8_t col) {
    pin_t pin = col_pins[col];
    if (pin != NO_PIN) {
        ATOMIC_BLOCK_FORCEON {
            writePinHigh(pin);
        }
        return true;
    }
    return false;
}

static bool unselect_col(uint8_t col) {
    pin_t pin = col_pins[col];
    if (pin != NO_PIN) {
        ATOMIC_BLOCK_FORCEON {
            writePinLow(pin);
        }
        return true;
    }
    return false;
}

__attribute__((weak)) void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col, matrix_row_t row_shifter) {
    if (!select_col(current_col)) {
        dprintf("Error: failed to power on col %d\n", current_col);
        return;
    }
    // wait_us(500); //  rise and fall time of pt is 15us but depends on current
    wait_ms(1);
    // wait_us(30);

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        if (row_pins[row_index] == NO_PIN) {
            continue;
        }
        // Check row pin state
        if (readPin(row_pins[row_index]) == 1) {
            // Pin HI, set col bit
            current_matrix[row_index] |= row_shifter;
        } else {
            // Pin LO, clear col bit
            current_matrix[row_index] &= ~row_shifter;
        }
    }

    unselect_col(current_col);
    waitInputPinDelay();
}

uint8_t matrix_scan(void) {
    matrix_row_t curr_matrix[MATRIX_ROWS] = {0};

    // Set col, read rows
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++, row_shifter <<= 1) {
        matrix_read_rows_on_col(curr_matrix, current_col, row_shifter);
    }

    bool changed = memcmp(matrix, curr_matrix, sizeof(curr_matrix)) != 0;
    if (changed) {
        memcpy(matrix, curr_matrix, sizeof(curr_matrix));
    }

    // This *must* be called for correct keyboard behavior
    matrix_scan_quantum();

    return (uint8_t)changed;
}

inline matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

#if (MATRIX_COLS <= 8)
#    define print_matrix_header() print("\nr/c 01234567\n")
#    define print_matrix_row(row) print_bin_reverse8(matrix_get_row(row))
#elif (MATRIX_COLS <= 16)
#    define print_matrix_header() print("\nr/c 0123456789ABCDEF\n")
#    define print_matrix_row(row) print_bin_reverse16(matrix_get_row(row))
#elif (MATRIX_COLS <= 32)
#    define print_matrix_header() print("\nr/c 0123456789ABCDEF0123456789ABCDEF\n")
#    define print_matrix_row(row) print_bin_reverse32(matrix_get_row(row))
#endif

void matrix_print(void) {
    print_matrix_header();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row);
        print(": ");
        print_matrix_row(row);
        print("\n");
    }
}

__attribute__((weak)) void matrix_init_kb(void) {
    matrix_init_user();
}
__attribute__((weak)) void matrix_scan_kb(void) {
    matrix_scan_user();
}
__attribute__((weak)) void matrix_init_user(void) {}
__attribute__((weak)) void matrix_scan_user(void) {}
