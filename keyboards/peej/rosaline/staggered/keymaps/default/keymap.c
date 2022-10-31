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
 * ,--------.------.------.------.------.------.------.------.------.------.------.------.------.--------.
 * | Tab    |  Q   |  W   |  E   |  R   |  T   |  Y   |  U   |  I   |  O   |  P   |  [   |  ]   | Bksp   |
 * |--------'-.----'-.----'-.----'-.----'-.----'-.----'-.----'-.----'-.----'-.----'-.----'-.----'--------|
 * | Esc      |  A   |  S   |  D   |  F   |  G   |  H   |  J   |  K   |  L   |  ;   |  '   | Enter       |
 * |----------'---.--'---.--'---.--'---.--'---.--'---.--'---.--'---.--'---.--'---.--'---.--'------.------|
 * | Shft         |  Z   |  X   |  C   |  V   |  B   |  N   |  M   |  ,   |  .   |  /   | Shft    |  Fn  |
 * |--------.-----'.-----'--.---'------'------'---.--'------'--.---'--.---'--.---'--.---'--.------+------|
 * | Ctrl   | Gui  | Alt    | Space               | Space      | Alt  | Ctrl | Left | Down |  Up  | Rght |
 * `--------'------'--------'---------------------'------------'------'------'------'------'------'------'
 */
[_QWERTY] = LAYOUT_all(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
    KC_GESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, FN,
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,  KC_SPC,           KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Function
 * ,--------.------.------.------.------.------.------.------.------.------.------.------.------.--------.
 * | Tab    |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   |  -   |  =   | Del    |
 * |--------'-.----'-.----'-.----'-.----'-.----'-.----'-.----'-.----'-.----'-.----'-.----'-.----'--------|
 * | Esc      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 | Enter       |
 * |----------'---.--'---.--'---.--'---.--'---.--'---.--'---.--'---.--'---.--'---.--'---.--'------.------|
 * | Shft         |  Z   |  X   |  C   |  V   |  B   |  N   |  M   |  ,   |  .   |  /   | Shft    |  Fn  |
 * |--------.-----'.-----'--.---'------'------'---.--'------'--.---'--.---'--.---'--.---'--.------+------|
 * | Ctrl   | Gui  | Alt    | Space               | Space      | Alt  | Ctrl | Left | Down |  Up  | Rght |
 * `--------'------'--------'---------------------'------------'------'------'------'------'------'------'
 */
[_FUNCTION] = LAYOUT_all(
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_DEL,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,           _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLS, _______, _______,
    _______, _______, _______,                   _______, _______,          _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
)

};
