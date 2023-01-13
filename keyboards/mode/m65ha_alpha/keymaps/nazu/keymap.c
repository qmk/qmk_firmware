/* Copyright 2023 Tom Sennewald (@beelzebubi)
 * SPDX-License-Identifier: GPL-2.0-or-later
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

#include "nazu.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   * QWERTY
   * ,-----------------------------------------------------------------------------------------------,
   * |  ^  | 1 ! | 2 @ | 3 # | 4 $ | 5 % | 6 ^ | 7 & | 8 * | 9 ( | 0 ) | - _ | = + | Backspace | Del |
   * |-----------------------------------------------------------------------------------------------|
   * |  Tab   |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |   \ |  |PgUp |
   * |-----------------------------------------------------------------------------------------|-----|
   * |   Caps  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  | ; : | ' " |    Enter    |PgDwn|
   * |-----------------------------------------------------------------------------------------------|
   * |    Shift    |  Z  |  X  |  C  |  V  |  B  |  N  |  M  | , < | . > | / ? |  Shift  | Up  | End |
   * |-----------------------------------------------------------------------------------------------|
   * | LCtl  | LGUI  | LAlt  |            Space                  |RAlt | FN1 |     |Left |Down |Right|
   * `-----------------------------------------------------------------------------------------------´
   */
	[_QWERTY] = LAYOUT_65_ansi_blocker(
    KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,             KC_BSPC,  KC_DEL,
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGUP,
    KC_BSPC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,            KC_ENT,             KC_PGDN,
    TD_CAPS,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,            KC_RSFT,            KC_UP,    KC_END,
    KC_LCTL,  KC_LGUI, KC_LALT,                                TD_SPC,                                   KC_RALT,  MO(_FN1), KC_LEFT,  KC_DOWN,  KC_RGHT
  ),

  /*
   * Colemak DH
   * ,-----------------------------------------------------------------------------------------------,
   * |  `  | 1 ! | 2 @ | 3 # | 4 $ | 5 % | 6 ^ | 7 & | 8 * | 9 ( | 0 ) | - _ | = + | Backspace | Del |
   * |-----------------------------------------------------------------------------------------------|
   * |  Tab   |  Q  |  W  |  F  |  P  |  G  |  J  |  L  |  U  |  Y  | ; : | [ { | ] } |   \ |  |PgUp |
   * |-----------------------------------------------------------------------------------------|-----|
   * |Backspace|  A  |  R  |  S  |  T  |  D  |  H  |  N  |  E  |  I  |  O  | ' " |    Enter    |PgDwn|
   * |-----------------------------------------------------------------------------------------------|
   * |    Shift    |  Z  |  X  |  C  |  V  |  B  |  K  |  M  | , < | . > | / ? |  Shift  | Up  | End |
   * |-----------------------------------------------------------------------------------------------|
   * | LCtl  | LGUI  | LAlt  |            Space                  |RAlt | FN1 |     |Left |Down |Right|
   * `-----------------------------------------------------------------------------------------------´
   */
	[_COLEMAK] = LAYOUT_65_ansi_blocker(
    KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,             KC_BSPC, KC_DEL,
    KC_TAB,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC,  KC_BSLS,           KC_PGUP,
    KC_BSPC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,           KC_ENT,            KC_PGDN,
    TD_CAPS,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,            KC_UP,   KC_END,
    KC_LCTL,  KC_LGUI, KC_LALT,                                TD_SPC,                                  KC_RALT, MO(_FN1), KC_LEFT,  KC_DOWN, KC_RGHT
),

  /*
   * Colemak DH
   * ,-----------------------------------------------------------------------------------------------,
   * |  `  | 1 ! | 2 @ | 3 # | 4 $ | 5 % | 6 ^ | 7 & | 8 * | 9 ( | 0 ) | - _ | = + | Backspace | Del |
   * |-----------------------------------------------------------------------------------------------|
   * |  Tab   |  Q  |  W  |  F  |  P  |  B  |  J  |  L  |  U  |  Y  | ; : | [ { | ] } |   \ |  |PgUp |
   * |-----------------------------------------------------------------------------------------|-----|
   * |Backspace|  A  |  R  |  S  |  T  |  G  |  M  |  N  |  E  |  I  |  O  | ' " |    Enter    |PgDwn|
   * |-----------------------------------------------------------------------------------------------|
   * |    Shift    |  Z  |  X  |  C  |  D  |  V  |  K  |  H  | , < | . > | / ? |  Shift  | Up  | End |
   * |-----------------------------------------------------------------------------------------------|
   * | LCtl  | LGUI  | LAlt  |            Space                  |RAlt | FN1 |     |Left |Down |Right|
   * `-----------------------------------------------------------------------------------------------´
   */
	[_COLEMAK_DH] = LAYOUT_65_ansi_blocker(
    KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,             KC_BSPC, KC_DEL,
    KC_TAB,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC,  KC_BSLS,           KC_PGUP,
    KC_BSPC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,           KC_ENT,            KC_PGDN,
    TD_CAPS,  KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,            KC_UP,   KC_END,
    KC_LCTL,  KC_LGUI, KC_LALT,                                TD_SPC,                                  KC_RALT, MO(_FN1), KC_LEFT,  KC_DOWN, KC_RGHT
),

  /*
   * FN1
   * ,-----------------------------------------------------------------------------------------------,
   * |  `  | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |   Reset   |Mute |
   * |-----------------------------------------------------------------------------------------------|
   * |        |QWRTY|CLMAK|CLMKD|     |     |     |     |     |     |     |     |     |        |SWAP |
   * |-----------------------------------------------------------------------------------------|-----|
   * |         |     |     |     |     |     |     |     |     |     |     |     |             |NORM |
   * |-----------------------------------------------------------------------------------------------|
   * |             |     |     |     |     |     |     |     |     |     |     |         |VolU |Home |
   * |-----------------------------------------------------------------------------------------------|
   * |       |       |       |           Play/Pause              |     |     |     |Prev |VolD |Next |
   * `-----------------------------------------------------------------------------------------------´
   */
	[_FN1] = LAYOUT_65_ansi_blocker(
    KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           QK_BOOT, KC_MUTE,
    _______,  QWERTY,  COLEMAK, CLMKDH,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_SWAP,
    _______,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,          KC_NORM,
    _______,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,          KC_VOLU, KC_HOME,
    _______,  _______,  _______,                                KC_MPLY,                                _______, XXXXXXX, KC_MPRV, KC_VOLD, KC_MNXT
  ),

};
