/* Copyright 2020 blindassassin111
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
#define ___ KC_NO

#define LAYOUT_all( \
    L00, L01, L02, L03,   L04, L05, L06, L07, L08, L09, L0A,        R01, R02,   R03, R04, R05, R06,   R07, R08, R09, \
    L10, L11, L12, L13,   L14, L15, L16, L17, L18, L19, L0B,    R10, R11, R12, R13, R14, R15, R16, R17,    R18, R19, \
    L20, L21, L22, L23,   L24, L25, L26, L27, L28, L29,       R20, R21, R22, R23, R24, R25, R26, R27,      R28, R29, \
    L30, L31, L32, L33,   L34, L35, L36, L37, L38, L39,     R30, R31, R32, R33, R34, R35, R36, R37,        R38, R39, \
    L40, L41, L42, L43,   L44, L45, L46, L47, L48, L49, L4A,      R41, R42, R43, R44, R45, R46, R47,       R48,      \
    L50, L51, L52, L53,    L54, L55, L56, L57, L58,                 R52, R53, R54, R55, R56,          R57, R49, R59  \
) { \
    { L00, L01, L02, L03, L04, L05, L06, L07, L08, L09, L0A }, \
    { L10, L11, L12, L13, L14, L15, L16, L17, L18, L19, L0B }, \
    { L20, L21, L22, L23, L24, L25, L26, L27, L28, L29, ___ }, \
    { L30, L31, L32, L33, L34, L35, L36, L37, L38, L39, ___ }, \
    { L40, L41, L42, L43, L44, L45, L46, L47, L48, L49, L4A }, \
    { L50, L51, L52, L53, L54, L55, L56, L57, L58, ___, ___ }, \
    { ___, R01, R02, R03, R04, R05, R06, R07, R08, R09, ___ }, \
    { R10, R11, R12, R13, R14, R15, R16, R17, R18, R19, ___ }, \
    { R20, R21, R22, R23, R24, R25, R26, R27, R28, R29, ___ }, \
    { R30, R31, R32, R33, R34, R35, R36, R37, R38, R39, ___ }, \
    { ___, R41, R42, R43, R44, R45, R46, R47, R48, ___, ___ }, \
    { ___, ___, R52, R53, R54, R55, R56, R57, R49, R59, ___ }  \
}
