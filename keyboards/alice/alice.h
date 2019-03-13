/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

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

/* LAYOUT
 * ┌───┐ ┌───┬───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┬───┬───┐
 * │63 │ │00 │01 │02 │03 │04 │05 │06 │         │07 │08 │09 │10 │11 │12 │13 │14 │
 * ├───┤ ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┘       ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │64 │ │15   │16 │17 │18 │19 │20 │         │21 │22 │23 │24 │25 │26 │27 │28   │
 * ├───┤ ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┐        └┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │65 │ │29    │30 │31 │32 │33 │34 │         │35 │36 │37 │38 │39 │40 │41      │
 * └───┘ ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐     ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 *       │42      │43 │44 │45 │46 │47 │     │48 │49 │50 │51 │52 │53 │54    │55 │
 *       ├─────┬──┴──┬┴───┴┬──┴───┴┬──┴─┐   ├───┴───┴──┬┴───┴┬──┴───┴────┬─┴───┤
 *       │56   │     │57   │58     │59  │   │60        │61   │           │62   │
 *       └─────┘     └─────┴───────┴────┘   └──────────┴─────┘           └─────┘
 */
#define LAYOUT( \
  K63,   K00, K01, K02, K03, K04, K05, K06,      K07, K08, K09, K10, K11, K12, K13, K14, \
  K64,   K15, K16, K17, K18, K19, K20,      K21, K22, K23, K24, K25, K26, K27, K28,      \
  K65,   K29, K30, K31, K32, K33, K34,      K35, K36, K37, K38, K39, K40,      K41,      \
         K42, K43, K44, K45, K46, K47,      K48, K49, K50, K51, K52, K53, K54, K55,      \
         K56,      K57,      K58, K59,           K60,      K61,                K62       \
) \
{ \
  { K00  , K01  , K02  , K03  , K04  , K05  , K06  , K07  , K08  , K09  , K10  , K11  , K12  , K13  , K14   }, \
  { K15  , K16  , K17  , K18  , K19  , K20  , K21  , K22  , K23  , K24  , K25  , K26  , K27  , K28  , KC_NO }, \
  { K29  , K30  , K31  , K32  , K33  , K34  , K35  , K36  , K37  , K38  , K39  , K40  , K41  , KC_NO, KC_NO }, \
  { K42  , K43  , K44  , K45  , K46  , K47  , K48  , K49  , K50  , K51  , K52  , K53  , K54  , K55  , KC_NO }, \
  { K56  , K57  , K58  , K59  , KC_NO, KC_NO, K60  , K61  , K62  , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
  { K63  , K64  , K65  , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }  \
}

