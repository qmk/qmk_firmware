/* Copyright 2021 NachoxMacho
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
* along with this program.  If not, see &lt;http://www.gnu.org/licenses/&gt;.
*/

#pragma once

#include "quantum.h"

#define LAYOUT_numpad_6x5( \
	K00, K01, K02, K03, K04, \
	K10, K11, K12, K13, K14, \
	K20, K21, K22, K23,      \
	K30, K31, K32, K33, K34, \
	K40, K41, K42, K43,      \
	K50, K51,      K52, K53  \
) { \
	{ K00,   K01,   K02,   K03,   K04 }, \
	{ K10,   K11,   K12,   K13,   K14 }, \
	{ K20,   K21,   K22,   K23,   K34 }, \
	{ K30,   K31,   K32,   K33,   KC_NO }, \
	{ K40,   K41,   K42,   K43,   KC_NO }, \
	{ K50,   K51,   K52,   K53,   KC_NO }  \
}
