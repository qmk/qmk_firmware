/*
Copyright 2017 Input Club

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
#ifndef K_TYPE_H
#define K_TYPE_H

#include "quantum.h"

#define KEYMAP( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K10, K11, K12, K13, K14, K15, K16, \
    K17, K18, K19, K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K30, K31, K32, K33, \
    K34, K35, K36, K37, K38, K39, K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K50, \
    K51, K52, K53, K54, K55, K56, K57, K58, K59, K60, K61, K62, K63, \
    K64, K65, K66, K67, K68, K69, K70, K71, K72, K73, K74, K75, K76, \
    K77, K78, K79, K80, K81, K82, K83, K84, K85, K86, K87 \
) { \
    {   K01,   K11,   K21,   K30,   K39,   K48,   K58,   K65, KC_NO,   K83, }, \
    {   K02,   K12,   K22, KC_NO,   K40,   K49,   K59,   K66,   K75,   K84, }, \
    {   K03,   K13,   K23,   K31,   K41,   K50,   K60,   K67, KC_NO,   K85, }, \
    {   K04,   K14,   K24,   K32,   K42,   K51,   K61,   K68,   K76,   K86, }, \
    {   K05,   K15,   K25,   K33,   K43,   K52,   K62,   K69,   K77,   K87, }, \
    {   K06,   K16,   K26,   K34,   K44,   K53, KC_NO,   K70,   K78, KC_NO, }, \
    {   K07,   K17,   K27,   K35,   K45,   K54,   K63,   K71,   K79, KC_NO, }, \
    {   K08,   K18,   K28,   K36,   K46,   K55, KC_NO,   K72,   K80, KC_NO, }, \
    {   K09,   K19,   K29,   K37,   K47,   K56,   K64,   K73,   K81, KC_NO, }, \
    {   K10,   K20, KC_NO,   K38, KC_NO,   K57, KC_NO,   K74,   K82, KC_NO, }, \
}

#endif
