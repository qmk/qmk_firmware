/* Copyright 2021 Paul James
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

enum layers {
  _QWERTY = 0,
  _FUNCTION
};

#define FN MO(_FUNCTION)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,--------------------------------------------------------------------------------------------------------.
 * | Tab  |  Q   |  W   |  E   |  R   |  T   |  7   |  8   |  9   |  Y   |  U   |  I   |  O   |  P   | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |  A   |  S   |  D   |  F   |  G   |  4   |  5   |  6   |  H   |  J   |  K   |  L   |  ;   |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shft |  Z   |  X   |  C   |  V   |  B   |  1   |  2   |  3   |  N   |  M   |  ,   |  .   |  /   | Entr |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  Fn  | Alt  | Cmd  |  Fn  | Spac | Spac |  0   | Spac | Spac |  Fn  | Left | Down |  Up  | Rght |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x15(
    KC_TAB,  KC_Q, KC_W,    KC_E,    KC_R, KC_T,   KC_P7,  KC_P8, KC_P9,  KC_Y,   KC_U, KC_I,    KC_O,    KC_P,    KC_BSPC,
    QK_GESC, KC_A, KC_S,    KC_D,    KC_F, KC_G,   KC_P4,  KC_P5, KC_P6,  KC_H,   KC_J, KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z, KC_X,    KC_C,    KC_V, KC_B,   KC_P1,  KC_P2, KC_P3,  KC_N,   KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    KC_LCTL, FN,   KC_LALT, KC_LGUI, FN,   KC_SPC, KC_SPC, KC_P0, KC_SPC, KC_SPC, FN,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Function
 * ,--------------------------------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |  F7  |  F8  |  F9  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F4  |  F5  |  F6  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F1  |  F2  |  F3  |  F12 |ISO # |ISO / |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  F10 |      |      |      | Next | Vol- | Vol+ | Play |
 * `--------------------------------------------------------------------------------------------------------'
 */
[_FUNCTION] = LAYOUT_ortho_4x15(
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_F7,   KC_F8,  KC_F9,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F4,   KC_F5,  KC_F6,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F1,   KC_F2,  KC_F3,   KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_F10, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
)

};
