/* Copyright 2020 Gautham Yerroju <gautham.yerroju@gmail.com>
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
 *4
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
#define LAYOUT( \
    L00, L01, L02, L03, L04, L05,           R06, R07, R08, R09, R10, R11, \
    L12, L13, L14, L15, L16, L17,           R18, R19, R20, R21, R22, R23, \
    L24, L25, L26, L27, L28, L29,           R30, R31, R32, R33, R34, R35, \
             L36, L37, L38, L39, L40,    R41, R42, R43, R44, R45 \
                        ) \
{ \
    { L05, L04, L03, L02, L01, L00 }, \
    { L17, L16, L15, L14, L13, L12 }, \
    { L29, L28, L27, L26, L25, L24 }, \
    { L40, L39, L38, L37, L36, KC_NO },\
    \
    { R06, R07, R08, R09, R10, R11 }, \
    { R18, R19, R20, R21, R22, R23 }, \
    { R30, R31, R32, R33, R34, R35 }, \
    { R41, R42, R43, R44, R45, KC_NO } \
}
