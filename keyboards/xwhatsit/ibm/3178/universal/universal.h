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
    k_1_5, k_1_6,    k_2_6, k_1_7, k_2_7, k_1_8, k_2_8, k_1_9, k_2_9, k_1_10, k_2_10, k_1_11, k_2_11, k_1_12, k_2_12,      k_1_13,    k_1_14, k_2_14,    k_2_15, k_1_15, k_2_16, \
    k_3_5, k_3_6,    k_4_6,    k_3_7, k_4_7, k_3_8, k_4_8, k_3_9, k_4_9, k_3_10, k_4_10, k_3_11, k_4_11, k_3_12, k_4_12,   k_3_13,    k_3_14, k_4_14,    k_3_15, k_4_15, k_3_16, \
    k_5_5, k_5_6,    k_5_7,     k_6_7, k_5_8, k_6_8, k_5_9, k_6_9, k_5_10, k_6_10, k_5_11, k_6_11, k_6_12, k_5_12, k_4_13, k_5_13,    k_5_14, k_6_14,    k_5_15, k_6_15, k_5_16, \
    k_7_5, k_6_6,    k_7_6, k_7_7, k_8_7, k_7_8, k_8_8, k_7_9, k_7_10, k_8_10, k_7_11, k_8_11, k_8_12, k_7_12,     k_6_13,            k_7_14, k_8_14,    k_7_15, k_8_15, k_7_16, \
                     k_8_6,                               k_8_9,                                          k_7_13,          k_8_13 \
) \
{ \
    { k_1_5,  k_1_6,  k_1_7,  k_1_8,  k_1_9, k_1_10, k_1_11, k_1_12, k_1_13, k_1_14, k_1_15, KC_NO  }, \
    { KC_NO,  k_2_6,  k_2_7,  k_2_8,  k_2_9, k_2_10, k_2_11, k_2_12, KC_NO , k_2_14, k_2_15, k_2_16 }, \
    { k_3_5,  k_3_6,  k_3_7,  k_3_8,  k_3_9, k_3_10, k_3_11, k_3_12, k_3_13, k_3_14, k_3_15, k_3_16 }, \
    { KC_NO,  k_4_6,  k_4_7,  k_4_8,  k_4_9, k_4_10, k_4_11, k_4_12, k_4_13, k_4_14, k_4_15, KC_NO  }, \
    { k_5_5,  k_5_6,  k_5_7,  k_5_8,  k_5_9, k_5_10, k_5_11, k_5_12, k_5_13, k_5_14, k_5_15, k_5_16 }, \
    { KC_NO,  k_6_6,  k_6_7,  k_6_8,  k_6_9, k_6_10, k_6_11, k_6_12, k_6_13, k_6_14, k_6_15, KC_NO  }, \
    { k_7_5,  k_7_6,  k_7_7,  k_7_8,  k_7_9, k_7_10, k_7_11, k_7_12, k_7_13, k_7_14, k_7_15, k_7_16 }, \
    { KC_NO,  k_8_6,  k_8_7,  k_8_8,  k_8_9, k_8_10, k_8_11, k_8_12, k_8_13, k_8_14, k_8_15, KC_NO  }  \
}
