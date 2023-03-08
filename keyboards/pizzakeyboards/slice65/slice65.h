/* Copyright 2022 Christoph Baumann
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
    K1_1, K2_1,  K1_2, K2_2,  K1_3, K2_3,  K1_4, K2_4,  K1_5, K2_5,  K1_6, K2_6,  K1_7, K2_7,  K1_8, \
    K3_1, K4_1,  K3_2, K4_2,  K3_3, K4_3,  K3_4, K4_4,  K3_5, K4_5,  K3_6, K4_6,  K3_7, K4_7,  K3_8, \
    K5_1, K6_1,  K5_2, K6_2,  K5_3, K6_3,  K5_4, K6_4,  K5_5, K6_5,  K5_6, K6_6,        K6_7,  K5_8, \
    K7_1,        K7_2, K8_2,  K7_3, K8_3,  K7_4, K8_4,  K7_5, K8_5,  K7_6, K8_6,  K7_7, K8_7,  K7_8, \
    K9_1, K10_1, K9_2,                     K9_4,                     K9_6, K10_6, K9_7, K10_7, K9_8  \
) \
{ \
    {K1_1,   K1_2,  K1_3,   K1_4,  K1_5,   K1_6,  K1_7,   K1_8},\
    {K2_1,   K2_2,  K2_3,   K2_4,  K2_5,   K2_6,  K2_7,   KC_NO},\
    {K3_1,   K3_2,  K3_3,   K3_4,  K3_5,   K3_6,  K3_7,   K3_8},\
    {K4_1,   K4_2,  K4_3,   K4_4,  K4_5,   K4_6,  K4_7,   KC_NO},\
    {K5_1,   K5_2,  K5_3,   K5_4,  K5_5,   K5_6,  KC_NO,  K5_8},\
    {K6_1,   K6_2,  K6_3,   K6_4,  K6_5,   K6_6,  K6_7,   KC_NO},\
    {K7_1,   K7_2,  K7_3,   K7_4,  K7_5,   K7_6,  K7_7,   K7_8},\
    {KC_NO,  K8_2,  K8_3,   K8_4,  K8_5,   K8_6,  K8_7,   KC_NO},\
    {K9_1,   K9_2,  KC_NO,  K9_4,  KC_NO,  K9_6,  K9_7,   K9_8},\
    {K10_1,  KC_NO, KC_NO,  KC_NO, KC_NO,  K10_6, K10_7,  KC_NO}\
}
