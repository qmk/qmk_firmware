/*
Copyright 2017 Kyle Peatt <kpeatt@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define ______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
    * ,-----------------------------------------------------------------------------------------.
    * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |   Bkspc   |
    * |-----------------------------------------------------------------------------------------+
    * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \   |
    * |-----------------------------------------------------------------------------------------+
    * | Caps/FN |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
    * |-----------------------------------------------------------------------------------------+
    * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |     RShift      |
    * |-----------------------------------------------------------------------------------------+
    * | Ctrl |  GUI  |  Alt  |              Space                |  Alt  |  GUI  |  Ctrl |  Fn  |
    * `-----------------------------------------------------------------------------------------'
    */

    [0] = LAYOUT_60_ansi(
        QK_GESC, KC_1,  KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL, KC_BSPC,
        KC_TAB,  KC_Q,  KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC,KC_BSLS,
        LT(1, KC_CAPS), KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        KC_LCTL,KC_LGUI,KC_LALT,                KC_SPC,                          KC_RALT,KC_RGUI, KC_RCTL, MO(1)
    ),

    /* FN Layer
    * ,-----------------------------------------------------------------------------------------.
    * |  `~ | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10  | F11  | F12  |        |
    * |-----------------------------------------------------------------------------------------+
    * |        |     |  Up |     |     |     |     |     |     |     |RGBMOD| Val+| Val- |RBGTOG|
    * |-----------------------------------------------------------------------------------------+
    * |         | Left| Down|Right|     |     |     |     | Sat+| Sat-| Hue+| Hue-|             |
    * |-----------------------------------------------------------------------------------------+
    * |           |     |     |     |     |     |     |     |     |     |     |     |     |     |
    * |-----------------------------------------------------------------------------------------+
    * |      |       |       |                                   |     |      |     |     |     |
    * `-----------------------------------------------------------------------------------------'
    */

    [1] = LAYOUT_60_ansi(
        KC_GRV, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, ______,
        ______,______,KC_UP,______,______,______,______,______,______,______,RGB_MOD,RGB_VAI,RGB_VAD,RGB_TOG,
        ______,KC_LEFT,KC_DOWN,KC_RGHT,______, ______, ______,______,RGB_SAI,RGB_SAD,RGB_HUI,RGB_HUD,______,
        ______,______,______,______,______, ______, ______,______,______,______,______,        ______,
        ______,______,______,                ______,                        ______,______,______,______
    ),
    /* You can copy this layer as base for a new fn layer * /
	[n] = LAYOUT_60_ansi(
        ______,______,______,______,______,______,______,______,______,______,______,______,______,______,
        ______,______,______,______,______,______,______,______,______,______,______,______,______,______,
        ______,______,______,______,______,______,______,______,______,______,______,______,______,
        ______,______,______,______,______,______,______,______,______,______,______,        ______,
        ______,______,______,                ______,                        ______,______,______,______
    ), // */
};
