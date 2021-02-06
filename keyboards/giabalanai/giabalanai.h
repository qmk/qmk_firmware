/* Copyright 2020 3araht
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
    l00, l01, l02, l03, l04, l05, l06, l07, l08, l09, l0a, l0b, \
      l10, l11, l12, l13, l14, l15, l16, l17, l18, l19, l1a, l1b, \
        l20, l21, l22, l23, l24, l25, l26, l27, l28, l29, l2a, l2b, \
          l30, l31, l32, l33, l34, l35, l36, l37, l38, l39, l3a, l3b, \
            l40, l41, l42, l43, l44, l45, l46, l47, l48, l49, l4a, l4b, \
    \
    r20, \
      r00, r01, r02, r03, r04, r05, r06, r07, r08, r09, r0a, r0b,   renc, \
    r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r1a, r1b, r1c,  \
      r21, r22, r23, r24, r25, r26, r27, r28, r29, r2a, r2b, r2c   \
) { \
    { l00,   l10,  l20, l30, l40, l0b, l1b, l2b,   l3b,   l4b }, \
    { l01,   l11,  l21, l31, l41, l0a, l1a, l2a,   l3a,   l4a }, \
    { l02,   l12,  l22, l32, l42, l09, l19, l29,   l39,   l49 }, \
    { l03,   l13,  l23, l33, l43, l08, l18, l28,   l38,   l48 }, \
    { l04,   l14,  l24, l34, l44, l07, l17, l27,   l37,   l47 }, \
    { l05,   l15,  l25, l35, l45, l06, l16, l26,   l36,   l46 }, \
    \
    { r00,   r01,  r02, r03, r04, r05, r06, KC_NO, KC_NO, KC_NO }, \
    { r10,   r11,  r12, r13, r14, r15, r16, KC_NO, KC_NO, KC_NO }, \
    { r20,   r21,  r22, r23, r24, r25, r26, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, renc, r0b, r0a, r09, r08, r07, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, r1c,  r1b, r1a, r19, r18, r17, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, r2c,  r2b, r2a, r29, r28, r27, KC_NO, KC_NO, KC_NO }  \
}

#define LAYOUT_giabaRInaix2( \
    l00, l01, l02, l03, l04, l05, l06, l07, l08, l09, l0a, l0b, \
      l10, l11, l12, l13, l14, l15, l16, l17, l18, l19, l1a, l1b, \
        l20, l21, l22, l23, l24, l25, l26, l27, l28, l29, l2a, l2b, \
          l30, l31, l32, l33, l34, l35, l36, l37, l38, l39, l3a, l3b, \
            l40, l41, l42, l43, l44, l45, l46, l47, l48, l49, l4a, l4b, \
    \
    r00, r01, r02, r03, r04, r05, r06, r07, r08, r09, r0a, r0b, \
      r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r1a, r1b, \
        r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r2a, r2b, \
          r30, r31, r32, r33, r34, r35, r36, r37, r38, r39, r3a, r3b, \
            r40, r41, r42, r43, r44, r45, r46, r47, r48, r49, r4a, r4b  \
) { \
    { l00, l10, l20, l30, l40, l0b, l1b, l2b, l3b, l4b }, \
    { l01, l11, l21, l31, l41, l0a, l1a, l2a, l3a, l4a }, \
    { l02, l12, l22, l32, l42, l09, l19, l29, l39, l49 }, \
    { l03, l13, l23, l33, l43, l08, l18, l28, l38, l48 }, \
    { l04, l14, l24, l34, l44, l07, l17, l27, l37, l47 }, \
    { l05, l15, l25, l35, l45, l06, l16, l26, l36, l46 }, \
    \
    { r4b, r3b, r2b, r1b, r0b, r40, r30, r20, r10, r00 }, \
    { r4a, r3a, r2a, r1a, r0a, r41, r31, r21, r11, r01 }, \
    { r49, r39, r29, r19, r09, r42, r32, r22, r12, r02 }, \
    { r48, r38, r28, r18, r08, r43, r33, r23, r13, r03 }, \
    { r47, r37, r27, r17, r07, r44, r34, r24, r14, r04 }, \
    { r46, r36, r26, r16, r06, r45, r35, r25, r15, r05 }  \
}
