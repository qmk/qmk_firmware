/* Copyright 2020 Fidel Coria
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

#define LAYOUT_split_3x5_4( \
    K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, \
    K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, \
    K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, \
          K402, K403, K404, K405, K406, K407, K408, K409  \
) { \
    { K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110 }, \
    { K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210 }, \
    { K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310 }, \
    { KC_NO, K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  KC_NO }  \
}
