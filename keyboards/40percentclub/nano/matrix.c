/*

Note for ErgoDox EZ customizers: Here be dragons!
This is not a file you want to be messing with.
All of the interesting stuff for you is under keymaps/ :)
Love, Erez

Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>

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

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "nano.h"
#include <string.h>

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_stage[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static uint16_t debouncing_time;
static bool debouncing = false;

__attribute__ ((weak))
void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{

    DDRF  &= ~(1<<4 | 1<<5 | 1<<6 | 1<<7);
    PORTF |=  (1<<4 | 1<<5 | 1<<6 | 1<<7);
    DDRC  &= ~(1<<6);
    PORTC |=  (1<<6);
    DDRD  &= ~(1<<0 | 1<<1 | 1<<4);
    PORTD |=  (1<<0 | 1<<1 | 1<<4);

    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
        matrix_stage[i] = 0;
    }

    matrix_init_quantum();

}

uint8_t matrix_scan(void)
{
    matrix_stage[0] =
        (PINF&(1<<4) ? 0 : (1<<0)) |
        (PINF&(1<<5) ? 0 : (1<<1)) |
        (PINF&(1<<6) ? 0 : (1<<2)) |
        (PINF&(1<<7) ? 0 : (1<<3));
    matrix_stage[1] =
        (PIND&(1<<1) ? 0 : (1<<0)) |
        (PIND&(1<<0) ? 0 : (1<<1)) |
        (PIND&(1<<4) ? 0 : (1<<2)) |
        (PINC&(1<<6) ? 0 : (1<<3));

    if (memcmp(matrix_debouncing, matrix_stage, sizeof(matrix)) != 0) {
        debouncing = true;
        debouncing_time = timer_read();
    }

    matrix_debouncing[0] = matrix_stage[0];
    matrix_debouncing[1] = matrix_stage[1];

    if (debouncing && (timer_elapsed(debouncing_time) > 20)) {
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
            matrix[i] = matrix_debouncing[i];
        }
        debouncing = false;
    }

    matrix_scan_quantum();

    return 1;
}

bool matrix_is_modified(void)
{
    return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop16(matrix[i]);
    }
    return count;
}

