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

#include "rev2.h"

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  { 24,     NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
  { 25,     NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
  { 26,     27,     NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
  { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
  { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
}, {
  // LED Index to Physical Position
    { 224,  0 },
    { 224,  9 },
    { 224, 21 },
    { 224, 33 },
    { 224, 45 },
    { 223, 51 },
    { 206, 52 },
    { 190, 52 },
    { 172, 52 },
    { 154, 57 },
    { 136, 61 },
    { 118, 63 },
    { 101, 64 },
    { 80 , 60 },
    { 64 , 57 },
    { 46 , 53 },
    { 28 , 53 },
    { 10 , 52 },
    { 3  , 51 },
    { 2  , 45 },
    { 2  , 33 },
    { 2  , 20 },
    { 2  ,  9 },
    { 0  ,  0 },
    { 9  ,  3 },
    { 6  , 14 },
    { 4  , 26 },
    { 21 , 27 }

}, {
  // LED Index to Flag
  2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2,
  8, 8, 8, 8
} };


void keyboard_pre_init_kb(void) {
    rgb_matrix_set_flags(LED_FLAG_MODIFIER|LED_FLAG_UNDERGLOW|LED_FLAG_KEYLIGHT);
    keyboard_pre_init_user();
}
#endif

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

    /* Order of pins is: B2, B1, B0, A7, A6, A5, A4, A13, B7, B6, B5, B4, B3, A15, A14
       Pin is active low, therefore we have to invert the result. */

    matrix_row_t cols = ~(((portb & (0x1 <<  2)) >>  2)   // B2  (0)
                        | ((portb & (0x1 <<  1)) >>  0)   // B1  (1)
                        | ((portb & (0x1 <<  0)) <<  2)   // B0  (2)
                        | ((porta & (0x1 <<  7)) >>  4)   // A7  (3)
                        | ((porta & (0x1 <<  6)) >>  2)   // A6  (4)
                        | ((porta & (0x1 <<  5)) >>  0)   // A5  (5)
                        | ((porta & (0x1 <<  4)) <<  2)   // A4  (6)
                        | ((porta & (0x1 << 13)) >>  6)   // A13 (7)
                        | ((portb & (0x1 <<  7)) <<  1)   // B7  (8)
                        | ((portb & (0x1 <<  6)) <<  3)   // B6  (9)
                        | ((portb & (0x1 <<  5)) <<  5)   // B5  (10)
                        | ((portb & (0x1 <<  4)) <<  7)   // B4  (11)
                        | ((portb & (0x1 <<  3)) <<  9)   // B3  (12)
                        | ((porta & (0x1 << 15)) >>  2)   // A15 (13)
                        | ((porta & (0x1 << 14)) >>  0)); // A14 (14)

    current_matrix[current_row] = cols;

    /* Wait until col pins are high again or 'timer' expired. */
    // Taken from karlk90/yaemk
    size_t counter = 0xFF;
    while (((palReadGroup(GPIOA, 0xE0E0, 0) != 0xE0E0) || ((palReadGroup(GPIOB, 0xFF, 0) != 0xFF))) && counter != 0) {
        counter--;
    }
}
