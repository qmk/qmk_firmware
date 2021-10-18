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

#include "ninjin.h"

void eeconfig_init_kb(void) {  // EEPROM is getting reset!
    rgblight_enable(); // Enable RGB by default
    rgblight_mode(RGBLIGHT_MODE_RGB_TEST); // set to RGBLIGHT_MODE_RGB_TEST by default

    eeconfig_update_kb(0);
    eeconfig_init_user();
}

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

    /* Order of pins is: A9, A8, B15, B14, B13, B12, B11, B10, B2, B1, B0, A7, A6, A5, A4, B6, B5
       Pin is active low, therefore we have to invert the result. */

    matrix_row_t cols = ~(((porta & (0x1 <<  9)) >>  9)   // A9  (0)
                        | ((porta & (0x1 <<  8)) >>  7)   // A8  (1)
                        | ((portb & (0x1 << 15)) >> 13)   // B15 (2)
                        | ((portb & (0x1 << 14)) >> 11)   // B14 (3)
                        | ((portb & (0x1 << 13)) >>  9)   // B13 (4)
                        | ((portb & (0x1 << 12)) >>  7)   // B12 (5)
                        | ((portb & (0x1 << 11)) >>  5)   // B11 (6)
                        | ((portb & (0x1 << 10)) >>  3)   // B10 (7)
                        | ((portb & (0x1 <<  2)) <<  6)   // B2  (8)
                        | ((portb & (0x1 <<  1)) <<  8)   // B1  (9)
                        | ((portb & (0x1 <<  0)) << 10)   // B0  (10)
                        | ((porta & (0x1 <<  7)) <<  4)   // A7  (11)
                        | ((porta & (0x1 <<  6)) <<  6)   // A6  (12)
                        | ((porta & (0x1 <<  5)) <<  8)   // A5  (13)
                        | ((porta & (0x1 <<  4)) << 10)   // A4  (14)
                        | ((portb & (0x1 <<  6)) <<  9)   // B6  (15)
                        | ((portb & (0x1 <<  5)) << 11)); // B5  (16)

    current_matrix[current_row] = cols;

    /* Wait until col pins are high again or 'timer' expired. */
    // Taken from karlk90/yaemk
    size_t counter = 0xFF;
    while (((palReadGroup(GPIOA, 0x3F0, 0) != 0x3F0)
            || ((palReadGroup(GPIOB, 0xFC67, 0) != 0x3))) && counter != 0) {
        counter--;
    }
}

