/*
 * Copyright 2020 Richard Titmuss (richard.titmuss@gmail.com)
 * Copyright 2012-2018 Jun Wako, Jack Humbert, Yiancar
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "mcp2301x.h"

// TODO support ROW2COL

#define PRIMARY_COLS (sizeof(col_pins) / sizeof(pin_t))
#define SECONDARY_COLS (sizeof(secondary_col_pins) / sizeof(mcp2301x_pin_t))

static const pin_t          row_pins[]                 = MATRIX_ROW_PINS;
static const pin_t          col_pins[]                 = MATRIX_COL_PINS;
static const mcp2301x_pin_t secondary_row_pins[]       = MCP2301X_ROW_PINS;
static const mcp2301x_pin_t secondary_col_pins[]       = MCP2301X_COL_PINS;

static void select_row(uint8_t row) {
    setPinOutput(row_pins[row]);
    writePinLow(row_pins[row]);
}

static void unselect_row(uint8_t row) { setPinInputHigh(row_pins[row]); }

static void unselect_rows(void) {
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInputHigh(row_pins[x]);
    }
}

static void select_secondary_row(uint8_t row) { mcp2301x_writePins(~secondary_row_pins[row]); }

static void init_pins(void) {
    unselect_rows();
    for (uint8_t x = 0; x < PRIMARY_COLS; x++) {
        setPinInputHigh(col_pins[x]);
    }
}

static matrix_row_t read_cols(void) {
    matrix_row_t state = 0;

    // For each col...
    for (uint8_t col_index = 0; col_index < PRIMARY_COLS; col_index++) {
        // Select the col pin to read (active low)
        uint8_t pin_state = readPin(col_pins[col_index]);

        // Populate the matrix row with the state of the col pin
        state |= pin_state ? 0 : (MATRIX_ROW_SHIFTER << col_index);
    }

    return state;
}

static matrix_row_t read_secondary_cols(void) {
    matrix_row_t state = 0;

    mcp2301x_pin_t pins;
    if (mcp2301x_readPins(&pins)) {
        return 0;
    }

    for (uint8_t col_index = 0; col_index < SECONDARY_COLS; col_index++) {
        uint16_t pin_state = pins & (secondary_col_pins[col_index]);
        state |= pin_state ? 0 : (MATRIX_ROW_SHIFTER << col_index);
    }

    return state;
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    matrix_row_t last_row_value = current_matrix[current_row];

    select_row(current_row);
    select_secondary_row(current_row);

    current_matrix[current_row] = read_cols() | (read_secondary_cols() << PRIMARY_COLS);

    unselect_row(current_row);

    return (last_row_value != current_matrix[current_row]);
}

void matrix_init_custom(void) { init_pins(); }

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        changed |= read_cols_on_row(current_matrix, current_row);
    }

    return changed;
}
