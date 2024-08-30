/*
Copyright 2021 Paul Ewing

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

enum bloomer_layers {
  DEFAULT,
  FN
};

#define RGB_N UG_NEXT // Rotate to next RGB mode
#define RGB_P UG_PREV // Rotate to next RGB mode

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[DEFAULT] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_PSCR, KC_SCRL, KC_PAUS,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_INS,  KC_HOME, KC_PGUP,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_CAPS, KC_END,  KC_PGDN,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                 KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LEFT, KC_UP,   KC_RGHT,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LGUI, KC_LALT, KC_GRV,  MO(FN),  KC_BSPC, KC_DEL,  KC_DOWN, KC_ENT,    KC_SPC,  KC_LBRC, KC_RBRC, KC_RALT, KC_RGUI, KC_RCTL
),

[FN] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,
    _______, _______, _______, _______, _______, _______, UG_HUEU, UG_SATU, UG_VALU, _______, _______, _______, _______, _______, _______,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, UG_HUED, UG_SATD, UG_VALD, _______, KC_GRV,  KC_LBRC, KC_RBRC, _______, _______,
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, RGB_P,   UG_TOGG, RGB_N,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
    _______, _______, _______, _______, _______, _______, _______, RGB_M_P, _______, _______, _______, _______, _______, _______, _______
)

};

