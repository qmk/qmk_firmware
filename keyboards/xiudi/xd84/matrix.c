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
    // init all cols high - IC2 all input
    pca9555_set_config(IC2, PCA9555_PORT0, ALL_INPUT);  // same as initial state
    pca9555_set_config(IC2, PCA9555_PORT1, ALL_INPUT);  // same as initial state

    // init all rows - IC1 port0 input
    pca9555_set_config(IC1, PCA9555_PORT0, ALL_INPUT);  // same as initial state
    pca9555_set_output(IC1, PCA9555_PORT0, ALL_LOW);
}

static void select_row(uint8_t row) {
    // For the XD84 all rows are on the same IC and port
    // so its safe enough to assume here row == pin
    uint8_t pin  = row;
    uint8_t mask = 1 << pin;

    // we configure output once in init, as pca9555 remembers state when flipping between input/output 
    // pca9555_set_output(IC1, PCA9555_PORT0, ALL_HIGH & (~mask));
    pca9555_set_config(IC1, PCA9555_PORT0, ALL_INPUT & (~mask));
}

static uint16_t read_cols(void) {
    // uint16_t state_1 = pca9555_read_pins(IC2, PCA9555_PORT0);
    // uint16_t state_2 = pca9555_read_pins(IC2, PCA9555_PORT1);
    uint16_t state = 0;
    pca9555_read_pins_all(IC2, &state);

    // For the XD84 all cols are on the same IC and mapped sequentially
    // while this technically gives 16 column reads,
    // the 16th column can never be set so is safely ignored
    // return ~((state_2 << 8) | state_1);
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
