/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

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

#include "matrix.h"

#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif


// #define MATRIX_ROW_PINS { A7, A6, A5, A4 }
// #define MATRIX_COL_PINS { D7, C2, C3, C4, C5, C6, C7, A3, A2, A1, A0, B0 }

static uint8_t debouncing = DEBOUNCE;

static matrix_row_t matrix[MATRIX_ROWS];
static uint8_t matrix_debouncing[MATRIX_COLS];

void matrix_init(void) {

    MCUCSR = (1<<JTD);
    MCUCSR = (1<<JTD);

    //ADCSRA = 0;

    // rows (input)
    DDRA &= ~((1 << 7) | (1 << 6) | (1 << 5) | (1 << 4));
    PORTA &= ~((1 << 7) | (1 << 6) | (1 << 5) | (1 << 4));

    // cols (output)
    DDRD |= ((1 << 7));
    DDRC |= ((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7));
    DDRA |= ((1 << 3) | (1 << 2) | (1 << 1) | (1 << 0));
    DDRB |= ((1 << 0));

    PORTD &= ~((1 << 7));
    PORTC &= ~((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7));
    PORTA &= ~((1 << 3) | (1 << 2) | (1 << 1) | (1 << 0));
    PORTB &= ~((1 << 0));

    // initialize matrix state: all keys off
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix[row] = 0x00;
    }
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        matrix_debouncing[col] = 0x00;
    }

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {

    for (uint8_t c = 0; c < MATRIX_COLS; c++) {
        switch (c) {
          case 0:  PORTD |= (1 << 7); break;
          case 1:  PORTC |= (1 << 2); break;
          case 2:  PORTC |= (1 << 3); break;
          case 3:  PORTC |= (1 << 4); break;
          case 4:  PORTC |= (1 << 5); break;
          case 5:  PORTC |= (1 << 6); break;
          case 6:  PORTC |= (1 << 7); break;
          case 7:  PORTA |= (1 << 3); break;
          case 8:  PORTA |= (1 << 2); break;
          case 9:  PORTA |= (1 << 1); break;
          case 10: PORTA |= (1 << 0); break;
          case 11: PORTB |= (1 << 0); break;
        }
        _delay_us(5);

        uint8_t current_col = (
           ((PINA & (1 << 7)) ? 1 : 0 ) |
          (((PINA & (1 << 6)) ? 1 : 0 ) << 1) |
          (((PINA & (1 << 5)) ? 1 : 0 ) << 2) |
          (((PINA & (1 << 4)) ? 1 : 0 ) << 3)
        );

        switch (c) {
          case 0:  PORTD &= ~(1 << 7); break;
          case 1:  PORTC &= ~(1 << 2); break;
          case 2:  PORTC &= ~(1 << 3); break;
          case 3:  PORTC &= ~(1 << 4); break;
          case 4:  PORTC &= ~(1 << 5); break;
          case 5:  PORTC &= ~(1 << 6); break;
          case 6:  PORTC &= ~(1 << 7); break;
          case 7:  PORTA &= ~(1 << 3); break;
          case 8:  PORTA &= ~(1 << 2); break;
          case 9:  PORTA &= ~(1 << 1); break;
          case 10: PORTA &= ~(1 << 0); break;
          case 11: PORTB &= ~(1 << 0); break;
        }

        if (matrix_debouncing[c] != current_col) {
            matrix_debouncing[c] = current_col;
            debouncing = DEBOUNCE;
        }
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = 0;
                for (uint8_t j = 0; j < MATRIX_COLS; j++) {
                    matrix[i] |= (((matrix_debouncing[j] & (1 << i)) ? 1L : 0 ) << j);
                }
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

__attribute__ ((weak))
void matrix_init_user(void) { }

__attribute__ ((weak))
void matrix_scan_user(void) { }
