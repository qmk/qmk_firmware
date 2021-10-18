/*
Copyright 2021 KapCave

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include "quantum.h"

/*
 * ┌─────┬─────┬─────┬─────┐
 * │Num1 │ Eq  │Slsh │Star │
 * ├─────┼─────┼─────┼─────┤
 * │  7  │  8  │  9  │     │
 * ├─────┼─────┼─────┤Plus │
 * │  4  │  5  │  6  │     │
 * ├─────┼─────┼─────┼─────┤
 * │  1  │  2  │  3  │     │
 * ├─────┴─────┼─────┤ Ent │
 * │     0     │  .  │     │
 * └───────────┴─────┴─────┘
 */

#define LAYOUT_numpad_5x4( \
	K_NUM1, K_SLSH, K_STAR, K_MINUS, \
    K_7, K_8, K_9, \
    K_4, K_5, K_6, K_PLUS, \
    K_1, K_2, K_3, \
         K_0, K_DOT, K_ENT   \
) { \
	{ K_NUM1, K_SLSH, K_STAR, K_MINUS }, \
    { K_7, K_8, K_9, KC_NO }, \
    { K_4, K_5, K_6, K_PLUS }, \
    { K_1, K_2, K_3, K_ENT }, \
    { K_0, K_DOT, KC_NO, KC_NO }  \
}

/*
 * ┌─────┬─────┬─────┬─────┐
 * │Num1 │Eql  │Slsh │Star │
 * ├─────┼─────┼─────┼─────┤
 * │  7  │  8  │  9  │Minus│
 * ├─────┼─────┼─────┼─────┤
 * │  4  │  5  │  6  │Plus │
 * ├─────┼─────┼─────┼─────┤
 * │  1  │  2  │  3  │     │
 * ├─────┼─────┼─────┤ Ent │
 * │  0  │ 10  │  .  │     │
 * └─────┴─────┴─────┴─────┘
 */

#define LAYOUT_numpad_aek( \
	K_NUM1, K_EQ1, K_SLSH1, K_STAR1, \
    K_7, K_8, K_9, K_MINUS1, \
    K_4, K_5, K_6, K_PLUS, \
    K_1, K_2, K_3, \
         K_0, K_DOT1, K_ENT   \
) { \
	{ K_NUM1, K_EQ1, K_SLSH1, K_STAR1 }, \
    { K_7, K_8, K_9, K_MINUS1 }, \
    { K_4, K_5, K_6, K_PLUS }, \
    { K_1, K_2, K_3, K_ENT }, \
    { K_0, K_DOT1, KC_NO, KC_NO }  \
}

/*
 * ┌─────┬─────┬─────┬─────┐
 * │Num1 │ Eq  │Slsh │Star │
 * ├─────┼─────┼─────┼─────┤
 * │  7  │  8  │  9  │Minus│
 * ├─────┼─────┼─────┼─────┤
 * │  4  │  5  │  6  │Plus │
 * ├─────┼─────┼─────┼─────┤
 * │  1  │  2  │  3  │ 11  │
 * ├─────┼─────┼─────┼─────┤
 * │  0  │ 10  │  .  │ Ent │
 * └─────┴─────┴─────┴─────┘
 */

#define LAYOUT_ortho_5x4( \
	K_NUM1, K_EQ1, K_SLSH1, K_STAR1, \
    K_7, K_8, K_9, K_MINUS1, \
    K_4, K_5, K_6, K_PLUS, \
    K_1, K_2, K_3, K_11, \
    K_0, K_10, K_DOT1, K_ENT   \
) { \
	{ K_NUM1, K_EQ1, K_SLSH1, K_STAR1 }, \
    { K_7, K_8, K_9, K_MINUS1 }, \
    { K_4, K_5, K_6, K_PLUS }, \
    { K_1, K_2, K_3, K_ENT }, \
    { K_0, K_DOT1, K_10, K_11 }  \
}
