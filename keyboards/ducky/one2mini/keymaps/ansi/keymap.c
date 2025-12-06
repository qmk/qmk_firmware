/* Copyright 2019 /u/KeepItUnder
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

// LAYERS
enum Layer {
    _QWERTY = 0,        // Standard QWERTY layer
    _FUNCTION,          // Function key layer
    _COLOUR             // RGB key layer
};
#define _QW _QWERTY
#define _FN _FUNCTION
#define _CLR _COLOUR

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14
    QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_NUBS,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RGUI, MO(_FN), KC_RCTL
  ),

  [_FUNCTION] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
    _______, MS_BTN1, MS_UP,   MS_BTN2, MS_WHLU, _______, KC_INS,  _______, KC_UP,   KC_PAUS, KC_PGUP, KC_HOME, KC_PSCR, _______,
    _______, MS_LEFT, MS_DOWN, MS_RGHT, MS_WHLD, _______, KC_SCRL, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_END,           KC_ENT,
    _______,          _______, KC_APP,  _______, _______, _______, KC_CALC, KC_MUTE, KC_VOLD, KC_VOLU, _______,          _______,
    _______, KC_APP,  MO(_CLR),                           _______,                            _______, KC_APP,  _______, _______
  ),

  [_COLOUR] = LAYOUT_60_ansi(
    //       2        3        4        5        6        7        8        9        10       11       12       13       14
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, RM_NEXT, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, RM_HUEU, RM_SATU, RM_VALU, RM_SPDU, _______, _______, _______, _______, _______, _______,          _______,
    _______,          RM_HUED, RM_SATD, RM_VALD, RM_SPDD, _______, _______, _______, _______, _______, _______,          _______,
    _______, _______, _______,                            RM_TOGG,                            _______, _______, _______, _______
  ),
};
