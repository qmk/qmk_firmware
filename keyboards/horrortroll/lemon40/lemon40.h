/* Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
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

#define XXX KC_NO

/* ┌─────┬───┬───┬───┬───┬───┐      ┌───┬───┬───┬───┬───┬───┬────┐
 * │00   │01 │02 │03 │04 │05 │      │06 │40 │41 │42 │43 │44 │45  │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┐     └┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴────┤
 * │10    │11 │12 │13 │14 │15 │      │16 │50 │51 │52 │53 │55     │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐  ┌─┴─┬─┴─┬─┴─┬─┴─┬┬┴──┬┴──┬────┤
 * │20      │21 │22 │23 │24 │25 │  │26 │60 │61 │62 ││63 │64 │65  │
 * └┬────┬──┴─┬─┼───┴┬──┴───┴───┤  ├───┴───┴┬──┴─┬─┘├───┼───┼───┬┘
 *  │30  │31  │ │32  │34        │  │70      │72  │  │73 │74 │75 │
 *  └────┴────┘ └────┴──────────┘  └────────┴────┘  └───┴───┴───┘
 */

#define LAYOUT( \
    K00, K01, K02, K03, K04, K05,      K06, K40, K41, K42, K43, K44, K45, \
    K10, K11, K12, K13, K14, K15,      K16, K50, K51, K52, K53,      K55, \
    K20, K21, K22, K23, K24, K25,      K26, K60, K61, K62, K63, K64, K65, \
    K30, K31, K32,      K34,                K70,      K72, K73, K74, K75  \
) { \
    { K00, K01, K02, K03, K04, K05, K06 }, \
    { K10, K11, K12, K13, K14, K15, K16 }, \
    { K20, K21, K22, K23, K24, K25, K26 }, \
    { K30, K31, K32, XXX, K34, XXX, XXX }, \
    { K40, K41, K42, K43, K44, K45, XXX }, \
    { K50, K51, K52, K53, XXX, K55, XXX }, \
    { K60, K61, K62, K63, K64, K65, XXX }, \
    { K70, XXX, K72, K73, K74, K75, XXX }  \
}

