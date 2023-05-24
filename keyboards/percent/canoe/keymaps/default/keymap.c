/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

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

#define _BL 0
#define _FL 1


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BL] = LAYOUT_65_ansi_blocker(
      KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  KC_PSCR,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS,  KC_DEL,
      KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT,  KC_ENT,            KC_PGUP,
      KC_LSFT,          KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, KC_UP,    KC_PGDN,
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                 KC_RALT, MO(_FL),           KC_LEFT, KC_DOWN,  KC_RIGHT),

  [_FL] = LAYOUT_65_ansi_blocker(
      KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_DEL,   KC_PAUS,
      KC_TRNS, KC_NO,   KC_UP,   KC_NO,   RGB_TOG,RGB_VAI,RGB_HUI,RGB_SAI,KC_INS, QK_BOOT,   KC_PSCR, KC_SLCK,  KC_PAUS, KC_BSLS,  KC_SLCK,
      KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT,RGB_MOD,RGB_VAD,RGB_HUD,RGB_SAD,KC_NO,  KC_NO,   KC_F14,  KC_F15,   KC_INS,            KC_HOME,
      KC_LSFT,          KC_MPRV, KC_MPLY, KC_MNXT,KC_NO,  KC_NO,  KC_NO,  KC_MUTE,KC_VOLD, KC_VOLU, KC_NO,    KC_RSFT, KC_PGUP,  KC_END,
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_TRNS,                KC_RALT, KC_TRNS,           KC_HOME, KC_PGDOWN,KC_END)

};
