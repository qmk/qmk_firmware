/* Copyright 2020 Purdea Andrei
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

// NOTE: this may be wrong. The pictures based on which I constructed the layout don't show
// if there are any holes in the colums used. THe order of column must be correct though.

// There are two always-pressed calibration pads on the last column (whatever number it has)

#define LAYOUT( \
    k_00, k_01, k_02,      k_03, k_04, k_05,      k_06, k_07, k_08, k_09, \
    k_10, k_11, k_12,      k_13, k_14, k_15,      k_16, k_17, k_18, k_19, \
    k_20, k_21, k_22,      k_23, k_24, k_25,      k_26, k_27, k_28, k_29, \
    k_30, k_31, k_32,      k_33, k_34, k_35,      k_36, k_37, k_38, k_39, \
    k_40, k_41, k_42,      k_43, k_44, k_45,      k_46, k_47, k_48, k_49  \
) \
{ \
    { k_30,  k_31, k_33,  k_34, KC_NO, k_37,  k_38 }, \
    { k_41,  k_32, k_44,  k_35, k_36,  k_48,  k_39 }, \
    { k_20,  k_22, k_23,  k_25, k_26,  k_27,  k_29 }, \
    { k_40,  k_42, k_43,  k_45, k_46,  k_47,  k_49 }, \
    { k_00,  k_01, k_03,  k_04, k_06,  k_07,  k_08 }, \
    { k_10,  k_12, k_13,  k_15, KC_NO, k_17,  k_19 }, \
    { KC_NO, k_02, KC_NO, k_05, KC_NO, KC_NO, k_09 }, \
    { k_21,  k_11, k_24,  k_14, k_16,  k_28,  k_18 }  \
}
