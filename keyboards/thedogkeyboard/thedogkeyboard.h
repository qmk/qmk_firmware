/* Copyright 2019 kakunpc
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
#define LAYOUT_all( \
    k01,   k07,k13,k19,k24,   k29,k35,k40,k45,   k50,k56,k62,k66,   k70,k76,k82,\
    \
    k02,k08,k14,k20,k25,k30,k36,k41,k46,k51,k57,k63,k67,       k71,   k77,k84,k83,   k88,k93,k97,k102,   \
    k03,   k09,k15,k21,k26,k31,k37,k42,k47,k52,k58,k64,k68,    k72,   k78,k86,k85,   k89,k94,k98,k103,   \
    k04,    k10,k16,k22,k27,k32,k38,k43,k48,k53,k59,k65,       k73,                  k90,k95,k99,k110,   \
    k05,     k11,k17,k23,k28,k33,k39,k44,k49,k54,k60,          k74,       k87,       k91,k96,k100,k104,  \
    k06, k12, k18, k105, k106, k34, k107, k108, k55, k61, k69, k75,   k79,k80,k81,   k92,k109,k101,k111  \
    \
) \
{ \
    { k01, k02, k03, k04, k05, k06 }, \
    { k07, k08, k09, k10, k11, k12 }, \
    { k13, k14, k15, k16, k17, k18 }, \
    { k19, k20, k21, k22, k23, k105 }, \
    { k24, k25, k26, k27, k28, k106 }, \
    { k29, k30, k31, k32, k33, k34 }, \
    { k35, k36, k37, k38, k39, k107 }, \
    { k40, k41, k42, k43, k44, k108 }, \
    { k45, k46, k47, k48, k49, KC_NO }, \
    { k50, k51, k52, k53, k54, k55 }, \
    { k56, k57, k58, k59, k60, k61 }, \
    { k62, k63, k64, k65, KC_NO, KC_NO }, \
    { k66, k67, k68, k69, KC_NO, KC_NO }, \
    { k70, k71, k72, k73, k74, k75 }, \
    { k76, k77, k78, k79, k80, k81 }, \
    { k82, k83, k84, k85, k86, k87 }, \
    { k88, k89, k90, k91, k92, KC_NO }, \
    { k93, k94, k95, k96, k109, KC_NO }, \
    { k97, k98, k99, k100, k101, KC_NO }, \
    { k102, k103, k104, k110, k111, KC_NO } \
}
