/* Copyright 2020 DmNosachev
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
  K35, K34,   KA7, KA6, KA5, KA4, KA3, KA2, KA1, KA0, K97, K96, K95, K94, K93,   K92, K57,    K23,   K22, \
  K33, K32,   K91,  K90, K87, K86, K85, K84, K83, K82, K81, K80, K77, K76, K75,       K21, K20, K17, K16, \
  K31, K30,   K73,   K72, K71, K70, K67, K66, K65, K64, K63, K62, K61, K60,      K74, K15, K14, K13, K12, \
  K26, K27,   K56,    K54, K53, K52, K51, K50, K47, K46, K45, K44, K43,    K42,  K41, K11, K10, K07, K04, \
  K24, K25,   K40,   K55,                   K37,                           K36,       K06,      K05 \
) \
{ \
/* 0 */  { XXX, XXX, XXX, XXX, K04, K05, K06, K07 }, \
/* 1 */  { K10, K11, K12, K13, K14, K15, K16, K17 }, \
/* 2 */  { K20, K21, K22, K23, K24, K25, K26, K27 }, \
/* 3 */  { K30, K31, K32, K33, K34, K35, K36, K37 }, \
/* 4 */  { K40, K41, K42, K43, K44, K45, K46, K47 }, \
/* 5 */  { K50, K51, K52, K53, K54, K55, K56, K57 }, \
/* 6 */  { K60, K61, K62, K63, K64, K65, K66, K67 }, \
/* 7 */  { K70, K71, K72, K73, K74, K75, K76, K77 }, \
/* 8 */  { K80, K81, K82, K83, K84, K85, K86, K87 }, \
/* 9 */  { K90, K91, K92, K93, K94, K95, K96, K97 }, \
/* A */  { KA0, KA1, KA2, KA3, KA4, KA5, KA6, KA7 }  \
}
/*         0    1    2    3    4    5    6    7     */

