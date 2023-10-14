// Copyright 2023 Mathias Andersson (@Wraul)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "matrix.h"
#include "wait.h"

void pulse_registers(void) {
    gpio_write_pin_high(B1);
    asm("nop");
    gpio_write_pin_low(B1);
}

void matrix_read_mode(void) {
    gpio_set_pin_input_high(B3);
    wait_us(5);
}

void matrix_write_mode(void) {
    gpio_set_pin_output(B3);
}

void reset_registers(void) {
    matrix_write_mode();
    for (uint8_t i = 0; i < 40; i++) {
        gpio_write_pin_high(B3);
        pulse_registers();
    }
    gpio_write_pin_low(B3);
    pulse_registers();
    matrix_read_mode();
}

void shift_registers(void) {
    matrix_write_mode();
    gpio_write_pin_high(B3);
    pulse_registers();
    matrix_read_mode();
}

void matrix_init_custom(void) {
    gpio_set_pin_output(B1);
    gpio_set_pin_input_high(B2);
    gpio_set_pin_output(B3);

    gpio_write_pin_high(B1);
    gpio_write_pin_high(B3);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool         matrix_has_changed = false;
    matrix_row_t current_row_value;

    reset_registers();

    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        current_row_value = 0;

        for (uint8_t current_col = 0; current_col < MATRIX_COLS / 2; current_col++) {
            /* Left hand scan (Bank U1) */
            if (!gpio_read_pin(B3)) {
                current_row_value |= (matrix_row_t)1 << current_col;
            }
            /* Right hand scan (Bank U2) */
            if (!gpio_read_pin(B2)) {
                current_row_value |= (matrix_row_t)1 << (current_col + 8);
            }
            shift_registers();
        }

        if (current_matrix[current_row] != current_row_value) {
            current_matrix[current_row] = current_row_value;
            matrix_has_changed          = true;
        }
    }

    return matrix_has_changed;
}
