/* Copyright 2021 floookay
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation,   either version 2 of the License, or
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

#define XXX KC_NO

/*
 *           ┌───┬───┬───┬───┬───┐                                   ┌───┬───┬───┬───┬───┐
 * ┌─────┬───┤L02│L03│L04│L05│L06│                                   │R00│R01│R02│R03│R04├───┬─────┐
 * │L00  │L01├───┼───┼───┼───┼───┤       ┌───┐           ┌───┐       ├───┼───┼───┼───┼───┤R05│R06  │
 * ├─────┼───┤L12│L13│L14│L15│L16│       │L16│           │R10│       │R10│R11│R12│R13│R14├───┼─────┤
 * │L10  │L11├───┼───┼───┼───┼───┤       │   │           │   │       ├───┼───┼───┼───┼───┤R15│R16  │
 * ├─────┼───┤L22│L23│L24│L25│L26│       ├───┤           ├───┤       │R20│R21│R22│R23│R24├───┼─────┤
 * │L20  │L21├───┼───┼───┼───┼───┼───┐   │L36├───┐   ┌───┤R30│   ┌───┼───┼───┼───┼───┼───┤R25│R26  │
 * ├─────┼───┤L32│L33│L34│L35│L36│L41│   │   │   │   │   │   │   │R45│R30│R31│R32│R33│R34├───┼─────┤
 * │L30  │L31├───┼───┼───┼┬──┴──┬┴──┬┘   └──┬┘  ┌┘   └┐  └┬──┘   └┬──┴┬──┴──┬┼───┼───┼───┤R35│R36  │
 * └─────┴───┤L42│L43│L44││L45  │L46│       │L46│     │R40│       │R40│R41  ││R42│R43│R44├───┴─────┘
 *           └───┴───┴───┘└─────┴───┘       └───┘     └───┘       └───┴─────┘└───┴───┴───┘
 */

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT_all( \
    l00, l01, l02, l03, l04, l05, l06,               r00, r01, r02, r03, r04, r05, r06, \
    l10, l11, l12, l13, l14, l15, l16,               r10, r11, r12, r13, r14, r15, r16, \
    l20, l21, l22, l23, l24, l25, l26,               r20, r21, r22, r23, r24, r25, r26, \
    l30, l31, l32, l33, l34, l35, l36, l41,     r45, r30, r31, r32, r33, r34, r35, r36, \
              l42, l43, l44,   l45,   l46,       r40,   r41,   r42, r43, r44            \
){ \
    { l00, l01, l02, l03, l04, l05, l06 }, \
    { l10, l11, l12, l13, l14, l15, l16 }, \
    { l20, l21, l22, l23, l24, l25, l26 }, \
    { l30, l31, l32, l33, l34, l35, l36 }, \
    { XXX, l41, l42, l43, l44, l45, l46 }, \
    { r06, r05, r04, r03, r02, r01, r00 }, \
    { r16, r15, r14, r13, r12, r11, r10 }, \
    { r26, r25, r24, r23, r22, r21, r20 }, \
    { r36, r35, r34, r33, r32, r31, r30 }, \
    { XXX, r45, r44, r43, r42, r41, r40 }  \
}

#define LAYOUT_ergo( \
    l00, l01, l02, l03, l04, l05, l06,               r00, r01, r02, r03, r04, r05, r06, \
    l10, l11, l12, l13, l14, l15, l16,               r10, r11, r12, r13, r14, r15, r16, \
    l20, l21, l22, l23, l24, l25,                         r21, r22, r23, r24, r25, r26, \
    l30, l31, l32, l33, l34, l35, l36, l41,     r45, r30, r31, r32, r33, r34, r35, r36, \
              l42, l43, l44,   l45,   l46,       r40,   r41,   r42, r43, r44            \
){ \
    { l00, l01, l02, l03, l04, l05, l06 }, \
    { l10, l11, l12, l13, l14, l15, l16 }, \
    { l20, l21, l22, l23, l24, l25, XXX }, \
    { l30, l31, l32, l33, l34, l35, l36 }, \
    { XXX, l41, l42, l43, l44, l45, l46 }, \
    { r06, r05, r04, r03, r02, r01, r00 }, \
    { r16, r15, r14, r13, r12, r11, r10 }, \
    { r26, r25, r24, r23, r22, r21, XXX }, \
    { r36, r35, r34, r33, r32, r31, r30 }, \
    { XXX, r45, r44, r43, r42, r41, r40 }  \
}
