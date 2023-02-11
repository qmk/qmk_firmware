/* Copyright 2020 unrelenting.technology
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
    l00,      l01, l02, l03, l04, l05, r00, r01, r02, r03, r04, r05, r06, \
    l06, l07, l08, l09, l10, l11, l12, r07, r08, r09, r10, r11, r12, r13, \
    l13, l14, l15, l16, l17, l18, r14, r15, r16, r17, r18, r19, r20, r21, \
    l19, l20, l21, l22, l23, l24, r22, r23, r24, r25, r26, r27,      r28, \
    l25,      l26, l27, l28, l29, l30, r29, r30, r31, r32, r33, r34, r35, \
    l31, l32, l33, l34,      l35,      r36,      r37, r38, r39, r40, r41 \
) { \
    {   l00,   l06,   l13,   l19,   l25,   l31, KC_NO,   r00,   r07, r14, r22, r29, r21 },  \
    {   l01,   l07,   l14,   l20,   l26,   l32, KC_NO,   r01,   r08, r15, r23, r30, r36 },  \
    {   l02,   l08,   l15,   l21,   l27,   l33, KC_NO,   r02,   r09, r16, r24, r31, r37 },  \
    {   l03,   l09,   l16,   l22,   l28,   l34, KC_NO,   r03,   r10, r17, r25, r32, r38 },  \
    {   l04,   l10,   l17,   l23,   l29,   l35, KC_NO,   r04,   r11, r18, r27, r33, r39 },  \
    {   l05,   l11,   l18,   l24,   l30,   l12, KC_NO,   r05,   r12, r19, r26, r34, r40 },  \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   r06,   r13, r20, r28, r35, r41 },  \
}
