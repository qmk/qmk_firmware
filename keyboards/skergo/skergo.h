/* Copyright (C) 2021  Keyz.io Ltd.
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

#pragma once

#include "quantum.h"

#define ___ KC_NO

/*                                                                      ┌───┐
 * ┌───┬───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┬───┬───┐│1E │   ┌───────┐
 * │00 │01 │02 │03 │04 │05 │06 │       │07 │08 │09 │0A │0B │0C │0D │0E │├───┤   │0E     │ 2u Backspace
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┘     ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤│2E │   └───────┘
 * │10   │11 │12 │13 │14 │15 │       │16 │17 │18 │19 │1A │1B │1C │1D   │├───┤
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┐      └┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤│3E │
 * │20    │21 │22 │23 │24 │25 │       │26 │27 │28 │29 │2A │2B │2C      │└───┘
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐   ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┘
 * │30      │31 │32 │33 │34 │35 │   │46 │36 │37 │38 │39 │3A │3B    │┌───┐
 * ├────┬───┴───┼───┴─┬─┴───┴─┬─┴─┐ └─┬─┴───┴───┴┬──┴──┬┴───┴──────┘│3D │
 * │40  │       │42   │44     │45 │   │47        │49   │        ┌───┼───┼───┐
 * └────┘       └─────┴───────┴───┘   └──────────┴─────┘        │4C │4D │4E │
 *                                                              └───┴───┴───┘
 * - Position K46 (secondary B key) is optional
 */

#define LAYOUT_2u_bs( \
	K00, K01, K02, K03, K04, K05, K06,        K07, K08, K09, K0A, K0B, K0C, K0E,   K1E, \
	K10, K11, K12, K13, K14, K15,        K16, K17, K18, K19, K1A, K1B, K1C, K1D,   K2E, \
	K20, K21, K22, K23, K24, K25,        K26, K27, K28, K29, K2A, K2B,      K2C,   K3E, \
	K30, K31, K32, K33, K34, K35,        K46, K36, K37, K38, K39, K3A, K3B, K3D,        \
	K40,      K42,      K44, K45,        K47,           K49,           K4C, K4D, K4E    \
) { \
	{ K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, ___, K0E }, \
	{ K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E }, \
	{ K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, ___, K2E }, \
	{ K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, ___, K3D, K3E }, \
	{ K40, ___, K42, ___, K44, K45, K46, K47, ___, K49, ___, ___, K4C, K4D, K4E }  \
}

#define LAYOUT_split_bs( \
	K00, K01, K02, K03, K04, K05, K06,        K07, K08, K09, K0A, K0B, K0C, K0D, K0E,   K1E, \
	K10, K11, K12, K13, K14, K15,        K16, K17, K18, K19, K1A, K1B, K1C, K1D,        K2E, \
	K20, K21, K22, K23, K24, K25,        K26, K27, K28, K29, K2A, K2B,      K2C,        K3E, \
	K30, K31, K32, K33, K34, K35,        K46, K36, K37, K38, K39, K3A, K3B, K3D,             \
	K40,      K42,      K44, K45,        K47,           K49,           K4C, K4D, K4E         \
) { \
	{ K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E }, \
	{ K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E }, \
	{ K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, ___, K2E }, \
	{ K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, ___, K3D, K3E }, \
	{ K40, ___, K42, ___, K44, K45, K46, K47, ___, K49, ___, ___, K4C, K4D, K4E }  \
}
