// Copyright 2023 Cameron Varley (@RustedAperture)
// SPDX-License-Identifier: GPL-2.0-or-later

/*
 * scan matrix
 */
#include "matrix.h"
#include <string.h>
#include "atomic_util.h"
#include "wait.h"
#include "print.h"
#include "debug.h"

/* matrix state(1:on, 0:off) */
extern matrix_row_t matrix[MATRIX_ROWS];     // debounced values
extern matrix_row_t raw_matrix[MATRIX_ROWS]; // raw values

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
#define MATRIX_ROW_SHIFTER ((matrix_row_t)1)

static inline void setPinOutput_writeLow(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_output(pin);
        gpio_write_pin_low(pin);
    }
}

static inline void setPinOutput_writeHigh(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_output(pin);
        gpio_write_pin_high(pin);
    }
}

static inline void setPinInputHigh_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_input_high(pin);
    }
}

static inline uint8_t readMatrixPin(pin_t pin) {
    if (pin != NO_PIN) {
        return gpio_read_pin(pin);
    } else {
        return 1;
    }
}

static bool select_col(uint8_t col) {
    pin_t pin = col_pins[col];
    if (pin != NO_PIN) {
        setPinOutput_writeLow(pin);
        return true;
    }
    return false;
}

static void unselect_col(uint8_t col) {
    pin_t pin = col_pins[col];
    if (pin != NO_PIN) {
#            ifdef MATRIX_UNSELECT_DRIVE_HIGH
        setPinOutput_writeHigh(pin);
#            else
        setPinInputHigh_atomic(pin);
#            endif
    }
}

static void unselect_cols(void) {
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        unselect_col(x);
    }
}


__attribute__((weak)) void matrix_init_custom(void) {
    unselect_cols();
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        if (row_pins[x] != NO_PIN) {
            setPinInputHigh_atomic(row_pins[x]);
        }
    }
    setPinInputHigh_atomic(B8);
}

__attribute__((weak)) void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col, matrix_row_t row_shifter) {    // Start with a clear matrix row
        bool key_pressed = false;

    // Select col
    if (!select_col(current_col)) { // select col
        return;                     // skip NO_PIN col
    }
    matrix_output_select_delay();

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        // Check row pin state
        if (current_col == 3 && row_index == 2 && readMatrixPin(B8) == 1) {
            current_matrix[row_index] |= row_shifter;
            key_pressed = !readMatrixPin(B8);
        } else if (readMatrixPin(row_pins[row_index]) == 0) {
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
    static matrix_row_t temp_matrix[MATRIX_ROWS] = {0};

    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        matrix_read_rows_on_col(temp_matrix, current_col, row_shifter);
    }

    bool changed = memcmp(current_matrix, temp_matrix, sizeof(temp_matrix)) != 0;
    if (changed) {
        memcpy(current_matrix, temp_matrix, sizeof(temp_matrix));
    }
    return changed;
}
