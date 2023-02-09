/*
Base Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
Modified 2017 Andrew Novak <ndrw.nvk@gmail.com>
Modified 2018 Wayne Jones (WarmCatUK) <waynekjones@gmail.com>
 
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

#define LAYOUT( \
    K05, K25, K35, K45, K55, K06, KA6, KA7, K07, KB5, KC5, KD5, KE5, KD1, KE1, KE2, \
    K04, K14, K24, K34, K44, K54, K16, KB6, KB7, K17, KA4, KB4, KC4, KE4,      KD0, \
    K03, K13, K23, K33, K43, K53, K26, KC6, KC7, K27, KA3, KB3, KC3, KD3,      K67, \
    K02, K12, K22, K32, K42, K52, K36, KD6, KD7, K37, KA2, KB2, KD2,           KE0, \
    K01, K11, K21, K31, K41, K51, K46, KE6, KE7, K47, KA1, KB1,           K86, K77, \
    K00, K10, K20,           K56,                     K57, KB0, KC0, K96, K76, K66  \
){ \
    { K00, K10,   K20, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KB0, KC0,   KD0,   KC_NO }, \
    { K01, K11,   K21, K31,   K41,   K51,   KC_NO, KC_NO, KC_NO, KC_NO, KA1,   KB1, KC_NO, KD1,   KE1   }, \
    { K02, K12,   K22, K32,   K42,   K52,   KC_NO, KC_NO, KC_NO, KC_NO, KA2,   KB2, KC_NO, KD2,   KE2   }, \
    { K03, K13,   K23, K33,   K43,   K53,   KC_NO, KC_NO, KC_NO, KC_NO, KA3,   KB3, KC3,   KD3,   KC_NO }, \
    { K04, K14,   K24, K34,   K44,   K54,   KC_NO, KC_NO, KC_NO, KC_NO, KA4,   KB4, KC4,   KC_NO, KE4   }, \
    { K05, KC_NO, K25, K35,   K45,   K55,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KB5, KC5,   KD5,   KE5   }, \
    { K06, K16,   K26, K36,   K46,   K56,   K66,   K76,   K86,   K96,   KA6,   KB6, KC6,   KD6,   KE6   }, \
    { K07, K17,   K27, K37,   K47,   K57,   K67,   K77,   KE0,   KC_NO, KA7,   KB7, KC7,   KD7,   KE7   } \
}

#define LAYOUT_75_iso( \
    K50, K52, K53, K54, K55, K60, K6A, K7A, K70, K5B, K5C, K5D, K5E, K1D, K1E, K2E, \
    K40, K41, K42, K43, K44, K45, K61, K6B, K7B, K71, K4A, K4B, K4C,      K4E, K0D, \
    K30, K31, K32, K33, K34, K35, K62, K6C, K7C, K72, K3A, K3B, K3C,           K76, \
    K20, K21, K22, K23, K24, K25, K63, K6D, K7D, K73, K2A, K2B, K2C, K2D,      K0E, \
    K10, K03, K11, K12, K13, K14, K15, K64, K6E, K7E, K74, K1A, K1B,      K68, K77, \
    K00, K01, K02,                K65,                K75, K0B, K0C, K69, K67, K66  \
){ \
    { K00, K01,   K02, K03, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K0B, K0C,   K0D,   KC_NO }, \
    { K10, K11,   K12, K13, K14,   K15,   KC_NO, KC_NO, KC_NO, KC_NO, K1A,   K1B, KC_NO, K1D,   K1E   }, \
    { K20, K21,   K22, K23, K24,   K25,   KC_NO, KC_NO, KC_NO, KC_NO, K2A,   K2B, K2C,   K2D,   K2E   }, \
    { K30, K31,   K32, K33, K34,   K35,   KC_NO, KC_NO, KC_NO, KC_NO, K3A,   K3B, K3C,   KC_NO, KC_NO }, \
    { K40, K41,   K42, K43, K44,   K45,   KC_NO, KC_NO, KC_NO, KC_NO, K4A,   K4B, K4C,   KC_NO, K4E   }, \
    { K50, KC_NO, K52, K53, K54,   K55,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K5B, K5C,   K5D,   K5E   }, \
    { K60, K61,   K62, K63, K64,   K65,   K66,   K67,   K68,   K69,   K6A,   K6B, K6C,   K6D,   K6E   }, \
    { K70, K71,   K72, K73, K74,   K75,   K76,   K77,   K0E,   KC_NO, K7A,   K7B, K7C,   K7D,   K7E   } \
}

#define LAYOUT_75_iso_rwkl( \
    K50, K52, K53, K54, K55, K60, K6A, K7A, K70, K5B, K5C, K5D, K5E, K1D, K1E, K2E, \
    K40, K41, K42, K43, K44, K45, K61, K6B, K7B, K71, K4A, K4B, K4C,      K4E, K0D, \
    K30, K31, K32, K33, K34, K35, K62, K6C, K7C, K72, K3A, K3B, K3C,           K76, \
    K20, K21, K22, K23, K24, K25, K63, K6D, K7D, K73, K2A, K2B, K2C, K2D,      K0E, \
    K10, K03, K11, K12, K13, K14, K15, K64, K6E, K7E, K74, K1A, K1B,      K68, K77, \
    K00, K01, K02,                K65,                K75,   K0C,    K69, K67, K66  \
){ \
    { K00, K01,   K02, K03, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K0C,   K0D,   KC_NO }, \
    { K10, K11,   K12, K13, K14,   K15,   KC_NO, KC_NO, KC_NO, KC_NO, K1A,   K1B,   KC_NO, K1D,   K1E   }, \
    { K20, K21,   K22, K23, K24,   K25,   KC_NO, KC_NO, KC_NO, KC_NO, K2A,   K2B,   K2C,   K2D,   K2E   }, \
    { K30, K31,   K32, K33, K34,   K35,   KC_NO, KC_NO, KC_NO, KC_NO, K3A,   K3B,   K3C,   KC_NO, KC_NO }, \
    { K40, K41,   K42, K43, K44,   K45,   KC_NO, KC_NO, KC_NO, KC_NO, K4A,   K4B,   K4C,   KC_NO, K4E   }, \
    { K50, KC_NO, K52, K53, K54,   K55,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K5B,   K5C,   K5D,   K5E   }, \
    { K60, K61,   K62, K63, K64,   K65,   K66,   K67,   K68,   K69,   K6A,   K6B,   K6C,   K6D,   K6E   }, \
    { K70, K71,   K72, K73, K74,   K75,   K76,   K77,   K0E,   KC_NO, K7A,   K7B,   K7C,   K7D,   K7E   } \
}
