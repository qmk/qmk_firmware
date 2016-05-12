/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

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
#ifndef ACTIONMAP_COMMON_H
#define ACTIONMAP_COMMON_H


/* Alps64 keymap definition macro */
#define ACTIONMAP( \
    K36, K37, K46, K47, K56, K57, K66, K67, K76, K77, K06, K07, K17, K26, K27, \
    K34, K35, K44, K45, K54, K55, K64, K65, K75, K05, K15, K16, K25, K24, \
    K32, K33, K43, K52, K53, K63, K73, K74, K03, K04, K13, K14, K23, \
    K31, K41, K42, K51, K61, K62, K71, K72, K01, K02, K11, K12, K21, K22, \
    K30, K40, K50,           K60,                     K70, K00, K10, K20  \
) { \
    { AC_##K00, AC_##K01, AC_##K02, AC_##K03, AC_##K04, AC_##K05, AC_##K06, AC_##K07 }, \
    { AC_##K10, AC_##K11, AC_##K12, AC_##K13, AC_##K14, AC_##K15, AC_##K16, AC_##K17 }, \
    { AC_##K20, AC_##K21, AC_##K22, AC_##K23, AC_##K24, AC_##K25, AC_##K26, AC_##K27 }, \
    { AC_##K30, AC_##K31, AC_##K32, AC_##K33, AC_##K34, AC_##K35, AC_##K36, AC_##K37 }, \
    { AC_##K40, AC_##K41, AC_##K42, AC_##K43, AC_##K44, AC_##K45, AC_##K46, AC_##K47 }, \
    { AC_##K50, AC_##K51, AC_##K52, AC_##K53, AC_##K54, AC_##K55, AC_##K56, AC_##K57 }, \
    { AC_##K60, AC_##K61, AC_##K62, AC_##K63, AC_##K64, AC_##K65, AC_##K66, AC_##K67 }, \
    { AC_##K70, AC_##K71, AC_##K72, AC_##K73, AC_##K74, AC_##K75, AC_##K76, AC_##K77 } \
}

/* AEK US */
#define ACTIONMAP_AEK( \
    K36, K37, K46, K47, K56, K57, K66, K67, K76, K77, K06, K07, K17, K27, \
    K34, K35, K44, K45, K54, K55, K64, K65, K75, K05, K15, K16, K25, K24, \
    K32, K33, K43, K52, K53, K63, K73, K74, K03, K04, K13, K14, K23, \
    K31, K42, K51, K61, K62, K71, K72, K01, K02, K11, K12, K21, \
    K30, K40, K50,           K60,                          K00, K10, K20  \
) ACTIONMAP( \
    K36, K37, K46, K47, K56, K57, K66, K67, K76, K77, K06, K07, K17, NUHS,K27, \
    K34, K35, K44, K45, K54, K55, K64, K65, K75, K05, K15, K16, K25, K24, \
    K32, K33, K43, K52, K53, K63, K73, K74, K03, K04, K13, K14, K23, \
    K31, NUBS,K42, K51, K61, K62, K71, K72, K01, K02, K11, K12, K21, ESC, \
    K30, K40, K50,           K60,                     APP, K00, K10, K20  \
)

#endif
