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
    l51,l50,l00,l01,l02,l03,l04,r04,r03,r02,r01,r00,r50,r51,r52,\
    l61,l60,l10,l11,l12,l13,l14,r14,r13,r12,r11,r10,r60,r61,r62,\
    l71,l70,l20,l21,l22,l23,l24,r24,r23,r22,r21,r20,r70,r71,r72,\
    l81,l80,l30,l31,l32,l33,l34,r34,r33,r32,r31,r30,r80,r81,r82,\
    l91,l90,l40,l41,l42,l43,l44,r44,r43,r42,r41,r40,r90,r91,r92\
) \
{ \
    {l00,  l01,  l02,  l03,  l04  }, \
    {l10,  l11,  l12,  l13,  l14  }, \
    {l20,  l21,  l22,  l23,  l24  }, \
    {l30,  l31,  l32,  l33,  l34  }, \
    {l40,  l41,  l42,  l43,  l44  }, \
    {l50,  l51,  KC_NO,KC_NO,KC_NO}, \
    {l60,  l61,  KC_NO,KC_NO,KC_NO}, \
    {l70,  l71,  KC_NO,KC_NO,KC_NO}, \
    {l80,  l81,  KC_NO,KC_NO,KC_NO}, \
    {l90,  l91,  KC_NO,KC_NO,KC_NO}, \
    {r00,  r01,  r02,  r03,  r04  }, \
    {r10,  r11,  r12,  r13,  r14  }, \
    {r20,  r21,  r22,  r23,  r24  }, \
    {r30,  r31,  r32,  r33,  r34  }, \
    {r40,  r41,  r42,  r43,  r44  }, \
    {r50,  r51,  r52,  KC_NO,KC_NO}, \
    {r60,  r61,  r62,  KC_NO,KC_NO}, \
    {r70,  r71,  r72,  KC_NO,KC_NO}, \
    {r80,  r81,  r82,  KC_NO,KC_NO}, \
    {r90,  r91,  r92,  KC_NO,KC_NO}, \
}
