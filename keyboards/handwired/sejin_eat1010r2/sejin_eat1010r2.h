/* Copyright 2023 DmNosachev
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

/* readability */
#define XXX KC_NO

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

#define LAYOUT( \
	K10,      K1B, K2B, K27, K17,   K15, K25, K14, K13,    K24, K35, K26, K16,   K1C, K2C, K1D, \
	K20, K30, K3B, K37, K21, K11, K12, K22, K45, K34, K23, K33, K44, K06, K46,   K36, K3C, K3D,  K2D, K3E, K4E, K3F, \
	K40,  K00, K4B, K47, K41, K31, K32, K42, K55, K04, K43, K03, K54, K07,       K05, K4C, K0C,  K0D, K4D, K0E, K4F, \
	K70,   K50, K0B, K67, K51, K01, K02, K52, K65, K64, K53,              K63,                   K5C, K5D, K5E, \
	K7A,    K6B, K5B, K77, K71, K61, K62, K72, K75, K74, K73,             K6A,        K56,       K6C, K6D, K6E, K5F, \
	K79,     K78,               K7B,                               K68,   K69,   K66, K76, K7C,  K7E,      K7F \
) \
{ \
/* 0 */  { K00, K01, K02, K03, K04, K05, K06, K07, XXX, XXX, XXX, K0B, K0C, K0D, K0E, XXX }, \
/* 1 */  { K10, K11, K12, K13, K14, K15, K16, K17, XXX, XXX, XXX, K1B, K1C, K1D, XXX, XXX }, \
/* 2 */  { K20, K21, K22, K23, K24, K25, K26, K27, XXX, XXX, XXX, K2B, K2C, K2D, XXX, XXX }, \
/* 3 */  { K30, K31, K32, K33, K34, K35, K36, K37, XXX, XXX, XXX, K3B, K3C, K3D, K3E, K3F }, \
/* 4 */  { K40, K41, K42, K43, K44, K45, K46, K47, XXX, XXX, XXX, K4B, K4C, K4D, K4E, K4F }, \
/* 5 */  { K50, K51, K52, K53, K54, K55, K56, XXX, XXX, XXX, XXX, K5B, K5C, K5D, K5E, K5F }, \
/* 6 */  { XXX, K61, K62, K63, K64, K65, K66, K67, K68, K69, K6A, K6B, K6C, K6D, K6E, XXX }, \
/* 7 */  { K70, K71, K72, K73, K74, K75, K76, K77, K78, K79, K7A, K7B, K7C, XXX, K7E, K7F }  \
}
/*          0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F     */

#define LAYOUT_debug( \
	K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, \
	K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, \
	K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, K2F, \
	K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E, K3F, \
	K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4D, K4E, K4F, \
	K50, K51, K52, K53, K54, K55, K56, K57, K58, K59, K5A, K5B, K5C, K5D, K5E, K5F, \
	K60, K61, K62, K63, K64, K65, K66, K67, K68, K69, K6A, K6B, K6C, K6D, K6E, K6F, \
	K70, K71, K72, K73, K74, K75, K76, K77, K78, K79, K7A, K7B, K7C, K7D, K7E, K7F  \
) \
{ \
/* 0 */  { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F }, \
/* 1 */  { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F }, \
/* 2 */  { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, K2F }, \
/* 3 */  { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E, K3F }, \
/* 4 */  { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4D, K4E, K4F }, \
/* 5 */  { K50, K51, K52, K53, K54, K55, K56, K57, K58, K59, K5A, K5B, K5C, K5D, K5E, K5F }, \
/* 6 */  { K60, K61, K62, K63, K64, K65, K66, K67, K68, K69, K6A, K6B, K6C, K6D, K6E, K6F }, \
/* 7 */  { K70, K71, K72, K73, K74, K75, K76, K77, K78, K79, K7A, K7B, K7C, K7D, K7E, K7F }  \
}
/*          0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F     */

