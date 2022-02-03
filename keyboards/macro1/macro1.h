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

#pragma once

#include "quantum.h"

/* KEYMAP_numpad
 * ┌───┐   ┌───┬───┐ 
 * │K00│   │K02│K03│
 * └───┘   └───┴───┘ 
 * ┌───┬───┬───┬───┐
 * │K10│K11│K12│K13│
 * ├───┼───┼───┼───┤ 
 * │K20│K21│K22│K23│
 * ├───┼───┼───┤   │ 
 * │K30│K31│K32│   │
 * ├───┼───┼───┼───┤ 
 * │K40│K41│K42│K43│
 * ├───┴───┼───┤   │ 
 * │K50    │K52│   │
 * └───────┴───┴───┘
 */
#define LAYOUT_numpad( \
	K00,      K02, K03, \
	K10, K11, K12, K13, \
	K20, K21, K22, K23, \
	K30, K31, K32,      \
	K40, K41, K42, K43, \
	K50,      K52  \
) { \
	{ K00,   KC_NO, K02,   K03 }, \
	{ K10,   K11,   K12,   K13 }, \
	{ K20,   K21,   K22,   K23 }, \
	{ K30,   K31,   K32,   KC_NO }, \
	{ K40,   K41,   K42,   K43 }, \
	{ K50,   KC_NO, K52,   KC_NO }  \
}

/* KEYMAP_southpaw
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
#define LAYOUT_southpaw( \
	K00,      K02, K03, \
	K10, K11, K12, K13, \
	K20, K21, K22, K23, \
	     K31, K32, K33, \
	K40, K41, K42, K43, \
	     K51, K52  \
) { \
	{ K00,   KC_NO, K02,   K03 }, \
	{ K10,   K11,   K12,   K13 }, \
	{ K20,   K21,   K22,   K23 }, \
	{ KC_NO, K31,   K32,   K33 }, \
	{ K40,   K41,   K42,   K43 }, \
	{ KC_NO, K51,   K52,   KC_NO }  \
}

/* KEYMAP_macropad
 * ┌───┐   ┌───┬───┐ 
 * │K00│   │K01│K02│
 * └───┘   └───┴───┘ 
 * ┌───┬───┬───┬───┐
 * │K10│K11│K12│K13│
 * ├───┼───┼───┼───┤ 
 * │K20│K21│K22│K23│
 * ├───┼───┼───┼───┤ 
 * │K30│K31│K32│K33│
 * ├───┼───┼───┼───┤ 
 * │K40│K41│K42│K43│
 * ├───┼───┼───┼───┤ 
 * │K50│K51│K52│K53│
 * └───┴───┴───┴───┘
 */
#define LAYOUT_macropad( \
	K00,      K02, K03, \
	K10, K11, K12, K13, \
	K20, K21, K22, K23, \
	K30, K31, K32, K33, \
	K40, K41, K42, K43, \
	K50, K51, K52, K53  \
) { \
	{ K00,   KC_NO,  K02,  K03 }, \
	{ K10,   K11,   K12,   K13 }, \
	{ K20,   K21,   K22,   K23 }, \
	{ K30,   K31,   K32,   K33 }, \
	{ K40,   K41,   K42,   K43 }, \
	{ K50,   K51,   K52,   K53 }  \
}
