// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "matrix.h"

static matrix_row_t read_row(uint8_t row) {
    matrix_io_delay();  // without this wait read unstable value.

    // keypad and program buttons
    if (row == 12) {
        return ~(gpio_read_pin(B4) | (gpio_read_pin(B5) << 1) | 0b11111100);
    }

    return ~(gpio_read_pin(B6) | gpio_read_pin(B2) << 1 | gpio_read_pin(B3) << 2 | gpio_read_pin(B1) << 3 | gpio_read_pin(F7) << 4 | gpio_read_pin(F6) << 5 | gpio_read_pin(F5) << 6 | gpio_read_pin(F4) << 7);
}

static void unselect_rows(void) {
    // set A,B,C,G to 0
    PORTD &= 0xF0;
}

static void select_rows(uint8_t row) {
    // set A,B,C,G to row value
    PORTD |= (0x0F & row);
}

void matrix_init_custom(void) {
    // output low (multiplexers)
    gpio_set_pin_output(D0);
    gpio_set_pin_output(D1);
    gpio_set_pin_output(D2);
    gpio_set_pin_output(D3);

    // input with pullup (matrix)
    gpio_set_pin_input_high(B6);
    gpio_set_pin_input_high(B2);
    gpio_set_pin_input_high(B3);
    gpio_set_pin_input_high(B1);
    gpio_set_pin_input_high(F7);
    gpio_set_pin_input_high(F6);
    gpio_set_pin_input_high(F5);
    gpio_set_pin_input_high(F4);

    // input with pullup (program and keypad buttons)
    gpio_set_pin_input_high(B4);
    gpio_set_pin_input_high(B5);

    // initialize row and col
    unselect_rows();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_rows(i);
        matrix_row_t row = read_row(i);
        unselect_rows();
        bool row_has_changed = current_matrix[i] != row;
        matrix_has_changed |= row_has_changed;
        current_matrix[i] = row;
    }

    return matrix_has_changed;
}
