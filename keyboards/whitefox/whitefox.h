/*
Copyright 2014 Jun Wako <wakojun@gmail.com>

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
#ifndef WHITEFOX_H
#define WHITEFOX_H

#include "quantum.h"

/* WhiteFox
 * ,---------------------------------------------------------------.
 * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|Ins|
 * |---------------------------------------------------------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Backs|Del|
 * |---------------------------------------------------------------|
 * |CapsL |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter   |PgU|
 * |---------------------------------------------------------------|
 * |Shif|   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |PgD|
 * |---------------------------------------------------------------|
 * |Ctrl|Gui |Alt |         Space    |App |Alt |Gui |  |Lef|Dow|Rig|
 * `---------------------------------------------------------------'
 */

#define LAYOUT( \
    K00, K10, K20, K30, K40, K50, K60, K70, K80, K01, K11, K21, K31, K41, K51, K61, \
    K71, K81, K02, K12, K22, K32, K42, K52, K62, K72, K82, K03, K13, K23,      K33, \
    K43, K53, K63, K73, K83, K04, K14, K24, K34, K44, K54, K64, K74, K84,      K05, \
    K15, K25, K35, K45, K55, K65, K75, K85, K06, K16, K26, K36, K46,      K56, K66, \
    K76, K86, K07,                K17,           K27, K37, K47,      K57, K67, K77  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07   }, \
    { K10, K11, K12, K13, K14, K15, K16, K17   }, \
    { K20, K21, K22, K23, K24, K25, K26, K27   }, \
    { K30, K31, K32, K33, K34, K35, K36, K37   }, \
    { K40, K41, K42, K43, K44, K45, K46, K47   }, \
    { K50, K51, K52, K53, K54, K55, K56, K57   }, \
    { K60, K61, K62, K63, K64, K65, K66, K67   }, \
    { K70, K71, K72, K73, K74, K75, K76, K77   }, \
    { K80, K81, K82, K83, K84, K85, K86, KC_NO }  \
}

/* Keymap for truefox layout */
#define LAYOUT_truefox( \
    K00, K10, K20, K30, K40, K50, K60, K70, K80, K01, K11, K21, K31, K41, K51, K61, \
    K71, K81, K02, K12, K22, K32, K42, K52, K62, K72, K82, K03, K13, K23,      K33, \
    K43, K53, K63, K73, K83, K04, K14, K24, K34, K44, K54, K64,      K84,      K05, \
    K15,      K35, K45, K55, K65, K75, K85, K06, K16, K26, K36, K46,      K56, K66, \
    K76, K86, K07,                K17,           K27, K37,           K57, K67, K77  \
) { \
    { K00, K01, K02, K03, K04,   K05,   K06, K07   }, \
    { K10, K11, K12, K13, K14,   K15,   K16, K17   }, \
    { K20, K21, K22, K23, K24,   KC_NO, K26, K27   }, \
    { K30, K31, K32, K33, K34,   K35,   K36, K37   }, \
    { K40, K41, K42, K43, K44,   K45,   K46, KC_NO }, \
    { K50, K51, K52, K53, K54,   K55,   K56, K57   }, \
    { K60, K61, K62, K63, K64,   K65,   K66, K67   }, \
    { K70, K71, K72, K73, KC_NO, K75,   K76, K77   }, \
    { K80, K81, K82, K83, K84,   K85,   K86, KC_NO }  \
}

/* ISO WhiteFox
 * ,---------------------------------------------------------------.
 * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| Backsp|Ins|
 * |---------------------------------------------------------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Enter|Del|
 * |------------------------------------------------------`    |---|
 * |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  \|    |PgU|
 * |---------------------------------------------------------------|
 * |Shif|   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |PgD|
 * |---------------------------------------------------------------|
 * |Ctrl|Gui |Alt |         Space    |Fn0 |Alt |Gui |  |Lef|Dow|Rig|
 * `---------------------------------------------------------------'
 */

#define LAYOUT_iso( \
    K00, K10, K20, K30, K40, K50, K60, K70, K80, K01, K11, K21, K31, K51,      K61, \
    K71, K81, K02, K12, K22, K32, K42, K52, K62, K72, K82, K03, K13,           K33, \
    K43, K53, K63, K73, K83, K04, K14, K24, K34, K44, K54, K64, K74, K84,      K05, \
    K15, K25, K35, K45, K55, K65, K75, K85, K06, K16, K26, K36, K46,      K56, K66, \
    K76, K86, K07,                K17,           K27, K37, K47,      K57, K67, K77  \
) { \
    { K00, K01,   K02, K03,   K04, K05, K06, K07   }, \
    { K10, K11,   K12, K13,   K14, K15, K16, K17   }, \
    { K20, K21,   K22, KC_NO, K24, K25, K26, K27   }, \
    { K30, K31,   K32, K33,   K34, K35, K36, K37   }, \
    { K40, KC_NO, K42, K43,   K44, K45, K46, K47   }, \
    { K50, K51,   K52, K53,   K54, K55, K56, K57   }, \
    { K60, K61,   K62, K63,   K64, K65, K66, K67   }, \
    { K70, K71,   K72, K73,   K74, K75, K76, K77   }, \
    { K80, K81,   K82, K83,   K84, K85, K86, KC_NO }  \
}


#define LAYOUT_kc( \
        K00, K10, K20, K30, K40, K50, K60, K70, K80, K01, K11, K21, K31, K41, K51, K61, \
        K71, K81, K02, K12, K22, K32, K42, K52, K62, K72, K82, K03, K13, K23,      K33, \
        K43, K53, K63, K73, K83, K04, K14, K24, K34, K44, K54, K64, K74, K84,      K05, \
        K15, K25, K35, K45, K55, K65, K75, K85, K06, K16, K26, K36, K46,      K56, K66, \
        K76, K86, K07,                K17,           K27, K37, K47,      K57, K67, K77  \
    )   \
    LAYOUT( \
        KC_##K00, KC_##K10, KC_##K20, KC_##K30, KC_##K40, KC_##K50, KC_##K60, KC_##K70, KC_##K80, KC_##K01, KC_##K11, KC_##K21, KC_##K31, KC_##K41, KC_##K51, KC_##K61, \
        KC_##K71, KC_##K81, KC_##K02, KC_##K12, KC_##K22, KC_##K32, KC_##K42, KC_##K52, KC_##K62, KC_##K72, KC_##K82, KC_##K03, KC_##K13, KC_##K23,           KC_##K33, \
        KC_##K43, KC_##K53, KC_##K63, KC_##K73, KC_##K83, KC_##K04, KC_##K14, KC_##K24, KC_##K34, KC_##K44, KC_##K54, KC_##K64, KC_##K74, KC_##K84,           KC_##K05, \
        KC_##K15, KC_##K25, KC_##K35, KC_##K45, KC_##K55, KC_##K65, KC_##K75, KC_##K85, KC_##K06, KC_##K16, KC_##K26, KC_##K36, KC_##K46,           KC_##K56, KC_##K66, \
        KC_##K76, KC_##K86, KC_##K07,                               KC_##K17,                     KC_##K27, KC_##K37, KC_##K47,           KC_##K57, KC_##K67, KC_##K77  \
    )

#endif
