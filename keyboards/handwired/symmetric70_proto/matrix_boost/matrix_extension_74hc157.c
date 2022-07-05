// Copyright 2022 Takeshi Ishii (@mtei)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdint.h>
#include <stdbool.h>
#include "matrix.h"
#include "quantum.h"

#ifdef DIRECT_PIN
#    error DIRECT_PIN is not yet supported.
#endif
#ifdef DIODE_DIRECTION
#    if DIODE_DIRECTION == ROW2COL
#        error DIODE_DIRECTION == ROW2COL is not yet supported.
#    endif
#endif

#ifdef SPLIT_KEYBOARD
#    error SPLIT_KEYBOARD dose not support.
#endif

#define ROWS_PER_HAND (MATRIX_ROWS)

static const pin_t row_pins[ROWS_PER_HAND] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS]   = MATRIX_COL_PINS;

#ifdef MATRIX_DEBUG_DELAY_START
#    pragma message "MATRIX_DEBUG_DELAY_* enable"
#else
#    define MATRIX_DEBUG_DELAY_START()
#    define MATRIX_DEBUG_DELAY_END()
#endif

#ifdef MATRIX_MUL_SELECT
static const pin_t col_sel[MATRIX_COLS] = MATRIX_MUL_SEL;
#endif

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
        return readPin(pin);
    } else {
        return 1;
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
#ifdef MATRIX_UNSELECT_DRIVE_HIGH
        setPinOutput_writeHigh(pin);
#else
        setPinInputHigh_atomic(pin);
#endif
    }
}

void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;

    if (!select_row(current_row)) { // Select row
        return;                     // skip NO_PIN row
    }
    matrix_output_select_delay();
#ifdef MATRIX_MUL_SELECT
    setPinOutput(MATRIX_MUL_SELECT);
#endif
    // For each col...
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++, row_shifter <<= 1) {
#ifdef MATRIX_MUL_SELECT
        writePin(MATRIX_MUL_SELECT, col_sel[col_index]);
        waitInputPinDelay();
#endif
        uint8_t pin_state = readMatrixPin(col_pins[col_index]);

        // Populate the matrix row with the state of the col pin
        current_row_value |= pin_state ? 0 : row_shifter;
    }

    // Unselect row
    unselect_row(current_row);
    MATRIX_DEBUG_DELAY_START();
    matrix_output_unselect_delay(current_row, current_row_value != 0); // wait for all Col signals to go HIGH
    MATRIX_DEBUG_DELAY_END();

    // Update the matrix
    current_matrix[current_row] = current_row_value;
}
