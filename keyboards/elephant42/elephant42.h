/* Copyright 2021 illness072
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
  L00, L01, L02, L03, L04, L05,    R00, R01, R02, R03, R04, R05, \
  L10, L11, L12, L13, L14, L15,    R10, R11, R12, R13, R14, R15, \
       L21, L22, L23, L24, L25,    R20, R21, R22, R23, R24,      \
            L30, L31, L32, L33,    R30, R31, R32, R33 \
) { \
    {   L00,   L01, L02, L03, L04, L05 }, \
    {   L10,   L11, L12, L13, L14, L15 }, \
    { KC_NO,   L21, L22, L23, L24, L25 }, \
    { KC_NO, KC_NO, L30, L31, L32, L33 }, \
    {   R05,   R04, R03, R02, R01, R00 }, \
    {   R15,   R14, R13, R12, R11, R10 }, \
    { KC_NO,   R24, R23, R22, R21, R20 }, \
    { KC_NO, KC_NO, R33, R32, R31, R30 } \
}
