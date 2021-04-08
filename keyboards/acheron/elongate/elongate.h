/* Copyright 2020 Gondolindrim
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
 * layout of the board and position of the Keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

#define KNO KC_NO

#define LAYOUT( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K49, K41, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19,      K1B, K1C, K4A, K42, \
    K20,      K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K4B, K44, \
    K30, K31, K32,      K34,           K37,      K3A, K3B, K3C, K3D, K4C, K47  \
)\
{\
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, KNO, K1B, K1C }, \
    { K20, KNO, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C }, \
    { K30, K31, K32, KNO, K34, KNO, KNO, K37, KNO, K3A, K3B, K3C, K3D }, \
    { KNO, K41, K42, KNO, K44, KNO, KNO, K47, KNO, K49, K4A, K4B, K4C }  \
}
