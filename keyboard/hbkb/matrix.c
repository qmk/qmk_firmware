/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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


/*
 * Happy Buckling Keyboard(IBM Model M mod)
 *
 * Pin usage:
 *   COL: PD0-7
 *   ROW: PB0-7, PF4-7
 */

#if (MATRIX_COLS > 16)
#   error "MATRIX_COLS must not exceed 16"
#endif
#if (MATRIX_ROWS > 255)
#   error "MATRIX_ROWS must not exceed 255"
#endif


#ifndef DEBOUNCE
#   define DEBOUNCE	0
#endif
static uint8_t debouncing = DEBOUNCE;

// matrix state buffer(1:on, 0:off)
#if (MATRIX_COLS <= 8)
static uint8_t *matrix;
static uint8_t *matrix_prev;
static uint8_t _matrix0[MATRIX_ROWS];
static uint8_t _matrix1[MATRIX_ROWS];
#else
static uint16_t *matrix;
static uint16_t *matrix_prev;
static uint16_t _matrix0[MATRIX_ROWS];
static uint16_t _matrix1[MATRIX_ROWS];
#endif

#ifdef MATRIX_HAS_GHOST
static bool matrix_has_ghost_in_row(uint8_t row);
#endif
static uint8_t read_col(void);
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
    print_enable = true;
    debug_enable = true;
    debug_matrix = true;
    debug_keyboard = false;
    debug_mouse = false;
    print("debug enabled.\n");

    // JTAG disable for PORT F. write JTD bit twice within four cycles.
    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);

    // initialize rows
    unselect_rows();

    // initialize columns to input with pull-up(DDR:0, PORT:1)
    DDRD = 0x00;
    PORTD = 0xFF;

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) _matrix0[i] = 0x00;
    for (uint8_t i=0; i < MATRIX_ROWS; i++) _matrix1[i] = 0x00;
    matrix = _matrix0;
    matrix_prev = _matrix1;
}

uint8_t matrix_scan(void)
{
    if (!debouncing) {
        uint8_t *tmp = matrix_prev;
        matrix_prev = matrix;
        matrix = tmp;
    }

    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        unselect_rows();
        select_row(i);
        _delay_us(30);  // without this wait read unstable value.
        if (matrix[i] != (uint8_t)~read_col()) {
            matrix[i] = (uint8_t)~read_col();
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); print("\n");
            }
            _delay_ms(1);   // TODO: work around. HAHAHAHAHAAHA
            debouncing = DEBOUNCE;
        }
    }
    unselect_rows();

    if (debouncing) {
        debouncing--;
    }

    return 1;
}

bool matrix_is_modified(void)
{
    if (debouncing) return false;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (matrix[i] != matrix_prev[i]) {
            return true;
        }
    }
    return false;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & (1<<col));
}

inline
#if (MATRIX_COLS <= 8)
uint8_t matrix_get_row(uint8_t row)
#else
uint16_t matrix_get_row(uint8_t row)
#endif
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < matrix_rows(); row++) {
        phex(row); print(": ");
#if (MATRIX_COLS <= 8)
        pbin_reverse(matrix_get_row(row));
#else
        pbin_reverse16(matrix_get_row(row));
#endif
#ifdef MATRIX_HAS_GHOST
        if (matrix_has_ghost_in_row(row)) {
            print(" <ghost");
        }
#endif
        print("\n");
    }
}

#ifdef MATRIX_HAS_GHOST
inline
static bool matrix_has_ghost_in_row(uint8_t row)
{
    // no ghost exists in case less than 2 keys on
    if (((matrix[row] - 1) & matrix[row]) == 0)
        return false;

    // ghost exists in case same state as other row
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        if (i != row && (matrix[i] & matrix[row]))
            return true;
    }
    return false;
}
#endif

inline
static uint8_t read_col(void)
{
    return PIND;
}

inline
static void unselect_rows(void)
{
    // Hi-Z(DDR:0, PORT:0) to unselect
    DDRB  &= ~0b11111111;
    PORTB &= ~0b11111111;
    DDRF  &= ~0b11110000;
    PORTF &= ~0b11110000;
}

inline
static void select_row(uint8_t row)
{
    // Output low(DDR:1, PORT:0) to select
    switch (row) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            DDRB  |=  (1<<row);
            PORTB &= ~(1<<row);
            break;
        case 8:
            DDRF  |=  (1<<4);
            PORTF &= ~(1<<4);
            break;
        case 9:
        case 10:
        case 11:
            DDRF  |=  (1<<(row-4));
            PORTF &= ~(1<<(row-4));
            break;
    }
}
