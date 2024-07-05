/* Copyright 2020 rtwayland
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
  _BASE,
  _SYMBOL,
  _NUM,
  _NAV,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
      LCTL_T(KC_ESC), KC_A, KC_S, KC_D, LT(2,KC_F), KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
      KC_LALT, LGUI_T(KC_Z), KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, LGUI_T(KC_SLSH), KC_ENT,
      MO(3), KC_LSFT, LALT_T(KC_TAB), LT(3,KC_ENT), LT(1,KC_SPC), KC_BSPC
     ),
  [_SYMBOL] = LAYOUT(
      LCTL(KC_C), KC_TILD, KC_AT, KC_LCBR, KC_RCBR, KC_HASH, KC_ASTR, KC_CIRC, KC_AMPR, KC_PIPE, KC_BSLS, LCTL(KC_GRV),
      KC_LCTL, KC_GRV, KC_MINS, KC_LPRN, KC_RPRN, KC_EXLM, KC_QUES, KC_DLR, KC_LT, KC_GT, KC_SLSH, KC_DQUO,
      KC_LALT, KC_LGUI, KC_UNDS, KC_LBRC, KC_RBRC, KC_PLUS, KC_P0, KC_EQL, KC_PERC, KC_COLN, KC_NO, KC_NO,
      KC_TRNS, KC_LSFT, KC_NO, KC_TRNS, KC_TRNS, KC_NO
     ),
  [_NUM] = LAYOUT(
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_ASTR, KC_7, KC_8, KC_9, KC_SLSH, KC_EQL,
      KC_LCTL, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_PLUS, KC_4, KC_5, KC_6, KC_MINS, KC_PERC,
      KC_LALT, KC_LGUI, KC_NO, KC_NO, KC_NO, KC_NO,  KC_0, KC_1, KC_2, KC_3, KC_DOT, KC_PENT,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_SPC, KC_BSPC
     ),
  [_NAV] = LAYOUT(
      KC_NO, KC_NO, LALT(KC_RGHT), SGUI(KC_LBRC), SGUI(KC_RBRC), KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_NO, KC_NO, KC_NO,
      KC_NO, KC_LCTL, KC_LALT, KC_LSFT, KC_LGUI, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LALT(KC_LEFT), KC_END, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
      KC_TRNS, KC_NO, KC_NO, KC_NO, KC_SPC, KC_BSPC
     )
};
