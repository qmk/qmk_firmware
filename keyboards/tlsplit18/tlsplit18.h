/* Copyright 2020 satromi
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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

/*          L03, L07, L11, L15, L19, L23, L27, L31,               R03, R07, R11, R15, R19, R23, R27, R03,      \
    L01, L04, L08, L12, L16, L20, L24, L28, L32, L35,     R01, R04, R08, R12, R16, R20, R24, R28, R32, R01, \
    L02, L05, L09, L13, L17, L21, L25, L29, L33, L36,     R02, R05, R09, R13, R17, R21, R25, R29, R33, R02, \
         L06, L10, L14, L18, L22, L26, L30, L34,               R06, R10, R14, R18, R22, R26, R30, R34       \

         L03, L07, L11, L15, L19, L23, L27, L31,      \
    L01, L04, L08, L12, L16, L20, L24, L28, L32, L35, \
    L02, L05, L09, L13, L17, L21, L25, L29, L33, L36, \
         L06, L10, L14, L18, L22, L26, L30, L34       \

    { ___, L03, L07, L11, L15, L19, L23, L27, L31, ___ }, \
    { L01, L04, L08, L12, L16, L20, L24, L28, L32, L35 }, \
    { L02, L05, L09, L13, L17, L21, L25, L29, L33, L36 }, \
    { ___, L06, L10, L14, L18, L22, L26, L30, L34, ___ }, \
    { ___, R03, R07, R11, R15, R19, R23, R27, R31, ___ }, \
    { R01, R04, R08, R12, R16, R20, R24, R28, R32, R35 }, \
    { R02, R05, R09, R13, R17, R21, R25, R29, R33, R36 }, \
    { ___, R06, R10, R14, R18, R22, R26, R30, R34, ___ }  \

 */
#define LAYOUT( \
         L03, L07, L11, L15, L19, L23, L27, L31,               R31, R27, R23, R19, R15, R11, R07, R03,      \
    L01, L04, L08, L12, L16, L20, L24, L28, L32, L35,     R35, R32, R28, R24, R20, R16, R12, R08, R04, R01, \
    L02, L05, L09, L13, L17, L21, L25, L29, L33, L36,     R36, R33, R29, R25, R21, R17, R13, R09, R05, R02, \
         L06, L10, L14, L18, L22, L26, L30, L34,               R34, R30, R26, R22, R18, R14, R10, R06       \
) {                                                       \
    { ___, L01, L02, ___ }, \
    { L03, L04, L05, L06 }, \
    { L07, L08, L09, L10 }, \
    { L11, L12, L13, L14 }, \
    { L15, L16, L17, L18 }, \
    { L19, L20, L21, L22 }, \
    { L23, L24, L25, L26 }, \
    { L27, L28, L29, L30 }, \
    { L31, L32, L33, L34 }, \
    { ___, L35, L36, ___ }, \
    { ___, R01, R02, ___ }, \
    { R03, R04, R05, R06 }, \
    { R07, R08, R09, R10 }, \
    { R11, R12, R13, R14 }, \
    { R15, R16, R17, R18 }, \
    { R19, R20, R21, R22 }, \
    { R23, R24, R25, R26 }, \
    { R27, R28, R29, R30 }, \
    { R31, R32, R33, R34 }, \
    { ___, R35, R36, ___ } \
}

