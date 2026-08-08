// Copyright 2021 JasonRen(biu)
// Copyright 2026 Steffen Olszewski (@sodevel)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "matrix.h"

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

static void select_row(uint8_t row) {
    palSetLine(row_pins[row]);
}

static void unselect_row(uint8_t row) {
    palClearLine(row_pins[row]);
}

static void unselect_cols(void) {
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        palSetLineMode(col_pins[x], PAL_MODE_INPUT_PULLDOWN);
    }
}

static void init_pins(void) {
    unselect_cols();
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        palSetLineMode(row_pins[x], PAL_MODE_OUTPUT_PUSHPULL);
    }
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        palClearLine(row_pins[x]);
    }
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;

    // Select row
    select_row(current_row);
    matrix_output_select_delay();

    // For each col...
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
        // Select the col pin to read (active low)
        uint8_t pin_state = gpio_read_pin(col_pins[col_index]);

        // Populate the matrix row with the state of the col pin
        current_row_value |= pin_state ? (MATRIX_ROW_SHIFTER << col_index) : 0;
    }

    // Unselect row
    unselect_row(current_row);
    matrix_output_unselect_delay(current_row, current_row_value != 1); // wait for all Col signals to go HIGH

    // If the row has changed, store the row and return the changed flag.
    if (current_matrix[current_row] != current_row_value) {
        current_matrix[current_row] = current_row_value;
        return true;
    }

    return false;
}

void matrix_init_custom(void) {
    // initialize key pins
    init_pins();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        changed |= read_cols_on_row(current_matrix, current_row);
    }

    return changed;
}
