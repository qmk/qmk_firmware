/* Copyright 2019 Evy Dekkers
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

#define XXX KC_NO

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT_78_ansi( \
	K51, K52, 	K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K2C, K0E, \
	K53, K54,	K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,      K1E, \
	K55, K56,	K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2D,      K2E, \
	K57, K58,	K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D,      K3E, \
	K59, K5A,	K40, K41, K42,                K49,           K4A, K4B, K47, K4C, K4D,      K4E  \
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E }, \
    { K30, XXX, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E }, \
    { K40, K41, K42, XXX, XXX, XXX, XXX, K47, XXX, K49, K4A, K4B, K4C, K4D, K4E }, \
    { XXX, K51, K52, K53, K54, K55, K56, K57, K58, K59, K5A, XXX, XXX, XXX, XXX }  \
}
#define LAYOUT_78_iso( \
	K51, K52, 	K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K2C, K0E, \
	K53, K54,	K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,           K1E, \
	K55, K56,	K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K1D, K2D,      K2E, \
	K57, K58,	K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D,      K3E, \
	K59, K5A,	K40, K41, K42,                K49,           K4A, K4B, K47, K4C, K4D,      K4E  \
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E }, \
    { K40, K41, K42, XXX, XXX, XXX, XXX, K47, XXX, K49, K4A, K4B, K4C, K4D, K4E }, \
    { XXX, K51, K52, K53, K54, K55, K56, K57, K58, K59, K5A, XXX, XXX, XXX, XXX }  \
}
