// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

/* Copyright 2021 QMK
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
//const uint16_t PROGMEM keymaps[][MATRIX_COLS][MATRIX_ROWS] = {
    [0] = LAYOUT_96_ansi(
//KC_ESC,  KC_Q,    KC_1,    KC_A,    KC_Z,    KC_TAB,  KC_GRV,  KC_CAPS,
//KC_NO,   KC_W,    KC_NO,   KC_S,    KC_X,    KC_NO,   KC_NO,   KC_NO,
//KC_F4,   KC_E,    KC_3,    KC_D,    KC_C,    KC_F3,   KC_F2,   KC_F1,
//KC_G,    KC_R,    KC_4,    KC_F,    KC_V,    KC_T,    KC_5,    KC_B,
//KC_H,    KC_U,    KC_7,    KC_J,    KC_M,    KC_Y,    KC_6,    KC_N,
//KC_NO,   KC_I,    KC_8,    KC_K,    KC_COMM, KC_NO,   KC_NO,   KC_NO,
//KC_BSPC, KC_UP,   KC_DOWN, KC_ENT,  KC_SPC,  KC_NO,   KC_BSLS, KC_PAUS,
//KC_F11,  KC_O,    KC_9,    KC_L,    KC_DOT,  KC_F10,  KC_F9,   KC_F12,
//KC_QUOT, KC_P,    KC_0,    KC_SCLN, KC_SLSH, KC_LBRC, KC_MINS, KC_EQL,
//KC_INS,  KC_LEFT, KC_RGHT, KC_PGDN, KC_END,  KC_HOME, KC_PGUP, KC_DEL,
//KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_MUTE, KC_NO,
//KC_NO,   KC_NO,   KC_LALT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_RALT,
//KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_RGUI, KC_NO,
//KC_LGUI, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
//KC_NO,   KC_NO,   KC_NO,   KC_RCTL, KC_NO,   KC_LCTL, KC_NO,   KC_NO,
//KC_NO,   KC_RSFT, KC_NO,   KC_NO,   KC_LSFT, KC_NO,   KC_NO,   KC_NO

KC_ESC, KC_F7,   KC_F4,   KC_G,    KC_H,    KC_NO,   KC_BSPC, KC_F11,
KC_QUOT, KC_INS, KC_NO,   KC_NO,   KC_NO,   KC_LGUI, KC_NO,   KC_NO,

KC_Q,   KC_W,    KC_E,    KC_R,    KC_U,    KC_I,    KC_UP,   KC_O,
KC_P,   KC_LEFT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_RSFT,

KC_1,   KC_2,   KC_3,    KC_4,    KC_7,    KC_8,    KC_DOWN, KC_9,
KC_0,   KC_RGHT, KC_NO,   KC_LALT, KC_NO,   KC_NO,   KC_NO,   KC_NO,

KC_A,   KC_S,    KC_D,    KC_F,    KC_J,    KC_K,    KC_ENT,  KC_L,
KC_SCLN, KC_PGDN, KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_RCTL, KC_NO,

KC_Z,   KC_X,    KC_C,    KC_V,    KC_M,    KC_COMM, KC_SPC,  KC_DOT,
KC_SLSH, KC_END, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_LSFT,

KC_TAB, KC_F6,   KC_F3,   KC_T,    KC_Y,    KC_NO,   KC_RBRC,   KC_F10,
KC_LBRC, KC_HOME, KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_LCTL, KC_NO,

KC_GRV, KC_F5,   KC_F2,   KC_5,    KC_6,    KC_NO,   KC_BSLS, KC_F9,
KC_MINS, KC_PGUP, KC_MUTE, KC_NO,  KC_RGUI, KC_NO,   KC_NO,   KC_NO,

KC_CAPS, KC_F8, KC_F1,    KC_B,    KC_N,    KC_NO,   KC_PAUS, KC_F12,
KC_EQL,  KC_DEL, KC_NO,   KC_RALT, KC_NO,   KC_NO,   KC_NO,   KC_NO

    )
};
