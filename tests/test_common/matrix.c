/* Copyright 2017 Fred Sundvik
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
#include "test_matrix.h"
#include <string.h>

static matrix_row_t matrix[MATRIX_ROWS] = {};

void matrix_init(void) {
    clear_all_keys();
    matrix_init_kb();
}

uint8_t matrix_scan(void) {
    matrix_scan_kb();
    return 1;
}

matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_print(void) {}

void matrix_init_kb(void) {}

void matrix_scan_kb(void) {}

void press_key(uint8_t col, uint8_t row) {
    matrix[row] |= (matrix_row_t)1 << col;
}

void release_key(uint8_t col, uint8_t row) {
    matrix[row] &= ~((matrix_row_t)1 << col);
}

bool matrix_is_on(uint8_t row, uint8_t col) {
    return (matrix[row] & ((matrix_row_t)1 << col));
}

void clear_all_keys(void) {
    memset(matrix, 0, sizeof(matrix));
}

void led_set(uint8_t usb_led) {}
