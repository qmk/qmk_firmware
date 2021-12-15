/* Copyright 2021 Paul James
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

#define LAYOUT_ortho_7u( \
    l11, l12, l13, l14, l15, m11, m12, m13, m14, m15, r11, r12, r13, r14, r15, \
    l21, l22, l23, l24, l25, m21, m22, m23, m24, m25, r21, r22, r23, r24, r25, \
    l31, l32, l33, l34, l35, m31, m32, m33, m34, m35, r31, r32, r33, r34, r35, \
    l41, l42, l43, l44, l45, m41, m42, m43, m44, m45, r41, r42, r43, r44, r45, \
    l51, l52, l53, l54,                m53,                r52, r53, r54, r51  \
) \
{ \
    { r11, r12, r13, r14, r15, r25, r35, r45 }, \
    { r21, r22, r23, r24, r34, r44, r53, r54 }, \
    { r31, r32, r33, r43, r42, r41, r51, r52 }, \
    { l11, l12, l13, l14, l15, l25, l35, l45 }, \
    { l21, l22, l23, l24, l34, l44, l53, l54 }, \
    { l31, l32, l33, l43, l42, l41, l51, l52 }, \
    { m11, m12, m13, m14, m15, m25, m35, m45 }, \
    { m21, m22, m23, m24, m34, m44, m53, KC_NO }, \
    { m31, m32, m33, m43, m42, m41, KC_NO, KC_NO } \
}
