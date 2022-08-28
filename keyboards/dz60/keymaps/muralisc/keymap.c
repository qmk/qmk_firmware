/* Copyright 2022 Murali Suresh
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

// Copied from keyboards/dz60/keymaps/60_ansi/keymap.c

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,------------------------------------------------------------------------------------------.
   * | ` ~  |  1! |  2@ |  3# |  4$ |  5% |  6^ |  7& |  8* |  9( |  0) |  -  |  =  |   Bkspc   |
   * |------------------------------------------------------------------------------------------+
   * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |     \   |
   * |------------------------------------------------------------------------------------------+
   * | Ctl_T(C) |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
   * |------------------------------------------------------------------------------------------+
   * | Shift      |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |    RShift       |
   * |------------------------------------------------------------------------------------------+
   * |  MO1  |  Cmd  |  Alt  |              Space                | RAlt | Cmd  |  MO2  |  RCTL  |
   * `------------------------------------------------------------------------------------------'
   */

	LAYOUT_60_ansi(
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
		MO(1)  , KC_LGUI,          KC_LALT,                   KC_SPC,                             KC_RALT, KC_RGUI,          MO(2),   KC_RCTL),

  /* Qwerty
   * ,------------------------------------------------------------------------------------------.
   * | Esc  |  F1 |  F2 |  F3 |  F4 |  5% |  6^ |  7& |  8* |  9( |  0) |  -  |  =  |   Bkspc   |
   * |------------------------------------------------------------------------------------------+
   * | Tab    |  Q  |  W  | End |  R  |  T  |  Y  |  U  |  I  |  O  | PsCr| SlCk| Paus|     \   |
   * |------------------------------------------------------------------------------------------+
   * | Ctl_T(C) | Home|  S  |  D  | Pgdn|  G  | Left| Down| Up  | Rght| Home| PgUp|    Enter    |
   * |------------------------------------------------------------------------------------------+
   * | Shift      |  Z  |  X  |  C  |  V  | PgUp|  N  |  M  |  ,  | End | PgDn|    RShift       |
   * |------------------------------------------------------------------------------------------+
   * |  MO1  |  Cmd  |  Alt  |              Space                | RAlt | Cmd  |  MO2  |  RCTL  |
   * `------------------------------------------------------------------------------------------'
   */


	LAYOUT_60_ansi(
		KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,
		KC_TRNS,          KC_TRNS, KC_TRNS, KC_END , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS, QK_BOOT,
		KC_TRNS,          KC_HOME, KC_TRNS, KC_TRNS, KC_PGDN, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP ,  KC_RGHT, KC_HOME, KC_PGUP, KC_TRNS,
		KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS, KC_END,  KC_PGDN,          KC_TRNS,
		KC_TRNS, KC_TRNS,          KC_TRNS,                   KC_TRNS,                            KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS),

	LAYOUT_60_ansi(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,
		KC_TRNS,          RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS, QK_BOOT,
		KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS,  KC_HOME, KC_PGUP, KC_TRNS,
		KC_TRNS,          KC_TRNS, KC_TRNS, BL_DEC,  BL_TOGG, BL_INC,  BL_STEP, KC_TRNS, KC_DEL,  KC_END,  KC_PGDN,          KC_TRNS,
		KC_TRNS, KC_TRNS,          KC_TRNS,                   KC_TRNS,                            KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS)
};
