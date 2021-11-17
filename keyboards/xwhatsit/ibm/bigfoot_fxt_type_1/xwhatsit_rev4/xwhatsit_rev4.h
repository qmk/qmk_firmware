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

#define LAYOUT( \
    k_1_1, k_1_2,   k_1_5, k_1_6, k_1_7, k_1_8, k_1_9, k_1_10, k_1_11, k_1_12, k_1_13, k_1_14, k_1_15, k_1_16, k_1_17, k_1_19      , k_1_21        , k_1_23        , \
    k_2_1, k_2_2,   k_2_5,    k_2_7, k_2_8, k_2_9, k_2_10, k_2_11, k_2_12, k_2_13, k_2_14, k_2_15, k_2_16, k_2_17, k_1_18 ,  k_2_19, k_1_20, k_2_21, k_1_22, k_2_23, \
    k_3_1, k_3_2,   k_3_5,     k_3_7, k_3_8, k_3_9, k_3_10, k_3_11, k_3_12, k_3_13, k_3_14, k_3_15, k_3_16, k_3_17, k_2_18,          k_2_20, k_3_21, k_2_22, k_4_23, \
    k_4_1, k_4_2,   k_4_5,  k_4_7, k_4_8, k_4_9, k_4_10, k_4_11, k_4_12, k_4_13, k_4_14, k_4_15, k_4_16, k_4_17, k_3_18    , k_3_19, k_3_20, k_4_21, k_3_22, \
    k_4_4, k_4_3,   k_4_6    ,                              k_4_18                                   , k_4_19              , k_4_20        , k_4_22 \
) \
{ \
    { k_1_1, k_1_2, KC_NO, KC_NO, k_1_5, k_1_6, k_1_7, k_1_8, k_1_9, k_1_10, k_1_11, k_1_12, k_1_13, k_1_14, k_1_15, k_1_16, k_1_17, k_1_18, k_1_19, k_1_20, k_1_21, k_1_22, k_1_23 }, \
    { k_2_1, k_2_2, KC_NO, KC_NO, k_2_5, KC_NO, k_2_7, k_2_8, k_2_9, k_2_10, k_2_11, k_2_12, k_2_13, k_2_14, k_2_15, k_2_16, k_2_17, k_2_18, k_2_19, k_2_20, k_2_21, k_2_22, k_2_23 }, \
    { k_3_1, k_3_2, KC_NO, KC_NO, k_3_5, KC_NO, k_3_7, k_3_8, k_3_9, k_3_10, k_3_11, k_3_12, k_3_13, k_3_14, k_3_15, k_3_16, k_3_17, k_3_18, k_3_19, k_3_20, k_3_21, k_3_22, KC_NO  }, \
    { k_4_1, k_4_2, k_4_3, k_4_4, k_4_5, k_4_6, k_4_7, k_4_8, k_4_9, k_4_10, k_4_11, k_4_12, k_4_13, k_4_14, k_4_15, k_4_16, k_4_17, k_4_18, k_4_19, k_4_20, k_4_21, k_4_22, k_4_23 }, \
}

//k_2_6? (4th on the second row appears to be a calibration pad)
//k_3_23? (last) is a calibration pad