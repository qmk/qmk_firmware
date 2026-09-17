/* Copyright 2022 durken (https://github.com/durken1/)
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
#include "i2c_slave.h"

#define MY_I2C_ADDRESS (0x20U << 1)

void matrix_init_custom(void) {
    i2c_slave_init(MY_I2C_ADDRESS);
}


bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;
    matrix_row_t current_row_value;

    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        current_row_value = 0; // Start with empty row
        current_row_value |= (((matrix_row_t)(i2c_slave_reg[current_row+4])) << 5); // Add left half scan
        current_row_value |= ((matrix_row_t)i2c_slave_reg[current_row]); // Add right half scan

        if (current_matrix[current_row] != current_row_value) {
            matrix_has_changed = true;
        }
        current_matrix[current_row] = current_row_value;
    }

    return matrix_has_changed;
}
