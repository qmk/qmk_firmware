/*
  Copyright 2017 Gabriel Young <gabeplaysdrums@live.com>
  Copyright 2018 Alexander Fougner <fougner89 at gmail.com>

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

#ifndef DEBOUNCE
#   define DEBOUNCE 5
#endif
static uint8_t debouncing = DEBOUNCE;

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t scan_col(void) {
    return (
        (PINC&(1<<7) ? 0 : ((matrix_row_t)1<<0)) |
        (PINB&(1<<6) ? 0 : ((matrix_row_t)1<<1)) |
        (PINB&(1<<1) ? 0 : ((matrix_row_t)1<<2)) |
        (PINB&(1<<0) ? 0 : ((matrix_row_t)1<<3)) |
        (PINB&(1<<5) ? 0 : ((matrix_row_t)1<<4)) |
        (PINB&(1<<3) ? 0 : ((matrix_row_t)1<<5)) |
        (PINB&(1<<4) ? 0 : ((matrix_row_t)1<<6)) |
        (PINB&(1<<2) ? 0 : ((matrix_row_t)1<<7))
    );
}

static void select_col(uint8_t col) {
    switch (col) {
        case 0: PORTD = (PORTD & ~0b00111111) | 0b00110011; break;
        case 1: PORTD = (PORTD & ~0b00111111) | 0b00100011; break;
        case 2: PORTD = (PORTD & ~0b00111111) | 0b00010111; break;
        case 3: PORTD = (PORTD & ~0b00111111) | 0b00110011; break;
        case 4: PORTD = (PORTD & ~0b00111111) | 0b00010011; break;
        case 5: PORTD = (PORTD & ~0b00111111) | 0b00011011; break;
        case 6: PORTD = (PORTD & ~0b00111111) | 0b00110100; break;
        case 7: PORTD = (PORTD & ~0b00111111) | 0b00111010; break;
        case 8: PORTD = (PORTD & ~0b00111111) | 0b00111000; break;
        case 9: PORTD = (PORTD & ~0b00111111) | 0b00111100; break;
        case 10: PORTD = (PORTD & ~0b00111111) | 0b00110010; break;
        case 11: PORTD = (PORTD & ~0b00111111) | 0b00011111; break;
        case 12: PORTD = (PORTD & ~0b00111111) | 0b00001111; break;
        case 13: PORTD = (PORTD & ~0b00111111) | 0b00100111; break;
        case 14: PORTD = (PORTD & ~0b00111111) | 0b00000111; break;
        case 15: PORTD = (PORTD & ~0b00111111) | 0b00110110; break;
        case 16: PORTD = (PORTD & ~0b00111111) | 0b00001011; break;
        case 17: PORTD = (PORTD & ~0b00111111) | 0b00000011; break;
    }
}

void matrix_init(void) {
    /* Row output pins */
    DDRD  |=  0b00111111;
    /* Column input pins */
    DDRC  &= ~0b10000000;
    DDRB  &= ~0b01111111;
    PORTC |=  0b10000000;
    PORTB |=  0b01111111;

    for (uint8_t i=0; i < MATRIX_ROWS; i++)
        matrix[i] = matrix_debouncing[i] = 0;

    matrix_init_kb();
}

uint8_t matrix_scan(void) {
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        select_col(col);
        _delay_us(3);
        matrix_row_t col_scan = scan_col();
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            bool prev_bit = matrix_debouncing[row] & ((matrix_row_t)1<<col);
            bool curr_bit = col_scan & (1<<row);
            if (prev_bit != curr_bit) {
                matrix_debouncing[row] ^= ((matrix_row_t)1<<col);
                debouncing = DEBOUNCE;
            }
        }
    }

    if (debouncing) {
        if (--debouncing)
            _delay_ms(1);
        else
            for (uint8_t i = 0; i < MATRIX_ROWS; i++)
                matrix[i] = matrix_debouncing[i];
    }

    matrix_scan_kb();
    return 1;
}

inline matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_print(void) {
#ifndef NO_PRINT
    print("\nr\\c ABCDEFGHIJKLMNOPQR\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t matrix_row = matrix_get_row(row);
        xprintf("%02X: ", row);
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            bool curr_bit = matrix_row & (1<<col);
            xprintf("%c", curr_bit ? '*' : '.');
        }
        print("\n");
    }
#endif
}
