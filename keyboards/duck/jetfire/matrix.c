/*
Copyright 2016 Ralf Schmitt <ralf@bunkertor.net>
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
#    define DEBOUNCE 5
#endif

static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static uint8_t read_rows(uint8_t col);
static void init_ports(void);
static void unselect_cols(void);
static void select_col(uint8_t col);

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

void backlight_init_ports(void)
{
  DDRD  |=  0b01010000;
  PORTD &=  0b10101111;
  DDRB  |=  0b00001110;
  PORTB &=  0b11110001;
  DDRE  |=  0b01000000;
  PORTE &=  0b10111111;
}

void matrix_init(void)
{
    backlight_init_ports();
    unselect_cols();
    init_ports();
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
        uint8_t rows = read_rows(col);
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

static void init_ports(void)
{
    // Rows are inputs (inputs are 0)
    DDRD  &= 0b11010000;
    DDRB  &= 0b01111111;
    DDRE  &= 0b11111011;

    // Columns are outputs (outputs are high)
    DDRF  |= 0b00000011;
    DDRC  |= 0b11000000;
    DDRB  |= 0b01110001;
    DDRD  |= 0b10000000;
}

static uint8_t read_rows(uint8_t col)
{
  if(col == 15) {
    return (PINE&(1<<2) ? 0 : (1<<0)) |
           (PIND&(1<<0) ? (1<<1) : 0) |
           (PIND&(1<<1) ? (1<<2) : 0) |
           (PIND&(1<<2) ? (1<<3) : 0) |
           (PIND&(1<<3) ? (1<<4) : 0) |
           (PIND&(1<<5) ? (1<<5) : 0);

  } else {
    return (PINB&(1<<7) ? (1<<0) : 0) |
           (PIND&(1<<0) ? (1<<1) : 0) |
           (PIND&(1<<1) ? (1<<2) : 0) |
           (PIND&(1<<2) ? (1<<3) : 0) |
           (PIND&(1<<3) ? (1<<4) : 0) |
           (PIND&(1<<5) ? (1<<5) : 0);

  }
}

static void unselect_cols(void)
{
    PORTF &= 0b11111100;
    PORTC &= 0b00111111;
    PORTB &= 0b10001110;
    PORTD &= 0b01111111;
}

static void select_col(uint8_t col)
{
    switch (col) {
        case 0:
            PORTC |= 0b01000000;
            break;
        case 1:
            PORTC |= 0b01000000;
            PORTF |= 0b00000001;
            break;
        case 2:
            PORTC |= 0b01000000;
            PORTF |= 0b00000010;
            break;
        case 3:
            PORTC |= 0b01000000;
            PORTF |= 0b00000011;
            break;
        case 4:
            PORTC |= 0b11000000;
            break;
        case 5:
            PORTC |= 0b11000000;
            PORTF |= 0b00000001;
            break;
        case 6:
            PORTC |= 0b11000000;
            PORTF |= 0b00000010;
            break;
        case 7:
            PORTC |= 0b11000000;
            PORTF |= 0b00000011;
            break;
        case 8:
            PORTB |= 0b01000000;
            break;
        case 9:
            PORTB |= 0b01000000;
            PORTF |= 0b00000001;
            break;
        case 10:
            PORTB |= 0b01000000;
            PORTF |= 0b00000010;
            break;
        case 11:
            PORTB |= 0b01000000;
            PORTF |= 0b00000011;
            break;
        case 12:
            PORTB |= 0b01000000;
            PORTC |= 0b10000000;
            break;
        case 13:
            PORTB |= 0b01000000;
            PORTF |= 0b00000001;
            PORTC |= 0b10000000;
            break;
        case 14:
            PORTB |= 0b01000000;
            PORTF |= 0b00000010;
            PORTC |= 0b10000000;
            break;
        case 15:
            PORTB |= 0b01000000;
            PORTF |= 0b00000011;
            PORTC |= 0b10000000;
            break;
        case 16:
            PORTB |= 0b00100000;
            break;
        case 17:
            PORTB |= 0b00010000;
            break;
        case 18:
            PORTD |= 0b10000000;
            break;
        case 19:
            PORTB |= 0b00000001;
            break;
    }
}
