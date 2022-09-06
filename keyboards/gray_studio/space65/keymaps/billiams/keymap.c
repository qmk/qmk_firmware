/* Copyright 2019 MechMerlin
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

  /* Qwerty
   * ,------------------------------------------------------------------------------------------------.
   * |  `  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  | \ |  DEL  |  INS |
   * |------------------------------------------------------------------------------------------------+
   * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  | Bkspc  | PGUP |
   * |------------------------------------------------------------------------------------------------+
   * |   Fn1   |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    | PGDN |
   * |------------------------------------------------------------------------------------------------+
   * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  | ?/ |    Shift   | Up  |  ESC |
   * |------------------------------------------------------------------------------------------------+
   * | Ctrl |  Alt  |  Cmd  |              Space               |  Alt |  Ctrl |  Left  | Down | Right |
   * `------------------------------------------------------------------------------------------------'
   */

[0] = LAYOUT( \
        KC_GRAVE, KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL, KC_INS, \
        KC_TAB,   KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC, KC_PGUP,        \
        MO(1),    KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_PGDN,                 \
        KC_LSFT,  KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_ESC,         \
        KC_LCTL,  KC_LALT, KC_LGUI,                KC_SPC, KC_SPC, KC_SPC,         KC_RALT, KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT         \
    ),

  /* 1st Layer
   * ,------------------------------------------------------------------------------------------------.
   * |     |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |Vol- |Vol+ | Next |
   * |------------------------------------------------------------------------------------------------+
   * |        |RGB T|RGB M| Hue-| Hue+| Sat-| Sat+| Val-| Val+|      |      |    |      |      | Prev |
   * |------------------------------------------------------------------------------------------------+
   * |         | RGBP | RGPG | RGPK |    |     | Left| Down| Up |Right|     |     | Play/Pause |      |
   * |------------------------------------------------------------------------------------------------+
   * |           |     |     |     |     |     |     |     |    | Scr- | Scr+ |    |    | PGUP |      |
   * |------------------------------------------------------------------------------------------------+
   * |      |       |       |                                  |      |  Fn2  |  HOME  | PGDN  |  END |
   * `------------------------------------------------------------------------------------------------'
   */

[1] = LAYOUT( \
             KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,  KC_VOLD, KC_VOLU, KC_MFFD, \
             KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, RGB_SPD,  RGB_SPI, KC_TRNS, KC_TRNS, KC_TRNS, KC_MRWD,          \
             KC_TRNS, RGB_M_P, RGB_M_G, RGB_M_K, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_TRNS, KC_TRNS, KC_MPLY, KC_TRNS,                   \
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BRID,  KC_BRIU, KC_TRNS, KC_TRNS, KC_PGUP, KC_TRNS,          \
             KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,  MO(2),            KC_HOME, KC_PGDN, KC_END            \
    ),

  /* 2nd Layer
   * ,------------------------------------------------------------------------------------------------.
   * |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |      |
   * |------------------------------------------------------------------------------------------------+
   * |        |     |     |     |     |     |     |     |     |      |     |     |      |      |      |
   * |------------------------------------------------------------------------------------------------+
   * |         |     |     |     |     |     |     |     |    |    |      |      |            |       |
   * |------------------------------------------------------------------------------------------------+
   * |           |     |     |     |     |     |     |     |     |     |     |     |     |    | RESET |
   * |------------------------------------------------------------------------------------------------+
   * |      |       |       |                                   |      |       |       |       |      |
   * `------------------------------------------------------------------------------------------------'
   */

[2] = LAYOUT( \
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          \
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   \
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,            \
             KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS           \
    ),
};
