/*
 * Copyright (c) 2020 Yaotian Feng / Codetector
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

#define MATRIX_INPUT_PRESSED_STATE 0

#ifdef MATRIX_ROW_PINS
static pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
#endif // MATRIX_ROW_PINS
#ifdef MATRIX_COL_PINS
static pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
#endif // MATRIX_COL_PINS

#define ROWS_PER_HAND (MATRIX_ROWS)

void matrix_init_custom(void) {};

static inline uint8_t readMatrixPin(pin_t pin) {
    if (pin != NO_PIN) {
        return (palReadLine(pin) == MATRIX_INPUT_PRESSED_STATE) ? 0 : 1;
    } else {
        return 1;
    }
}

static bool select_col(uint8_t col) {
    pin_t pin = col_pins[col];
    if (pin != NO_PIN) {
        palClearLine(pin);
        return true;
    }
    return false;
}

static void unselect_col(uint8_t col) {
    pin_t pin = col_pins[col];
    if (pin != NO_PIN) {
        palSetLine(pin);
    }
}

static void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col, matrix_row_t row_shifter) {
    bool key_pressed = false;

    // Select col
    if (!select_col(current_col)) { // select col
        return;                     // skip NO_PIN col
    }
    matrix_output_select_delay();

    // For each row...
    for (uint8_t row_index = 0; row_index < ROWS_PER_HAND; row_index++) {
        // Check row pin state
        if (readMatrixPin(row_pins[row_index]) == 0) {
            // Pin LO, set col bit
            current_matrix[row_index] |= row_shifter;
            key_pressed = true;
        } else {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~row_shifter;
        }
    }

    // Unselect col
    unselect_col(current_col);
    matrix_output_unselect_delay(current_col, key_pressed); // wait for all Row signals to go HIGH
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    matrix_row_t curr_matrix[MATRIX_ROWS] = {0};

    // Set col, read rows
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++, row_shifter <<= 1) {
        matrix_read_rows_on_col(curr_matrix, current_col, row_shifter);
    }

    bool changed = memcmp(current_matrix, curr_matrix, sizeof(curr_matrix)) != 0;
    if (changed) memcpy(current_matrix, curr_matrix, sizeof(curr_matrix));

    return changed;
};

#ifndef MATRIX_IO_DELAY
#    define MATRIX_IO_DELAY 30
#endif

// Rows only need time to return high when a key on the column pulled one low.
// QMK's default waits MATRIX_IO_DELAY after every column, even with no key down,
// and on Cortex-M0 its wait_us() sleeps for at least one 1 ms system tick. This
// busy-waits instead, in steps of 128 cycles since wait_cpuclock() takes at most 135.
#define SETTLE_STEPS (MATRIX_IO_DELAY * (CPU_CLOCK / 1000000L) / 128)

void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
    if (key_pressed) {
        for (uint16_t i = 0; i < SETTLE_STEPS; i++) {
            wait_cpuclock(128);
        }
    }
}
