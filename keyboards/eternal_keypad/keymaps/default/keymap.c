/* Copyright 2021 duckyb
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
    _BASE,
    _ARROW,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base Layer
   * ,-------------------------------------.
   * |     |  Esc  |  1|  2|  3|  4|  5|  6|
	 * |		 |-------+---+---+---+---+---+---|
   * |     |  Tab  |  Q|  W|  E|  R|  T|  7|
	 * |----||-------+---+---+---+---+---+---|
   * | F13|| Enter |  A|  S|  D|  F|  G|  8|
	 * |----||-------+---+---+---+---+---+---|
   * | F14|| Shift |  Z|  X|  C|  V|  B|  9|
   * |----||-------------------------------|
   * | F15|| LCtrl | _FN |Alt|  Space  |  0|
   * `----'`-------------------------------'
   */
    [_BASE] = LAYOUT(
		        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, 
		        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_7, 
		KC_F13, KC_ENT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_8, 
		KC_F14, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_9, 
		KC_F15, KC_LCTL, OSL(_FN), KC_LALT, KC_SPC, LT(_ARROW, KC_0)
    ),
  /* Arrows Layer
   * ,--------------------------------------------------.
   * |     |       |    |    |     |    |       |       |
	 * |		 |-------+----+----+-----+----+-------+-------|
   * |     |       |    |  UP|     |RGB?|  HUE+ |  HUE- |
	 * |----||-------+----+----+-----+----+-------+-------|
   * |    ||       |LEFT|DOWN|RIGHT|    |BRIGHT+|BRIGHT-|
	 * |----||-------+----+----+-----+----+-------+-------|
   * |    ||       |    |    |     |    | MODE+ | MODE- |
   * |----||--------------------------------------------|
   * | RST||       |       |     |         |            |
   * `----'`--------------------------------------------'
   */
    [_ARROW] = LAYOUT(
		         _______, _______, _______, _______, _______, _______, _______,
		         _______, _______, KC_UP, _______, RGB_TOG, RGB_HUI, RGB_HUD, 
		_______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, RGB_VAI, RGB_VAD, 
		_______, _______, _______, _______, _______, _______, RGB_MOD, RGB_RMOD, 
		QK_BOOT, _______, _______, _______, _______, _______
    ),
  /* Function Layer
   * ,-------------------------------------.
   * |     |       | F1| F2| F3| F4| F5| F6|
	 * |		 |-------+---+---+---+---+---+---|
   * |     |       |  P|  O|  I|  U|  Y| F7|
	 * |----||-------+---+---+---+---+---+---|
   * |    ||  Bspc |  ;|  L|  K|  J|  H| F8|
	 * |----||-------+---+---+---+---+---+---|
   * |    ||       |Gui|  M|  N|F12|F11| F9|
   * |----||-------------------------------|
   * |    ||       |     |   |         |F10|
   * `----'`-------------------------------'
   */
    [_FN] = LAYOUT(
		         _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,
		         _______, KC_P, KC_O, KC_I, KC_U, KC_Y, KC_F7, 
		_______, KC_BSPC, KC_SCLN, KC_L, KC_K, KC_J, KC_H, KC_F8, 
		_______, _______, KC_LGUI, KC_M, KC_N, KC_F12, KC_F11, KC_F9, 
		_______, _______, _______, _______, _______, KC_F10
    )
};
