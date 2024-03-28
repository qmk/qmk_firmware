// Copyright 2023 David Hoelscher (@customMK)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "matrix.h"
#include <string.h>

// Pin definitions
static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

void matrix_wait_for_pin(pin_t pin, uint8_t target_state) {
    rtcnt_t start = chSysGetRealtimeCounterX();
    rtcnt_t end   = start + 5000;
    while (chSysIsCounterWithinX(chSysGetRealtimeCounterX(), start, end)) {
        if (readPin(pin) == target_state) {
            break;
        }
    }
}

void matrix_wait_for_port(stm32_gpio_t *port, uint32_t target_bitmask) {
    rtcnt_t start = chSysGetRealtimeCounterX();
    rtcnt_t end   = start + 5000;
    while (chSysIsCounterWithinX(chSysGetRealtimeCounterX(), start, end)) {
        if ((palReadPort(port) & target_bitmask) == target_bitmask) {
            break;
        }
    }
}

void shift_pulse_clock(void) {
        writePinHigh(COL_SHIFT_CLK_PIN);
        matrix_wait_for_pin(COL_SHIFT_CLK_PIN, 1);
        writePinLow(COL_SHIFT_CLK_PIN);
}

void matrix_init_custom(void) {
    //set all row pins as input with pullups
    for (int i = 0; i < MATRIX_ROWS; ++i) {
        writePinHigh(row_pins[i]);
        setPinInputHigh(row_pins[i]);
    }

    //set all column pins high in ROW2COL matrix
    setPinOutput(COL_SHIFT_IN_PIN);
    setPinOutput(COL_SHIFT_CLK_PIN);
    writePinHigh(COL_SHIFT_IN_PIN);
    matrix_wait_for_pin(COL_SHIFT_IN_PIN, 1);

    for (int i = 0; i < MATRIX_COLS; ++i) {
        shift_pulse_clock();
    }

}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    static matrix_row_t temp_matrix[MATRIX_ROWS] = {0};

    writePinLow(COL_SHIFT_IN_PIN);
    matrix_wait_for_pin(COL_SHIFT_IN_PIN, 0);

    // Setup the output column pin
    shift_pulse_clock();

    writePinHigh(COL_SHIFT_IN_PIN);
    for (int current_col = 0; current_col < MATRIX_COLS; ++current_col) {

        // Read the column ports
        uint32_t gpio_a = palReadPort(GPIOA);
        uint32_t gpio_b = palReadPort(GPIOB);
        
        // row 0, pin A8
        int current_row = 0;
        if ((gpio_a & (1 << 8)) >> 8) {
            temp_matrix[current_row] &= ~(1ul << current_col);
        } else {
            temp_matrix[current_row] |= (1ul << current_col);
        }
        // row 1, pin A1
        current_row = 1;
        if ((gpio_a & (1 << 1)) >> 1) {
            temp_matrix[current_row] &= ~(1ul << current_col);
        } else {
            temp_matrix[current_row] |= (1ul << current_col);
        }
        // row 2, pin A2
        current_row = 2;
        if ((gpio_a & (1 << 2)) >> 2) {
            temp_matrix[current_row] &= ~(1ul << current_col);
        } else {
            temp_matrix[current_row] |= (1ul << current_col);
        }
        // row 3, pin B3
        current_row = 3;
        if ((gpio_b & (1 << 1)) >> 1) {
            temp_matrix[current_row] &= ~(1ul << current_col);
        } else {
            temp_matrix[current_row] |= (1ul << current_col);
        }
        // row 4, pin A7
        current_row = 4;
        if ((gpio_a & (1 << 7)) >> 7) {
            temp_matrix[current_row] &= ~(1ul << current_col);
        } else {
            temp_matrix[current_row] |= (1ul << current_col);
        }
        
        // Setup the output column pin
        shift_pulse_clock();
    
    }

    // Check if matrix has changed, return the last-read data
    bool changed = memcmp(current_matrix, temp_matrix, sizeof(temp_matrix)) != 0;
    if (changed) {
        memcpy(current_matrix, temp_matrix, sizeof(temp_matrix));
    }
    shift_pulse_clock();
    return changed;
}
