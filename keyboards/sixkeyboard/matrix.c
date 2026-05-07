/*

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
#include "timer.h"
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
    gpio_set_pin_input_high(C7);
    gpio_set_pin_input_high(B5);
    gpio_set_pin_input_high(B7);
    gpio_set_pin_input_high(D1);
    gpio_set_pin_input_high(D4);
    gpio_set_pin_input_high(D6);

    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
        matrix_stage[i] = 0;
    }

    matrix_init_kb();

}

uint8_t matrix_scan(void)
{
    matrix_stage[0] = (PINC&(1<<7) ? 0 : (1<<0)) | (PINB&(1<<7) ? 0 : (1<<1)) | (PINB&(1<<5) ? 0 : (1<<2));
    matrix_stage[1] = (PIND&(1<<6) ? 0 : (1<<0)) | (PIND&(1<<1) ? 0 : (1<<1)) | (PIND&(1<<4) ? 0 : (1<<2));

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

    matrix_scan_kb();

    return 1;
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
