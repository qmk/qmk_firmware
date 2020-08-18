/* Copyright 2020 mtei
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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
     l00, l01, l02, l03, l04, l05, l06,            r01, r02, r03, r04, r05, r06, r07, \
      l10, l11, l12, l13, l14, l15, l16,          r11, r12, r13, r14, r15, r16, r17, \
     l20, l21, l22, l23, l24, l25, l26,            r21, r22, r23, r24, r25, r26, r27, \
    l30, l31, l32, l33, l34, l35, l36, l37,    r30, r31, r32, r33, r34, r35, r36, r37, \
    l40,      l42, l43, l44, l45,      l47,    r40,      r42, r43, r44, r45,      r47  \
) { \
    { l00, l01, l02, l03, l04, l05, l06, KC_NO,   KC_NO, r01, r02, r03, r04, r05, r06,   r07 }, \
    { l10, l11, l12, l13, l14, l15, l16, KC_NO,   KC_NO, r11, r12, r13, r14, r15, r16,   r17 }, \
    { l20, l21, l22, l23, l24, l25, l26, KC_NO,   KC_NO, r21, r22, r23, r24, r25, r26,   r27 }, \
    { l30, l31, l32, l33, l34, l35, l36, l37,     r30,   r31, r32, r33, r34, r35, r36,   r37 }, \
    { l40, KC_NO, l42, l43, l44, l45, KC_NO, l47, r40, KC_NO, r42, r43, r44, r45, KC_NO, r47 }  \
}
