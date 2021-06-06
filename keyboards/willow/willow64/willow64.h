/* Copyright 2021 Hanachi
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
    L01, L02, L03, L04, L05, L06,              R01, R02, R03, R04, R05, R06, R28, R07, R35, \
    L07, L08, L09, L10, L11, L12,              R08, R09, R10, R11, R12, R13, R34, R14, \
    L13, L14, L15, L16, L17, L18,              R15, R16, R17, R18, R19, R20, R21,  \
    L19, L20, L21, L22, L23, L24, L25,    R22, R23, R24, R25, R26, R27,        R29, \
                   L26, L27, L28, L29,    R30, R31, R32, R33                      \
    ) \
    { \
        { L01, L02, L03, L04, L05, L06, XXX, XXX  }, \
        { L07, L08, L09, L10, L11, L12, XXX, XXX  }, \
        { L13, L14, L15, L16, L17, L18, XXX, XXX  }, \
        { L19, L20, L21, L22, L23, L24, L25, XXX  }, \
        { XXX, XXX, XXX, L26, L27, L28, L29, XXX  }, \
        { XXX, R01, R02, R03, R04, R05, R06 ,R07  }, \
        { XXX, R08, R09, R10, R11, R12, R13, R14  }, \
        { XXX, R15, R16 ,R17, R18, R19, R20, R21  }, \
        { R22, R23, R24, R25, R26 ,R27, R28, R29  }, \
        { R30, R31, R32, R33, XXX, XXX, R34, R35 }  \
    }

/* LED POSITION
    03, 04, 11, 12, 21, 22,            35, 36, 45, 46, 53, 54, 60, 61, 63, \
    02, 05, 10, 13, 20, 23,            34, 37, 44, 47, 52, 55, 59,   62,   \
    01, 06, 09, 14, 19, 24,            33, 38, 43, 48, 51, 56,       58,   \
    00, 07, 08, 15, 18, 25, 28,    29, 32, 39, 42, 49, 50,           57,   \
                16, 17, 26, 27,    30, 31, 40, 41                          \
*/
