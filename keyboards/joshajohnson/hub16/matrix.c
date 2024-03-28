/*
Copyright 2012-2018 Jun Wako, Jack Humbert, Yiancar

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "wait.h"
#include "util.h"
#include "matrix.h"

// Encoder things
#define SWITCH_1 F7
#define SWITCH_2 D7
static bool read_encoder_switches(matrix_row_t current_matrix[], uint8_t current_row);

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

/* matrix state(1:on, 0:off) */
extern matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
extern matrix_row_t matrix[MATRIX_ROWS];      // debounced values

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

static void init_pins(void) {
    unselect_rows();
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinInputHigh(col_pins[x]);
    }
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Store last value of row prior to reading
    matrix_row_t last_row_value = current_matrix[current_row];

    // Clear data in matrix row
    current_matrix[current_row] = 0;

    // Select row and wait for row selecton to stabilize
    select_row(current_row);
    wait_us(30);

    // For each col...
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
        // Select the col pin to read (active low)
        uint8_t pin_state = readPin(col_pins[col_index]);

        // Populate the matrix row with the state of the col pin
        current_matrix[current_row] |= pin_state ? 0 : (MATRIX_ROW_SHIFTER << col_index);
    }

    // Unselect row
    unselect_row(current_row);

    return (last_row_value != current_matrix[current_row]);
}


void matrix_init_custom(void) {
    // initialize key pins
    setPinInput(SWITCH_1);
    setPinInput(SWITCH_2);
    init_pins();
}

bool matrix_scan_custom(void) {
    bool changed = false;

    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        changed |= read_cols_on_row(raw_matrix, current_row);
    }

    // Read encoder switches, already debounced
    changed |= read_encoder_switches(matrix, 4);

    return changed;
}

static bool read_encoder_switches(matrix_row_t current_matrix[], uint8_t current_row) {
    // Store last value of row prior to reading
    matrix_row_t last_row_value = current_matrix[current_row];

    // Clear data in matrix row
    current_matrix[current_row] = 0;

    // Debounce the encoder buttons using a shift register
    static uint8_t btn_1_array;
    static uint8_t btn_2_array;
    bool           btn_1_rise = 0;
    bool           btn_2_rise = 0;
    btn_1_array <<= 1;
    btn_2_array <<= 1;
    btn_1_array |= readPin(SWITCH_1);
    btn_2_array |= readPin(SWITCH_2);
    (btn_1_array == 0b01111111) ? (btn_1_rise = 1) : (btn_1_rise = 0);
    (btn_2_array == 0b01111111) ? (btn_2_rise = 1) : (btn_2_rise = 0);

    // Populate the matrix row with the state of the encoder
    current_matrix[current_row] |= btn_1_rise ? (1 << 0) : 0;
    current_matrix[current_row] |= btn_2_rise ? (1 << 1) : 0;

    return (last_row_value != current_matrix[current_row]);
}
