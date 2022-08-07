/* Copyright 2022 QMK / James Young (@noroadsleft)
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

/*
 * ┌───┬───┬───┬───┐
 * │00 │01 │02 │03 │
 * └───┴───┴───┴───┘
 * ┌───┬───┬───┬───┐
 * │10 │11 │12 │13 │
 * ├───┼───┼───┼───┤   ┌───┐
 * │20 │21 │22 │23 │   │   │
 * ├───┼───┼───┼───┤   │?? │ 2u Plus
 * │30 │31 │32 │33 │   │   │
 * ├───┼───┼───┼───┤   ├───┤
 * │40 │41 │42 │43 │   │   │
 * ├───┼───┼───┼───┤   │?? │ 2u Enter
 * │50 │51 │52 │53 │   │   │
 * └───┴───┴───┴───┘   └───┘
 * ┌───────┐
 * │??     │ 2u 0
 * └───────┘
 */


#define LAYOUT_ortho_6x4( \
    K00, K01, K02, K03, \
    K10, K11, K12, K13, \
    K20, K21, K22, K23, \
    K30, K31, K32, K33, \
    K40, K41, K42, K43, \
    K50, K51, K52, K53  \
) { \
    { K00, K01, K02, K03 }, \
    { K10, K11, K12, K13 }, \
    { K20, K21, K22, K23 }, \
    { K30, K31, K32, K33 }, \
    { K40, K41, K42, K43 }, \
    { K50, K51, K52, K53 }, \
}
