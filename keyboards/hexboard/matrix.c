// Copyright 2023 Zach DeCook
// SPDX-License-Identifier: GPL-3.0-only
#include "matrix.h"

static const uint8_t columns[MATRIX_COLS] = MATRIX_COL_PINS;

// At least four of these should be defined!
static const pin_t mux_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

void matrix_init_custom(void) {
    // Set pinModes for the digital button matrix.
    // For each column pin...
    for (int pinNumber = 0; pinNumber < MATRIX_COLS; pinNumber++) {
        // set the pinMode to INPUT_PULLUP (+3.3V / HIGH).
        gpio_set_pin_input_high(columns[pinNumber]);
    }
    gpio_set_pin_output(mux_pins[0]);
    gpio_set_pin_output(mux_pins[1]);
    gpio_set_pin_output(mux_pins[2]);
    gpio_set_pin_output(mux_pins[3]);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    // Button Deck
    // Iterate through each of the row pins on the multiplexing chip.
    for (int rowIndex = 0; rowIndex < 14; rowIndex++) {
        gpio_write_pin(mux_pins[0], rowIndex & 1);
        gpio_write_pin(mux_pins[1], (rowIndex & 2) >> 1);
        gpio_write_pin(mux_pins[2], (rowIndex & 4) >> 2);
        gpio_write_pin(mux_pins[3], (rowIndex & 8) >> 3);
        // Now iterate through each of the column pins that are connected to the current row pin.
        for (int columnIndex = 0; columnIndex < MATRIX_COLS; columnIndex++) {
            // Hold the currently selected column pin in a variable.
            pin_t columnPin = columns[columnIndex];
            // Set that row pin to INPUT_PULLUP mode (+3.3V / HIGH).
            gpio_set_pin_input_high(columnPin);
            matrix_io_delay();
            bool previousValue = (current_matrix[rowIndex] >> columnIndex) & 1;
            bool buttonState   = !gpio_read_pin(columnPin); // inverted...
            matrix_has_changed |= previousValue != buttonState;
            if (buttonState) {
                current_matrix[rowIndex] |= (1 << columnIndex);
            } else {
                current_matrix[rowIndex] &= ~(1 << columnIndex);
            }

            // Set the selected column pin back to INPUT mode (0V / LOW).
            gpio_set_pin_input(columnPin);
        }
    }

    return matrix_has_changed;
}
