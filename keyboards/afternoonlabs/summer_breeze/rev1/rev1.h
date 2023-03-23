/* Copyright 2021 Afternoon Labs
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
    LW00, LW01, LW02, L00, L01, L02, L03, L04, L05,           R00, R01, R02, R03, R04, R05, MC0, MC1, MC2, \
    LW10, LW11, LW12, L10, L11, L12, L13, L14, L15,           R10, R11, R12, R13, R14, R15, MC3, MC4, MC5, \
          LW21,       L20, L21, L22, L23, L24, L25,           R20, R21, R22, R23, R24, R25,      AUP,      \
    LW30, LW31, LW32, L30, L31, L32, L33, L34, L35,           R30, R31, R32, R33, R34, R35, ALT, ADN, ART, \
                                LT0, LT1, LT2, LT3, RT0, RT1, RT2, RT3  \
) \
{ \
    { L05, L04, L03, L02, L01, L00, LW02, LW01, LW00 }, \
    { L15, L14, L13, L12, L11, L10, LW12, LW11, LW10 }, \
    { L25, L24, L23, L22, L21, L20, KC_NO, LW21, KC_NO }, \
    { L35, L34, L33, L32, L31, L30, LW32, LW31, LW30 }, \
    { LT3, LT2, LT1, LT0, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { R00, R01, R02, R03, R04, R05, MC0, MC1, MC2 }, \
    { R10, R11, R12, R13, R14, R15, MC3, MC4, MC5 }, \
    { R20, R21, R22, R23, R24, R25, KC_NO, AUP, KC_NO }, \
    { R30, R31, R32, R33, R34, R35, ALT, ADN, ART }, \
    { RT0, RT1, RT2, RT3, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
}
