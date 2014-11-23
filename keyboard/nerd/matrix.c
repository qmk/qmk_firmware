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
#include "backlight.h"


#ifndef DEBOUNCE
#   define DEBOUNCE 5
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static uint16_t read_inputs(void);
static void init_inputs(void);
static void init_outputs(void);
static void reset_inputs(void);
static void reset_outputs(void);
static void select_output(uint8_t col);

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
    backlight_init_ports();
    init_inputs();
    init_outputs();

    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
}

uint8_t matrix_scan(void)
{
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        reset_inputs();
        reset_outputs();
        select_output(col);
        _delay_us(3);
        uint16_t rows = read_inputs();
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

static void init_inputs(void)
{
    DDRE &= ~0b01000000; // PE6 (Col 0)
    DDRB &= ~0b00001111; // PB0 (Col 1), PB1 (Col 2), PB2 (Col 3), PB3 (Col 4)
    DDRF &= ~0b00000001; // PF0 (Col 5)
    DDRD &= ~0b00100011; // PD0 (Col 6), PD1 (Col 8 TKL), PD5 (Col 7)
}

static uint16_t read_inputs(void)
{
    return (PINE&(1<<6) ? 0 : (1<<0)) |  // PE6 (Col 0)
           (PINB&(1<<0) ? 0 : (1<<1)) |  // PB0 (Col 1)
           (PINB&(1<<1) ? 0 : (1<<2)) |  // PB1 (Col 2)
           (PINB&(1<<2) ? 0 : (1<<3)) |  // PB2 (Col 3)
           (PINB&(1<<3) ? 0 : (1<<4)) |  // PB3 (Col 4)
           (PINF&(1<<0) ? 0 : (1<<5)) |  // PF0 (Col 5)
           (PIND&(1<<0) ? 0 : (1<<6)) |  // PD0 (Col 6)
           (PIND&(1<<5) ? 0 : (1<<7)) |  // PD5 (Col 7)
           (PIND&(1<<1) ? 0 : (1<<8));   // PD1 (Col 8 TKL)
}

static void reset_inputs(void)
{
    PORTE |= 0b01000000; // PE6 (Col 0)
    PORTB |= 0b00001111; // PB0 (Col 1), PB1 (Col 2), PB2 (Col 3), PB3 (Col 4)
    PORTF |= 0b00000001; // PF0 (Col 5)
    PORTD |= 0b00100011; // PD0 (Col 6), PD1 (Col 8 TKL), PD5 (Col 7)
}

static void init_outputs(void)
{
    DDRB |= 0b00010000; // PB4 (Row 0)
    DDRE |= 0b00000100; // PE2 (Row 1)
    DDRF |= 0b11110010; // PF4 (Row 2), PF7 (Row 3), PF1 (Row 4), PF6 (Row 5), PF5 (Row 7)
    DDRC |= 0b11000000; // PC6 (Row 6), PC7 (Row 9)
    DDRD |= 0b10000000; // PD7 (Row 8)
}

static void reset_outputs(void)
{
    PORTB |= 0b00010000; // PB4 (Row 0)
    PORTE |= 0b00000100; // PE2 (Row 1)
    PORTF |= 0b11110010; // PF4 (Row 2), PF7 (Row 3), PF1 (Row 4), PF6 (Row 5), PF5 (Row 7)
    PORTC |= 0b11000000; // PC6 (Row 6), PC7 (Row 9)
    PORTD |= 0b10000000; // PD7 (Row 8)
}

static void select_output(uint8_t col)
{
    switch (col) {
        case 0:
            PORTB &= ~(1<<4);
            break;
        case 1:
            PORTE &= ~(1<<2);
            break;
        case 2:
            PORTF &= ~(1<<4);
            break;
        case 3:
            PORTF &= ~(1<<7);
            break;
        case 4:
            PORTF &= ~(1<<1);
            break;
        case 5:
            PORTF &= ~(1<<6);
            break;
        case 6:
            PORTC &= ~(1<<6);
            break;
        case 7:
            PORTF &= ~(1<<5);
            break;
        case 8:
            PORTD &= ~(1<<7);
            break;
        case 9:
            PORTC &= ~(1<<7);
            break;
    }
}
