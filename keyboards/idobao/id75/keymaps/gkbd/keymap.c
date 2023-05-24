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
	[0] = LAYOUT_ortho_5x15(/* Latin base */
		KC_ESC, KC_PSLS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_PSCR, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL, KC_DEL,
		KC_TAB, KC_SCLN, KC_P, KC_Y, KC_T, KC_U, KC_G, KC_PGUP, KC_H, KC_N, KC_V, KC_K, KC_X, KC_MINS, KC_INS,
		KC_CAPS, KC_W, KC_D, KC_S, KC_A, KC_E, KC_O, KC_PGDN, KC_L, KC_R, KC_I, KC_M, KC_B, KC_C, KC_ENT,
		KC_LSFT, KC_BSLS, KC_J, KC_LBRC, KC_RBRC, KC_COMM, KC_DOT, KC_UP, KC_QUOT, KC_Z, KC_Q, KC_F, KC_SLSH, KC_GRV, KC_RSFT,
		KC_LCTL, KC_LGUI, KC_LALT, MO(2), KC_HOME, KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, KC_SPC, KC_END, MO(2), KC_RALT, RGUI_T(KC_APP), KC_RCTL
	),
	[1] = LAYOUT_ortho_5x15(/* Unicode layer */
		KC_TRNS, KC_SLSH, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, UC(0x10EB), UC(0x10DE), UC(0x10E8), UC(0x10E2), UC(0x10E3), UC(0x10D2), KC_TRNS, UC(0x10EE), UC(0x10DC), UC(0x10D5), UC(0x10D9), UC(0x10E9), KC_TRNS, KC_TRNS,
		KC_SCLN, UC(0x10D7), UC(0x10D3), UC(0x10E1), UC(0x10D0), UC(0x10D4), UC(0x10DD), KC_TRNS, UC(0x10DA), UC(0x10E0), UC(0x10D8), UC(0x10DB), UC(0x10D1), UC(0x10EA), KC_TRNS,
		KC_TRNS, UC(0x10DF), UC(0x10EF), UC(0x10E7), UC(0x10EC), KC_TRNS, KC_TRNS, KC_TRNS, UC(0x10E6), UC(0x10D6), UC(0x10E5), UC(0x10E4), UC(0x10F0), UC(0x10ED), KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),
	[2] = LAYOUT_ortho_5x15(/* Function keys */
		RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TG(1), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_TOG,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_SLCK, KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NO, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO, KC_PAUS,
		KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_F11, KC_NO, KC_NO, KC_NO, KC_F12, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	)
};
