/* Copyright 2020 Alabahuy
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

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT_all( \
    K00, K40, K01, K41, K02, K42,   K03, K43, K04, K44, K05, K45, \
    K10, K50, K11, K51, K12, K52,   K13, K53, K14, K54, K15, K55, \
    K20, K60, K21, K61, K22, K62,   K23, K63, K24, K64, K25, K65, \
    K30, K70, K31, K71, K32, K72,   K33, K73, K34, K74, K35, K75, \
                   K80, K81,     K82,    K83, K84 \
) \
{ \
    { K00, K01, K02, K03, K04, K05   }, \
    { K10, K11, K12, K13, K14, K15   }, \
    { K20, K21, K22, K23, K24, K25   }, \
    { K30, K31, K32, K33, K34, K35   }, \
    { K40, K41, K42, K43, K44, K45   }, \
    { K50, K51, K52, K53, K54, K55   }, \
    { K60, K61, K62, K63, K64, K65   }, \
    { K70, K71, K72, K73, K74, K75   }, \
    { K80, K81, K82, K83, K84, KC_NO }, \
}
