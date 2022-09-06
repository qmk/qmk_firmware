/* Copyright 2020 Neil Brian Ramirez
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
    /* Base */
    /* ENC1_CCW, ENC1_P,  ENC1_CW,   ENC2_CCW, ENC2_P, ENC2_CW,
		         MACRO1,  MACRO2,    MACRO3,   MACRO4,
			     MACRO5,  MACRO6,    MACRO7,   MACRO8
	*/
	[0] = LAYOUT(
		KC_VOLD, KC_ESC,   KC_VOLU,  KC_BRID, RESET,  KC_BRIU,
		         KC_Q,     KC_W,     KC_E,     KC_R,
			     KC_A,     KC_S,     KC_D,     KC_F
		
    ),
};

