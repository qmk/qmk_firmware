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

/* LAYOUT
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0d │0e │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │
 * ├───┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬───┬───┤
 * │30 │31 │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3c │3d │3e │
 * ├───┴┬──┴─┬─┴──┬┴───┴───┼───┴┬──┴───┴───┼───┼───┼───┼───┼───┤
 * │40  │41  │42  │44      │46  │48        │4a │4b │4c │4d │4e │
 * └────┴────┴────┴────────┴────┴──────────┴───┴───┴───┴───┴───┘
*/
#define LAYOUT( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0a, K0b, K0c, K0d, K0e, \
    K10,      K12, K13, K14, K15, K16, K17, K18, K19, K1a, K1b, K1c, K1d, K1e, \
    K20,      K22, K23, K24, K25, K26, K27, K28, K29, K2a, K2b, K2c, K2d,      \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3a, K3b, K3c, K3d, K3e, \
    K40, K41, K42,      K44,      K46,      K48,      K4a, K4b, K4c, K4d, K4e  \
) { \
    { K00,   K02,   K04,   K06,   K08,   K0a, K0c,   K0d }, \
    { K01,   K03,   K05,   K07,   K09,   K0b, KC_NO, K0e }, \
    { K10,   K12,   K14,   K16,   K18,   K1a, K1c,   K1d }, \
    { KC_NO, K13,   K15,   K17,   K19,   K1b, KC_NO, K1e }, \
    { K20,   K22,   K24,   K26,   K28,   K2a, K2c,   K2d }, \
    { KC_NO, K23,   K25,   K27,   K29,   K2b, KC_NO, K2e }, \
    { K30,   K32,   K34,   K36,   K38,   K3a, K3c,   K3d }, \
    { K31,   K33,   K35,   K37,   K39,   K3b, KC_NO, K3e }, \
    { K40,   K42,   K44,   K46,   K48,   K4a, K4c,   K4d }, \
    { K41,   KC_NO, KC_NO, KC_NO, KC_NO, K4b, KC_NO, K4e } \
}

/* LAYOUT_60_ansi 
  * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ 
  * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0e     │ 
  * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ 
  * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │ 
  * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ 
  * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │ 
  * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤ 
  * │30      │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d        │ 
  * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ 
  * │40  │41  │42  │46                      │4a  │4b  │4d  │4e  │ 
  * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ 
 */ 
 #define LAYOUT_60_ansi( \
     K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0a, K0b, K0c,      K0e, \
     K10,      K12, K13, K14, K15, K16, K17, K18, K19, K1a, K1b, K1c, K1d, K1e, \
     K20,      K22, K23, K24, K25, K26, K27, K28, K29, K2a, K2b, K2c, K2d,      \
     K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3a, K3b,      K3d,      \
     K40, K41, K42,                K46,                K4a, K4b,      K4d, K4e  \
 ) { \
    { K00,   K02,   K04,   K06,   K08,   K0a, K0c,   K0e   }, \
    { K01,   K03,   K05,   K07,   K09,   K0b, KC_NO, KC_NO }, \
    { K10,   K12,   K14,   K16,   K18,   K1a, K1c,   K1d   }, \
    { KC_NO, K13,   K15,   K17,   K19,   K1b, KC_NO, K1e   }, \
    { K20,   K22,   K24,   K26,   K28,   K2a, K2c,   KC_NO }, \
    { KC_NO, K23,   K25,   K27,   K29,   K2b, KC_NO, K2d   }, \
    { K30,   K32,   K34,   K36,   K38,   K3a, KC_NO, K3d   }, \
    { KC_NO, K33,   K35,   K37,   K39,   K3b, KC_NO, KC_NO }, \
    { K40,   K42,   KC_NO, K46,   KC_NO, K4a, KC_NO, K4d   }, \
    { K41,   KC_NO, KC_NO, KC_NO, KC_NO, K4b, KC_NO, K4e   } \
}

