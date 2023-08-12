// Copyright 2023 NaturaZh (@NaturalZh)
// SPDX-License-Identifier: GPL-2.0-or-later
//Matrix read cols set row
//Matrix logic ADAPTS to PTIR

#include "quantum.h"

#define ALL_KEY_COL_PULL A15
#define TEST_PIN A10
#define ReadDelayTime 80
#define MATRIX_INPUT_PRESSED_STATE 0

pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

static inline void select_row_delay(uint16_t n) {
    while (n-- > 0) {
        asm volatile("nop" ::: "memory");
    };
}

static inline void setPinOutput_writeLow(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinOutput(pin);
        writePinLow(pin);
    }
}

static inline void setPinOutput_writeHigh(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinOutput(pin);
        writePinHigh(pin);
    }
}

static inline void setPinInput_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinInput(pin);
    }
}

static bool select_row(uint8_t row) {
    pin_t pin = row_pins[row];
    if (pin != NO_PIN) {
        setPinOutput_writeHigh(pin);
        return true;
    }
    return false;
}

static void unselect_row(uint8_t row) {
    pin_t pin = row_pins[row];
    if (pin != NO_PIN) {
        setPinOutput_writeLow(pin);
    }
}

static void unselect_rows(void) {
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        unselect_row(x);
    }
}

static void setPinInput_cols(void) {
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        if (col_pins[x] != NO_PIN) {
            setPinInput_atomic(col_pins[x]);
        }
    }
}

static inline uint8_t readMatrixPin(pin_t pin) {
    if (pin != NO_PIN) {
        return (readPin(pin) == MATRIX_INPUT_PRESSED_STATE) ? 0 : 1;
    } else {
        return 1;
    }
}

// matrix code

void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;
    // Select row
    if (!select_row(current_row)) { // select row
        return;                     // skip NO_PIN row
    }
    select_row_delay(ReadDelayTime);

    // For each col...
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++, row_shifter <<= 1) {
        uint8_t pin_state = readMatrixPin(col_pins[col_index]);

        // Populate the matrix row with the state of the col pin
        current_row_value |= pin_state ? 0 : row_shifter;
    }
    setPinOutput_writeLow(TEST_PIN);
    unselect_row(current_row);
    setPinOutput_writeLow(ALL_KEY_COL_PULL);
    matrix_output_unselect_delay(current_row, current_row_value != 0); // wait for all Col signals to go HIGH
    current_matrix[current_row] = current_row_value;
}

void matrix_init_custom(void) {
    // TODO: initialize hardware here
    setPinInput_cols();
    unselect_rows();
    setPinOutput_writeHigh(ALL_KEY_COL_PULL);
    setPinOutput_writeLow(TEST_PIN);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    matrix_row_t curr_matrix[MATRIX_ROWS] = {0};

    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        setPinOutput_writeHigh(ALL_KEY_COL_PULL);
        matrix_read_cols_on_row(curr_matrix, current_row);
    }

    matrix_has_changed = memcmp(current_matrix, curr_matrix, sizeof(curr_matrix)) != 0;
    if (matrix_has_changed) memcpy(current_matrix, curr_matrix, sizeof(curr_matrix));

    return matrix_has_changed;
}
