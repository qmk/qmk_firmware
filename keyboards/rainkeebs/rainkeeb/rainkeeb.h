/* Copyright 2020 Regan Palmer
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
    K00, K10, K01, K11, K02,      K13, K03, K14, K04, K15, \
    K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, \
    K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, \
    K60, K70, K61, K72,      K62,      K73, K64, K74, K65  \
) { \
    { K00,   K01,   K02,   K03,   K04,   KC_NO }, \
    { K10,   K11,   KC_NO, K13,   K14,   K15 }, \
    { K20,   K21,   K22,   K23,   K24,   K25 }, \
    { K30,   K31,   K32,   K33,   K34,   KC_NO }, \
    { K40,   K41,   K42,   K43,   K44,   K45 }, \
    { K50,   K51,   K52,   K53,   K54,   KC_NO }, \
    { K60,   K61,   K62,   KC_NO, K64,   K65 }, \
    { K70,   KC_NO, K72,   K73,   K74,   KC_NO }  \
}
