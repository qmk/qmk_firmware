/* Copyright 2020 rate
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
 * ,------------------------
 * |                   K07 |
 * |------------------------
 * | K00 | K01 | K02 | K03 |
 * |------------------------
 * | K04 | K05 | K06 |     |
 * |------------------ K11 -
 * | K08 | K09 | K10 |     |
 * |------------------------
 * | K12 | K13 | K14 |     |
 * |------------------ K17 -
 * |    K15    | K16 |     |
 * |------------------------
 */
#define LAYOUT( \
                   K07, \
    K00, K01, K02, K03, \
    K04, K05, K06,      \
    K08, K09, K10, K11, \
    K12, K13, K14,      \
    K15,      K16, K17 ) { \
    { K00,   K01,   K02,   K03 }, \
    { K04,   K05,   K06,   K07 }, \
    { K08,   K09,   K10,   K11 }, \
    { K12,   K13,   K14,   KC_NO }, \
    { K15,   KC_NO, K16,   K17 }, \
}
