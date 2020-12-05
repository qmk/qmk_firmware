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
#pragma once

#include "quantum.h"

#ifdef INFINITY_PROTOTYPE

/* Infinity prototype */
#define LAYOUT_60_ansi_split_bs_rshift( \
    K00, K10, K20, K30, K40, K50, K60, K70, K80, K01, K11, K21, K31, K41, K86, \
    K51, K61, K71, K81, K02, K12, K22, K32, K42, K52, K62, K72, K82, K03, \
    K13, K23, K33, K43, K53, K63, K73, K83, K04, K14, K24, K34, K44, \
    K54, K64, K74, K84, K05, K15, K25, K35, K45, K55, K65, K75, K85, \
    K06, K16, K26,           K36,                K46, K56, K66, K76 \
) { \
    { K00, K01, K02, K03, K04, K05, K06 }, \
    { K10, K11, K12, K13, K14, K15, K16 }, \
    { K20, K21, K22, K23, K24, K25, K26 }, \
    { K30, K31, K32, K33, K34, K35, K36 }, \
    { K40, K41, K42, K43, K44, K45, K46 }, \
    { K50, K51, K52, K53, K54, K55, K56 }, \
    { K60, K61, K62, K63, K64, K65, K66 }, \
    { K70, K71, K72, K73, K74, K75, K76 }, \
    { K80, K81, K82, K83, K84, K85, K86 }  \
}

#else

/* Infinity production */
#define LAYOUT_60_ansi_split_bs_rshift( \
    K00, K10, K20, K30, K40, K50, K60, K70, K80, K01, K11, K21, K31, K41, K51, \
    K61, K71, K81, K02, K12, K22, K32, K42, K52, K62, K72, K82, K03, K13, \
    K23, K33, K43, K53, K63, K73, K83, K04, K14, K24, K34, K44, K54, \
    K64, K74, K84, K05, K15, K25, K35, K45, K55, K65, K75, K85, K06, \
    K16, K26, K36,           K46,                K56, K66, K76, K86 \
) { \
    { K00, K01, K02, K03, K04, K05, K06 }, \
    { K10, K11, K12, K13, K14, K15, K16 }, \
    { K20, K21, K22, K23, K24, K25, K26 }, \
    { K30, K31, K32, K33, K34, K35, K36 }, \
    { K40, K41, K42, K43, K44, K45, K46 }, \
    { K50, K51, K52, K53, K54, K55, K56 }, \
    { K60, K61, K62, K63, K64, K65, K66 }, \
    { K70, K71, K72, K73, K74, K75, K76 }, \
    { K80, K81, K82, K83, K84, K85, K86 }  \
}

#endif

