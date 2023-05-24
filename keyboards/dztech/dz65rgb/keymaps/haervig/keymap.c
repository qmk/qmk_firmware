/*
Copyright 2021 Jakob Hærvig <jakob.haervig@gmail.com>

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
#include "haervig.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi(
        KC_GESC,        DK_1,    CU_2,    DK_3,    CU_4,    DK_5,    CU_6,    CU_7,    CU_8,    CU_9,    CU_0,    CU_MINS, CU_EQL,  CU_BSPC, KC_HOME,
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    CU_LBRC, CU_RBRC, CU_BSLS, KC_PGUP,
        CTL_T(KC_CAPS), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    CU_SCLN, CU_QUOT,          KC_ENT,  KC_PGDN,
        CU_LSFT,                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    CU_COMM, CU_DOT,  CU_SLSH, CU_RSFT, KC_UP,   KC_END,
        KC_LCTL,        KC_LALT, KC_LGUI,                            KC_SPC,                    MO(1),   KC_RALT,   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_65_ansi(
        _______,        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,  _______,
        _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______,                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,        _______, _______,                            _______,                   _______, _______, _______, _______, _______, _______
    )
};
