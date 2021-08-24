/* Copyright 2020 NaCly
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
    k31, k62, k63, k13, k33, k70, k36, k17, k67, k6A, k7A, k3A, k5A, k79, k09, k00, \
    k61, k71, k72, k73, k74, k64, k65, k75, k76, k77, k78, k68, k66, k1A, k6C, k6E, k6D, \
    k11, k01, k02, k03, k04, k14, k15, k05, k06, k07, k08, k18, k16, k2A, k6B, k7E, k7D, \
    k12, k21, k22, k23, k24, k34, k35, k25, k26, k27, k28, k38, k4A, \
    k1F, k41, k42, k43, k44, k54, k55, k45, k46, k47, k58, k2F, k3E, \
    k60, k10, k39, k3B, k59, k29, k57, k40, k5E, k5B, k5C \
) \
{ \
 { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
 { k10, k11, k12, k13, k14, k15, k16, k17, k18, KC_NO, k1A, KC_NO, KC_NO, KC_NO, KC_NO, k1F }, \
 { KC_NO, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, KC_NO, KC_NO, KC_NO, KC_NO, k2F }, \
 { KC_NO, k31, KC_NO, k33, k34, k35, k36, KC_NO, k38, k39, k3A, k3B, KC_NO, KC_NO, k3E, KC_NO }, \
 { k40, k41, k42, k43, k44, k45, k46, k47, KC_NO, KC_NO, k4A, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
 { KC_NO, KC_NO, KC_NO, KC_NO, k54, k55, KC_NO, k57, k58, k59, k5A, k5B, k5C, KC_NO, k5E, KC_NO }, \
 { k60, k61, k62, k63, k64, k65, k66, k67, k68, KC_NO, k6A, k6B, k6C, k6D, k6E, KC_NO }, \
 { k70, k71, k72, k73, k74, k75, k76, k77, k78, k79, k7A, KC_NO, KC_NO, k7D, k7E, KC_NO }, \
}
