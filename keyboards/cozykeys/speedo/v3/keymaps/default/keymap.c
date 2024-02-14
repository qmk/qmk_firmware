/*
Copyright 2020 Paul Ewing

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

enum {
  LAYER_DEFAULT,
  LAYER_FN,

  __LAYER_COUNT,
};

#define FN MO(LAYER_FN)

#define RGB_N RGB_MOD  // Rotate to next RGB mode
#define RGB_P RGB_RMOD // Rotate to next RGB mode

const uint16_t PROGMEM keymaps[__LAYER_COUNT][MATRIX_ROWS][MATRIX_COLS] = {

[LAYER_DEFAULT] = LAYOUT(
    KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_UP,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LEFT,           KC_RGHT, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_DOWN,           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LGUI, KC_LALT, KC_GRV,  FN,      KC_BSPC, KC_DEL,            KC_ENT,  KC_SPC,  KC_LBRC, KC_RBRC, KC_RALT, KC_RGUI, KC_RCTL
),

[LAYER_FN] = LAYOUT(
    RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD,                            _______, _______, _______, _______, _______, QK_BOOT,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          RGB_TOG,          _______, KC_GRV,  KC_LBRC, KC_RBRC, _______, _______,
    KC_CAPS, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_INS,  RGB_N,            RGB_P,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_PAUS,          RGB_M_P,          KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
    _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______
),

};
