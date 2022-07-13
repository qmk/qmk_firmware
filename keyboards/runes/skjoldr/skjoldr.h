/* Copyright 2021 Vicktor
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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT(  \
	K00, K10, K20, K30, K40, K50, K60, K70, K80, K90, KA0, KB0, KC0, KD0, \
	K01, K11, K21, K31, K41, K51, K61, K71, K81, K91, KA1, KB1, KC1, KD1, \
	K02, K12, K22, K32, K42, K52, K62, K72, K82, K92, KA2, KB2, KC2,       \
	K03, K13, K23, K33, K43, K53, K63, K73, K83, K93, KA3,      KC3, KD3, \
	K04, K14, K24,           K54,                K94, KA4, KB4, KC4, KD4 \
) { \
	{K00, K10, K20, K30,   K40,   K50, K60,   K70,   K80,    K90, KA0, KB0,   KC0, KD0 }, \
	{K01, K11, K21, K31,   K41,   K51, K61,   K71,   K81,    K91, KA1, KB1,   KC1, KD1 }, \
	{K02, K12, K22, K32,   K42,   K52, K62,   K72,   K82,    K92, KA2, KB2,   KC2, KC_NO }, \
	{K03, K13, K23, K33,   K43,   K53, K63,   K73,   K83,    K93, KA3, KC_NO, KC3, KD3 }, \
	{K04, K14, K24, KC_NO, KC_NO, K54, KC_NO, KC_NO, KC_NO,  K94, KA4, KB4,   KC4, KD4 } \
}
