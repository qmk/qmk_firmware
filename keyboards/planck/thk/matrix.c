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


// #define MATRIX_ROW_PINS { A7, A6, A5, A4 }
// #define MATRIX_COL_PINS { D7, C2, C3, C4, C5, C6, C7, A3, A2, A1, A0, B0 }

static uint8_t debouncing = DEBOUNCE;

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static bool dip_switch[4] = {0, 0, 0, 0};

__attribute__ ((weak))
void dip_update(uint8_t index, bool active) { }

__attribute__ ((weak))
void dip_update_kb(uint8_t index, bool active) { }

bool last_dip_switch[4] = {0};

void matrix_init(void) {

    // disables JTAG so we can use them as columns
    MCUCSR = (1<<JTD);
    MCUCSR = (1<<JTD);

    // dip switch (input, pull-up)
    DDRD &= ~((1 << 0) | (1 << 1) | (1 << 4) | (1 << 6));
    PORTD |= ((1 << 0) | (1 << 1) | (1 << 4) | (1 << 6));

    // rows (output)
    DDRA |= ((1 << 7) | (1 << 6) | (1 << 5) | (1 << 4));
    PORTA |= ((1 << 7) | (1 << 6) | (1 << 5) | (1 << 4));

    // cols (input)
    DDRD &= ~((1 << 7));
    DDRC &= ~((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7));
    DDRA &= ~((1 << 3) | (1 << 2) | (1 << 1) | (1 << 0));
    DDRB &= ~((1 << 0));

    // pull-up cols
    PORTD |= ((1 << 7));
    PORTC |= ((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7));
    PORTA |= ((1 << 3) | (1 << 2) | (1 << 1) | (1 << 0));
    PORTB |= ((1 << 0));

    // initialize matrix state: all keys off
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix[row] = 0x00;
        matrix_debouncing[row] = 0x00;
    }

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {

    // dip switch
    dip_switch[0] = !(PIND & (1 << 0));
    dip_switch[1] = !(PIND & (1 << 1));
    dip_switch[2] = !(PIND & (1 << 4));
    dip_switch[3] = !(PIND & (1 << 5));
    for (uint8_t i = 0; i < 4; i++) {
      if (last_dip_switch[i] ^ dip_switch[i]) {
        dip_update(i, dip_switch[i]);
        dip_update_kb(i, dip_switch[i]);
      }
    }
    memcpy(last_dip_switch, dip_switch, sizeof(&dip_switch));

    // actual matrix scan
    for (uint8_t c = 0; c < MATRIX_ROWS; c++) {
        switch (c) {
          case 0:  PORTA &= ~(1 << 7); break;
          case 1:  PORTA &= ~(1 << 6); break;
          case 2:  PORTA &= ~(1 << 5); break;
          case 3:  PORTA &= ~(1 << 4); break;
        }
        _delay_us(5);

        matrix_row_t current_row = (
          (((PIND & (1 << 7)) ? 0 : 1 ) << 0) |
          (((PINC & (1 << 2)) ? 0 : 1 ) << 1) |
          (((PINC & (1 << 3)) ? 0 : 1 ) << 2) |
          (((PINC & (1 << 4)) ? 0 : 1 ) << 3) |
          (((PINC & (1 << 5)) ? 0 : 1 ) << 4) |
          (((PINC & (1 << 6)) ? 0 : 1 ) << 5) |
          (((PINC & (1 << 7)) ? 0 : 1 ) << 6) |
          (((PINA & (1 << 3)) ? 0 : 1 ) << 7) |
          (((PINA & (1 << 2)) ? 0 : 1 ) << 8) |
          (((PINA & (1 << 1)) ? 0 : 1 ) << 9) |
          (((PINA & (1 << 0)) ? 0 : 1 ) << 10) |
          (((PINB & (1 << 0)) ? 0 : 1 ) << 11)
        );

        switch (c) {
          case 0:  PORTA |= (1 << 7); break;
          case 1:  PORTA |= (1 << 6); break;
          case 2:  PORTA |= (1 << 5); break;
          case 3:  PORTA |= (1 << 4); break;
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

__attribute__ ((weak))
void matrix_init_user(void) { }

__attribute__ ((weak))
void matrix_scan_user(void) { }

__attribute__ ((weak))
void matrix_init_kb(void) {
  matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
  matrix_scan_user();
}
