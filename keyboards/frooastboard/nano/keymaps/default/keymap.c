/* Copyright 2021-2022 frooastside
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
		LT(1, KC_ESC), KC_TILD),

	[1] = LAYOUT(
		KC_F23, KC_F24,
		KC_TRNS, TO(2)),

	[2] = LAYOUT(
		UG_TOGG, UG_NEXT,
		TO(3), TO(0)),

	[3] = LAYOUT(
		UG_HUED, UG_HUEU,
		TO(4), TO(2)),

	[4] = LAYOUT(
		UG_SATD, UG_SATU,
		TO(5), TO(3)),

	[5] = LAYOUT(
		UG_VALD, UG_VALU,
		TO(6), TO(4)),

	[6] = LAYOUT(
		KC_TRNS, KC_TRNS,
		QK_BOOT, TO(5))
};
