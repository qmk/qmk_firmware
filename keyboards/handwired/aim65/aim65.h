/* Copyright 2021 Matteo Bonora
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

#define LAYOUT( \
         K62, K71, K61, K74, K64, K75, K65, K76, K66, K77, K67, K72, K53,   \
    K52,   K42, K51, K41, K54, K44, K55, K45, K56, K46, K57, K47, K22, K40, \
       K60, K31, K21, K34, K24, K35, K25, K36, K26, K37, K27, K33, K12, K23,\
       K70,    K01, K11, K04, K14, K05, K15, K06, K16, K07, K17, K20,       \
                                    K00                                     \
) { \
    { K00,   K01,   KC_NO, KC_NO, K04,   K05,   K06,   K07   }, \
    { KC_NO, K11,   K12,   KC_NO, K14,   K15,   K16,   K17   }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27   }, \
    { KC_NO, K31,   KC_NO, K33,   K34,   K35,   K36,   K37   }, \
    { K40,   K41,   K42,   KC_NO, K44,   K45,   K46,   K47   }, \
    { KC_NO, K51,   K52,   K53,   K54,   K55,   K56,   K57   }, \
    { K60,   K61,   K62,   KC_NO, K64,   K65,   K66,   K67   }, \
    { K70,   K71,   K72,   KC_NO, K74,   K75,   K76,   K77   }, \
}
