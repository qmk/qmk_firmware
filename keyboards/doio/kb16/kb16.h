/* Copyright 2022 DOIO
 * Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
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

/*                    06 ◯ 05 16 ◯ 15
 * ┌───┬───┬───┬───┐   ┌───┐    ┌───┐
 * │00 │01 │02 │03 │   │04 │    │14 │
 * ├───┼───┼───┼───┤   └───┘    └───┘
 * │10 │11 │12 │13 │
 * ├───┼───┼───┼───┤      26 ◯ 25
 * │20 │21 │22 │23 │       ┌───┐
 * ├───┼───┼───┼───┤       │24 │
 * │30 │31 │32 │33 │       └───┘
 * └───┴───┴───┴───┘
 */

#define LAYOUT( \
    K00, K01, K02, K03, K06, K04, K05, \
    K10, K11, K12, K13, K16, K14, K15, \
    K20, K21, K22, K23, K26, K24, K25, \
    K30, K31, K32, K33                 \
) { \
    { K00, K01, K02, K03, K04, K05, K06 }, \
    { K10, K11, K12, K13, K14, K15, K16 }, \
    { K20, K21, K22, K23, K24, K25, K26 }, \
    { K30, K31, K32, K33, XXX, XXX, XXX }  \
}

