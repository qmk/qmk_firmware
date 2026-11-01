// Copyright 2026 Andreas Hirschauer
// SPDX-License-Identifier: GPL-2.0-or-later

#include "matrix.h"

#include "gpio.h"
#include "wait.h"

// Active-high columns and pull-down rows require a custom scanner.
static const pin_t row_pins[MATRIX_ROWS] = {
    GP23, GP22, GP21, GP20, GP19, GP18,
};

static const pin_t col_pins[MATRIX_COLS] = {
    GP6, GP7, GP8, GP9, GP10, GP11, GP12, GP13, GP14, GP15, GP16, GP17, GP3, GP2,
};

void matrix_init_custom(void) {
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        gpio_set_pin_output(col_pins[col]);
        gpio_write_pin_low(col_pins[col]);
    }

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        gpio_set_pin_input_low(row_pins[row]);
    }
}

// Map alternate Enter and centre Space contacts to their layout positions.
static void fold_duplicate_positions(matrix_row_t rows[]) {
    if (rows[3] & MATRIX_ROW_SHIFTER << 13) {
        rows[3] = (rows[3] & ~(MATRIX_ROW_SHIFTER << 13)) | MATRIX_ROW_SHIFTER << 12;
    }
    if (rows[5] & MATRIX_ROW_SHIFTER << 5) {
        rows[5] = (rows[5] & ~(MATRIX_ROW_SHIFTER << 5)) | MATRIX_ROW_SHIFTER << 4;
    }
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    matrix_row_t rows[MATRIX_ROWS] = {0};

    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        gpio_write_pin_high(col_pins[col]);
        matrix_io_delay();

        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            if (gpio_read_pin(row_pins[row])) {
                rows[row] |= MATRIX_ROW_SHIFTER << col;
            }
        }

        gpio_write_pin_low(col_pins[col]);
    }

    fold_duplicate_positions(rows);

    bool changed = false;
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        changed |= current_matrix[row] != rows[row];
        current_matrix[row] = rows[row];
    }
    return changed;
}
