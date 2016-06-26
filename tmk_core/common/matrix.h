/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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
#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>
#include <stdbool.h>

#if MATRIX_COLS <= 8
typedef uint8_t matrix_row_t;
#elif MATRIX_COLS <= 16
typedef uint16_t matrix_row_t;
#elif MATRIX_COLS <= 32
typedef uint32_t matrix_row_t;
#else
#   error "There are too many columns."
#endif

#if DIODE_DIRECTION == ROW2COL
#   if MATRIX_ROWS <= 8
typedef uint8_t matrix_col_t;
#   elif MATRIX_ROWS <= 16
typedef uint16_t matrix_col_t;
#   elif MATRIX_ROWS <= 32
typedef uint32_t matrix_col_t;
#   else
#       error "There are too many rows."
#   endif
#endif

typedef struct {
    uint8_t input_addr:4;
    uint8_t bit:4;
} io_pin_t;

#ifdef __cplusplus
extern "C" {
#endif
/* counts the number of rows in the matrix */
uint8_t matrix_rows(void);
/* counts the number of columns in the matrix */
uint8_t matrix_cols(void);
/* sets up the matrix before matrix_init */
void matrix_setup(void);
/* intializes the matrix */
void matrix_init(void);
/* scans the entire matrix */
uint8_t matrix_scan(void);
/* checks if the matrix has been modified */
bool matrix_is_modified(void) __attribute__ ((deprecated));
/* checks if a key is pressed */
bool matrix_is_on(uint8_t row, uint8_t col);
/* inspects the state of a row in the matrix */
matrix_row_t matrix_get_row(uint8_t row);
/* prints the matrix for debugging */
void matrix_print(void);
/* counts the total number of keys pressed */
uint8_t matrix_key_count(void);
/* controls power to the matrix */
void matrix_power_up(void);
void matrix_power_down(void);
/* executes code for Quantum */
void matrix_init_quantum(void);
void matrix_scan_quantum(void);

void matrix_init_kb(void);
void matrix_scan_kb(void);

void matrix_init_user(void);
void matrix_scan_user(void);

#ifdef __cplusplus
}
#endif

#endif
