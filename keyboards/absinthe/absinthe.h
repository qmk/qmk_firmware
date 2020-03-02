/* Copyright 2020 cfbender
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

#define _x_ KC_NO

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    K00, K10, K01, K11, K01, K12, K03, K13, K04, K14, K05, K15, K06, K16, K07, K17, K08, K18, \
    K20,      K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K26, K36, K27, K37, K28, K38, \
    K40,      K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K46,      K56,                     \
    K60, K61, K71, K62, K72, K63, K73, K64, K74, K65, K75,           K66, K67,      K68,     \
	K80, K81, K82,                K83,                K85,      K86,      K87, K77, K88, K78  \
) \
{ \
    { K00, _x_, K02, K03, K04, K05, K06, K07, K08, K09, _x_, K0B, K0C, K0D, K0E, K0F, K0G, K0H }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, _x_, K1F, K1G, K1H }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, _x_, K2F, K2G, K2H }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, _x_, K3D, _x_, _x_, _x_, _x_ }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, _x_, _x_, K4D, _x_, _x_, K4G, _x_ }, \
    { K50, K51, K52, _x_, _x_, _x_, K56, _x_, _x_, K59, K5A, _x_, K5C, _x_, K5E, K5F, K5G, K5H }  \
}
