/* Copyright 2021 Giorgi Chavchanidze
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
	[0] = LAYOUT_ortho_5x15(
			KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_F1, KC_F4, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL, KC_F7,
			KC_TAB, KC_K, KC_P, KC_L, KC_R, KC_C, KC_F2, KC_F5, KC_M, KC_U, KC_O, KC_W, KC_X, KC_SLSH, KC_F8,
			KC_CAPS, KC_D, KC_S, KC_T, KC_F, KC_N, KC_F3, KC_F6, KC_I, RSFT_T(KC_J), KC_E, KC_A, KC_H, KC_ENT, KC_F9,
			KC_PGUP, KC_Q, KC_B, KC_G, KC_COMM, KC_DOT, KC_LGUI, KC_RALT, KC_MINS, KC_V, KC_Y, KC_QUOT, KC_Z, KC_UP, KC_F10,
			KC_PGDN, KC_PSCR, KC_INS, KC_DEL, LT(1,KC_F11), KC_BSPC, KC_LSFT, KC_RCTL, KC_SPC, LT(1,KC_F12), KC_HOME, KC_END, KC_LEFT, KC_DOWN, KC_RGHT
		),
	[1] = LAYOUT_ortho_5x15(
			QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_TOG,
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
			KC_NO, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_SCRL, KC_NO, KC_NO, KC_PAUS, KC_BSLS, KC_PIPE, KC_SCLN, KC_COLN, KC_NO, KC_NO,
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
			KC_WAKE, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_GRV, KC_TRNS, KC_TRNS, KC_TILD, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_APP
		)
};

