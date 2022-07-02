/* Copyright 2022 Adam K (@Envious-Data)
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
//#include "via.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 *
 *
 *
 *
 */

#define LAYOUT_tkl_comb( \
   	 KC000,        KC001, KC002, KC003, KC004, KC005, KC006, KC007, KC008,        KC009, KC010, KC011, KC012, KC013, KC014, KC015, \
   	 															       \
	 KC100, KC101, KC102, KC103, KC104, KC105, KC106, KC107, KC108, KC109, KC110, KC111, KC112,        KC113, KC114, KC115, KC116, \
	 KC200,        KC201, KC202, KC203, KC204, KC205, KC206, KC207, KC208, KC209, KC210, KC211, KC212, KC213, KC214, KC215, KC216, \
	 KC300,        KC301, KC302, KC303, KC304, KC305, KC306, KC307, KC308, KC309, KC310, KC311, KC312, KC313,                      \
	 KC400, KC401, KC402, KC403, KC404, KC405, KC406, KC407, KC408, KC409, KC410, KC411,        KC412,               KC413,        \
	 KC500, KC501,        KC502,               KC503,                      KC504, KC505,        KC506, KC507, KC508, KC509, KC510  \
) { \
	{ KC000, KC_NO, KC001, KC002, KC003, KC004, KC_NO, KC005, KC006, KC007, KC008, KC009, KC010, KC011, KC012, KC013, KC014, KC015 }, \
	{ KC100, KC101, KC102, KC103, KC104, KC105, KC106, KC107, KC108, KC109, KC110, KC111, KC112, KC_NO, KC113, KC114, KC115, KC116 }, \
	{ KC200, KC_NO, KC201, KC202, KC203, KC204, KC205, KC206, KC207, KC208, KC209, KC210, KC211, KC212, KC213, KC214, KC215, KC216 }, \
	{ KC300, KC_NO, KC301, KC302, KC303, KC304, KC305, KC306, KC307, KC308, KC309, KC310, KC311, KC312, KC313, KC_NO, KC_NO, KC_NO }, \
	{ KC400, KC401, KC402, KC403, KC404, KC405, KC406, KC407, KC408, KC409, KC410, KC411, KC_NO, KC412, KC_NO, KC_NO, KC413, KC_NO }, \
	{ KC500, KC501, KC_NO, KC502, KC_NO, KC_NO, KC503, KC_NO, KC_NO, KC_NO, KC504, KC505, KC_NO, KC506, KC507, KC508, KC509, KC510 }, \
}
