/* Copyright 2021 Christoph Rehmann (crehmann)
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

#include "buzzard.h"

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
         L00, L01, L02, L03, L04,                          R05, R06, R07, R08, R09,      \
    L10, L11, L12, L13, L14, L15,                          R16, R17, R18, R19, R20, R21, \
    L22, L23, L24, L25, L26, L27,                          R28, R29, R30, R31, R32, R33, \
                             L34, L35, L36,      R37, R38, R39 \
) \
{ \
    { L04,   L03,   L02,   L01,   L00,   KC_NO }, \
    { L15,   L14,   L13,   L12,   L11,   L10   }, \
    { L27,   L26,   L25,   L24,   L23,   L22   }, \
    { L36,   L35,   L34,   KC_NO, KC_NO, KC_NO }, \
    { R05,   R06,   R07,   R08,   R19,   KC_NO }, \
    { R16,   R17,   R18,   R19,   R20,   R21   }, \
    { R28,   R29,   R30,   R31,   R32,   R33   }, \
    { R37,   R38,   R39,   KC_NO, KC_NO, KC_NO }, \
}

#define LAYOUT_stack(                               \
         L00, L01, L02, L03, L04,                   \
    L10, L11, L12, L13, L14, L15,                   \
    L22, L23, L24, L25, L26, L27,                   \
                   L34, L35, L36,                   \
                                                    \
                  R05, R06, R07, R08, R09,          \
                  R16, R17, R18, R19, R20, R21,     \
                  R28, R29, R30, R31, R32, R33,     \
                  R37, R38, R39                     \
)                                                   \
{                                                   \
    { L04,   L03,   L02,   L01,   L00,   KC_NO }, \
    { L15,   L14,   L13,   L12,   L11,   L10   }, \
    { L27,   L26,   L25,   L24,   L23,   L22   }, \
    { L36,   L35,   L34,   KC_NO, KC_NO, KC_NO }, \
    { R05,   R06,   R07,   R08,   R09,   KC_NO }, \
    { R16,   R17,   R18,   R19,   R20,   R21   }, \
    { R28,   R29,   R30,   R31,   R32,   R33   }, \
    { R37,   R38,   R39,   KC_NO, KC_NO, KC_NO }, \
}

#define LAYOUT_split_3x6_3 LAYOUT
