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

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"

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

inline uint8_t matrix_rows(void) {
    return MATRIX_ROWS;
}

inline uint8_t matrix_cols(void) {
    return MATRIX_COLS;
}

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

void matrix_init(void) {
    // disable JTAG
    MCUCR = (1<<JTD);
    MCUCR = (1<<JTD);

    // initialize row and col
    init_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
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
    matrix_scan_quantum();
    return 1;
}

bool matrix_is_modified(void) {
    if (debouncing) return false;
    return true;
}

inline bool matrix_is_on(uint8_t row, uint8_t col) {
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_print(void) {
  print("\nr/c 0123456789ABCDEF\n");
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    xprintf("%02X: %032lb\n", row, bitrev32(matrix_get_row(row)));
  }
}

uint8_t matrix_key_count(void) {
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop16(matrix[i]);
    }
    return count;
}

/* Column pin configuration
 * col:  0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17
 * pin: PF4  PF5  PF6  PF7  PC7  PC6  PB6  PB5  PB4  PD7  PD6  PD4  PD5  PD3  PB3  PB2  PB1  PB0
 */
static void  init_cols(void) {
    // Input with pull-up(DDR:0, PORT:1)
    DDRF  &= ~(1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
    PORTF |=  (1<<PF7 | 1<<PF6 | 1<<PF5 | 1<<PF4);
    DDRD  &= ~(1<<PD7 | 1<<PD6 | 1<<PD5 | 1<<PD4 | 1<<PD3);
    PORTD |=  (1<<PD7 | 1<<PD6 | 1<<PD5 | 1<<PD4 | 1<<PD3);
    DDRC  &= ~(1<<PC7 | 1<<PC6);
    PORTC |=  (1<<PC7 | 1<<PC6);
    DDRB  &= ~(1<<PB6 | 1<<PB5 | 1<<PB4 | 1<<PB3 | 1<<PB2| 1<<PB1| 1<<PB0);
    PORTB |=  (1<<PB6 | 1<<PB5 | 1<<PB4 | 1<<PB3 | 1<<PB2| 1<<PB1| 1<<PB0);
}

static matrix_row_t read_cols(void) {
    return (PINF&(1<<4) ? 0 : (1<<0)) |
           (PINF&(1<<5) ? 0 : (1<<1)) |
           (PINF&(1<<6) ? 0 : (1<<2)) |
           (PINF&(1<<7) ? 0 : (1<<3)) |
           (PINC&(1<<7) ? 0 : (1<<4)) |
           (PINC&(1<<6) ? 0 : (1<<5)) |
           (PINB&(1<<6) ? 0 : (1<<6)) |
           (PINB&(1<<5) ? 0 : (1<<7)) |
           (PINB&(1<<4) ? 0 : (1<<8)) |
           (PIND&(1<<7) ? 0 : (1<<9)) |
           (PIND&(1<<6) ? 0 : (1<<10)) |
           (PIND&(1<<4) ? 0 : (1<<11)) |
           (PIND&(1<<5) ? 0 : (1<<12)) |
           (PIND&(1<<3) ? 0 : (1<<13)) |
           (PINB&(1<<3) ? 0 : (1<<14)) |
           (PINB&(1<<2) ? 0 : (1UL<<15)) |
           (PINB&(1<<1) ? 0 : (1UL<<16)) |
           (PINB&(1<<0) ? 0 : (1UL<<17));
}

/* Row pin configuration
 * row:      0   1   2   3   4   5   6   x
 * pin: PD2  0   1   0   1   0   1   0   1
 *      PD1  0   0   1   1   0   0   1   1
 *      PD0  0   0   0   0   1   1   1   1
 */

static void init_rows(void) {
    DDRD  |= (1<<PD2 | 1<<PD1 | 1<<PD0);
}

static void unselect_rows(void) {
    // Select Y7
    //PORTD |= (1<<PD2 | 1<<PD1 | 1<<PD0);
    PORTD |= (1<<PD2);
    PORTD |= (1<<PD1);
    PORTD |= (1<<PD0);
}

static void select_row(uint8_t row) {
    (row & (1<<0)) ? (PORTD |= (1<<PD2)) : (PORTD &= ~(1<<PD2));
    (row & (1<<1)) ? (PORTD |= (1<<PD1)) : (PORTD &= ~(1<<PD1));
    (row & (1<<2)) ? (PORTD |= (1<<PD0)) : (PORTD &= ~(1<<PD0));
}
