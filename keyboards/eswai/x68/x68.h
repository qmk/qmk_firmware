/* Copyright 2019 eswai
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

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06,   k95, k94, k93, k92, k91, k90, \
    k10, k11, k12, k13, k14, k15, k16,   k87, k86, k85, k84, k83, k82, k81, k80, \
    k20, k21, k22, k23, k24, k25, k26,   k77, k76, k75, k74, k73, k72, k71, k70, \
    k30, k31, k32, k33, k34, k35, k36,   k66, k65, k64, k63, k62, k61, k60,  \
    k40, k41,           k42, k43, k44,   k55, k54, k53,           k52, k51, k50  \
) \
{ \
    { k00,   k01,   k02,   k03,   k04,   k05,   k06,   KC_NO }, \
    { k10,   k11,   k12,   k13,   k14,   k15,   k16,   KC_NO }, \
    { k20,   k21,   k22,   k23,   k24,   k25,   k26,   KC_NO }, \
    { k30,   k31,   k32,   k33,   k34,   k35,   k36,   KC_NO }, \
    { k40,   k41,   KC_NO, k42,   KC_NO, k43,   k44,   KC_NO }, \
    { k50,   k51,   k52,   k53,   k54,   KC_NO, k55,   KC_NO }, \
    { k60,   k61,   k62,   k63,   k64,   k65,   k66,   KC_NO }, \
    { k70,   k71,   k72,   k73,   k74,   k75,   k76,   k77   }, \
    { k80,   k81,   k82,   k83,   k84,   k85,   k86,   k87   }, \
    { KC_NO, KC_NO, k90,   k91,   k92,   k93,   k94,   k95   } \
}
