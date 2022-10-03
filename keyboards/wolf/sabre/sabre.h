/*
Copyright 2020 <contact@vwolf.be>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum.h"

/*
 * ┌───┐   ┌───┬───┬───┬───┐         ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
 * │00 │   │01 │11 │02 │12 │         │13 │04 │14 │05 │ │15 │06 │16 │07 │ │17 │08 │18 │
 * └───┘   └───┴───┴───┴───┘         └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
 * ┌───┬───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
 * │20 │30 │21 │31 │22 │32 │23 │       │33 │24 │34 │25 │35 │26 │36     │ │37 │28 │38 │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴     ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤
 * │40   │50 │41 │51 │42 │52 │       │43 │53 │44 │54 │45 │55 │46 │56   │ │57 │48 │58 │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┐      └┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘
 * │60    │70 │61 │71 │62 │72 │       │63 │73 │64 │74 │65 │75 │76      │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐   ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤     ┌───┐       ┌──────────┐
 * │80      │90 │81 │91 │82 │92 │   │83 │93 │84 │94 │85 │95 │86    │96 │     │88 │       │86        │ 2.75u RShift
 * ├─────┬──┴┬──┴──┬┴──┬┴───┴───┤   ├───┴───┴──┬┴──┬┴───┴┬──┴┬────┬┴───┘ ┌───┼───┼───┐   └──────────┘
 * │A0   │   │B0   │A1 │A2      │   │B3        │B4 │A5   │   │A6  │      │B7 │A8 │B8 │
 * └─────┘   └─────┴───┴────────┘   └──────────┴───┴─────┘   └────┘      └───┴───┴───┘
 *           ┌───┬─────┐                       ┌─────┬───┐
 *           │B0 │A1   │                       │B4   │A5 │
 *           └───┴─────┘                       └─────┴───┘
 *           ┌────┬────┐                       ┌────┬────┐
 *           │B0  │A1  │                       │B4  │A5  │
 *           └────┴────┘                       └────┴────┘
 */

/* sabre Keymap Definitions */
#define LAYOUT( \
    K00,      K01, K11, K02, K12,      K13, K04, K14, K05, K15, K06, K16, K07, K17, K08, K18, \
    K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K26, K36,      K37, K28, K38, \
    K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K46, K56,      K57, K48, K58, \
    K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K75,      K76,                     \
    K80, K90, K81, K91, K82, K92, K83, K93, K84, K94, K85, K95, K86, K96,           K88,      \
    KA0, KB0, KA1,      KA2,           KB3,      KB4, KA5,      KA6,           KB7, KA8, KB8  \
) { \
    { K00,   K01,   K02,   KC_NO, K04,   K05,   K06,   K07,   K08   }, \
    { KC_NO, K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18   }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   KC_NO, K28   }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,   K38   }, \
    { K40,   K41,   K42,   K43,   K44,   K45,   K46,   KC_NO, K48   }, \
    { K50,   K51,   K52,   K53,   K54,   K55,   K56,   K57,   K58   }, \
    { K60,   K61,   K62,   K63,   K64,   K65,   KC_NO, KC_NO, KC_NO }, \
    { K70,   K71,   K72,   K73,   K74,   K75,   K76,   KC_NO, KC_NO }, \
    { K80,   K81,   K82,   K83,   K84,   K85,   K86,   KC_NO, K88   }, \
    { K90,   K91,   K92,   K93,   K94,   K95,   K96,   KC_NO, KC_NO }, \
    { KA0,   KA1,   KA2,   KC_NO, KC_NO, KA5,   KA6,   KC_NO, KA8   }, \
    { KB0,   KC_NO, KC_NO, KB3,   KB4,   KC_NO, KC_NO, KB7,   KB8   }  \
}
