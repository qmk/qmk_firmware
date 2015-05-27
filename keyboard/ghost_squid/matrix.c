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

#ifndef DEBOUNCE
#   define DEBOUNCE 0
#endif
static uint8_t debouncing = DEBOUNCE;

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static uint8_t read_rows(void);
static void init_rows(void);
static void unselect_cols(void);
static void select_col(uint8_t col);

inline uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{
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
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            bool prev_bit = matrix_debouncing[row] & ((matrix_row_t)1<<col);
            bool curr_bit = rows & (1<<row);
            if (prev_bit != curr_bit) {
                matrix_debouncing[row] ^= ((matrix_row_t)1<<col);
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

inline bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline matrix_row_t matrix_get_row(uint8_t row)
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

/* Row pin configuration
 *
 * row: 0    1    2    3    4    5    6    7
 * pin: PB1  PC2  PB6  PB4  PB3  PB5  PB0  PB2
 *
 */
static void init_rows(void)
{
    DDRC &= ~0b00000100;
    DDRB &= ~0b01111111;
    PORTC |= 0b00000100;
    PORTB |= 0b01111111;
}

static uint8_t read_rows(void)
{
    return (PINB&(1<<1) ? 0 : (1<<0)) |
           (PINC&(1<<2) ? 0 : (1<<1)) |
           (PINB&(1<<6) ? 0 : (1<<2)) |
           (PINB&(1<<4) ? 0 : (1<<3)) |
           (PINB&(1<<3) ? 0 : (1<<4)) |
           (PINB&(1<<5) ? 0 : (1<<5)) |
           (PINB&(1<<0) ? 0 : (1<<6)) |
           (PINB&(1<<2) ? 0 : (1<<7));
}

/*  These columns uses two 74HC42 4 to 10 bit demultiplexers (low active).
 *
 *   COL PD6 PD5 PD4 PD3 PD2 PD1
 *   10   1   1   0   0   0   0
 *   15   1   1   0   0   0   1
 *    8   1   1   0   0   1   0
 *   14   1   1   0   1   0   0
 *    6   1   1   0   1   0   1
 *   13   1   1   0   1   1   0
 *   12   1   1   1   0   0   0
 *    9   1   1   1   0   1   0
 *   11   1   1   1   1   0   0
 *    7   1   1   1   1   1   0
 *
 *   COL PD1 PD2 PD3 PD4 PD5 PD6
 *    3   1   1   0   0   0   1
 *    4   1   1   0   0   1   0
 *   17   1   1   0   1   0   0
 *   16   1   1   0   1   1   0
 *    0   1   1   1   0   0   1
 *    5   1   1   1   0   1   0
 *    2   1   1   1   1   0   0
 *    1   1   1   1   1   1   0
 */
static void unselect_cols(void)
{
    DDRD |= 0b01111111;
    PORTD &= ~0b01111111;
}

static void select_col(uint8_t col)
{
    switch (col) {
        case 0:
            PORTD |= (1<<6) | (1<<3) | (1<<2) | (1<<1);
            break;
        case 1:
            PORTD |= (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1);
            break;
        case 2:
            PORTD |= (1<<4) | (1<<3) | (1<<2) | (1<<1);
            break;
        case 3:
            PORTD |= (1<<6) | (1<<2) | (1<<1);
            break;
        case 4:
            PORTD |= (1<<5) | (1<<2) | (1<<1);
            break;
        case 5:
            PORTD |= (1<<5) | (1<<3) | (1<<2) | (1<<1);
            break;
        case 6:
            PORTD |= (1<<6) | (1<<5) | (1<<3) | (1<<1);
            break;
        case 7:
            PORTD |= (1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2);
            break;
        case 8:
            PORTD |= (1<<6) | (1<<5) | (1<<2);
            break;
        case 9:
            PORTD |= (1<<6) | (1<<5) | (1<<4) | (1<<2);
            break;
        case 10:
            PORTD |= (1<<6) | (1<<5);
            break;
        case 11:
            PORTD |= (1<<6) | (1<<5) | (1<<4) | (1<<3);
            break;
        case 12:
            PORTD |= (1<<6) | (1<<5) | (1<<4);
            break;
        case 13:
            PORTD |= (1<<6) | (1<<5) | (1<<3) | (1<<2);
            break;
        case 14:
            PORTD |= (1<<6) | (1<<5) | (1<<3);
            break;
        case 15:
            PORTD |= (1<<6) | (1<<5) | (1<<1);
            break;
        case 16:
            PORTD |= (1<<5) | (1<<4) | (1<<2) | (1<<1);
            break;
        case 17:
            PORTD |= (1<<4) | (1<<2) | (1<<1);
            break;
    }
}
