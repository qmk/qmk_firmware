/* Copyright 2020 yfuku
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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */


#define LAYOUT( \
    A1, A2, A3, A4, A5, A6,     E1, E2, E3, E4, E5, E6,  \
    B1, B2, B3, B4, B5, B6, D1, F1, F2, F3, F4, F5, F6,  \
    C1, C2, C3, C4, C5, C6,     G1, G2, G3, G4, G5, G6,  \
                D4, D5, D6,     H1, H2, H3,\
                    H5, H6,     H4, D2, D3\
) { \
    { A1, A2, A3, A4, A5, A6 }, \
    { B1, B2, B3, B4, B5, B6 }, \
    { C1, C2, C3, C4, C5, C6 }, \
    { D1, D2, D3, D4, D5, D6 }, \
    { E1, E2, E3, E4, E5, E6 }, \
    { F1, F2, F3, F4, F5, F6 }, \
    { G1, G2, G3, G4, G5, G6 }, \
    { H1, H2, H3, H4, H5, H6}, \
}
