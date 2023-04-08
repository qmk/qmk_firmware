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
    L00, L01, L02, L03, L04, L05,                    R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,                    R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25,                    R20, R21, R22, R23, R24, R25, \
              L32, L33,                                        R32, R33, \
                        L34, L35,                    R30, R31, \
                        L44, L45,                    R40, R41, \
              L42, L43,                                        R42, R43 \
) { \
    { L00, L01, L02, L03, L04, L05 }, \
    { L10, L11, L12, L13, L14, L15 }, \
    { L20, L21, L22, L23, L24, L25 }, \
    { XXX, XXX, L32, L33, L34, L35 }, \
    { XXX, XXX, L42, L43, L44, L45 }, \
\
    { R00, R01, R02, R03, R04, R05 }, \
    { R10, R11, R12, R13, R14, R15 }, \
    { R20, R21, R22, R23, R24, R25 }, \
    { R30, R31, R32, R33, XXX, XXX }, \
    { R40, R41, R42, R43, XXX, XXX } \
}

#define LAYOUT_split_3x5_3( \
    L00, L01, L02, L03, L04,                                  R00, R01, R02, R03, R04, \
    L10, L11, L12, L13, L14,                                  R10, R11, R12, R13, R14, \
    L20, L21, L22, L23, L24,                                  R20, R21, R22, R23, R24, \
                        L33, L34,                        R30, R31, \
                                  L43,              R41, \
) { \
    { XXX, L00, L01, L02, L03, L04 }, \
    { XXX, L10, L11, L12, L13, L14 }, \
    { XXX, L20, L21, L22, L23, L24,}, \
    { XXX, XXX, XXX, XXX, L33, L34 }, \
    { XXX, XXX, XXX, XXX, L43, XXX }, \
\
    { R00, R01, R02, R03, R04, XXX }, \
    { R10, R11, R12, R13, R14, XXX }, \
    { R20, R21, R22, R23, R24, XXX }, \
    { R30, R31, XXX, XXX, XXX, XXX }, \
    { XXX, R41, XXX, XXX, XXX, XXX } \
}