/* Copyright 2022 Jens Peter Secher <jpsecher@gmail.com>
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

/*
 *             ┌───┐                                  ┌───┐
 *         ┌───┤02 ├───┐                          ┌───┤07 ├───┐
 *     ┌───┤01 ├───┤03 ├───┐                  ┌───┤06 ├───┤08 ├───┐
 * ┌───┤00 ├───┤12 ├───┤33 │                  │36 ├───┤17 ├───┤09 ├───┐
 * │30 ├───┤11 ├───┤13 ├───┤                  ├───┤16 ├───┤18 ├───┤39 │
 * ├───┤10 ├───┤22 ├───┤43 │                  │46 ├───┤27 ├───┤19 ├───┤
 * │40 ├───┤21 ├───┤23 ├───┘                  └───┤26 ├───┤28 ├───┤49 │
 * └───┤20 ├───┘   └───┘                          └───┘   └───┤29 ├───┘
 *     └───┘ ┌───┐ ┌───┬───┐                  ┌───┬───┐ ┌───┐ └───┘
 *           │04 │ │14 │24 ├───┐          ┌───┤25 │15 │ │05 │
 *           └───┘ └───┤   │34 ├───┐  ┌───┤35 │   ├───┘ └───┘ ┌───┐
 *                     └───┤   │44 │  │45 │   ├───┘           │38+│
 *                         └───┤   │  │   ├───┘               └───┘
 *                             └───┘  └───┘
 * + K38 is hidden.
 */
#define LAYOUT( \
  K30, K00, K01, K02, K03, K33,           K36, K06, K07, K08, K09, K39, \
  K40, K10, K11, K12, K13, K43,           K46, K16, K17, K18, K19, K49, \
       K20, K21, K22, K23,                     K26, K27, K28, K29, \
       K04, K14, K24, K34, K44,           K45, K35, K25, K15, K05, K38 \
) { \
    { K00, K01,   K02,   K03, K04, K05, K06, K07,   K08,   K09 }, \
    { K10, K11,   K12,   K13, K14, K15, K16, K17,   K18,   K19 }, \
    { K20, K21,   K22,   K23, K24, K25, K26, K27,   K28,   K29 }, \
    { K30, KC_NO, KC_NO, K33, K34, K35, K36, KC_NO, K38,   K39 }, \
    { K40, KC_NO, KC_NO, K43, K44, K45, K46, KC_NO, KC_NO, K49 }, \
}
