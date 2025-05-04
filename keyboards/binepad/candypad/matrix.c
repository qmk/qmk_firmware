// Copyright 2023 Silvino R. (@silvinor)
// Copyright 2012-2018 Jun Wako, Jack Humbert, Yiancar [portions from `qantum/matrix.c`]
// SPDX-License-Identifier: GPL-2.0-or-later

/**
 * This file is mostly a copy of `matrix.c` from the QMK core, however
 * it assumes the matrix is always COL2ROW and that the KB has BOTH
 * matrix and direct pins.
 *
 * For direct pins define
 *   `DIRECT_PINS_CUSTOM`
 * This stucture must exactly match the MATRIX_ROWS / MATRIX_COLS matrix.
 *
 * !! : The ROW that supports direct pins __must__ have the row set to NO_PIN in the matrix array.
 */

#include "matrix.h"
#include "debounce.h"
#include "atomic_util.h"
#include <string.h> // For memset, memcmp & memcpy
#include "wait.h"

#ifndef MATRIX_INPUT_PRESSED_STATE
#    define MATRIX_INPUT_PRESSED_STATE 0
#endif

static pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

// define DIRECT_PINS_CUSTOM in `config.h`
// !! : Must match the MATRIX_ROWS / MATRIX_COLS matrix structure
static pin_t direct_pins[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS_CUSTOM;

/* matrix state(1:on, 0:off) */
matrix_row_t raw_matrix[MATRIX_ROWS];

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

static inline uint8_t gpio_read_matrix_pin(pin_t pin) {
    if (pin != NO_PIN) {
        return (gpio_read_pin(pin) == MATRIX_INPUT_PRESSED_STATE) ? 0 : 1;
    } else {
        return 1;
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

void matrix_init_pins__matrix(void) {
    unselect_rows();
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        if (col_pins[x] != NO_PIN) {
            gpio_atomic_set_pin_input_high(col_pins[x]);
        }
    }
}

void matrix_init_pins__direct(void) {
    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < MATRIX_COLS; col++) {
            pin_t pin = direct_pins[row][col];
            if (pin != NO_PIN) {
                gpio_atomic_set_pin_input_high(pin);
            }
        }
    }
}

void matrix_init_custom(void) {
    // initialize key pins
    matrix_init_pins__matrix();
    matrix_init_pins__direct();

    // initialize matrix state: all keys off
    memset(raw_matrix, 0, sizeof(raw_matrix));
}

void matrix_read_cols_on_row__matrix(matrix_row_t current_matrix[], uint8_t current_row) {
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;

    if (!select_row(current_row)) { // Select row
        return;                     // skip NO_PIN row
    }
    matrix_output_select_delay();

    // For each col...
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++, row_shifter <<= 1) {
        uint8_t pin_state = gpio_read_matrix_pin(col_pins[col_index]);

        // Populate the matrix row with the state of the col pin
        current_row_value |= pin_state ? 0 : row_shifter;
    }

    // Unselect row
    unselect_row(current_row);
    matrix_output_unselect_delay(current_row, current_row_value != 0); // wait for all Col signals to go HIGH

    // Update the matrix
    current_matrix[current_row] = current_row_value;
}

void matrix_read_cols_on_row__direct(matrix_row_t current_matrix[], uint8_t current_row) {
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;

    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++, row_shifter <<= 1) {
        pin_t pin = direct_pins[current_row][col_index];
        if (NO_PIN != pin) {
            current_row_value |= gpio_read_matrix_pin(pin) ? 0 : row_shifter;
        }
    }

    // Update the matrix
    current_matrix[current_row] = current_row_value;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    // Matrix keys: Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        // if the row is a NO_PIN then assume it's on a direct pins matrix, else assume COL2ROW matrix
        if (NO_PIN != row_pins[current_row]) {
            matrix_read_cols_on_row__matrix(current_matrix, current_row);
        } else {
            matrix_read_cols_on_row__direct(current_matrix, current_row);
        }
    }

    matrix_has_changed = memcmp(raw_matrix, current_matrix, MATRIX_ROWS) != 0;
    if (matrix_has_changed) {
        memcpy(raw_matrix, current_matrix, MATRIX_ROWS);
    }

    return matrix_has_changed;
}
