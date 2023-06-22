/* Copyright 2019 Elliot Powell
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
  KC_F5,    QK_GESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
  KC_PGUP,  KC_TAB,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,       KC_ENT, 
  KC_PGDN,  KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_RSFT,
  KC_ESC,   LCTL_T(KC_LBRC), KC_LGUI, KC_LALT,  KC_SPC,  LT(1, KC_SPC), KC_RALT, MO(2), RCTL_T(KC_RBRC) ),
  [1] = LAYOUT( /* Base */
  _______,  _______,  KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0,     _______,
  _______,  _______,  _______, _______, _______, _______, _______, KC_LEFT, KC_UP,   KC_DOWN, KC_RIGHT,         _______,
  _______,  _______,           KC_VOLD, KC_MUTE, KC_VOLU, _______, _______, _______, _______, KC_MINS, KC_EQL, _______,
  _______,  _______,  _______, _______,          _______,          _______,          _______, _______, _______ ),
  [2] = LAYOUT( /* Base */
  _______,  KC_F1  ,  KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,
  _______,  _______,  _______, _______, _______, _______, _______, _______, KC_SCLN, KC_QUOT, KC_NUHS,          _______,
  _______,  _______,           KC_NUBS, _______, _______, _______, _______, _______, _______, KC_SLSH, _______, _______,
  _______,  _______,  _______, _______,          _______,          _______,          _______, _______,  QK_BOOT ),
};
