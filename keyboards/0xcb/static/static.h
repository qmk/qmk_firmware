/*
Copyright 2021 0xCB - Conor Burns

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

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

// clang-format off
 #define LAYOUT( \
                                                            K15, \
     K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K05, K35, \
     K20, K30, K21, K31, K22, K32, K23, K33, K24, K34,      K25, \
     K40,      K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, \
     K60, K70, K61, K71,      K72,           K64, K74, K65, K75  \
 ) \
 { \
     { K00,   K01,   K02,   K03,   K04,   K05 }, \
     { K10,   K11,   K12,   K13,   K14,   K15 }, \
     { K20,   K21,   K22,   K23,   K24,   K25 }, \
     { K30,   K31,   K32,   K33,   K34,   K35 }, \
     { K40,   K41,   K42,   K43,   K44,   K45 }, \
     { KC_NO, K51,   K52,   K53,   K54,   K55 }, \
     { K60,   K61,   KC_NO, KC_NO, K64,   K65 }, \
     { K70,   K71,   K72,   KC_NO, K74,   K75 }, \
 }
// clang-format on
