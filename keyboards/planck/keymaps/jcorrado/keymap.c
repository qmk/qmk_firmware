/* Copyright 2015-2017 Jack Humbert
 * Copyright 2018 Jereme Corrado
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

enum {
  _QWERTY = 0,
  _NUM,
  _SYM_L,
  _SYM_R
};

#define LMOD_0 LT(_SYM_L, KC_TAB)  /* Tab, hold: Sym layer */
#define LMOD_1 LT(_NUM, KC_ESC)    /* Esc, hold: Num layer */
#define LMOD_2 LSFT_T(KC_CAPS)     /* Caps Lock, hold: Left Shift */

#define RMOD_0 LT(_SYM_R, KC_BSPC) /* Backspace, hold: Sym layer */
#define RMOD_1 LT(_NUM, KC_QUOT)   /* Quote, hold: Nu layer */
#define RMOD_2 RSFT_T(KC_ENT)      /* Enter, hold: Right Shift */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | Tab/   | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | BacSp/ |
 * | Sym    |        |        |        |        |        |        |        |        |        |        | Sym    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | Esc/   | A      | S      | D      | F      | G      | H      | J      | K      | L      | :      | "      |
 * | Num    |        |        |        |        |        |        |        |        |        | ;      | '/Num  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | CapLk/ | Z      | X      | C      | V      | B      | N      | M      | <      | >      | ?      | Shift/ |
 * | Shift  |        |        |        |        |        |        |        | ,      | .      | /      | Enter  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | Toggle | ~      | {pipe} | Alt    | Ctrl   | Space  | Space  | Ctrl   | Alt    | {      | }      |        |
 * | Num    | `      | \      |        |        |        |        |        |        | [      | ]      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 */

[_QWERTY] = LAYOUT_planck_grid(
  LMOD_0,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    RMOD_0,
  LMOD_1,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, RMOD_1,
  LMOD_2,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RMOD_2,
  _______, KC_GRV,  KC_BSLS, KC_LALT, KC_LCTL, KC_SPC,  KC_SPC,  KC_RCTL, KC_RALT, KC_LBRC, KC_RBRC, _______
),


/*
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | =      |      1 |      2 |      3 |      4 |      5 | 6      | 7      | 8      | 9      |      0 | -      |
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | Left   | Down   | Up     | Right  |        |        |
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | Home   | PgDown | PgUp   | End    |        |        |
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 */

[_NUM] = LAYOUT_planck_grid(
  KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),


/*
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | +      | !      | @      | #      | $      | %      | ^      | &      | *      | (      | )      | _      |
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | F1     | F2     | F3     | F4     | F5     | F6     |        |        |        |        |        |
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | F7     | F8     | F9     | F10    | F11    | F12    |        |        |        |        |        |
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 */

[_SYM_L] = LAYOUT_planck_grid(
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, _______, _______, _______, _______,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_SYM_R] = LAYOUT_planck_grid(
  KC_PLUS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, _______, _______, _______, _______,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};
