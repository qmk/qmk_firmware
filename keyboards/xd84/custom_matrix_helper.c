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
#include <stdint.h>
#include <stdbool.h>
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"

//_____COULD BE COMMON_________________________________________________________
/* matrix state(1:on, 0:off) */
/*static*/ matrix_row_t raw_matrix[MATRIX_ROWS];
/*static*/ matrix_row_t matrix[MATRIX_ROWS];

__attribute__ ((weak))
matrix_row_t matrix_get_row(uint8_t row) {
  return matrix[row];
}

//_____CUSTOM MATRIX 'LITE'____________________________________________________
__attribute__ ((weak))
void custom_matrix_init(void) {
}

__attribute__ ((weak))
bool custom_matrix_scan(matrix_row_t current_matrix[]) {
    bool changed = true;
    return changed;
}

__attribute__ ((weak))
void matrix_init(void) {

  custom_matrix_init();

  // initialize matrix state: all keys off
  for (uint8_t i=0; i < MATRIX_ROWS; i++) {
    raw_matrix[i] = 0;
    matrix[i] = 0;
  }

  debounce_init(MATRIX_ROWS);

  matrix_init_quantum();
}

__attribute__ ((weak))
uint8_t matrix_scan(void) {
  bool changed = custom_matrix_scan(raw_matrix);

  debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

  matrix_scan_quantum();
  return 1;
}
