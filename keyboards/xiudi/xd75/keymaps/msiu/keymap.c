/* Copyright 2017 Benjamin Kesselring
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

/* What this layout is: QWERTY layout with the standard 40% layers. For easy
 * switching between my xd75 and contra
 */

#include QMK_KEYBOARD_H

// Layer shorthand
#define _QW 0
#define _DV 1
#define _LW 2
#define _RS 3
#define _FN 4

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | `      | 1      | 2      | 3      | 4      | 5      | -      | =      | \      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | TAB    | Q      | W      | E      | R      | T      | 7      | 8      | 9      | Y      | U      | I      | O      | P      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | ESC    | A      | S      | D      | F      | G      | 4      | 5      | 6      | H      | J      | K      | L      | ;      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | 1      | 2      | 3      | N      | M      | ,      | .      | /      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | HYPER  | LALT   | LGUI   | LOWER  | FN     | 0      |        | .      | SPACE  | RAISE  | LEFT   | DOWN   | UP     | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_QW] = LAYOUT_ortho_5x15( /* QWERTY */
  KC_GRV,          KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_PLUS, KC_MINS, KC_ASTR, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_7,    KC_8,    KC_9   , KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  LCTL_T(KC_ESC),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_4,    KC_5,    KC_6   , KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_1,    KC_2,    KC_3   , KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  KC_LCTL,         KC_HYPR, KC_LALT, KC_LGUI, MO(_LW), MO(_FN), KC_0,    _______, KC_DOT , KC_SPC,  MO(_RS), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
 ),

 /* Dvorak */

  [_DV] = LAYOUT_ortho_5x15( /* Dvorak */
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
   _______, KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    _______, _______, _______, KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    _______,
   _______, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    _______, _______, _______, KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH,
   _______, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    _______, _______, _______, KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),


/* LOWERED
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        | F1     | F2     | F3     | F4     | F5     |        |        |        | F6     | F7     | F8     | F9     | F10    | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | ~      | !      | @      | #      | $      | %      |        | VOLU   |        | ^      | &      | *      | (      | )      | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | F1     | F2     | F3     | F4     | F5     | PREV   | PLAY   | NEXT   | F6     | _      | +      | {      | }      | |      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        | F7     | F8     | F9     | F10    | F11    |        | VOLD   |        | F12    | PAGEDW | PAGEUP | HOME   | END    | MUTE   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        |        | MUTE   |        | PLAY   |        | PREV   | VOLD   | VOLU   | NEXT   |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_LW] = LAYOUT_ortho_5x15( /* LOWERED */
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, KC_VOLU, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_MPRV, KC_MPLY, KC_MNXT, KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  _______, KC_VOLD, _______, KC_F12,  KC_PGDN, KC_PGUP, KC_HOME, KC_END , KC_MUTE,
  _______, _______, _______, _______, _______, _______, _______, KC_MUTE, _______, KC_MPLY, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
 ),

/* RAISED
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        | F1     | F2     | F3     | F4     | F5     |        |        |        | F6     | F7     | F8     | F9     | F10    | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | `      | 1      | 2      | 3      | 4      | 5      |        | VOLU   |        | 6      | 7      | 8      | 9      | 0      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | F1     | F2     | F3     | F4     | F5     | PREV   | PLAY   | NEXT   | F6     | -      | =      | [      | ]      | \      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | F7     | F8     | F9     | F10    | F11    |        | VOLD   |        | F12    | PAGEUP | PAGEDW | HOME   | END    | MUTE   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        | MUTE   |        | PLAY   |        | PREV   | VOLD   | VOLU   | NEXT   |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_RS] = LAYOUT_ortho_5x15( /* RAISED */
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
  KC_GRV , KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, KC_VOLU, _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_MPRV, KC_MPLY, KC_MNXT, KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  _______, KC_VOLD, _______, KC_F12,  KC_PGDN, KC_PGUP, KC_HOME, KC_END , KC_MUTE,
  _______, _______, _______, _______, _______, _______, _______, KC_MUTE, _______, KC_MPLY, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
 ),

/* FUNCTION */

 [_FN] = LAYOUT_ortho_5x15( /* FUNCTION */
  RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, BL_TOGG, BL_INC,  BL_DEC,  _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP  , _______, KC_PSCR, _______,
  _______, _______, _______, TO(_DV), TO(_QW), _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  RESET  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
 )
};


