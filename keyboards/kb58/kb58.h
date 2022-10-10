/* Copyright 2021 beanaccle
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
    L00, L01, L02, L03, L04, L05,    R00, R01, R02, R03, R04, R05, R06, \
    L06, L07, L08, L09, L10, L11,    R07, R08, R09, R10, R11, R12, R13, \
    L12, L13, L14, L15, L16, L17,    R14, R15, R16, R17, R18, R19, R20, \
    L18, L19, L20, L21, L22, L23,    R21, R22, R23, R24, R25, R26, R27, \
                   L24, L25, L26,    R28, R29, R30 \
) { \
    {   L00,   L01,   L02,   L03,   L04,   L05 }, \
    {   L06,   L07,   L08,   L09,   L10,   L11 }, \
    {   L12,   L13,   L14,   L15,   L16,   L17 }, \
    {   L18,   L19,   L20,   L21,   L22,   L23 }, \
    { KC_NO, KC_NO, KC_NO,   L24,   L25,   L26 }, \
    {   R00,   R01,   R02,   R03,   R04,   R05,   R06 }, \
    {   R07,   R08,   R09,   R10,   R11,   R12,   R13 }, \
    {   R14,   R15,   R16,   R17,   R18,   R19,   R20 }, \
    {   R21,   R22,   R23,   R24,   R25,   R26,   R27 }, \
    {   R28,   R29,   R30, KC_NO, KC_NO, KC_NO, KC_NO } \
}
