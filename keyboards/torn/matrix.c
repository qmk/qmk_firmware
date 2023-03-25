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

#include "matrix.h"
#include "mcp23018.h"

#define SPLIT_MATRIX_COLS (MATRIX_COLS / 2)
#define SECONDARY_ROW_OFFSET (MATRIX_ROWS / 2)

typedef uint16_t mcp23018_pin_t;

static const pin_t          row_pins[MATRIX_ROWS]                 = MATRIX_ROW_PINS;
static const pin_t          col_pins[SPLIT_MATRIX_COLS]           = MATRIX_COL_PINS;
static const mcp23018_pin_t secondary_row_pins[MATRIX_ROWS]       = SECONDARY_ROW_PINS;
static const mcp23018_pin_t secondary_col_pins[SPLIT_MATRIX_COLS] = SECONDARY_COL_PINS;

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

static void select_secondary_row(uint8_t row) {
    uint8_t gpioa = 0xFF & ~secondary_row_pins[row];
    mcp23018_writeReg(GPIOA, &gpioa, 1);
}

static void init_pins(void) {
    unselect_rows();
    for (uint8_t x = 0; x < SPLIT_MATRIX_COLS; x++) {
        setPinInputHigh(col_pins[x]);
    }
}

static matrix_row_t read_cols(void) {
    matrix_row_t state = 0;

    // For each col...
    for (uint8_t col_index = 0; col_index < SPLIT_MATRIX_COLS; col_index++) {
        // Select the col pin to read (active low)
        uint8_t pin_state = readPin(col_pins[col_index]);

        // Populate the matrix row with the state of the col pin
        state |= pin_state ? 0 : (MATRIX_ROW_SHIFTER << col_index);
    }

    return state;
}

static matrix_row_t read_secondary_cols(void) {
    matrix_row_t state = 0;

    uint8_t mcp23018_pin_state[2];
    if (mcp23018_readReg(GPIOA, mcp23018_pin_state, 2)) {
        return 0;
    }

    uint16_t pins = mcp23018_pin_state[0] | (mcp23018_pin_state[1] << 8);

    for (uint8_t col_index = 0; col_index < SPLIT_MATRIX_COLS; col_index++) {
        uint16_t pin_state = pins & (secondary_col_pins[col_index]);
        state |= pin_state ? 0 : (MATRIX_ROW_SHIFTER << col_index);
    }

    return state;
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    matrix_row_t last_row_value = current_matrix[current_row];

    select_row(current_row);
    select_secondary_row(current_row);

    current_matrix[current_row] = read_cols() | (read_secondary_cols() << 6);

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
