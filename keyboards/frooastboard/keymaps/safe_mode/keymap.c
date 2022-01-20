/* Copyright 2021 frooastside
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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
	[0] = LAYOUT(
		KC_Z, KC_X,
		TO(1), KC_TILD),

	[1] = LAYOUT(
		RGB_TOG, RGB_MOD,
		TO(2), TO(0)),

	[2] = LAYOUT(
		RGB_HUD, RGB_HUI,
		TO(3), TO(1)),

	[3] = LAYOUT(
		RGB_SAD, RGB_SAI,
		TO(4), TO(2)),

	[4] = LAYOUT(
		RGB_VAD, RGB_VAI,
		TO(5), TO(3)),

	[5] = LAYOUT(
		KC_TRNS, KC_TRNS,
		RESET, TO(4))
};
