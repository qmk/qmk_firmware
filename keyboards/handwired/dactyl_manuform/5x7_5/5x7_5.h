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

#define LAYOUT( \
    L11, L12, L13, L14, L15, L16, L17,              R11, R12, R13, R14, R15, R16, R17, \
    L21, L22, L23, L24, L25, L26, L27,              R21, R22, R23, R24, R25, R26, R27, \
    L31, L32, L33, L34, L35, L36, L37,              R31, R32, R33, R34, R35, R36, R37, \
    L41, L42, L43, L44, L45, L46,                        R42, R43, R44, R45, R46, R47, \
    L51, L52, L53, L54,      L55, L65, L66,    R62, R63, R53,      R54, R55, R56, R57, \
                                  L63, L64,    R64, R65 \
) { \
    { L11, L12, L13, L14, L15, L16, L17 }, \
    { L21, L22, L23, L24, L25, L26, L27 }, \
    { L31, L32, L33, L34, L35, L36, L37 }, \
    { L41, L42, L43, L44, L45, L46, XXX }, \
    { L51, L52, L53, L54, L55, XXX, XXX }, \
    { XXX, XXX, L63, L64, L65, L66, XXX }, \
    { R11, R12, R13, R14, R15, R16, R17 }, \
    { R21, R22, R23, R24, R25, R26, R27 }, \
    { R31, R32, R33, R34, R35, R36, R37 }, \
    { XXX, R42, R43, R44, R45, R46, R47 }, \
    { XXX, XXX, R53, R54, R55, R56, R57 }, \
    { XXX, R62, R63, R64, R65, XXX, XXX } \
}
