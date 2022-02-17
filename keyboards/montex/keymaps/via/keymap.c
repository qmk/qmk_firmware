/* Copyright 2021 Tybera
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
* along with this program.  If not, see &lt;http://www.gnu.org/licenses/&gt;.
*/

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_numpad_6x5(
        KC_GRAVE,  KC_ESC,  KC_TAB,  MO(1),   KC_BSPC,
        KC_COMMA,  KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
        KC_LGUI,   KC_P7,   KC_P8,   KC_P9,
        KC_LALT,   KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_LSHIFT, KC_P1,   KC_P2,   KC_P3,
        KC_LCTRL,  KC_P0,            KC_PDOT, KC_PENT
    ),
    [1] = LAYOUT_numpad_6x5(
        RESET,   _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, KC_HOME, KC_UP,   KC_PGUP,
        _______, KC_LEFT, XXXXXXX, KC_RGHT, _______,
        _______, KC_END,  KC_DOWN, KC_PGDN,
        _______, KC_INS,           KC_DEL,  _______
    ),
	[2] = LAYOUT_numpad_6x5(
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______,          _______, _______
    ),
	[3] = LAYOUT_numpad_6x5(
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______,          _______, _______
    )
};
