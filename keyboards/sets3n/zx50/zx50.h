/* Copyright 2021 Sets3n/Сэцэн
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

/* Standard arrangement / LAYOUT
 * ┌─────────────────────────────────┬───┬─────────┐
 * │                                 │45 │         │
 * ├───┬───┬───┬───┬───┬───┬───┬───┬─┴─┬─┴─┬───┬───┤
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │
 * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
 * │10 │11 │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │
 * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
 * │20 │21 │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │
 * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
 * │30 │31 │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │
 * ├───┼───┼───┼───┼───┼───┴───┼───┼───┼───┼───┼───┤
 * │40 │41 │42 │43 │44 │46(2u) │47 │48 │49 │4a │4b │
 * └───┴───┴───┴───┴───┴───────┴───┴───┴───┴───┴───┘
*/

#define LAYOUT( \
	K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0a, K0b, \
	K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1a, K1b, \
	K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2a, K2b, \
	K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3a, K3b, \
	K40, K41, K42, K43, K44, k45, K46, K47, K48, K49, K4a, K4b  \
) { \
	{ K00,  K01,  K02,  K03,  K04,  K05,   K06,  K07,  K08,  K09,  K0a,  K0b }, \
	{ K10,  K11,  K12,  K13,  K14,  K15,   K16,  K17,  K18,  K19,  K1a,  K1b }, \
	{ K20,  K21,  K22,  K23,  K24,  K25,   K26,  K27,  K28,  K29,  K2a,  K2b }, \
	{ K30,  K31,  K32,  K33,  K34,  K35,   K36,  K37,  K38,  K39,  K3a,  K3b }, \
	{ K40,  K41,  K42,  K43,  K44,  k45,   K46,  K47,  K48,  K49,  K4a,  K4b }  \
}
