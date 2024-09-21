/*
Copyright 2021 quadcube <james@quadcube.xyz>
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

/*
 * Default Alix Layout
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* 0: Default layer
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ Tab │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │  `  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ Esc │  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  ;  │  '  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│Shift│  Z  │  X  │  C  │  V  │  B  │Enter│  N  │  M  │  ,  │  .  │  /  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│Ctrl │ Alt │     │ Gui │█████│Bksp │Space│█████│ Gui │     │  [  │  ]  │
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
   */
[0] = LAYOUT_40_alix(
        KC_TAB,    KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_GRV,
        KC_ESC,    KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT,   KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_ENT, KC_N,   KC_M,   KC_COMM,   KC_DOT,  KC_SLSH,
        KC_LCTL,   KC_RALT, KC_LGUI,KC_NO,  LT(1, KC_BSPC), LT(2, KC_SPC), KC_NO, KC_RGUI,       KC_LBRC, KC_RBRC
),
/* 1: Lower Layer
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│  ~  │  !  │  @  │  #  │  $  │  %  │  ^  │  &  │  *  │  (  │  )  │  |  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ DEL |  F1 |  F2 |  F3 |  F4 |  F5 │Left │Down │ Up  │Right│  ;  │  '  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│Shift│  F6 │  F7 │  F8 │  F9 │ F10 │Enter|Next |Vol- |Vol+ | Play│  /  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│Ctrl │ Alt │     │ Gui │█████│Bksp │Space│█████│ Gui │     │  _  │  +  │
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
     */
[1]= LAYOUT_40_alix(
        KC_TILD,   KC_EXLM, KC_AT,  KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
        KC_DEL,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_SCLN, KC_QUOT,
        KC_LSFT,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_ENT,  KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY,  KC_SLSH,
        KC_LCTL,  KC_RALT, KC_LGUI, KC_NO,  LT(1, KC_BSPC), LT(2, KC_SPC), KC_NO, KC_RGUI,          KC_UNDS, KC_PLUS
),

/* 2: Raise Layer
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│  ~  │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  \  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ DEL │  F1 │  F2 │  F3 │  F4 │  F5 │Left │Down │ Up  │Right│  ;  │  '  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│Shift│  F6 │  F7 │  F8 │  F9 │ F10 │Enter│Next │PgDn │PgUp │Home │ End │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│Ctrl │ Alt │     │ Gui │█████│Bksp │Space│█████│ Gui │     │  -  │  =  │
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
 */
[2]= LAYOUT_40_alix(
        KC_TILD,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,   KC_7,   KC_8,    KC_9,    KC_0,      KC_BSLS,
        KC_DEL,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_SCLN,   KC_QUOT,
        KC_LSFT,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_ENT, KC_MNXT, KC_PGDN, KC_PGUP, KC_HOME,  KC_END,
        KC_LCTL,  KC_RALT, KC_LGUI, KC_NO,  LT(1, KC_BSPC), LT(2, KC_SPC), KC_NO, KC_RGUI,         KC_MINS,  KC_EQL
),
};
