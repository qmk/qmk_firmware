/* Copyright 2021 Marby
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
   L_1,  L_5,  L_9,  L_13, L_17, L_21, R_25, R_29, R_33, R_37, R_41, R_45, \
   L_2,  L_6,  L_10, L_14, L_18, L_22, R_26, R_30, R_34, R_38, R_42, R_46, \
   L_3,  L_7,  L_11, L_15, L_19, L_23, R_27, R_31, R_35, R_39, R_43, R_47, \
   L_4,  L_8,  L_12, L_16, L_20, L_24, R_28, R_32, R_36, R_40, R_44, R_48  \
) \
{ \
{ KC_NO, L_1,   L_2,   L_3,   L_4,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
{ L_5,   KC_NO, L_6,   L_7,   L_8,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
{ L_9,   L_10,  KC_NO, L_11,  L_12,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
{ L_13,  L_14,  L_15,  KC_NO, L_16,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
{ L_17,  L_18,  L_19,  L_20,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
{ L_21,  L_22,  L_23,  L_24,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
{ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, R_25,  R_26,  R_27,  R_28  }, \
{ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, R_29,  KC_NO, R_30,  R_31,  R_32  }, \
{ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, R_33,  R_34,  KC_NO, R_35,  R_36  }, \
{ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, R_37,  R_38,  R_39,  KC_NO, R_40  }, \
{ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, R_41,  R_42,  R_43,  R_44,  KC_NO }, \
{ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, R_45,  R_46,  R_47,  R_48,  KC_NO } \
}
