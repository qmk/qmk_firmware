// Copyright 2023 Silvino R. (@silvinor)
// Copyright 2012-2018 Jun Wako, Jack Humbert, Yiancar [portions from `qantum/matrix.c`]
// SPDX-License-Identifier: GPL-2.0-or-later

/**
 * This file is mostly a copy of `matrix.c` from the QMK core, however
 * it assumes the matrix is always COL2ROW and that the KB has BOTH
 * matrix and direct pins.

 * For direct pins define
 *   `DIRECT_PINS_CUSTOM`
 * This stucture must match exactly the MATRIX_ROWS / MATRIX_COLS matrix.
 *
 * NB!!: The ROW that supports direct pins **must** have the row set
 *   to NO_PIN in the matrix array.
*/

#include "matrix.h"
#include "debounce.h"
#include "atomic_util.h"
#include <string.h>
#include "wait.h"
#include "print.h"

#ifndef DEBOUNCE
#    define DEBOUNCE 5
#endif

#ifndef MATRIX_INPUT_PRESSED_STATE
#    define MATRIX_INPUT_PRESSED_STATE 0
#endif

#ifndef MATRIX_IO_DELAY
#    define MATRIX_IO_DELAY 30
#endif

static pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

// define DIRECT_PINS_CUSTOM in `config.h`
// ** NB: ** must match the MATRIX_ROWS / MATRIX_COLS matrix structure
static pin_t direct_pins[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS_CUSTOM;

/* matrix state(1:on, 0:off) */
matrix_row_t raw_matrix[MATRIX_ROWS];
matrix_row_t matrix[MATRIX_ROWS];

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__((weak)) void matrix_scan_user(void) {}

__attribute__((weak)) void matrix_scan_kb(void) {
    matrix_scan_user();
}

#define print_matrix_header() print("\nr/c 01234567\n")
#define print_matrix_row(row) print_bin_reverse8(matrix_get_row(row))

__attribute__((weak)) void matrix_output_select_delay(void) {
    waitInputPinDelay();
}

__attribute__((weak)) void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
    wait_us(MATRIX_IO_DELAY);
}

static inline void setPinOutput_writeLow(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinOutput(pin);
        writePinLow(pin);
    }
}

static inline void setPinInputHigh_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinInputHigh(pin);
    }
}

static inline uint8_t readMatrixPin(pin_t pin) {
    if (pin != NO_PIN) {
        return (readPin(pin) == MATRIX_INPUT_PRESSED_STATE) ? 0 : 1;
    } else {
        return 1;
    }
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

static bool select_row(uint8_t row) {
    pin_t pin = row_pins[row];
    if (pin != NO_PIN) {
        setPinOutput_writeLow(pin);
        return true;
    }
    return false;
}

static void unselect_row(uint8_t row) {
    pin_t pin = row_pins[row];
    if (pin != NO_PIN) {
        setPinInputHigh_atomic(pin);
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
            setPinInputHigh_atomic(col_pins[x]);
        }
    }
}

void matrix_init_pins__direct(void) {
    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < MATRIX_COLS; col++) {
            pin_t pin = direct_pins[row][col];
            if (pin != NO_PIN) {
                setPinInputHigh(pin);
            }
        }
    }
}

inline uint8_t matrix_rows(void) {
    return MATRIX_ROWS;
}

inline uint8_t matrix_cols(void) {
    return MATRIX_COLS;
}

void matrix_init(void) {
    // initialize key pins
    matrix_init_pins__matrix();
    matrix_init_pins__direct();

    // initialize matrix state: all keys off
    memset(raw_matrix, 0, sizeof(raw_matrix));
    memset(matrix, 0, sizeof(matrix));

    // Unless hardware debouncing - Init the configured debounce routine
    debounce_init(MATRIX_ROWS);

    // This *must* be called for correct keyboard behavior
    matrix_init_kb();
}

inline bool matrix_is_on(uint8_t row, uint8_t col) {
    return (matrix[row] & ((matrix_row_t)1 << col));
}

inline matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
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
        uint8_t pin_state = readMatrixPin(col_pins[col_index]);

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
            current_row_value |= readMatrixPin(pin) ? 0 : row_shifter;
        }
    }

    // Update the matrix
    current_matrix[current_row] = current_row_value;
}

uint8_t matrix_scan(void) {
    matrix_row_t curr_matrix[MATRIX_ROWS] = {0};

    // Matrix keys: Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        // if the row is a NO_PIN then assume it's on a direct pins matrix, else assume COL2ROW matrix
        if (NO_PIN != row_pins[current_row]) {
            matrix_read_cols_on_row__matrix(curr_matrix, current_row);
        } else {
            matrix_read_cols_on_row__direct(curr_matrix, current_row);
        }
    }

    bool changed = memcmp(raw_matrix, curr_matrix, sizeof(curr_matrix)) != 0;
    if (changed) memcpy(raw_matrix, curr_matrix, sizeof(curr_matrix));

    changed = debounce(raw_matrix, matrix, MATRIX_ROWS, changed);
    matrix_scan_kb();

    return (uint8_t)changed;
}
