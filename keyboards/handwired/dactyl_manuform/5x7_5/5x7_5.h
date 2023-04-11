/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT_5x7_5( \
    L10, L11, L12, L13, L14, L15, L16,              R10, R11, R12, R13, R14, R15, R16, \
    L20, L21, L22, L23, L24, L25, L26,              R20, R21, R22, R23, R24, R25, R26, \
    L30, L31, L32, L33, L34, L35, L36,              R30, R31, R32, R33, R34, R35, R36, \
    L40, L41, L42, L43, L44, L45,                        R41, R42, R43, R44, R45, R46, \
    L50, L51, L52, L53,      L54, L64, L65,    R61, R62, R52,      R53, R54, R55, R56, \
                                  L62, L63,    R63, R64 \
) { \
    { L10, L11, L12, L13, L14, L15, L16 }, \
    { L20, L21, L22, L23, L24, L25, L26 }, \
    { L30, L31, L32, L33, L34, L35, L36 }, \
    { L40, L41, L42, L43, L44, L45, XXX }, \
    { L50, L51, L52, L53, L54, XXX, XXX }, \
    { XXX, XXX, L62, L63, L64, L65, XXX }, \
    { R10, R11, R12, R13, R14, R15, R16 }, \
    { R20, R21, R22, R23, R24, R25, R26 }, \
    { R30, R31, R32, R33, R34, R35, R36 }, \
    { XXX, R41, R42, R43, R44, R45, R46 }, \
    { XXX, XXX, R52, R53, R54, R55, R56 }, \
    { XXX, R61, R62, R63, R64, XXX, XXX } \
}
