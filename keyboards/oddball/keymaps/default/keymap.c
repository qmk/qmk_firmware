/* Copyright 2020 Alexander Tulloh
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

enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
     KC_BSPC,   KC_Q,    KC_W,    KC_E,    KC_R,       KC_T,          KC_Y,     KC_U,     KC_I,    KC_O,    KC_P,    KC_TAB,
     KC_LALT,   KC_A,    KC_S,    KC_D,    KC_F,       KC_G,          KC_H,     KC_J,     KC_K,    KC_L,    KC_SCLN, KC_SPC,
     KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,       KC_B,          KC_N,     KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                           MO(_LOWER), KC_LCTL,       _______,  MO(_RAISE)
  ),

  [_LOWER] = LAYOUT(
     KC_DEL,    KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_BTN3,       KC_DQUO,  KC_7,    KC_8,    KC_9,    KC_ASTR, KC_UNDS,
     KC_SCROLL, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_BTN2,       KC_QUOT,  KC_4,    KC_5,    KC_6,    KC_PLUS, KC_ENT,
     _______,   KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_BTN1,       KC_0,     KC_1,    KC_2,    KC_3,    KC_MINS, _______,
                                           _______, _______,       _______,  _______
  ),

  [_RAISE] = LAYOUT(
     _______,   KC_ESC,  KC_F7,   KC_F9,   KC_F9,   KC_F10,        KC_PIPE,  KC_PGUP, KC_UP,   KC_PGDN, KC_GRAVE, _______,
     _______,   KC_LGUI, KC_F4,   KC_F5,   KC_F6,   KC_F11,        KC_AMPR,  KC_LEFT, KC_DOWN, KC_RGHT, KC_TILD,  _______,
     _______,   KC_INS,  KC_F1,   KC_F2,   KC_F3,   KC_F12,        KC_EQUAL, KC_HOME, KC_MPLY, KC_END,  KC_BSLS,  _______,
                                           _______, _______,       _______,  _______
  )
};
