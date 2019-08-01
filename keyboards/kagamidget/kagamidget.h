/* Copyright 2019 yynmt
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

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    K01, K05, K09, K13, K17, K21, K25, K29, K33, K37, K41, K45, \
    K02, K06, K10, K14, K18, K22, K26, K30, K34, K38, K42, K46, \
    K03, K07, K11, K15, K19, K23, K27, K31, K35, K39, K43, K47, \
    K04, K08, K12, K16, K20, K24, K28, K32, K36, K40, K44, K48  \
) \
{ \
    { K01, K05, K09, K13, K17, K21, K25, K29, K33, K37, K41, K45 }, \
    { K02, K06, K10, K14, K18, K22, K26, K30, K34, K38, K42, K46 }, \
    { K03, K07, K11, K15, K19, K23, K27, K31, K35, K39, K43, K47 }, \
    { K04, K08, K12, K16, K20, K24, K28, K32, K36, K40, K44, K48 }, \
}
