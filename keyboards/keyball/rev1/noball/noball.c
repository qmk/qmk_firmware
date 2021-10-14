/*
Copyright 2021 @Yowkees
Copyright 2021 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include "pointing_device.h"
#include "trackball.h"

// clang-format off
matrix_row_t matrix_mask[MATRIX_ROWS] = {
    0b0111111,
    0b0111111,
    0b0011111,
    0b0111111,

    0b0111111,
    0b0111111,
    0b0011111,
    0b0111111,
};
// clang-format on

bool trackball_has(void) {
    // rev1/ball has a trackball always.
    return false;
}

void trackball_secondary_availablity(bool available) {
    // modify matrix_mask by secondary board type (has ball or no balls)
    int base = is_keyboard_left() ? 4 : 0;
    if (available) {
        matrix_mask[base + 2] = 0b0111111;
        matrix_mask[base + 3] = 0b0011111;
        keyball_adjust_trackball_handness();
    } else {
        matrix_mask[base + 2] = 0b0011111;
        matrix_mask[base + 3] = 0b0111111;
    }
}
