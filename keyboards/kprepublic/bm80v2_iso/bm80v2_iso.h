/* Copyright 2022 bdtc123 *
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

#define LAYOUT_tkl_iso( \
    K0_0,       K0_2, K0_3, K0_4, K0_5, K0_6,K0_7, K0_8, K0_9,   K0_A, K0_B, K0_C, K0_D,      K0_E, K0_F, K0_10, \
    K1_0, K1_1, K1_2, K1_3, K1_4, K1_5, K1_6, K1_7, K1_8, K1_9, K1_A, K1_B, K1_C,    K1_D,    K1_E, K1_F, K1_10, \
     K2_0,   K2_1, K2_2, K2_3, K2_4, K2_5, K2_6, K2_7, K2_8, K2_9, K2_A, K2_B, K2_C,   K2_D,  K2_E, K2_F, K2_10, \
     K3_0,    K3_1, K3_2, K3_3, K3_4, K3_5, K3_6, K3_7, K3_8, K3_9, K3_A, K3_B,    K3_C,                         \
    K4_0,  K4_1,  K4_2, K4_3, K4_4, K4_5,  K4_6, K4_7, K4_8, K4_9, K4_A, K4_B, K4_C,                K4_F,        \
    K5_0,  K5_1,  K5_2,             K5_5,                           K5_A, K5_B, K5_C, K5_D,   K5_E, K5_F, K5_10  \
) { \
	{ K0_0,  KC_NO, K0_2,  K0_3,  K0_4,  K0_5,  K0_6, K0_7,  K0_8,  K0_9,  K0_A,  K0_B,  K0_C,  K0_D,  K0_E,  K0_F,  K0_10 }, \
	{ K1_0,  K1_1,  K1_2,  K1_3,  K1_4,  K1_5,  K1_6,  K1_7,  K1_8,  K1_9,  K1_A,  K1_B,  K1_C,  K1_D,  K1_E,  K1_F,  K1_10 }, \
	{ K2_0,  K2_1,  K2_2,  K2_3,  K2_4,  K2_5,  K2_6,  K2_7,  K2_8,  K2_9,  K2_A,  K2_B,  K2_C,  K2_D,  K2_E,  K2_F,  K2_10 }, \
	{ K3_0,  K3_1,  K3_2,  K3_3,  K3_4,  K3_5,  K3_6,  K3_7,  K3_8,  K3_9,  K3_A,  K3_B,  K3_C,  KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ K4_0,  K4_1,  K4_2,  K4_3,  K4_4,  K4_5,  K4_6,  K4_7,  K4_8,  K4_9,  K4_A,  K4_B,  K4_C,  KC_NO, KC_NO, K4_F,  KC_NO }, \
	{ K5_0,  K5_1,  K5_2,  KC_NO, KC_NO, K5_5,  KC_NO, KC_NO, KC_NO, KC_NO, K5_A,  K5_B,  K5_C,  K5_D,  K5_E,  K5_F,  K5_10 }  \
}

