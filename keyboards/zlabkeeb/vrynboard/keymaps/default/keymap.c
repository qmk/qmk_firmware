/*
Copyright 2024 zlabkeeb (zlabkeeb@gmail.com)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        QK_KB_0,
        KC_VOLD,   KC_MUTE,   KC_VOLU,
        KC_LEFT,   KC_MPLY,   KC_RGHT,
        KC_ESC,    KC_PSCR,   KC_DEL
    ),

    [1] = LAYOUT(
        QK_KB_0,
        KC_1,   KC_2,   KC_3,
        KC_4,   KC_6,   KC_7,
        KC_TRNS,   KC_TRNS,   KC_TRNS
    ),

    [2] = LAYOUT(
        QK_KB_0,
        KC_J,   KC_K,   KC_L,
        KC_M,   KC_N,   KC_O,
        KC_TRNS,   KC_TRNS,   KC_TRNS
    ),

    [3] = LAYOUT(
        QK_KB_0,
        UG_NEXT,   UG_TOGG,  UG_PREV,
        UG_HUED,   KC_ESC,   UG_HUEU,
        UG_VALD,   KC_ENT,   UG_VALU
    )
};
