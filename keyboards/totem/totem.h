/* Copyright 2022
 * GEIST @geigeigeist
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

//#pragma once
#include "quantum.h"

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

// readability
#define ___ KC_NO

//      |SW01|SW02|SW03|SW04|SW05|  |SW05|SW04|SW03|SW02|SW01|
//      |SW06|SW07|SW08|SW09|SW10|  |SW10|SW09|SW08|SW07|SW06| 
// |SW16|SW11|SW12|SW13|SW14|SW15|  |SW15|SW14|SW13|SW12|SW11|SW16|
//                |SW17|SW18|SW19|  |SW19|SW18|SW17|

#define LAYOUT( \
         L00, L01, L02, L03, L04,    R00, R01, R02, R03, R04,     \
         L10, L11, L12, L13, L14,    R10, R11, R12, R13, R14,     \
    L30, L20, L21, L22, L23, L24,    R20, R21, R22, R23, R24, R34,\
                   L32, L33, L34,    R30, R31, R32                \
    )                                        \
    {                                        \
        { L00,   L01,   L02,   L03,   L04 }, \
        { L10,   L11,   L12,   L13,   L14 }, \
        { L20,   L21,   L22,   L23,   L24 }, \
        { L30,   ___,   L32,   L33,   L34 }, \
        { R04,   R03,   R02,   R01,   R00 }, \
        { R14,   R13,   R12,   R11,   R10 }, \
        { R24,   R23,   R22,   R21,   R20 }, \
        { R34,   ___,   R32,   R31,   R30 }, \
    }


