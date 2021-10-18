/* Copyright 2021 Harrison Chan (Xelus)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "rev1.h"

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

void matrix_init_pins(void) {
    for (size_t i = 0; i < MATRIX_COLS; i++) {
        setPinInputHigh(col_pins[i]);
    }
    for (size_t i = 0; i < MATRIX_ROWS; i++) {
        setPinOutput(row_pins[i]);
        writePinHigh(row_pins[i]);
    }
}

void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    /* Drive row pin low. */
    writePinLow(row_pins[current_row]);
    while (readPin(row_pins[current_row]) != 0)
        ;

    uint16_t porta = palReadPort(GPIOA);
    uint16_t portb = palReadPort(GPIOB);

    /* Drive row pin high again. */
    writePinHigh(row_pins[current_row]);

    /* Order of pins is: B13, B12, B11, B10, B2, B1, B0, A7, A6, A5, A4, A2, A1, A0, A3, B6, B5
       Pin is active low, therefore we have to invert the result. */

    matrix_row_t cols = ~(((portb & (0x1 << 13)) >> 13)   // B13 (0)
                        | ((portb & (0x1 << 12)) >> 11)   // B12 (1)
                        | ((portb & (0x1 << 11)) >>  9)   // B11 (2)
                        | ((portb & (0x1 << 10)) >>  7)   // B10 (3)
                        | ((portb & (0x1 <<  2)) <<  2)   // B2  (4)
                        | ((portb & (0x1 <<  1)) <<  4)   // B1  (5)
                        | ((portb & (0x1 <<  0)) <<  6)   // B0  (6)
                        | ((porta & (0x1 <<  7)) >>  0)   // A7  (7)
                        | ((porta & (0x1 <<  6)) <<  2)   // A6  (8)
                        | ((porta & (0x1 <<  5)) <<  4)   // A5  (9)
                        | ((porta & (0x1 <<  4)) <<  6)   // A4  (10)
                        | ((porta & (0x1 <<  2)) <<  9)   // A2  (11)
                        | ((porta & (0x1 <<  1)) << 11)   // A1  (12)
                        | ((porta & (0x1 <<  0)) << 13)   // A0  (13)
                        | ((porta & (0x1 <<  3)) << 11)   // A3  (14)
                        | ((portb & (0x1 <<  6)) <<  9)   // B6  (15)
                        | ((portb & (0x1 <<  5)) << 11)); // B5  (16)

    current_matrix[current_row] = cols;

    /* Wait until col pins are high again or 'timer' expired. */
    // Taken from karlk90/yaemk
    size_t counter = 0xFF;
    while (((palReadGroup(GPIOA, 0xFF, 0) != 0xFF)
            || ((palReadGroup(GPIOB, 0x3C67, 0) != 0x3C67))) && counter != 0) {
        counter--;
    }
}
