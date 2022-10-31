/*
Copyright 2022 Joe Scotto

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_split_3x6_3(
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        KC_ENT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, 
        LSFT_T(KC_ESC), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, 
        KC_LALT, KC_LGUI, KC_SPC, MO(1), MO(2), KC_LCTL
    ),
	[1] = LAYOUT_split_3x6_3(
        KC_GRV, KC_UNDS, KC_MINS, KC_PLUS, KC_EQL, KC_NO, KC_NO, KC_MRWD, KC_MPLY, KC_MFFD, KC_NO, KC_DEL, 
        KC_ENT, KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, KC_BSLS, KC_NO, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT, KC_CAPS, 
        LSFT_T(KC_ESC), KC_LBRC, KC_QUOT, KC_DQUO, KC_RBRC, KC_NO, KC_NO, KC_VOLD, KC_MUTE, KC_VOLU, KC_NO, KC_RSFT, 
        KC_LALT, KC_LGUI, KC_SPC, KC_NO, KC_NO, KC_LCTL
    ),
	[2] = LAYOUT_split_3x6_3(
        KC_ESC, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, 
        KC_ENT, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_CAPS, 
        LSFT_T(KC_ESC), KC_NO, KC_NO, KC_NO, KC_NO, MO(3), KC_NO, KC_NO, KC_COMM, KC_DOT, KC_NO, KC_RSFT, 
        KC_LALT, KC_LGUI, KC_SPC, KC_NO, KC_NO, KC_LCTL
    ),
	[3] = LAYOUT_split_3x6_3(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, 
        QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LGUI, 
        LSFT_T(KC_ESC), KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RSFT, 
        KC_LALT, KC_LGUI, KC_SPC, KC_NO, KC_NO, KC_LCTL
    )
};

