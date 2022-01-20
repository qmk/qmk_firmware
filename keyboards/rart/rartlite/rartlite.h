/*
Copyright 2021 Alabahuy
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

#define LAYOUT_right_numpad( \
    K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K34, K05,  K15, K06, K16, \
    K20,   K30, K21, K31, K22, K32, K23, K33, K24, K54,    K25,  K35, K26, K36, \
    K40,     K50, K41, K51, K42, K52, K43, K53, K44, K74,  K45,  K55, K46, K56, \
    K60,   K70,     K61,     K62,      K63,    K73,   K64, K65, K75,  K66, K76  \
) \
{ \
    { K00,   K01,   K02,   K03,  K04,  K05,  K06 }, \
    { K10,   K11,   K12,   K13,  K14,  K15,  K16 }, \
    { K20,   K21,   K22,   K23,  K24,  K25,  K26 }, \
    { K30,   K31,   K32,   K33,  K34,  K35,  K36 }, \
    { K40,   K41,   K42,   K43,  K44,  K45,  K46 }, \
    { K50,   K51,   K52,   K53,  K54,  K55,  K56 }, \
    { K60,   K61,   K62,   K63,  K64,  K65,  K66 }, \
    { K70,   KC_NO, KC_NO, K73,  K74,  K75,  K76 }, \
}

#define LAYOUT_left_numpad( \
    K16, K06, K15,  K05, K34, K14, K04, K13, K03, K12, K02, K11, K01, K10, K00, \
    K36, K26, K35,  K25,   K54, K24, K33, K23, K32, K22, K31,  K21, K30,   K20, \
    K56, K46, K55,  K45,    K74, K44, K53, K43, K52, K42,  K51,  K41, K50, K40, \
    K76, K66,  K75, K65, K64,      K73,     K63,      K62,   K61,    K70,  K60  \
) \
{ \
    { K00,   K01,   K02,   K03,  K04,  K05,  K06 }, \
    { K10,   K11,   K12,   K13,  K14,  K15,  K16 }, \
    { K20,   K21,   K22,   K23,  K24,  K25,  K26 }, \
    { K30,   K31,   K32,   K33,  K34,  K35,  K36 }, \
    { K40,   K41,   K42,   K43,  K44,  K45,  K46 }, \
    { K50,   K51,   K52,   K53,  K54,  K55,  K56 }, \
    { K60,   K61,   K62,   K63,  K64,  K65,  K66 }, \
    { K70,   KC_NO, KC_NO, K73,  K74,  K75,  K76 }, \
}
