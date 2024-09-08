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
#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

// enum custom_keycodes {
//   QWERTY = SAFE_RANGE,
//   LOWER,
//   RAISE
// };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        //1      2        3        4        5        6        7        8        9        10       11       12       13       14       15       16       17       18       19       20       21
MO(1), KC_PSLS, KC_PAST, KC_PMNS,
KC_P7, KC_P8,   KC_P9,   KC_PPLS,
KC_P4, KC_P5,   KC_P6,   
KC_P1, KC_P2,   KC_P3,   KC_PENT,
KC_P0,          KC_PDOT


    ),
    [1] = LAYOUT(
        //1      2        3        4        5        6        7        8        9        10       11       12       13       14       15       16       17       18       19       20       21
MO(1),   KC_NUM,  MO(2),   KC_CALC,
KC_HOME, KC_UP,   KC_PGUP, KC_TRNS,
KC_LEFT, KC_TRNS, KC_RGHT,   
KC_END,  KC_DOWN, KC_PGDN, KC_TRNS,
KC_TRNS,          KC_TRNS


    ),
        [2] = LAYOUT(
        //1      2        3        4        5        6        7        8        9        10       11       12       13       14       15       16       17       18       19       20       21
KC_TRNS, KC_TRNS, KC_TRNS, RGB_VAI,
RGB_TOG, RGB_SAI, KC_TRNS, RGB_VAD,
RGB_HUD, KC_TRNS, RGB_HUI,   
KC_TRNS, RGB_SAD, KC_TRNS, KC_TRNS,
RGB_MOD,          KC_TRNS


    )
    
    
};
