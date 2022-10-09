/*
Copyright 2020 Tybera
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

#define LAYOUT_tkl_ansi( \
    K00,      K02, K03, K04, K05,   K06, K07, K08, K68,    K67, K65, K64, K63,  K66, K62, K61,  \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K78, K70, K77, K75, K73,       K76, K72, K71,  \
    K20,   K21, K22, K23, K24, K25, K26, K27, K28, K88, K87, K85, K84, K83,     K86, K82, K81,  \
    K30,    K31, K32, K33, K34, K35, K36, K37, K38, K98, K97, K95, K93,                         \
    K40,       K42, K43, K44, K45, K46, K47, K48, KA8, KA7, KA5, KA4,                K92,       \
    K50,  K51,  K52,              K56,                K58,  K57,  K54,  K53,    KA6, KA2, KA1   \
) { \
    { K00,   KC_NO, K02,   K03,   K04,   K05,   K06,   K07,   K08   }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18   }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28   }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,   K38   }, \
    { K40,   KC_NO, K42,   K43,   K44,   K45,   K46,   K47,   K48   }, \
    { K50,   K51,   K52,   K53,   K54,   KC_NO, K56,   K57,   K58   }, \
    { KC_NO, K61,   K62,   K63,   K64,   K65,   K66,   K67,   K68   }, \
    { K70,   K71,   K72,   K73,   KC_NO, K75,   K76,   K77,   K78   }, \
    { KC_NO, K81,   K82,   K83,   K84,   K85,   K86,   K87,   K88   }, \
    { KC_NO, KC_NO, K92,   K93,   KC_NO, K95,   KC_NO, K97,   K98   }, \
    { KC_NO, KA1,   KA2,   KC_NO, KA4,   KA5,   KA6,   KA7,   KA8   }, \
}


