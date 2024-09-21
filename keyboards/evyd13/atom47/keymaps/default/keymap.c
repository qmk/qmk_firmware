/*
Copyright 2021 Evelien Dekkers

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

#define _MA 0 //Main layer
#define _FN 1 //Fn
#define _FN1 2 //Fn1
#define _PN 3 //Pn

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_MA] = LAYOUT_split_space(
  KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_DEL,   KC_BSPC,
  KC_TAB,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,            KC_ENT,
  KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_RSFT,  MO(_FN1),
  KC_LCTL,  KC_LGUI,  KC_LALT,  MO(_PN),            KC_SPC,             KC_SPC,             MO(_FN),  KC_RALT,  KC_APP,   KC_RCTL),
 
[_FN] = LAYOUT_split_space(
  _______,  KC_VOLD,  KC_VOLU,  KC_MUTE,  QK_BOOT,  _______,  KC_CALC,  KC_PGUP,  KC_UP,    KC_PGDN,  KC_PSCR,  KC_SCRL,  KC_PAUS,
  KC_CAPS,  KC_MPRV,  KC_MPLY,  KC_MNXT,  _______,  _______,  KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RIGHT, KC_INS,             _______,
  _______,            _______,  _______,  _______,  _______,  _______,  _______,  BL_TOGG,  BL_DOWN,  BL_UP,    _______,  _______,
  _______,  _______,  _______,  _______,            _______,            _______,            _______,  _______,  _______,  _______),
 
[_FN1] = LAYOUT_split_space(
  KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,            KC_EQL,
  _______,            _______,  _______,  _______,  _______,  KC_QUOT,  KC_SLSH,  KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_RSFT,  _______,
  _______,  _______,  _______,  _______,            _______,            _______,            _______,  _______,  _______,  _______),
 
[_PN] = LAYOUT_split_space(
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  RGB_TOG,  RGB_HUI,  RGB_SAI,  RGB_VAI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  RGB_MOD,            RGB_HUD,  RGB_SAD,  RGB_VAD,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,            _______,            _______,            _______,  _______,  _______,  QK_BOOT),
};
