/*
Copyright 2021 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include QMK_KEYBOARD_H

#include "lib/keyball/keyball.h"

//////////////////////////////////////////////////////////////////////////////

// clang-format off
matrix_row_t matrix_mask[MATRIX_ROWS] = {
    0b0111111,
    0b0111111,
    0b0011111,
    0b0011111,

    0b0111111,
    0b0111111,
    0b0011111,
    0b0011111,
};
// clang-format on

//////////////////////////////////////////////////////////////////////////////

static uint8_t peek_matrix_intersection(pin_t out_pin, pin_t in_pin) {
    extern void matrix_io_delay(void);
    setPinInputHigh(in_pin);
    setPinOutput(out_pin);
    writePinLow(out_pin);
    wait_us(1);
    uint8_t pin_state = readPin(in_pin);
    setPinInputHigh(out_pin);
    matrix_io_delay();
    return pin_state;
}

bool is_keyboard_left(void) {
    return !peek_matrix_intersection(keyball.this_have_ball ? F7 : F6, B5);
}

//////////////////////////////////////////////////////////////////////////////

void keyball_on_adjust_layout(keyball_adjust_t v) {
    if (v == KEYBALL_ADJUST_PRIMARY) {
        // adjust matrix mask
        bool is_left                                                      = is_keyboard_left();
        matrix_mask[(is_left ? 2 : 6) + (keyball.this_have_ball ? 0 : 1)] = 0b0111111;
        matrix_mask[(is_left ? 6 : 2) + (keyball.that_have_ball ? 0 : 1)] = 0b0111111;
    }
}
