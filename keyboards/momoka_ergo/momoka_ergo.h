/* Copyright 2021 StefanGrindelwald
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

#define XXX KC_NO

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    L05, L04, L03, L02, L01, L00,                       R70, R71, R72, R73, R74, R75, \
    L15, L14, L13, L12, L11, L10,                       R80, R81, R82, R83, R84, R85, \
    L25, L24, L23, L22, L21, L20,                       R90, R91, R92, R93, R94, R95, \
    L35, L34, L33, L32, L31, L30,                       RA0, RA1, RA2, RA3, RA4, RA5, \
    L45, L44, L43, L42, L41,                                 RB1, RB2, RB3, RB4, RB5, \
                                  L51, L40,   RB0, RC1,                               \
                                       L50,   RC0,                                    \
                             L52, L61, L60,   RD0, RD1, RC2                           \
    ) \
    { \
        { L00, L01, L02, L03, L04, L05 }, \
        { L10, L11, L12, L13, L14, L15 }, \
        { L20, L21, L22, L23, L24, L25 }, \
        { L30, L31, L32, L33, L34, L35 }, \
        { L40, L41, L42, L43, L44, L45 }, \
        { L50, L51, L52, XXX, XXX, XXX }, \
        { L60, L61, XXX, XXX, XXX, XXX }, \
        { R70, R71, R72, R73, R74, R75 }, \
        { R80, R81, R82, R83, R84, R85 }, \
        { R90, R91, R92, R93, R94, R95 }, \
        { RA0, RA1, RA2, RA3, RA4, RA5 }, \
        { RB0, RB1, RB2, RB3, RB4, RB5 }, \
        { RC0, RC1, RC2, XXX, XXX, XXX }, \
        { RD0, RD1, XXX, XXX, XXX, XXX }  \
    }
