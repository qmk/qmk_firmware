/*
Copyright 2018 Jack Humbert <jack.humb@gmail.com>

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

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "matrix.h"

#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif

__attribute__ ((weak))
void matrix_init_kb(void) {
  matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
  matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) { }

__attribute__ ((weak))
void matrix_scan_user(void) { }

// #define MATRIX_ROW_PINS { B3, B4, B5, B6, B7 }
// #define MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, A6, A7, C7, C6, C5, C4, C3, C2, D7 }

static uint8_t debouncing = DEBOUNCE;

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

void matrix_init(void) {

    // disables JTAG so we can use them as columns
    MCUCSR = (1<<JTD);
    MCUCSR = (1<<JTD);

    // rows (output)
    DDRB |= ((1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7));
    PORTB |= ((1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7));

    // cols (input)
    DDRA &= ~((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7));
    DDRC &= ~((1 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (1 << 3) | (1 << 2));
    DDRD &= ~((1 << 7));

    // pull-up cols
    PORTA |= ((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7));
    PORTC |= ((1 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (1 << 3) | (1 << 2));
    PORTD |= ((1 << 7));

    // initialize matrix state: all keys off
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix[row] = 0x00;
        matrix_debouncing[row] = 0x00;
    }

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {

    // actual matrix scan
    for (uint8_t c = 0; c < MATRIX_ROWS; c++) {
        switch (c) {
          case 0:  PORTB &= ~(1 << 3); break;
          case 1:  PORTB &= ~(1 << 4); break;
          case 2:  PORTB &= ~(1 << 5); break;
          case 3:  PORTB &= ~(1 << 6); break;
          case 4:  PORTB &= ~(1 << 7); break;
        }
        _delay_us(5);

        matrix_row_t current_row = (
          (((PINA & (1 << 0)) ? 0 : 1 ) << 0)  |
          (((PINA & (1 << 1)) ? 0 : 1 ) << 1)  |
          (((PINA & (1 << 2)) ? 0 : 1 ) << 2)  |
          (((PINA & (1 << 3)) ? 0 : 1 ) << 3)  |
          (((PINA & (1 << 4)) ? 0 : 1 ) << 4)  |
          (((PINA & (1 << 5)) ? 0 : 1 ) << 5)  |
          (((PINA & (1 << 6)) ? 0 : 1 ) << 6)  |
          (((PINA & (1 << 7)) ? 0 : 1 ) << 7)  |
          (((PINC & (1 << 7)) ? 0 : 1 ) << 8)  |
          (((PINC & (1 << 6)) ? 0 : 1 ) << 9)  |
          (((PINC & (1 << 5)) ? 0 : 1 ) << 10) |
          (((PINC & (1 << 4)) ? 0 : 1 ) << 11) |
          (((PINC & (1 << 3)) ? 0 : 1 ) << 12) |
          (((PINC & (1 << 2)) ? 0 : 1 ) << 13) |
          (((PIND & (1 << 7)) ? 0 : 1 ) << 14)
        );

        switch (c) {
          case 0:  PORTB |= (1 << 3); break;
          case 1:  PORTB |= (1 << 4); break;
          case 2:  PORTB |= (1 << 5); break;
          case 3:  PORTB |= (1 << 6); break;
          case 4:  PORTB |= (1 << 7); break;
        }

        if (matrix_debouncing[c] != current_row) {
            matrix_debouncing[c] = current_row;
            debouncing = DEBOUNCE;
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

    matrix_scan_quantum();

    return 1;
}

inline matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_print(void) {
}
