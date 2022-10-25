/* Copyright 2021 AndyChiu
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
L01,L41,L02,L03,L04,L05,L06,           R01, R02, R03, R04, R05, R06, R07, R08, R09,\
L07,L08,L09,L10,L11,L12,L13,           R10, R11, R12, R13, R14, R15, R16, R17, R18,\
L14,L15,L16,L17,L18,L19,L20,           R19, R20, R21, R22, R23, R24, R25, R26, R27,\
L21,L22,L23,L24,L25,L26,L27,           R28, R29, R30, R31, R32, R33, R34,      R35,\
L28,L29,L30,L31,L32,L33,L34,           R36, R37, R38, R39, R40, R41,           R42,\
L35,        L36,L37,L38,L39,L40,  R43, R44, R45, R46, R47\
) {  \
       { L01,L41,L02,L03,L04,L05,L06,KC_NO},  \
       { L07,L08,L09,L10,L11,L12,L13,KC_NO},  \
       { L14,L15,L16,L17,L18,L19,L20,KC_NO},  \
       { L21,L22,L23,L24,L25,L26,L27,KC_NO},  \
       { L28,L29,L30,L31,L32,L33,L34,KC_NO},  \
       { L35,KC_NO,L36,L37,L38,L39,L40,KC_NO}, \
       { R01,R02,R03,R04,R05,R06,R07,R08}, \
       { R10,R11,R12,R13,R14,R15,R16,R17},\
       { R19,R20,R21,R22,R23,R24,R25,R26},\
       { R28,R29,R30,R31,R32,R33,R34,R27},\
       { R36,R37,R38,R39,R40,R41,R35,R18},\
       { R43,R44,R45,R46,R47,R42,KC_NO,R09}  \
}
