/* Copyright 2019 Jarred Steenvoorden
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

#define _BASE 0
#define _FN1 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_BASE] = LAYOUT(
      KC_F19, KC_F20, KC_F21, \
      KC_F16, KC_F17, KC_F18, \
      KC_F13, KC_F14, KC_F15, \
      KC_MUTE, KC_VOLD, KC_VOLU \
	),
  
	[_FN1] = LAYOUT(
		KC_HOME, KC_UP  , KC_PGUP , \
		KC_LEFT, KC_DOWN, KC_RIGHT, \
		KC_END , KC_BSPC, KC_PGDN , \
		KC_TRNS, XXXXXXX, KC_DEL    \
	)
};
