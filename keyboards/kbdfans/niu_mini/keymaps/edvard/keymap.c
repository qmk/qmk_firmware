/* Copyright 2021 Edvard Sire
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
    _QWERTY,
    _NUMPAD,
    _ARROWS,
    _SPECIAL,
    _FPS,
    _FIGHTING,
    _MOBA,
    _MOBA2,
    _MOUSE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,--------------------------------------------------------------------------------------,
 * |Esc/~ |   Q  |   W  |   E  |   R   |   T  |   Y  |   U    |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+-------+------+------+--------+------+--------------------|
 * | Tab  |   A  |   S  |   D  |   F   |   G  |   H  |   J    |   K  |   L  |   ;  |   "  |
 * |------+------+------+------+-------+------+------+--------+------+--------------------|
 * |Numpad|   Z  |   X  |   C  |   V   |   B  |   N  |   M    |   ,  |   .  |   /  |Arrows|
 * |------+------+------+------+-------+------+---------------+------+--------------------|
 * | Ctrl | GUI  |      |  Alt |Special|    Space    |RS/Enter|Mouse |      | Fps  | Del  |
 * `--------------------------------------------------------------------------------------`
 */
[_QWERTY] = LAYOUT_planck_mit(
    KC_GESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
    KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
    MO(1), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, MO(2),
    KC_LCTL, KC_LGUI, KC_TRNS, KC_LALT, MO(3), KC_SPC, KC_SFTENT, MO(8), KC_TRNS, TO(4), KC_DEL
),

/* NUMPAD
 * ,-----------------------------------------------------------------------------------.
 * |      |      |Power |      |RGBmoG|      |      |  7   |   8  |   9  |      | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      | Prev | Play | Next |      |      |  4   |   5  |   6  |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Trns |      |RGBmo-|RBGmd+|RGBtog|      |      |  1   |   2  |   3  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |    Space    |  0   |   ,  |   .  |      |Reset |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_planck_mit(
    KC_NO, KC_NO, KC_PWR, KC_NO, RGB_M_G, KC_NO, KC_NO, KC_7, KC_8, KC_9, KC_NO, KC_BSPC,
    KC_NO, KC_NO, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, KC_NO, KC_4, KC_5, KC_6, KC_NO, KC_NO,
    KC_TRNS, KC_NO, RGB_RMOD, RGB_MOD, RGB_TOG, KC_NO, KC_NO, KC_1, KC_2, KC_3, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_SPC, KC_0, KC_COMM, KC_DOT, KC_NO, QK_BOOT
),

/* ARROWS
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |      |      |      |  Up  |      |      | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |      |      | Left | Down |Right |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F9  | F10  | F11  | F12  |      |      |      |      |      |      | Trns |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |LCtrl | F13  | F14  | F15  | F16  |   Left Alt  |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ARROWS] = LAYOUT_planck_mit(
    KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, KC_BSPC,
    KC_NO, KC_F5, KC_F6, KC_F7, KC_F8, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO,
    KC_NO, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
    KC_LCTL, KC_F13, KC_F14, KC_F15, KC_F16, KC_LALT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
),

/* SPECIAL
 * ,-----------------------------------------------------------------------------------.
 * |  ~   |  !   |  @   |  #   |  $   |  %   |  ^   |  *   |  (   |  )   |  \   | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  [   |      |      |      |  &   |      |  -   |  [   |  ]   |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  =   |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | Trns |    Space    |LShift|      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SPECIAL] = LAYOUT_planck_mit(
    KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS, KC_BSPC,
    KC_NO, KC_LBRC, KC_NO, KC_NO, KC_NO, KC_AMPR, KC_NO, KC_MINS, KC_LBRC, KC_RBRC, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_EQL, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_SPC, KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO
),

/* FPS
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   |QWERTY|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |RShift|  Q   |  W   |  E   |  R   |  T   |  Y   |QWERTY|      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Tab  |  A   |  S   |  D   |  G   |  B   |  `   |      |      |      | MOBA |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |LCtrl |  Z   |  X   | LAlt |LShift|    Space    |Enter |      |      | Trns |FIGHTI|
 * `-----------------------------------------------------------------------------------'
 */
[_FPS] = LAYOUT_planck_mit(
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, TO(0),
    KC_RSFT, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, TO(0), KC_NO, KC_NO, KC_NO, KC_NO,
    KC_TAB, KC_A, KC_S, KC_D, KC_G, KC_B, KC_GRV, KC_NO, KC_NO, KC_NO, TO(6), KC_NO,
    KC_LCTL, KC_Z, KC_X, KC_LALT, KC_LSFT, KC_SPC, KC_ENT, KC_NO, KC_NO, KC_TRNS, TO(5)
),

/* FIGHTING
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |      |  W   |      |      |      |      |      |      |      |      |QWERTY|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |  A   |  S   |  D   |      |      |      |  J   |  K   |  L   |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |LCtrl |      |      |      |  H   |    Space    |      |      |      |      | Trns |
 * `-----------------------------------------------------------------------------------'
 */
[_FIGHTING] = LAYOUT_planck_mit(
    KC_ESC, KC_NO, KC_W, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(0),
    KC_TAB, KC_A, KC_S, KC_D, KC_NO, KC_NO, KC_NO, KC_J, KC_K, KC_L, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_LCTL, KC_NO, KC_NO, KC_NO, KC_H, KC_SPC, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS
),

/* MOBA
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |  1   |  2   |  3   |  4   |  5   |  6   |      |      |      |      |QWERTY|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |RShift|  Q   |  W   |  E   |  R   |  T   |  Y   |QWERTY|      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Tab  |  A   |  S   |  D   |  F   |  G   |  B   |      |      |      | Trns |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |LCtrl |  Z   |  X   | LAlt |MOBA2 |    Space    |Enter |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOBA] = LAYOUT_planck_mit(
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_NO, KC_NO, KC_NO, KC_NO, TO(0),
    KC_RSFT, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, TO(0), KC_NO, KC_NO, KC_NO, KC_NO,
    KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_B, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO,
    KC_LCTL, KC_Z, KC_X, KC_LALT, MO(7), KC_SPC, KC_ENT, KC_NO, KC_NO, KC_NO, KC_NO
    ),

/* MOBA2
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | Trns |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOBA2] = LAYOUT_planck_mit(
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
),

/* MOBA2
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      | MUp  |      |      |      | MWUp |MWDown|      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |MLeft |MDown |MRight|      |      |Mouse1|Mouse2|      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Trns |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_planck_mit(
    KC_NO, KC_NO, KC_NO, KC_MS_U, KC_NO, KC_NO, KC_NO, KC_WH_U, KC_WH_D, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO, KC_NO, KC_BTN1, KC_BTN2, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO
    )
};
