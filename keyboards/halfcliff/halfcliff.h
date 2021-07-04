/* Copyright 2021 n2
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
    l00,l01,l02,l03,l04,l05,l06,r00,r01,r02,r03,r04,r05,r06,r07,\
    l07,l08,l09,l10,l11,l12,l13,r08,r09,r10,r11,r12,r13,r14,r15,\
    l14,l15,l16,l17,l18,l19,l20,r16,r17,r18,r19,r20,r21,r22,r23,\
    l21,l22,l23,l24,l25,l26,l27,r24,r25,r26,r27,r28,r29,r30,r31,\
    l28,l29,l30,l31,l32,l33,l34,r32,r33,r34,r35,r36,r37,r38,r39\
) \
{ \
   {l02,  l03,  l04,  l05,  l06  }, \
   {l09,  l10,  l11,  l12,  l13  }, \
   {l16,  l17,  l18,  l19,  l20  }, \
   {l23,  l24,  l25,  l26,  l27  }, \
   {l30,  l31,  l32,  l33,  l34  }, \
   {l01,  l00,  KC_NO,KC_NO,KC_NO}, \
   {l08,  l07,  KC_NO,KC_NO,KC_NO}, \
   {l15,  l14,  KC_NO,KC_NO,KC_NO}, \
   {l22,  l21,  KC_NO,KC_NO,KC_NO}, \
   {l29,  l28,  KC_NO,KC_NO,KC_NO}, \
   {r04,  r03,  r02,  r01,  r00  }, \
   {r12,  r11,  r10,  r09,  r08  }, \
   {r20,  r19,  r18,  r17,  r16  }, \
   {r28,  r27,  r26,  r25,  r24  }, \
   {r36,  r35,  r34,  r33,  r32  }, \
   {r05,  r06,  r07,  KC_NO,KC_NO}, \
   {r13,  r14,  r15,  KC_NO,KC_NO}, \
   {r21,  r22,  r23,  KC_NO,KC_NO}, \
   {r29,  r30,  r31,  KC_NO,KC_NO}, \
   {r37,  r38,  r39,  KC_NO,KC_NO}, \
}
