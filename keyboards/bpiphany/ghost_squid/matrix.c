/*
  Copyright 2014 Ralf Schmitt <ralf@bunkertor.net>
  Copyright 2016 Daniel Svensson <dsvensson@gmail.com>

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

#include "matrix.h"
#include "quantum.h"

matrix_row_t read_rows(void) {
    return
        (PINB & (1 << 1) ? 0 : ((matrix_row_t)1 << 0)) |
        (PINC & (1 << 2) ? 0 : ((matrix_row_t)1 << 1)) |
        (PINB & (1 << 6) ? 0 : ((matrix_row_t)1 << 2)) |
        (PINB & (1 << 4) ? 0 : ((matrix_row_t)1 << 3)) |
        (PINB & (1 << 3) ? 0 : ((matrix_row_t)1 << 4)) |
        (PINB & (1 << 2) ? 0 : ((matrix_row_t)1 << 5)) |
        (PINB & (1 << 0) ? 0 : ((matrix_row_t)1 << 6)) |
        (PINB & (1 << 5) ? 0 : ((matrix_row_t)1 << 7));
}

void select_col(uint8_t col) {
    switch (col) {
        case  0: PORTD = (PORTD & ~0b01111110) | 0b01100010; break;
        case  1: PORTD = (PORTD & ~0b01111110) | 0b01101000; break;
        case  2: PORTD = (PORTD & ~0b01111110) | 0b01101100; break;
        case  3: PORTD = (PORTD & ~0b01111110) | 0b01110000; break;
        case  4: PORTD = (PORTD & ~0b01111110) | 0b01111000; break;
        case  5: PORTD = (PORTD & ~0b01111110) | 0b01100000; break;
        case  6: PORTD = (PORTD & ~0b01111110) | 0b01110100; break;
        case  7: PORTD = (PORTD & ~0b01111110) | 0b01100100; break;
        case  8: PORTD = (PORTD & ~0b01111110) | 0b01111100; break;
        case  9: PORTD = (PORTD & ~0b01111110) | 0b01101010; break;
        case 10: PORTD = (PORTD & ~0b01111110) | 0b00110110; break;
        case 11: PORTD = (PORTD & ~0b01111110) | 0b00010110; break;
        case 12: PORTD = (PORTD & ~0b01111110) | 0b01001110; break;
        case 13: PORTD = (PORTD & ~0b01111110) | 0b00111110; break;
        case 14: PORTD = (PORTD & ~0b01111110) | 0b00011110; break;
        case 15: PORTD = (PORTD & ~0b01111110) | 0b01000110; break;
        case 16: PORTD = (PORTD & ~0b01111110) | 0b00100110; break;
        case 17: PORTD = (PORTD & ~0b01111110) | 0b00101110; break;
    }
}

void matrix_init_custom(void) {
    /* Column output pins */
    setPinOutput(D1);
    setPinOutput(D2);
    setPinOutput(D3);
    setPinOutput(D4);
    setPinOutput(D5);
    setPinOutput(D6);

    /* Row input pins */
    writePinHigh(B0);
    writePinHigh(B1);
    writePinHigh(B2);
    writePinHigh(B3);
    writePinHigh(B4);
    writePinHigh(B5);
    writePinHigh(B6);
    writePinHigh(C2);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        select_col(col);
        matrix_io_delay();
        matrix_row_t rows = read_rows();

        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            bool prev_bit = current_matrix[row] & ((matrix_row_t)1 << col);
            bool curr_bit = rows & (1 << row);

            if (prev_bit != curr_bit) {
                current_matrix[row] ^= (matrix_row_t)1 << col;
                changed = true;
            }
        }
    }

    return changed;
}
