/* Copyright 2021 csandven
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

#define LAYOUT( \
    L00, L01, L02, L03, L04, L05, L06, L07,                     R00, R01, R02, R03, R04, R05, R06, R07,  \
    L10, L11, L12, L13, L14, L15, L16, L17,                     R10, R11, R12, R13, R14, R15, R16, R17,  \
    L20, L21, L22, L23, L24, L25, L26, L27,                     R20, R21, R22, R23, R24, R25, R26, R27,  \
    L30, L31, L32, L33, L34, L35, L36, L37, L44,           R40, R30, R31, R32, R33, R34, R35, R36, R37,  \
                          L40, L41, L42, L43,                 R41, R42, R43, R44                         \
    ) \
    { \
        { L07, L06, L05, L04, L03, L02, L01, L00 }, \
        { L17, L16, L15, L14, L13, L12, L11, L10 }, \
        { L27, L26, L25, L24, L23, L22, L21, L20 }, \
        { L37, L36, L35, L34, L33, L32, L31, L30 }, \
        { L43, L42, L41, L40, L44, KC_NO, KC_NO, KC_NO }, \
        { R00, R01, R02, R03, R04, R05, R06, R07 }, \
        { R10, R11, R12, R13, R14, R15, R16, R17 }, \
        { R20, R21, R22, R23, R24, R25, R26, R27 }, \
        { R30, R31, R32, R33, R34, R35, R36, R37 }, \
        { R41, R42, R43, R44, R40, KC_NO, KC_NO }  \
    }

#define LAYOUT_6_8( \
    L02, L03, L04, L05, L06, L07,                     R00, R01, R02, R03, R04, R05, R06, R07,  \
    L12, L13, L14, L15, L16, L17,                     R10, R11, R12, R13, R14, R15, R16, R17,  \
    L22, L23, L24, L25, L26, L27,                     R20, R21, R22, R23, R24, R25, R26, R27,  \
    L32, L33, L34, L35, L36, L37, L44,           R40, R30, R31, R32, R33, R34, R35, R36, R37,  \
                L40, L41, L42, L43,                 R41, R42, R43, R44                         \
    ) \
    { \
        { L07, L06, L05, L04, L03, L02, KC_NO, KC_NO }, \
        { L17, L16, L15, L14, L13, L12, KC_NO, KC_NO }, \
        { L27, L26, L25, L24, L23, L22, KC_NO, KC_NO }, \
        { L37, L36, L35, L34, L33, L32, KC_NO, KC_NO }, \
        { L43, L42, L41, L40, L44, KC_NO, KC_NO, KC_NO }, \
        { R00, R01, R02, R03, R04, R05, R06, R07 }, \
        { R10, R11, R12, R13, R14, R15, R16, R17 }, \
        { R20, R21, R22, R23, R24, R25, R26, R27 }, \
        { R30, R31, R32, R33, R34, R35, R36, R37 }, \
        { R41, R42, R43, R44, R40, KC_NO, KC_NO }  \
    }

#define LAYOUT_8_6( \
    L00, L01, L02, L03, L04, L05, L06, L07,                     R00, R01, R02, R03, R04, R05,  \
    L10, L11, L12, L13, L14, L15, L16, L17,                     R10, R11, R12, R13, R14, R15,  \
    L20, L21, L22, L23, L24, L25, L26, L27,                     R20, R21, R22, R23, R24, R25,  \
    L30, L31, L32, L33, L34, L35, L36, L37, L44,           R40, R30, R31, R32, R33, R34, R35,  \
                          L40, L41, L42, L43,                 R41, R42, R43, R44               \
    ) \
    { \
        { L07, L06, L05, L04, L03, L02, L01, L00 }, \
        { L17, L16, L15, L14, L13, L12, L11, L10 }, \
        { L27, L26, L25, L24, L23, L22, L21, L20 }, \
        { L37, L36, L35, L34, L33, L32, L31, L30 }, \
        { L43, L42, L41, L40, L44, KC_NO, KC_NO, KC_NO }, \
        { R00, R01, R02, R03, R04, R05, KC_NO, KC_NO }, \
        { R10, R11, R12, R13, R14, R15, KC_NO, KC_NO }, \
        { R20, R21, R22, R23, R24, R25, KC_NO, KC_NO }, \
        { R30, R31, R32, R33, R34, R35, KC_NO, KC_NO }, \
        { R41, R42, R43, R44, R40, KC_NO, KC_NO }  \
    }

#define LAYOUT_6_6( \
    L02, L03, L04, L05, L06, L07,                     R00, R01, R02, R03, R04, R05,  \
    L12, L13, L14, L15, L16, L17,                     R10, R11, R12, R13, R14, R15,  \
    L22, L23, L24, L25, L26, L27,                     R20, R21, R22, R23, R24, R25,  \
    L32, L33, L34, L35, L36, L37, L44,           R40, R30, R31, R32, R33, R34, R35,  \
                L40, L41, L42, L43,                 R41, R42, R43, R44               \
    ) \
    { \
        { L07, L06, L05, L04, L03, L02, KC_NO, KC_NO }, \
        { L17, L16, L15, L14, L13, L12, KC_NO, KC_NO }, \
        { L27, L26, L25, L24, L23, L22, KC_NO, KC_NO }, \
        { L37, L36, L35, L34, L33, L32, KC_NO, KC_NO }, \
        { L43, L42, L41, L40, L44, KC_NO, KC_NO, KC_NO }, \
        { R00, R01, R02, R03, R04, R05, KC_NO, KC_NO }, \
        { R10, R11, R12, R13, R14, R15, KC_NO, KC_NO }, \
        { R20, R21, R22, R23, R24, R25, KC_NO, KC_NO }, \
        { R30, R31, R32, R33, R34, R35, KC_NO, KC_NO }, \
        { R41, R42, R43, R44, R40, KC_NO, KC_NO }  \
    }
