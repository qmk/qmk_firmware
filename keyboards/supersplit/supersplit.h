/* Copyright 2022 tarneo (tarneo@tarneo.fr)
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

#define LAYOUT_split_6x4_9( \
        L00, L01, L02, L03, L04, L05, \
        L10, L11, L12, L13, L14, L15, \
        L20, L21, L22, L23, L24, L25, \
        L30, L31, L32, L33, L34, L35, \
                       LO3, LO4, LO5, \
        LT0, LT1, LT2, LT3, LT4, LT5, \
        R05, R04, R03, R02, R01, R00, \
        R15, R14, R13, R12, R11, R10, \
        R25, R24, R23, R22, R21, R20, \
        R35, R34, R33, R32, R31, R30, \
        RO5, RO4, RO3, \
        RT5, RT4, RT3, RT2, RT1, RT0 \
    ) \
    { \
        { L00, L01, L02, L03, L04, L05}, \
        { L10, L11, L12, L13, L14, L15}, \
        { L20, L21, L22, L23, L24, L25}, \
        { L30, L31, L32, L33, L34, L35}, \
        { KC_NO, KC_NO, KC_NO, LO3, LO4, LO5}, \
        { LT0, LT1, LT2, LT3, LT4, LT5}, \
        \
        { R00, R01, R02, R03, R04, R05}, \
        { R10, R11, R12, R13, R14, R15}, \
        { R20, R21, R22, R23, R24, R25}, \
        { R30, R31, R32, R33, R34, R35}, \
        { KC_NO, KC_NO, KC_NO, RO3, RO4, RO5}, \
        { RT0, RT1, RT2, RT3, RT4, RT5} \
    }


