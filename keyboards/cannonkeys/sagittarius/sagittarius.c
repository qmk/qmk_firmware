// Copyright 2024 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

#if defined(ENCODER_ENABLE) || defined(ENCODER_MAP_ENABLE)

#    if !defined(ENCODER_SETTLE_PIN_STATE_DELAY_US)
#        define ENCODER_SETTLE_PIN_STATE_DELAY_US 2
#    endif

static pin_t matrix_row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

void encoder_driver_task(void) {
    // Set all relevant rows to output, which is different to the matrix expectations
    for (uint8_t i = 0; i < 4; i++) {
        gpio_set_pin_output(matrix_row_pins[i]);
    }

    // Read each encoder
    for (uint8_t i = 0; i < 4; i++) {
        // Set the row pin low for the corresponding encoder...
        for (uint8_t j = 0; j < 4; j++) {
            gpio_write_pin(matrix_row_pins[j], (i == j) ? 0 : 1);
        }
        // ...and let them settle.
        wait_us(ENCODER_SETTLE_PIN_STATE_DELAY_US);

        // Run the normal encoder handling
        extern void encoder_quadrature_handle_read(uint8_t index, uint8_t pin_a_state, uint8_t pin_b_state);
        extern uint8_t encoder_quadrature_read_pin(uint8_t index, bool pad_b);
        encoder_quadrature_handle_read(i, encoder_quadrature_read_pin(i, false), encoder_quadrature_read_pin(i, true));
    }

    // Set all rows back to input-high as per matrix expectations
    for (uint8_t i = 0; i < 4; i++) {
        gpio_set_pin_input_high(matrix_row_pins[i]);
    }
}

#endif // defined(ENCODER_ENABLE) || defined(ENCODER_MAP_ENABLE)
