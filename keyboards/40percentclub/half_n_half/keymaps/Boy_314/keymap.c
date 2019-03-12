/* Copyright 2019 Boy_314
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
	[0] = LAYOUT(/* Base */
	  KC_GESC, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_LCTL, KC_LCTL, KC_F, KC_G, KC_C, KC_R, KC_L, KC_BSPC, 
	  KC_TAB,  KC_A,    KC_O,    KC_E,   KC_U, KC_I, KC_LALT, KC_RALT, KC_D, KC_H, KC_T, KC_N, KC_S, KC_ENT, 
	  KC_LSPO, KC_SCLN, KC_Q,    KC_J,   KC_K, KC_X, KC_LGUI, KC_APP,  KC_B, KC_M, KC_W, KC_V, KC_Z, KC_RSPC, 
	                                     MO(1),                              LT(2,KC_SPC)
	),
	[1] = LAYOUT(/* Numbers, Function Row, Media Control, Shifted Symbols, Dvorak Slash Key */
	  KC_TRNS, KC_1,  KC_2,  KC_3,  KC_4,   KC_5,   KC_TRNS, KC_TRNS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_SLSH, 
	  KC_CAPS, KC_F1, KC_F2, KC_F3, KC_F4,  KC_F5,  KC_F6,   KC_VOLU, KC_MPLY, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, 
	  KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,  KC_VOLD, KC_MNXT, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_TRNS,
									KC_TRNS,    					           KC_TRNS
	),
	[2] = LAYOUT(/* Arrows, Shifted Numbers, Symbols, Delete, Reset Key */
	  RESET,   KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL,
	  KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, 
	  KC_TRNS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_TRNS, KC_TRNS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS, 
										  KC_TRNS, 									   KC_TRNS
	)
};
