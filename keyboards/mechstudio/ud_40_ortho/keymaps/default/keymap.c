/* Copyright 2020 David Dejaeghere
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _MA,
    _LO,
    _HI
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_MA] = LAYOUT_ortho_4x12(
  KC_ESC,   KC_Q,        KC_W,        KC_E,        KC_R,        KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
  KC_TAB,   KC_A,        KC_S,        KC_D,        KC_F,        KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
  KC_LSFT,  KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_ENT,
  _______,  KC_LCTL,     KC_LALT,     KC_LGUI,     MO(_LO),     KC_SPC,   KC_SPC,   MO(_HI),  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT),

[_LO] = LAYOUT_ortho_4x12(
  KC_GRV,   KC_1,        KC_2,        KC_3,        KC_4,        KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_DEL,
  KC_TILD,  KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,    KC_F6,    KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,  KC_BSLS,
  _______,  KC_F7,       KC_F8,       KC_F9,       KC_F10,      KC_F11,   KC_F12,   _______,  _______,  KC_PGUP,  KC_PGDN,  _______,
  KC_INS,   KC_HOME,     KC_END,      KC_DEL,      _______,     _______,  _______,  _______,  _______,  KC_VOLD,  KC_VOLU,  _______),

[_HI] = LAYOUT_ortho_4x12(
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  UG_TOGG,  UG_NEXT,  UG_HUEU,  UG_SATU,  UG_VALU,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  UG_PREV,  UG_HUED,  UG_SATD,  UG_VALD,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______),
};
