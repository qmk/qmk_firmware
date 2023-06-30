/* Copyright 2020 jrfhoutx
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
 /* Keymap BASE: (Base Layer) Default Layer
   * .----.,---------------------------------------------------------------------.
   * | F1 || Esc |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P| [ | ] |    \   |  Del |
   * |----||---------------------------------------------------------------------|
   * | F2 || Tab   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  Return  |  PgUp|
   * |----||---------------------------------------------------------------------|
   * | F3 ||Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /| Shift | Up  |  PgDn|
   * |----||---------------------------------------------------------------------|
   * | F4 ||LCtrl|LGUI | Alt  |  Space  |  Space  | Alt |   |  L    |  Dn |   R  |
   * `----'`---------------------------------------------------------------------'
   */
[0] = LAYOUT_all( /* Smolka Base */
	KC_F1,   KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,         KC_BSPC, KC_DEL,
    KC_F2,   KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,                  KC_ENT,  KC_HOME,
    KC_F3,   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_RSFT,                  KC_UP,   KC_END,
    KC_F4,   KC_LCTL, MO(1),   KC_LALT,          KC_SPC,           KC_TRNS, KC_SPC,           KC_TRNS, KC_RALT,         KC_LEFT, KC_DOWN, KC_RGHT
  ),

[1] = LAYOUT_all( /* Smolka Base */
	QK_BOOT,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS
  ),
};
