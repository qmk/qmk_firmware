/* Copyright 2019 Rozakiin
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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
    _BL,
    _FL1,
    _FL2,
    _FL3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* Base Layer
    * ┌───┬───┬───┬───┐
    * │Esc│BLT│BL-│BL+│
    * ├───┼───┼───┼───┤
    * │NLK│ / │ * │ = │
    * ├───┼───┼───┼───┤
    * │ 7 │ 8 │ 9 │ - │
    * ├───┼───┼───┼───┤
    * │ 4 │ 5 │ 6 │ + │
    * ├───┼───┼───┼───┤
    * │ 1 │ 2 │ 3 │ENT│
    * ├───┼───┼───┼───┤
    * │ 0 │ 0 │ . │ENT│
    * └───┴───┴───┴───┘
    */
	[_BL] = LAYOUT_ortho_6x4(
	  KC_ESC,   BL_TOGG, BL_DEC,   BL_INC, 
		KC_NUM,   KC_PSLS, KC_PAST,  KC_PEQL, 
		KC_P7,    KC_P8,   KC_P9,    KC_PMNS, 
		KC_P4,    KC_P5,   KC_P6,    KC_PPLS, 
		KC_P1,    KC_P2,   KC_P3,    KC_PENT, 
		KC_P0,    KC_P0,   KC_PDOT,  KC_PENT
    ),
    /* Function Layer 1
    * ┌───┬───┬───┬───┐
    * │   │   │   │   │
    * ├───┼───┼───┼───┤
    * │   │   │   │   │
    * ├───┼───┼───┼───┤
    * │   │   │   │   │
    * ├───┼───┼───┼───┤
    * │   │   │   │   │
    * ├───┼───┼───┼───┤
    * │   │   │   │   │
    * ├───┼───┼───┼───┤
    * │   │   │   │   │
    * └───┴───┴───┴───┘
    */
	[_FL1] = LAYOUT_ortho_6x4(
		_______, _______, _______, _______, 
		_______, _______, _______, _______, 
		_______, _______, _______, _______, 
		_______, _______, _______, _______, 
		_______, _______, _______, _______, 
		_______, _______, _______, _______
    ),
    /* Function Layer 2
    * ┌───┬───┬───┬───┐
    * │   │   │   │   │
    * ├───┼───┼───┼───┤
    * │   │   │   │   │
    * ├───┼───┼───┼───┤
    * │   │   │   │   │
    * ├───┼───┼───┼───┤
    * │   │   │   │   │
    * ├───┼───┼───┼───┤
    * │   │   │   │   │
    * ├───┼───┼───┼───┤
    * │   │   │   │   │
    * └───┴───┴───┴───┘
    */
	[_FL2] = LAYOUT_ortho_6x4(
		_______, _______, _______, _______, 
		_______, _______, _______, _______, 
		_______, _______, _______, _______, 
		_______, _______, _______, _______, 
		_______, _______, _______, _______, 
		_______, _______, _______, _______
    ),
    /* Function Layer 3
    * ┌───┬───┬───┬───┐
    * │   │   │   │   │
    * ├───┼───┼───┼───┤
    * │   │   │   │   │
    * ├───┼───┼───┼───┤
    * │   │   │   │   │
    * ├───┼───┼───┼───┤
    * │   │   │   │   │
    * ├───┼───┼───┼───┤
    * │   │   │   │   │
    * ├───┼───┼───┼───┤
    * │   │   │   │   │
    * └───┴───┴───┴───┘
    */
	[_FL3] = LAYOUT_ortho_6x4(
		_______, _______, _______, _______, 
		_______, _______, _______, _______, 
		_______, _______, _______, _______, 
		_______, _______, _______, _______, 
		_______, _______, _______, _______, 
		_______, _______, _______, _______
    ),

};
