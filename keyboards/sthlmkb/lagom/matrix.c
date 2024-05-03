/* Copyright 2022 mohoyt
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
#include "wait.h"

#define COL_SHIFTER ((uint32_t)1)

// Column pins
static const uint8_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const uint8_t col_pins[MATRIX_MUX_COLS] = MATRIX_COL_MUX_PINS;

// Internal functions

static void init_pins(void) {
    // Set cols to outputs, low
    for (uint8_t pin = 0; pin < MATRIX_MUX_COLS; pin++) {
        gpio_set_pin_output(col_pins[pin]);
    }

    // Unselect cols
    for (uint8_t bit = 0; bit < MATRIX_MUX_COLS; bit++) {
        gpio_write_pin_low(col_pins[bit]);
    }

    // Set rows to input, pullup
    for (uint8_t pin = 0; pin < MATRIX_ROWS; pin++) {
        gpio_set_pin_input_high(row_pins[pin]);
    }
}

static void select_col(uint8_t col)
{
    for (uint8_t bit = 0; bit < MATRIX_MUX_COLS; bit++) {
        uint8_t state = (col & (0b1 << bit)) >> bit;
        gpio_write_pin(col_pins[bit], state);
    }
}

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col)
{
    bool matrix_changed = false;
    select_col(current_col);
    wait_us(5);

    // Read each row sequentially
    for(uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++)
    {
        matrix_row_t last_row_value = current_matrix[row_index];

        if (!gpio_read_pin(row_pins[row_index]))
        {
            current_matrix[row_index] |= (COL_SHIFTER << current_col);
        }
        else
        {
            current_matrix[row_index] &= ~(COL_SHIFTER << current_col);
        }

        if ((last_row_value != current_matrix[row_index]) && !(matrix_changed))
        {
            matrix_changed = true;
        }
    }

    return matrix_changed;
}

// Matrix scan functions

void matrix_init_custom(void) {
    init_pins();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    //Set col, read rows
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        changed |= read_rows_on_col(current_matrix, current_col);
    }

    return (uint8_t)changed;
}
