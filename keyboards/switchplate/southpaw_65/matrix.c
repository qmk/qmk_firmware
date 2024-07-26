/* Copyright 2019
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
#include "pca9555.h"

// PCA9555 slave addresses
#define IC1 0x20
#define IC2 0x21

//_____Utility funcs___________________________________________________________

static void init_pins(void) {
    // init all rows - IC1 port0 input
    pca9555_set_config(IC1, PCA9555_PORT0, ALL_INPUT);  // same as initial state

    // init all cols high - IC2 all input
    pca9555_set_config(IC1, PCA9555_PORT1, ALL_INPUT);  // same as initial state
    pca9555_set_config(IC2, PCA9555_PORT0, ALL_INPUT);  // same as initial state
    pca9555_set_config(IC2, PCA9555_PORT1, ALL_INPUT);  // same as initial state
    
    pca9555_set_output(IC1, PCA9555_PORT0, ALL_LOW);
}

static void select_row(uint8_t row) {
    // For the Southpaw Ext 65% pins 1-6 are used for the rows
    uint8_t pin  = row;
    uint8_t mask = 2 << pin;

    pca9555_set_config(IC1, PCA9555_PORT0, ALL_INPUT & (~mask));
}

static uint32_t read_cols(void) {
    //Read column inputs. Pins 13-31 are used. Split across both ICs but they are sequential
    uint8_t state_1 = 0;
    uint8_t state_2 = 0;
    uint8_t state_3 = 0;
    pca9555_read_pins(IC1, PCA9555_PORT1, &state_1);
    pca9555_read_pins(IC2, PCA9555_PORT0, &state_2);
    pca9555_read_pins(IC2, PCA9555_PORT1, &state_3);

    uint32_t state = ((((uint32_t)state_3 & 0b01111111) << 12) | ((uint32_t)state_2 << 4) | (((uint32_t)state_1 & 0b11110000) >> 4));
    return ~state;
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Store last value of row prior to reading
    matrix_row_t last_row_value = current_matrix[current_row];

    // Clear data in matrix row
    current_matrix[current_row] = 0;

    // Select row and wait for row selection to stabilize
    select_row(current_row);
    // Skip the wait_us(30); as i2c is slow enough to debounce the io changes

    current_matrix[current_row] = read_cols();

    // No need to Unselect row as the next `select_row` will blank everything

    return (last_row_value != current_matrix[current_row]);
}

//_____CUSTOM MATRIX IMPLEMENTATION____________________________________________________

void matrix_init_custom(void) {
    pca9555_init(IC1);
    pca9555_init(IC2);

    init_pins();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        changed |= read_cols_on_row(current_matrix, current_row);
    }
    return changed;
}
