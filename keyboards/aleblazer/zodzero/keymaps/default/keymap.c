/*
Copyright 2023 Spencer Deven <splitlogicdesign@gmail.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,                      RGB_MOD,   RGB_VAI,                     KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,     KC_G,   KC_MINS, KC_BSLS,  RGB_RMOD,  RGB_VAD, KC_KB_MUTE, KC_EQL, KC_H,     KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,   KC_GRV,  KC_LBRC,  QK_BOOT,   QK_BOOT, KC_RBRC, KC_DEL,    KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    KC_LCTL, KC_LALT, KC_LGUI, KC_MENU, MO(1), KC_SPC, KC_ENT,                                         MO(4), MO(3), MO(2), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),
 [1] = LAYOUT(
    _______,  KC_GRV,  _______, _______, _______, _______,                   _______, _______,                   _______, KC_PMNS, KC_UNDS, KC_PEQL, KC_PPLS, _______,
    _______,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, _______, _______, _______, _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,  _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______, _______
    ),
 [2] = LAYOUT(
    _______,  _______, _______, _______, _______, _______,                   _______, _______,                   KC_NUM,  _______, KC_P7, KC_P8, KC_P9, _______,
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P4, KC_P5, KC_P6, KC_PMNS,
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P1, KC_P2, KC_P3, KC_PPLS,
    _______,  _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, KC_P0, KC_PDOT, KC_PENT, KC_PSLS
    ),
  [3] = LAYOUT(
    _______,  KC_TILD, KC_PIPE, KC_LCBR, KC_RCBR, KC_DQUO,                   _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, _______, _______, _______, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    _______,  KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,  _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______, _______
    ),
  [4] = LAYOUT(
    _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     _______, _______,                   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, _______,
    _______,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,  KC_PSCR, KC_SCRL, KC_PAUS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,  _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______, _______
    ),
};


