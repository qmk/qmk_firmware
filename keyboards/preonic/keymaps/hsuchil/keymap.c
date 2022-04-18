/*
Copyright 2022 Hector Galindo <hi@hsuchil.com>

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
#include "hsuchil.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BSE] = LAYOUT_preonic_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,  KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
    RCT_ESC, KC_A,    KC_S,    KC_D,    KC_F,  KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    KC_LCTL, KC_HYPR, KC_LALT, KC_LGUI, L_LOW, KC_SPC,  KC_SPC,  L_HGH,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

[_LOW] = LAYOUT_preonic_grid(
    KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______, _______, _______, _______, _______, _______, _______, KC_LCBR, KC_RCBR, KC_QUES, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

[_HGH] = LAYOUT_preonic_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, KC_SLSH, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

[_FNC] = LAYOUT_preonic_grid(
    KC_F1   , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______ , RESET  , DEBUG  , _______, _______, RCG_NRM, RCG_SWP, _______, _______, _______, _______, _______,
    _______ , RGB_SPD, RGB_SPI, _______, _______, AG_NORM, AG_SWAP, _______, _______, _______, _______, _______,
    _______ , RGB_TOG, RGB_MOD, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______ , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

};
