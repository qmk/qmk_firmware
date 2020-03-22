/* Copyright 2020 Takeshi Nishio
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
    k18, k28, k38, k48, k58, k68,           k14, k24, k34, k54, k64, k74, \
    k81, k21, k31, k41, k51, k61,           k15, k25, k35, k45, k65, k75, \
    k82, k12, k32, k42, k52, k62,           k16, k26, k36, k46, k56, k76, \
    k83, k13, k23, k43, k53, k63, k73, k87, k17, k27, k37, k47, k57, k67  \
 ) \
 { \
     { KC_NO,   k21,    k31,    k41,    k51,    k61,    KC_NO,  k81     }, \
     { k12,     KC_NO,  k32,    k42,    k52,    k62,    KC_NO,  k82     }, \
     { k13,     k23,    KC_NO,  k43,    k53,    k63,    k73,    k83     }, \
     { k14,     k24,    k34,    KC_NO,  k54,    k64,    k74,    KC_NO   }, \
     { k15,     k25,    k35,    k45,    KC_NO,  k65,    k75,    KC_NO   }, \
     { k16,     k26,    k36,    k46,    k56,    KC_NO,  k76,    KC_NO   }, \
     { k17,     k27,    k37,    k47,    k57,    k67,    KC_NO,  k87     }, \
     { k18,     k28,    k38,    k48,    k58,    k68,    KC_NO,  KC_NO   } \
 }
