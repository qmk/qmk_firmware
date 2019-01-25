/*
Copyright 2014 Kai Ryu <kai1103@gmail.com>

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
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#ifdef UART_RGB_ENABLE
#include "uart_rgb.h"
#endif

#ifndef DEBOUNCE
#   define DEBOUNCE 5
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(void);
static void init_cols(void);
static void init_rows(void);
static void unselect_rows(void);
static void select_row(uint8_t row);

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

#ifdef UART_RGB_ENABLE
    uart_rgb_init();
#endif
    // disable JTAG
    MCUCR = _BV(JTD);
    MCUCR = _BV(JTD);

    // 85 REST
    DDRD |= _BV(PD7);
    PORTD |= _BV(PD7);

    // initialize row and col
    init_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
}

uint8_t matrix_scan(void)
{
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);
        _delay_us(30);  // without this wait read unstable value.
        matrix_row_t cols = read_cols();
        if (matrix_debouncing[i] != cols) {
            matrix_debouncing[i] = cols;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCE;
        }
        unselect_rows();
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
        phex(row); print(": ");
        pbin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop16(matrix[i]);
    }
    return count;
}

/* Column pin configuration
 * col: 0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15
 * pin: F7  F6  F5  F4  F1  F0  E6  D7  D6  D5  D1  D0  B7  B6  B0  C7
 * */
static void  init_cols(void)
{
    // Input with pull-up(DDR:0, PORT:1)
    DDRF &= 0b00001100;
    PORTF |= 0b11110011;

    DDRD &= 0b00011100;
    PORTD |= 0b11100011;

    DDRB &= ~(_BV(PB6) | _BV(PB7)| _BV(PB0));
    PORTB |= (_BV(PB6) | _BV(PB7)| _BV(PB0));

    DDRE &= ~_BV(PE6);
    PORTE |= _BV(PE6);

    DDRC &= ~_BV(PC7);
    PORTC |= _BV(PC7);

}

static matrix_row_t read_cols(void)
{

    return (PINF&_BV(PF7) ? 0 : (1<<0)) |
           (PINF&_BV(PF6) ? 0 : (1<<1)) |
           (PINF&_BV(PF5) ? 0 : (1<<2)) |
           (PINF&_BV(PF4) ? 0 : (1<<3)) |
           (PINF&_BV(PF1) ? 0 : (1<<4)) |
           (PINF&_BV(PF0) ? 0 : (1<<5)) |
           (PINE&_BV(PE6) ? 0 : (1<<6)) |
           (PIND&_BV(PD7) ? 0 : (1<<7)) |
           (PIND&_BV(PD6) ? 0 : (1<<8)) |
           (PIND&_BV(PD5) ? 0 : (1<<9)) |
           (PIND&_BV(PD1) ? 0 : (1<<10)) |
           (PIND&_BV(PD0) ? 0 : (1<<11)) |
           (PINB&_BV(PB7) ? 0 : (1<<12)) |
           (PINB&_BV(PB6) ? 0 : (1<<13)) |
           (PINB&_BV(PB0) ? 0 : (1<<14)) |
           (PINC&_BV(PC7) ? 0 : (1<<15));
}

/* Row pin configuration
 * row:     0   1   2   3   4   5   x
 * pin: B3  0   1   0   1   0   1   1
 *      B2  0   0   1   1   0   0   1
 *      B1  0   0   0   0   1   1   1
 */

static void init_rows(void)
{
     DDRB  |= (1<<PB1 | 1<<PB2 | 1<<PB3);
}

static void unselect_rows(void)
{
    // Hi-Z(DDR:0, PORT:0) to unselect
    PORTB |= (1<<PB1);
    PORTB |= (1<<PB2);
    PORTB |= (1<<PB3);
}

static void select_row(uint8_t row)
{
    // Output low(DDR:1, PORT:0) to select
    (row & (1<<0)) ? (PORTB |= (1<<PB3)) : (PORTB &= ~(1<<PB3));
    (row & (1<<1)) ? (PORTB |= (1<<PB2)) : (PORTB &= ~(1<<PB2));
    (row & (1<<2)) ? (PORTB |= (1<<PB1)) : (PORTB &= ~(1<<PB1));
}
