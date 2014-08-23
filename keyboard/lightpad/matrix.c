/*
Copyright 2014 Ralf Schmitt <ralf@bunkertor.net>

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

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "eeconfig.h"
#include "action_layer.h"
#include "backlight.h"

#ifndef DEBOUNCE
#   define DEBOUNCE 0
#endif
static uint8_t debouncing = DEBOUNCE;

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static uint8_t read_rows(void);
static uint8_t read_fwkey(void);
static void init_rows(void);
static void unselect_cols(void);
static void select_col(uint8_t col);

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

void misc_init(void) {
}

void matrix_init(void)
{
    backlight_init_ports();
    unselect_cols();
    init_rows();
    for (uint8_t i=0; i < MATRIX_ROWS; i++)  {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
}

uint8_t matrix_scan(void)
{
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        select_col(col);
        _delay_us(3);
        uint8_t rows = read_rows();
        // Use the otherwise unused col: 0 row: 0 for firmware key
        if(col == 0) {
            rows |= read_fwkey();
        }
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            bool prev_bit = matrix_debouncing[row] & ((matrix_row_t)1<<col);
            bool curr_bit = rows & (1<<row);
            if (prev_bit != curr_bit) {
                matrix_debouncing[row] ^= ((matrix_row_t)1<<col);
                if (debouncing) {
                    dprint("bounce!: "); dprintf("%02X", debouncing); dprintln();
                }
                debouncing = DEBOUNCE;
            }
        }
        unselect_cols();
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }

    return 1;
}

bool matrix_is_modified(void)
{
    if (debouncing) return false;
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
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        xprintf("%02X: %032lb\n", row, bitrev32(matrix_get_row(row)));
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop32(matrix[i]);
    }
    return count;
}

/* Row configuration
 *
 * row: 0    1    2    3    4    5
 * pin: PD0  PD1  PD2  PD3  PD5  PB7
 *
 * Firmware uses pin PE2
 */
static void init_rows(void)
{
    DDRD  &= ~0b00101111;
    PORTD |=  0b00101111;

    DDRB  &= ~0b10000000;
    PORTB |=  0b10000000;

    DDRE  &= ~0b00000100;
    PORTE |=  0b00000100;
}

static uint8_t read_rows(void)
{
    return (PIND&(1<<0) ? (1<<0) : 0) |
           (PIND&(1<<1) ? (1<<1) : 0) |
           (PIND&(1<<2) ? (1<<2) : 0) |
           (PIND&(1<<3) ? (1<<3) : 0) |
           (PIND&(1<<5) ? (1<<4) : 0) |
           (PINB&(1<<7) ? (1<<5) : 0);
}

static uint8_t read_fwkey(void)
{
    return PINE&(1<<2) ? 0 : (1<<0);
}

/* Column configuration
 *
 * col: 0    1    2    3
 * pin: PF0  PF1  PC7  PC6
 */
static void unselect_cols(void)
{
    DDRF |=   0b00000011;
    PORTF &= ~0b00000011;
    DDRC |=   0b11000000;
    PORTC &= ~0b11000000;
}

static void select_col(uint8_t col)
{
    switch (col) {
        case 0:
            PORTF |= (1<<0);
            break;
        case 1:
            PORTF |= (1<<1);
            break;
        case 2:
            PORTC |= (1<<7);
            break;
        case 3:
            PORTC |= (1<<6);
            break;
    }
}
