/* Copyright 2018 Jack Humbert
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
#include "brandonschlack.h"

#define _NUMPAD 0
#define _FN 1
#define _NUMLOCK 2
#define _MACRO 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_NUMPAD] = LAYOUT(
		KC_P7, KC_P8, KC_P9, \
		KC_P4, KC_P5, KC_P6, \
		KC_P1, KC_P2, KC_P3, \
		OSL(_FN), KC_P0, KC_PDOT \
	),

	[_FN] = LAYOUT(
		KC_PSLS, KC_PAST, KC_BSPC, \
		KC_TRNS, KC_TRNS, KC_PMNS, \
		TG(_NUMLOCK), DF(_MACRO), KC_PPLS, \
		KC_TRNS, DF(_MAGIC), KC_PENT \
	),

    [_NUMLOCK] = LAYOUT(
		KC_HOME, KC_UP, KC_PGUP, \
		KC_LEFT, CMD_TAB, KC_RGHT, \
		KC_END, KC_DOWN, KC_PGDN, \
		DF(_NUMPAD), KC_INS, KC_DEL  \
	),

    [_MACRO] = LAYOUT(
		KC_F13, KC_F14, KC_F15, \
		KC_F16, KC_F17, KC_F18, \
		KC_F19, KC_F20, KC_F21, \
		LT(_MAGIC,KC_F22), KC_F23, KC_F24  \
	),

    [_MAGIC] = LAYOUT(
		KC_MAKE, XXXXXXX, XXXXXXX, \
		XXXXXXX, XXXXXXX, XXXXXXX, \
		DF(_NUMPAD), DF(_NUMLOCK), DF(_MACRO), \
		KC_TRNS, XXXXXXX, XXXXXXX  \
	)
};
