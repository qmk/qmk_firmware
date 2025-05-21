// Copyright 2023 Silvino R. (@silvinor)
// Copyright 2012-2018 Jun Wako, Jack Humbert, Yiancar [portions from `qantum/matrix.c`]
// SPDX-License-Identifier: GPL-2.0-or-later

/**
 * This file is mostly a copy of `matrix.c` from the QMK core, however
 * it assumes the matrix is always COL2ROW and that the KB has BOTH
 * matrix and direct pins.

 * For direct pins define:
 *   `DIRECT_PINS_CUSTOM`
 * This stucture must match exactly the MATRIX_ROWS / MATRIX_COLS matrix.
 *
 * NB!!: The ROW that supports direct pins **must** have the row set
 *   to NO_PIN in the matrix array.
*/

#include "quantum.h"
#include "matrix.h"
#include "atomic_util.h"

// ---------- Interal defs and vars ----------

#ifndef MATRIX_INPUT_PRESSED_STATE
#    define MATRIX_INPUT_PRESSED_STATE 0
#endif

static pin_t row_pins[MATRIX_ROWS]                 = MATRIX_ROW_PINS;
static pin_t col_pins[MATRIX_COLS]                 = MATRIX_COL_PINS;
static pin_t direct_pins[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS_CUSTOM;

// ---------- Interal functions ----------
// .......... Helpers ..........

static inline void gpio_atomic_set_pin_output_low(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_output(pin);
        gpio_write_pin_low(pin);
    }
}

static inline void gpio_atomic_set_pin_input_high(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_input_high(pin);
    }
}

static bool select_row(uint8_t row) {
    pin_t pin = row_pins[row];
    if (pin != NO_PIN) {
        gpio_atomic_set_pin_output_low(pin);
        return true;
    }
    return false;
}

static void unselect_row(uint8_t row) {
    pin_t pin = row_pins[row];
    if (pin != NO_PIN) {
        gpio_atomic_set_pin_input_high(pin);
    }
}

static void unselect_rows(void) {
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        unselect_row(x);
    }
}

// .......... Inits ..........

void matrix_init_matrix_pins(void) {
    unselect_rows();
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        if (col_pins[x] != NO_PIN) {
            gpio_atomic_set_pin_input_high(col_pins[x]);
        }
    }
}

void matrix_init_direct_pins(void) {
    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < MATRIX_COLS; col++) {
            pin_t pin = direct_pins[row][col];
            if (pin != NO_PIN) {
                gpio_atomic_set_pin_input_high(pin);
            }
        }
    }
}

// .......... Scanners ..........

static inline uint8_t readMatrixPin(pin_t pin) {
    if (pin != NO_PIN) {
        return (gpio_read_pin(pin) == MATRIX_INPUT_PRESSED_STATE) ? 0 : 1;
    } else {
        return 1;
    }
}

void matrix_scan_matrix_row(matrix_row_t row_buffer[], uint8_t row_to_scan) {
    matrix_row_t scan_row_value = 0;

    if (!select_row(row_to_scan)) {
        return;
    }
    matrix_output_select_delay();

    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t col_to_scan = 0; col_to_scan < MATRIX_COLS; col_to_scan++, row_shifter <<= 1) {
        uint8_t pin_state = readMatrixPin(col_pins[col_to_scan]);

        // Populate the matrix row with the state of the col pin
        scan_row_value |= pin_state ? 0 : row_shifter;
    }

    unselect_row(row_to_scan);
    matrix_output_unselect_delay(row_to_scan, scan_row_value != 0);

    row_buffer[row_to_scan] = scan_row_value;
}

void matrix_scan_direct_row(matrix_row_t row_buffer[], uint8_t row_to_scan) {
    matrix_row_t scan_row_value = 0;

    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t col_to_scan = 0; col_to_scan < MATRIX_COLS; col_to_scan++, row_shifter <<= 1) {
        pin_t pin = direct_pins[row_to_scan][col_to_scan];
        if (pin != NO_PIN) {
            scan_row_value |= readMatrixPin(pin) ? 0 : row_shifter;
        }
    }

    row_buffer[row_to_scan] = scan_row_value;
}

// ========== Core functions required by lite matrix driver ==========

void matrix_init_custom(void) {
    matrix_init_matrix_pins();
    matrix_init_direct_pins();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    matrix_row_t buff_matrix[MATRIX_ROWS] = {0};

    for (uint8_t scan_row = 0; scan_row < MATRIX_ROWS; scan_row++) {
        // if the row is a NO_PIN then assume it's on a direct pins matrix, else assume COL2ROW matrix
        if (row_pins[scan_row] == NO_PIN) {
            matrix_scan_direct_row(buff_matrix, scan_row);
        } else {
            matrix_scan_matrix_row(buff_matrix, scan_row);
        }
    }

    bool matrix_has_changed = memcmp(current_matrix, buff_matrix, sizeof(buff_matrix)) != 0;
    if (matrix_has_changed) {
        memcpy(current_matrix, buff_matrix, sizeof(buff_matrix));
    }
    return matrix_has_changed;
}
