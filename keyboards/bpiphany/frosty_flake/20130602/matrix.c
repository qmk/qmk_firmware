/*
  Copyright 2017 Gabriel Young <gabeplaysdrums@live.com>

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

#include <util/delay.h>
#include "matrix.h"


static matrix_row_t scan_col(void) {
    // Each of the 8 columns is read off pins as below
    //   7  6  5  4  3  2  1  0
    // ,--,--,--,--,--,--,--,--,
    // |B0|B3|B2|B1|B6|B4|B5|C7|
    // `--`--`--`--`--`--`--`--`
    return (
        (PINC&(1<<2) ? 0 : ((matrix_row_t)1<<0)) |
        (PIND&(1<<0) ? 0 : ((matrix_row_t)1<<1)) |
        (PIND&(1<<1) ? 0 : ((matrix_row_t)1<<2)) |
        (PINC&(1<<7) ? 0 : ((matrix_row_t)1<<3)) |
        (PIND&(1<<5) ? 0 : ((matrix_row_t)1<<4)) |
        (PIND&(1<<4) ? 0 : ((matrix_row_t)1<<5)) |
        (PIND&(1<<2) ? 0 : ((matrix_row_t)1<<6)) |
        (PIND&(1<<6) ? 0 : ((matrix_row_t)1<<7))
    );
}

static void select_row(uint8_t row) {
    switch (row) {
        case  0: PORTB = (PORTB & ~0b01111110) | 0b00111010; break;
        case  1: PORTB = (PORTB & ~0b01111110) | 0b01011000; break;
        case  2: PORTB = (PORTB & ~0b01111110) | 0b01110000; break;
        case  3: PORTB = (PORTB & ~0b01111110) | 0b01101110; break;
        case  4: PORTB = (PORTB & ~0b01111110) | 0b01101100; break;
        case  5: PORTB = (PORTB & ~0b01111110) | 0b01101010; break;
        case  6: PORTB = (PORTB & ~0b01111110) | 0b01101000; break;
        case  7: PORTB = (PORTB & ~0b01111110) | 0b01100100; break;
        case  8: PORTB = (PORTB & ~0b01111110) | 0b01100000; break;
        case  9: PORTB = (PORTB & ~0b01111110) | 0b01100010; break;
        case 10: PORTB = (PORTB & ~0b01111110) | 0b00011010; break;
        case 11: PORTB = (PORTB & ~0b01111110) | 0b00011000; break;
        case 12: PORTB = (PORTB & ~0b01111110) | 0b00111100; break;
        case 13: PORTB = (PORTB & ~0b01111110) | 0b01100110; break;
        case 14: PORTB = (PORTB & ~0b01111110) | 0b00111000; break;
        case 15: PORTB = (PORTB & ~0b01111110) | 0b01110010; break;
        case 16: PORTB = (PORTB & ~0b01111110) | 0b00011110; break;
        case 17: PORTB = (PORTB & ~0b01111110) | 0b00111110; break;
    }
}

void matrix_init_custom(void) {
    /* Column output pins */
    DDRB  |=  0b01111110;
    /* Row input pins */
    DDRC  &= ~0b10000100;
    DDRD  &= ~0b01110111;
    PORTC |=  0b10000100;
    PORTD |=  0b01110111;
}

// matrix is 18 uint8_t.
// we select the row (one of 18), then read the column
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
	bool has_changed = false;
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t orig = current_matrix[row];
        select_row(row);
        _delay_us(3);
        current_matrix[row] = scan_col();
        has_changed |= (orig != current_matrix[row]);
    }

    return has_changed;
}
