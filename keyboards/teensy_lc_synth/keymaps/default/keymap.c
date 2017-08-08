/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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

#include "teensy_lc_synth.h"

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    KEYMAP(
           KC_1, KC_2,       KC_3, KC_4, KC_5, \
        KC_C, KC_D, KC_E, KC_F, KC_G, KC_A, KC_B \
    )
/*
    KEYMAP(
           KC_NO, KC_NO,       KC_NO, KC_NO, KC_NO, \
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO \
    )
*/
};
