/* Copyright 2021 Ocean
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

/*
 *     ┌───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┬───┐
 *     │00 │01 │02 │03 │04 │05 │   │06 │07 │08 │09 │0A │0B │3A │
 *    ┌┴───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┴──┬┘
 *    │10  │11 │12 │13 │14 │15 │   │16 │17 │18 │19 │1A │1B    │
 *  ┌─┴────┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼────┬─┘
 *  │20    │21 │22 │23 │24 │25 │   │26 │27 │28 │29 │2A │2B  │
 * ┌┴──┬───┼───┴───┼───┼───┼───┤   ├───┼───┼───┼───┴───┼───┬┘
 * │30 │31 │       │33 │34 │35 │   │36 │37 │38 │       │3B │
 * └───┴───┘       └───┴───┴───┘   └───┴───┴───┘       └───┘
 *                     ┌───────┐   ┌───────┐
 *                     │35     │   │36     │
 *                     └───────┘   └───────┘
 */

#define LAYOUT_all(\
  K00, K01, K02, K03, K04, K05,   K06, K07, K08, K09, K0A, K0B, K3A, \
  K10, K11, K12, K13, K14, K15,   K16, K17, K18, K19, K1A, K1B,      \
  K20, K21, K22, K23, K24, K25,   K26, K27, K28, K29, K2A, K2B,      \
  K30, K31,      K33, K34, K35,   K36, K37, K38,           K3B       \
) \
{ \
  { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B }, \
  { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B }, \
  { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B }, \
  { K30, K31, XXX, K33, K34, K35, K36, K37, K38, XXX, K3A, K3B }, \
}

#define LAYOUT_2x2u(\
  K00, K01, K02, K03, K04, K05,   K06, K07, K08, K09, K0A, K0B, K3A, \
  K10, K11, K12, K13, K14, K15,   K16, K17, K18, K19, K1A, K1B,      \
  K20, K21, K22, K23, K24, K25,   K26, K27, K28, K29, K2A, K2B,      \
  K30, K31,      K33,      K35,   K36,      K38,           K3B       \
) \
{ \
  { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B }, \
  { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B }, \
  { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B }, \
  { K30, K31, XXX, K33, XXX, K35, K36, XXX, K38, XXX, K3A, K3B }, \
}
