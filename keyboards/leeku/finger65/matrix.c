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
#include "i2c.h"

static uint8_t debouncing = DEBOUNCING_DELAY;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static uint32_t read_cols(void);
static void init_ports(void);
static void reset_cols(void);
static void reset_rows(void);
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
    init_ports();
    i2c_init(I2C_BITRATE_KHZ);
    for (uint8_t i=0; i < MATRIX_ROWS; i++)  {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
}

uint8_t matrix_scan(void)
{
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        select_row(row);
        _delay_us(3);
        uint32_t cols = read_cols();
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            bool prev_bit = matrix_debouncing[row] & ((matrix_row_t) 1UL << col);
            bool curr_bit = cols & (1UL << col);
            if (prev_bit != curr_bit) {
                matrix_debouncing[row] ^= ((matrix_row_t) 1UL << col);
                debouncing = DEBOUNCING_DELAY;
            }
        }
        reset_rows();
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

/* Pin out
 *
 * PA0 -> COL 0
 * PA1 -> COL 1
 * PA2 -> COL 2
 * PA3 -> COL 3
 * PA4 -> COL 4
 * PA5 -> COL 5
 * PA6 -> COL 6
 * PA7 -> COL 7
 *
 * PB0 -> COL 8
 * PB1 -> COL 9
 * PB2 -> COL10
 * PB3 -> COL11
 * PB4 -> COL12
 * PB5 -> COL13
 * PB6 -> COL14
 * PB7 -> COL15
 *
 * PD0 -> USB D+- level shifter(high 3.3v, low 5v)
 * PD1 -> PS2 pull-up for CLK
 * PD2 -> USB/PS2 DATA+
 * PD3 -> USB/PS2 DATA-
 * PD4 -> COL16
 * PD5 -> COL17
 * PD6 -> COL18
 * PD7 -> COL19
 *
 * PC0 -> I2C SCL (clock)
 * PC1 -> I2C SDA (data)
 * PC2 -> ROW 0
 * PC3 -> ROW 1
 * PC4 -> ROW 2
 * PC5 -> ROW 3
 * PC6 -> ROW 4
 * PC7 -> ROW 5
 */
static void init_ports(void)
{
    // Init row and column pins
    DDRA   =  0b00000000; // input
    DDRB   =  0b00000000; // input
    DDRD  &= ~0b11110000; // input
    DDRC  |=  0b11111100; // output
    reset_rows();
    reset_cols();

    DDRD  |=  0b00000011; // usb shifter output, ps2 pull up output
    PORTD |=  0b00000001; // usb shifter high, ps2 pull up low
}

static void reset_cols(void)
{
    PORTA |=  0b11111111; // high
    PORTB |=  0b11111111; // high
    PORTD |=  0b11110000; // high
}

static void reset_rows(void)
{
    PORTC |=  0b11111100; // high
}

static uint32_t read_cols(void)
{
    return (PINA&(1<<0) ? 0 : (1UL <<  0)) |
           (PINA&(1<<1) ? 0 : (1UL <<  1)) |
           (PINA&(1<<2) ? 0 : (1UL <<  2)) |
           (PINA&(1<<3) ? 0 : (1UL <<  3)) |
           (PINA&(1<<4) ? 0 : (1UL <<  4)) |
           (PINA&(1<<5) ? 0 : (1UL <<  5)) |
           (PINA&(1<<6) ? 0 : (1UL <<  6)) |
           (PINA&(1<<7) ? 0 : (1UL <<  7)) |
           (PINB&(1<<0) ? 0 : (1UL <<  8)) |
           (PINB&(1<<1) ? 0 : (1UL <<  9)) |
           (PINB&(1<<2) ? 0 : (1UL << 10)) |
           (PINB&(1<<3) ? 0 : (1UL << 11)) |
           (PINB&(1<<4) ? 0 : (1UL << 12)) |
           (PINB&(1<<5) ? 0 : (1UL << 13)) |
           (PINB&(1<<6) ? 0 : (1UL << 14)) |
           (PINB&(1<<7) ? 0 : (1UL << 15)) |
           (PIND&(1<<4) ? 0 : (1UL << 16)) |
           (PIND&(1<<5) ? 0 : (1UL << 17)) |
           (PIND&(1<<6) ? 0 : (1UL << 18)) |
           (PIND&(1<<7) ? 0 : (1UL << 19));
}

static void select_row(uint8_t row)
{
    switch(row) {
        case 0: PORTC &= ~0b00000100; break;
        case 1: PORTC &= ~0b00001000; break;
        case 2: PORTC &= ~0b00010000; break;
        case 3: PORTC &= ~0b00100000; break;
        case 4: PORTC &= ~0b01000000; break;
        case 5: PORTC &= ~0b10000000; break;
    }
}
