/* Copyright 2018  Andrew Heaston  @rooski15
 *
 * Developed by /u/holtenc at www.primekb.com
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
// Prime_R Rev 1.0

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* (Base Layer) Default Layer
   * ,---------------------------------------------------------------.
   * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|PUP|BSP|PSC|PUP|PDN|
   * |---------------------------------------------------------------|
   * |Grv|  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|PDN|DEL|  7|  8|  9|
   * |---------------------------------------------------------------|
   * |Tab |  A|  S|  D|  F|  G|  H|  J|  K|  L|  '|Return|  4|  5|  6|
   * |---------------------------------------------------------------|
   * |Shift|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  ?|Shift|  1|  2|  3|
   * |---------------------------------------------------------------|
   * |Ctrl|Gui |App|Alt| Space| Space  |Alt|App|GUI|Ctrl |  0|  .|Ret|
   * `---------------------------------------------------------------'
   */
  // 0: Base Layer
  [0] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_PGUP, KC_BSPC, KC_PSCR, KC_PGUP, KC_PGDN,
    KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_PGDN, KC_DEL,  KC_7,    KC_8,    KC_9,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,    KC_J,   KC_K,    KC_L,    KC_DQUO,          KC_ENT,  KC_4,    KC_5,    KC_6,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,    KC_N,   KC_M,    KC_LABK, KC_RABK, KC_QUES, KC_LSFT, KC_1,    KC_2,    KC_3,
    KC_LCTL,          KC_LGUI, KC_APP,  KC_LALT, MO(0),           KC_SPC,          KC_RALT, KC_APP,  KC_RGUI, KC_RCTL, KC_0,    KC_DOT,  KC_ENT
  ),

  // 1: Function Layer
  [1] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,          _______, _______, _______, _______, _______,          _______,          _______, _______, _______, _______, _______, _______
  ),

};
