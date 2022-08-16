/* Copyright 2020 Kyrre Havik Eriksen
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

#define LAYOUT( \
    L00, L01, L02, L03, L04, L05,              R06, R07, R08, R09, R10, R11, \
    L12, L13, L14, L15, L16, L17,              R18, R19, R20, R21, R22, R23, \
    L24, L25, L26, L27, L28, L29,              R30, R31, R32, R33, R34, R35, \
              L36, L37, L38, L39, L40,    R41, R42, R43, R44, R45,	     \
                   L46, L47, L48, L49,    R50, R51, R52, R53		     \
) \
{ \
    { XXX, L05, L04, L03, L02, L01, L00 }, \
    { XXX, L17, L16, L15, L14, L13, L12 }, \
    { XXX, L29, L28, L27, L26, L25, L24 }, \
    { L40, L39, L38, L37, L36, XXX, XXX }, \
    { L49, L48, L47, L46, XXX, XXX, XXX }, \
    { XXX, R06, R07, R08, R09, R10, R11 }, \
    { XXX, R18, R19, R20, R21, R22, R23 }, \
    { XXX, R30, R31, R32, R33, R34, R35 }, \
    { R41, R42, R43, R44, R45, XXX, XXX }, \
    { R50, R51, R52, R53, XXX, XXX, XXX }  \
}
