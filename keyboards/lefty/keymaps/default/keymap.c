/* Copyright 2021 Smoll Chungus (@smollchungus)
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

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _SPECIAL,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define SPECIAL MO(_SPECIAL)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT(
        KC_UP,      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
        KC_DOWN,    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        KC_RGHT,    LOWER,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
                    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
                    KC_LCTL,          KC_LALT,          RAISE,   SPECIAL
    ),

    [_LOWER] = LAYOUT(
        _______,    _______, _______, _______, _______, _______, _______, _______,
        _______,    _______, _______, _______, _______, _______, _______,
        _______,    _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______, _______,
                    _______,          _______,          _______, _______
    ),

    [_RAISE] = LAYOUT(
        _______,    _______, _______, _______, _______, _______, _______, _______,
        _______,    _______, _______, _______, _______, _______, _______,
        _______,    _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______, _______,
                    _______,          _______,          _______, _______
    ),

    [_SPECIAL] = LAYOUT(
        _______,    _______, _______, _______, _______, _______, _______, _______,
        _______,    _______, _______, _______, _______, _______, _______,
        _______,    _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______, _______,
                    _______,          _______,          _______, _______
    )

};
