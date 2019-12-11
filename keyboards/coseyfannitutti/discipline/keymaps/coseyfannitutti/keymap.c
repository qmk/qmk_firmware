/* Copyright 2019 COSEYFANNITUTTI
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

#define _BL 0
#define _FL 1

  /* Qwerty
   * .---------------------------------------------------------------------------------------------.
   * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  Bkspc  | Ins |
   * |---------------------------------------------------------------------------------------------+
   * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |   \  | Del |
   * |---------------------------------------------------------------------------------------------+
   * | Caps    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |   Enter   | PgUp|
   * |---------------------------------------------------------------------------------------------+
   * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |  Shift  |  U  | Pgdn|
   * |---------------------------------------------------------------------------------------------+
   * | Ctrl |  Win  |  Alt  |              Space                | RAlt | FN |||||||  L |  D  |  R  |
   * '---------------------------------------------------------------------------------------------'
   */

  /* FnLayer
   * .---------------------------------------------------------------------------------------------.
   * | ` ~ |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |  DELETE |PNTSC|
   * |---------------------------------------------------------------------------------------------+
   * | Tab    |     |     |     |RESET|     |     |     |     |     |     |PAUSE|     |  \   |     |
   * |---------------------------------------------------------------------------------------------+
   * | Caps    |     |     |     |     |     |     |     |     |     |     | INS |    Enter  | HOME|
   * |---------------------------------------------------------------------------------------------+
   * | Shift     |     |     |     |     |     |     |     |     |     |     |  Shift  |VOLUP| END |
   * |---------------------------------------------------------------------------------------------+
   * | Ctrl |  Win  |  Alt  |                                   | RAlt| FN |||||||  L  |VOLDN|  R  |
   * '---------------------------------------------------------------------------------------------'
   */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = LAYOUT_65_ansi_2_right_mods(
      KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  KC_DEL,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS,  KC_PGUP,
      KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT,  KC_ENT,            KC_PGDN,
      KC_LSFT,          KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, KC_UP,    MO(_FL),
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                 KC_RALT, MO(_FL),           KC_LEFT, KC_DOWN,  KC_RIGHT),

  [_FL] = LAYOUT_65_ansi_2_right_mods(
     /* esc      1        2        3        4       5       6       7       8       9         0        -         =     bkspc       `~  */
      KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_DEL,   KC_PSCR,
     /*  tab      Q       W        E        R        T      Y        U      I        O        P        [         ]        \      delete*/ 
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,  KC_TRNS,KC_TRNS,KC_TRNS,KC_INS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_PAUS, KC_TRNS,  KC_TRNS,
     /*  caps     A       S        D        F        G      H        J      K        L        ;        '        enter             pg up*/
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,  KC_INS,            KC_HOME,
     /* shift             Z         X        C       V       B       N      M        ,        .        /        shift     up      pg dn*/
      KC_LSFT,          KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS,  KC_RSFT, KC_VOLU,  KC_END,
     /* ctrl     win      alt                              space                    alt      fn                  left     down     right*/
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_TRNS,                KC_RALT, KC_TRNS,             KC_TRNS, KC_VOLD,  KC_TRNS)
};

