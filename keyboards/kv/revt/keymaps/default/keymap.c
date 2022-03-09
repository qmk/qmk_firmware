/* Copyright 2020 Hybrid65
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
/* Keymap (Base Layer) Default Layer
   *.----------------------------------------------------------------------------------------------------------------.
   *|                           |Esc|   | F1| F2| F3| F4| | F5| F6| F7| F8| | F9|F10|F12|F12|     |Pscr| Slck | Pause|
   *| Nlck|  / |  * |  -  |     | ~ |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0| - | = |Backsp |     | Inc| Home |  PgUp|
   *|----------------------------------------------------------------------------------------------------------------|
   *| NP7 | NP8| NP9|     |     |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P| [ | ] |  \  |     | Del|  End |  PgDw|
   *|---------------|  +  |------------------------------------------------------------------------------------------|
   *| NP4 | NP5| NP6|     |     |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L| ; | ' |Return |                        |
   *|---------------|-----|------------------------------------------------------------------------------------------|
   *| NP1 | NP2| NP3|     |     |Shift   |  Z|  X|  C|  V|  B|  N|  M| , | . | / |   Shift  |          |  Up  |      |
   *|---------------|Enter|------------------------------------------------------------------------------------------|
   *|    0     | Del|     |     |Ctrl|Win |Alt |        Space          |Alt | Win |FN |Ctrl |     |Left| Down | Right|
   *`----------------------------------------------------------------------------------------------------------------'
   */
[0] = LAYOUT_default(
                                        KC_ESC,           KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,    KC_PSCR, KC_SLCK, KC_PAUS,
  KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,   KC_GRV,  KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP,
  KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS,   KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN,
  KC_KP_4, KC_KP_5, KC_KP_6,            KC_CAPS, KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
  KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT,   KC_LSFT, KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,            KC_UP,
  KC_KP_0,          KC_PDOT,            KC_LCTL, KC_LGUI, KC_LALT,                KC_SPC,                                   KC_RALT, KC_RGUI, MO(1),   KC_RCTL,   KC_LEFT, KC_DOWN, KC_RIGHT),

/* Keymap Fn Layer
  *.-----------------------------------------------------------------------------------------------------------------.
  *|                           |   |   |F13|F14|F15|F16| |F17|F18|F19|F20| |F21|F22|F23|F24|     |     |      |      |
  *|     |    |    |     |     |   |   |   |   |   |   |   |   |   |   |   |   |   |       |     |Pl/Pa|  Next|  Vol+|
  *|-----------------------------------------------------------------------------------------------------------------|
  *|     |    |    |     |     |     |MB1|MBU|MB2|MWU|   |   |   |   |   |   |   |   |     |     | Stop|  Prev|  Vol-|
  *|---------------|     |-------------------------------------------------------------------------------------------|
  *|     |    |    |     |     |       |MBL|MBD|MBR|MWD|   |   |   |Rst|   |   |   |       |                         |
  *|---------------|-----|-------------------------------------------------------------------------------------------|
  *|     |    |    |     |     |        |   |   |Calc|   |   |   |Mute|   |   |   |        |           |      |      |
  *|---------------|     |-------------------------------------------------------------------------------------------|
  *|          |    |     |     |    |    |    |                       |    |     |   |     |     |     |      |      |
  *'-----------------------------------------------------------------------------------------------------------------'
  */
[1] = LAYOUT_default(
                                      _______,             KC_F13,  KC_F14,     KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,    _______, _______, _______,
_______, _______, _______, _______,   _______, _______,    _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   KC_MPLY, KC_MNXT, KC_VOLU,
_______, _______, _______, _______,   _______, KC_MS_BTN1, KC_MS_U, KC_MS_BTN2, KC_WH_U, _______, _______, _______, _______, _______, _______, _______, _______, _______,   KC_MSTP, KC_MPRV, KC_VOLD,
_______, _______, _______,            _______, KC_MS_L,    KC_MS_D, KC_MS_R,    KC_WH_D, _______, _______, _______,   RESET, _______, _______, _______,          _______,
_______, _______, _______, _______,   _______, _______,    _______, KC_CALC,    _______, _______, _______, KC_MUTE, _______, _______, _______,                   _______,            _______,
_______,          _______,            _______, _______,    _______,                      _______,                                     _______, _______, _______, _______,   _______, _______, _______),

};
