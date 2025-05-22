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

    // 85 REST
    gpio_set_pin_output(D7);
    gpio_write_pin_high(D7);

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
                dprintf("bounce!: %02X\n", debouncing);
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
        print_hex8(row); print(": ");
        print_bin_reverse16(matrix_get_row(row));
        print("\n");
    }
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

    gpio_set_pin_input_high(B0);
    gpio_set_pin_input_high(B6);
    gpio_set_pin_input_high(B7);

    gpio_set_pin_input_high(E6);

    gpio_set_pin_input_high(C7);

}

static matrix_row_t read_cols(void)
{

    return (gpio_read_pin(F7) ? 0 : (1<<0)) |
           (gpio_read_pin(F6) ? 0 : (1<<1)) |
           (gpio_read_pin(F5) ? 0 : (1<<2)) |
           (gpio_read_pin(F4) ? 0 : (1<<3)) |
           (gpio_read_pin(F1) ? 0 : (1<<4)) |
           (gpio_read_pin(F0) ? 0 : (1<<5)) |
           (gpio_read_pin(E6) ? 0 : (1<<6)) |
           (gpio_read_pin(D7) ? 0 : (1<<7)) |
           (gpio_read_pin(D6) ? 0 : (1<<8)) |
           (gpio_read_pin(D5) ? 0 : (1<<9)) |
           (gpio_read_pin(D1) ? 0 : (1<<10)) |
           (gpio_read_pin(D0) ? 0 : (1<<11)) |
           (gpio_read_pin(B7) ? 0 : (1<<12)) |
           (gpio_read_pin(B6) ? 0 : (1<<13)) |
           (gpio_read_pin(B0) ? 0 : (1<<14)) |
           (gpio_read_pin(C7) ? 0 : (1<<15));
}

/* Row pin configuration
 * row:     0   1   2   3   4   5   x
 * pin: B3  0   1   0   1   0   1   1
 *      B2  0   0   1   1   0   0   1
 *      B1  0   0   0   0   1   1   1
 */

static void init_rows(void)
{
    gpio_set_pin_input(B1);
    gpio_set_pin_input(B2);
    gpio_set_pin_input(B3);
}

static void unselect_rows(void)
{
    // Hi-Z(DDR:0, PORT:0) to unselect
    gpio_write_pin_high(B1);
    gpio_write_pin_high(B2);
    gpio_write_pin_high(B3);
}

static void select_row(uint8_t row)
{
    // Output low(DDR:1, PORT:0) to select
    gpio_write_pin(B3, row & (1<<0));
    gpio_write_pin(B2, row & (1<<1));
    gpio_write_pin(B1, row & (1<<2));
}
