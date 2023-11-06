 /* Copyright 2021 Laneware Peripherals
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

/* 
 * ┌───┐   ┌───┬───┐ 
 * │K00│   │K02│K03│
 * └───┘   └───┴───┘ 
 * ┌───┬───┬───┬───┐
 * │K10│K11│K12│K13│
 * ├───┼───┼───┼───┤ 
 * │K20│K21│K22│K23│
 * │   ├───┼───┼───┤ 
 * │   │K31│K32│K33│
 * ├───┼───┼───┼───┤ 
 * │K40│K41│K42│K43│
 * │   ├───┼───┴───┤ 
 * │   │K51│K52    │
 * └───┴───┴───────┘
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT_southpaw(
		KC_MUTE,     KC_MPLY,     KC_BSPC, 
		KC_CALC,     KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS, 
		KC_KP_PLUS,  KC_KP_7,     KC_KP_8,        KC_KP_9,  
		KC_KP_4,     KC_KP_5,     KC_KP_6, 
		KC_KP_ENTER, KC_KP_1,     KC_KP_2,        KC_KP_3,  
		KC_KP_DOT,   KC_KP_0),

	[1] = LAYOUT_southpaw(
		KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),

	[2] = LAYOUT_southpaw(
		KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS), };



