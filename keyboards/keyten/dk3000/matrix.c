// Copyright 2026 key10iq
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "matrix.h"

#define MUX_PIN_A A9
#define MUX_PIN_B C9
#define MUX_PIN_C C8
#define MUX_PIN_COM A8

#define DIRECT_ROW_PIN A10

static const pin_t col_pins[MATRIX_COLS] = {
    A5, A7, C5, B1, B0, C4, A6, A4, C1, B9, B8, B6, B4, D2, C11, A15, A14, C10, C12, B3, B5, B7, C2, C0
};

static const uint8_t mux_channel_to_row[8] = {
    5, // Ch0 -> Row5
    6, // Ch1 -> Row6
    7, // Ch2 -> Row7
    4, // Ch3 -> Row4
    2, // Ch4 -> Row2
    1, // Ch5 -> Row1
    0, // Ch6 -> Row0
    3  // Ch7 -> Row3
};

static void select_mux_channel(uint8_t channel) {
    channel &= 0x07;
    gpio_write_pin(MUX_PIN_A, channel & 0x01);
    gpio_write_pin(MUX_PIN_B, channel & 0x02);
    gpio_write_pin(MUX_PIN_C, channel & 0x04);
    wait_us(2);
}

static void enable_direct_row(void) {
    gpio_set_pin_output(DIRECT_ROW_PIN);
    gpio_write_pin_low(DIRECT_ROW_PIN);
    wait_us(2);
}

static void disable_direct_row(void) {
    gpio_write_pin_high(DIRECT_ROW_PIN);
    gpio_set_pin_input_high(DIRECT_ROW_PIN);
}

void matrix_init_custom(void) {
    gpio_set_pin_output(MUX_PIN_A);
    gpio_set_pin_output(MUX_PIN_B);
    gpio_set_pin_output(MUX_PIN_C);
    gpio_set_pin_output(MUX_PIN_COM);

    gpio_set_pin_input_high(DIRECT_ROW_PIN);

    for (uint8_t i = 0; i < MATRIX_COLS; i++) {
        gpio_set_pin_input_high(col_pins[i]);
    }

    gpio_write_pin_high(MUX_PIN_COM);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    for (uint8_t mux_channel = 0; mux_channel < 8; mux_channel++) {
        select_mux_channel(mux_channel);

        gpio_write_pin_low(MUX_PIN_COM);
        wait_us(5);

        uint8_t logical_row = mux_channel_to_row[mux_channel];
        matrix_row_t new_row_value = 0;

        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            if (gpio_read_pin(col_pins[col]) == 0) {
                new_row_value |= (1UL << col);
            }
        }

        gpio_write_pin_high(MUX_PIN_COM);

        if (current_matrix[logical_row] != new_row_value) {
            current_matrix[logical_row] = new_row_value;
            matrix_has_changed = true;
        }
    }

    enable_direct_row();
    wait_us(5);

    matrix_row_t new_direct_row_value = 0;
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        if (gpio_read_pin(col_pins[col]) == 0) {
            new_direct_row_value |= (1UL << col);
        }
    }

    disable_direct_row();

    if (current_matrix[8] != new_direct_row_value) {
        current_matrix[8] = new_direct_row_value;
        matrix_has_changed = true;
    }

    return matrix_has_changed;
}
