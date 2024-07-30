/* Copyright 2024 Martin Janů
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
#include "gpio.h"
#include "wait.h"

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

void matrix_init_custom(void) {
    // A multiplexer is connected to the output (row) pins
    for (int i = 0; i < MATRIX_ROWS; i++) {
        gpio_set_pin_output(row_pins[i]);
    }

    for (int i = 0; i < MATRIX_COLS; i++) {
        gpio_set_pin_input_high(col_pins[i]);
    }

    // This pin drives the multiplexer output
    gpio_write_pin_low(row_pins[0]);
}

// Select the active row (KSI) via the MUX
void select_row(uint8_t row) {
    gpio_write_pin(row_pins[1], (row >> 0) & 1);
    gpio_write_pin(row_pins[2], (row >> 1) & 1);
    gpio_write_pin(row_pins[3], (row >> 2) & 1);
    wait_ms(1);
}

// Read the KSO pins
matrix_row_t read_row(void) {
    matrix_row_t row_state = 0;

    for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
        row_state |= !gpio_read_pin(col_pins[col]) << col;
    }

    return row_state;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        matrix_row_t last_state = current_matrix[row];
        select_row(row);
        current_matrix[row] = read_row();
        matrix_has_changed |= last_state != current_matrix[row];
    }

    return matrix_has_changed;
}
