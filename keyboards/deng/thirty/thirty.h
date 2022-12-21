/* Copyright 2022 Leo Deng (@myst729)
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

#define LAYOUT_ortho_3x10( \
    K00, K01, K02, K03, K04, K34, K33, K32, K31, K30, \
    K10, K11, K12, K13, K14, K44, K43, K42, K41, K40, \
    K20, K21, K22, K23, K24, K54, K53, K52, K51, K50  \
) { \
    { K00, K01, K02, K03, K04 }, \
    { K10, K11, K12, K13, K14 }, \
    { K20, K21, K22, K23, K24 }, \
    { K30, K31, K32, K33, K34 }, \
    { K40, K41, K42, K43, K44 }, \
    { K50, K51, K52, K53, K54 }  \
}
