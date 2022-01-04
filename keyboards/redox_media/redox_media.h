/*
Copyright 2021 Shiftux <shiftux@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum.h"

#define XXX KC_NO

/*
 *                     ┌───┐                       ┌───┐┌───┐
 *                     │56 │                       │B6 ││B5 │
 *                     └───┘                       └───┘└───┘
 * ┌───┬───┬───┬───┬───┬───┐                       ┌───┬───┬───┬───┬───┬───┐
 * │00 │01 │02 │03 │04 │05 │                       │65 │64 │63 │62 │61 │60 │
 * ├───┼───┼───┼───┼───┼───┼───┐               ┌───┼───┼───┼───┼───┼───┼───┤
 * │10 │11 │12 │13 │14 │15 │06 │               │66 │75 │74 │73 │72 │71 │70 │
 * ├───┼───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┼───┤
 * │20 │21 │22 │23 │24 │25 │16 │               │76 │85 │84 │83 │82 │81 │80 │
 * ├───┼───┼───┼───┼───┼───┼───┘               └───┼───┼───┼───┼───┼───┼───┤
 * │30 │31 │32 │33 │34 │35 │ ┌───┬───┐   ┌───┬───┐ │95 │94 │93 │92 │91 │90 │
 * ├───┼───┼───┼───┼───┴───┘ │26 │36 │   │96 │86 │ └───┴───┼───┼───┼───┼───┤
 * │40 │41 │42 │43 │         ├───┼───┤   ├───┼───┤         │A3 │A2 │A1 │A0 │
 * └───┴───┴───┴───┘    ┌────┤   │   │   │   │   ├────┐    └───┴───┴───┴───┘
 *                      │44  │45 │46 │   │A6 │A5 │A4  │
 *                      └────┴───┴───┘   └───┴───┴────┘
 *
 *
 */

// rows are doubled
// clang-format off
#define LAYOUT( \
                        K56,                             KB6, KB5,                     \
  K00, K01, K02, K03, K04, K05,                          K65, K64, K63, K62, K61, K60, \
  K10, K11, K12, K13, K14, K15, K06,                K66, K75, K74, K73, K72, K71, K70, \
  K20, K21, K22, K23, K24, K25, K16,                K76, K85, K84, K83, K82, K81, K80, \
  K30, K31, K32, K33, K34, K35, K26, K36,      K96, K86, K95, K94, K93, K92, K91, K90, \
  K40, K41, K42, K43,   K44,    K45, K46,      KA6, KA5,   KA4,    KA3, KA2, KA1, KA0  \
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06 }, \
    { K10, K11, K12, K13, K14, K15, K16 }, \
    { K20, K21, K22, K23, K24, K25, K26 }, \
    { K30, K31, K32, K33, K34, K35, K36 }, \
    { K40, K41, K42, K43, K44, K45, K46 }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, K56 }, \
\
    { K60, K61, K62, K63, K64, K65, K66 }, \
    { K70, K71, K72, K73, K74, K75, K76 }, \
    { K80, K81, K82, K83, K84, K85, K86 }, \
    { K90, K91, K92, K93, K94, K95, K96 }, \
    { KA0, KA1, KA2, KA3, KA4, KA5, KA6 }, \
    { XXX, XXX, XXX, XXX, XXX, KB5, KB6 }  \
}
