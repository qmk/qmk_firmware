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

#define LAYOUT_kc( \
    A1, A2, A3, A4, A5, A6,     E1, E2, E3, E4, E5, E6,  \
    B1, B2, B3, B4, B5, B6, D1, F1, F2, F3, F4, F5, F6,  \
    C1, C2, C3, C4, C5, C6,     G1, G2, G3, G4, G5, G6,  \
                D4, D5, D6,     H1, H2, H3,\
                    H5, H6,     H4, D2, D3\
  ) \
  LAYOUT( \
    KC_##A1, KC_##A2, KC_##A3, KC_##A4, KC_##A5, KC_##A6,          KC_##E1, KC_##E2, KC_##E3, KC_##E4, KC_##E5, KC_##E6, \
    KC_##B1, KC_##B2, KC_##B3, KC_##B4, KC_##B5, KC_##B6, KC_##D1, KC_##F1, KC_##F2, KC_##F3, KC_##F4, KC_##F5, KC_##F6, \
    KC_##C1, KC_##C2, KC_##C3, KC_##C4, KC_##C5, KC_##C6,          KC_##G1, KC_##G2, KC_##G3, KC_##G4, KC_##G5, KC_##G6, \
                               KC_##D4, KC_##D5, KC_##D6,          KC_##H1, KC_##H2, KC_##H3, \
                                        KC_##D2, KC_##D3,          KC_##H4, KC_##H5, KC_##H6 \
  )
