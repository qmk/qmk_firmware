/* Copyright 2019 ENDO Katsuhiro <ka2hiro@kagizaraya.jp>
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

// clang-format off
#define LAYOUT( \
    L01, L02, L03, L04, L05, L06, R01, R02, R03, R04, R05, R06, \
    L07, L08, L09, L10, L11, L12, R07, R08, R09, R10, R11, R12, \
    L13, L14, L15, L16, L17, L18, R13, R14, R15, R16, R17, R18, \
    L19, L20, L21, L22, L23, L24, R19, R20, R21, R22, R23, R24  \
) { \
    { L01, L02, L03, L04, L05, L06 }, \
    { L07, L08, L09, L10, L11, L12 }, \
    { L13, L14, L15, L16, L17, L18 }, \
    { L19, L20, L21, L22, L23, L24 }, \
    { R01, R02, R03, R04, R05, R06 }, \
    { R07, R08, R09, R10, R11, R12 }, \
    { R13, R14, R15, R16, R17, R18 }, \
    { R19, R20, R21, R22, R23, R24 }  \
}

#define LAYOUT_extended( \
    L01, L02, L03, L04, L05, L06, M01, M02, M03, M04, M05, M06, R01, R02, R03, R04, R05, R06, \
    L07, L08, L09, L10, L11, L12, M07, M08, M09, M10, M11, M12, R07, R08, R09, R10, R11, R12, \
    L13, L14, L15, L16, L17, L18, M13, M14, M15, M16, M17, M18, R13, R14, R15, R16, R17, R18, \
    L19, L20, L21, L22, L23, L24, M19, M20, M21, M22, M23, M24, R19, R20, R21, R22, R23, R24  \
) { \
    { L01, L02, L03, L04, L05, L06 }, \
    { L07, L08, L09, L10, L11, L12 }, \
    { L13, L14, L15, L16, L17, L18 }, \
    { L19, L20, L21, L22, L23, L24 }, \
    { M01, M02, M03, M04, M05, M06 }, \
    { M07, M08, M09, M10, M11, M12 }, \
    { M13, M14, M15, M16, M17, M18 }, \
    { M19, M20, M21, M22, M23, M24 }, \
    { R01, R02, R03, R04, R05, R06 }, \
    { R07, R08, R09, R10, R11, R12 }, \
    { R13, R14, R15, R16, R17, R18 }, \
    { R19, R20, R21, R22, R23, R24 }  \
}
// clang-format on
