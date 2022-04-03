/* Copyright 2021 jurassic73
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
 * layout of the board and position of the keys minus blanks in the matrix.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix which includes blanks in the wired out matrix.
 */
#define LAYOUT( \
    k00,      k01, k02, k03, k04, k05,       k06, k07, k08, k09, k10, k11, k12, k13, k14, k15, \
    k32, k16, k17, k18, k19, k20, k21,     k22, k23, k24, k25, k26, k27,  k28,  k29, k30, k31, \
    k48, k33, k34, k35, k36, k37,       k54, k38, k39, k40, k41, k42, k43, k44, k45, k46, k47, \
    k61, k49, k50, k51, k52, k53,         k67, k55, k56, k57, k58, k59,    k60, \
    k74,   k62, k63, k64, k65, k66,         k80, k68, k69, k70, k71,       k72,      k73, \
    k75, k76, k77, k78,    k79,             k81,          k82, k83, k84, k85,   k86, k87, k88 \
    ) \
    { \
      { KC_NO, KC_NO, KC_NO, KC_NO, k00, k01, k02, k03, k04, k05 }, \
      { KC_NO, KC_NO, KC_NO, KC_NO, k16, k17, k18, k19, k20, k21 },  \
      { KC_NO, KC_NO, KC_NO, KC_NO, k32, k33, k34, k35, k36, k37 },  \
      { KC_NO, KC_NO, KC_NO, KC_NO, k48, k49, k50, k51, k52, k53 },  \
      { KC_NO, KC_NO, KC_NO, KC_NO, k61, k62, k63, k64, k65, k66, },  \
      { KC_NO, KC_NO, KC_NO, KC_NO, k74, k75, k76, k77, k78, k79, },  \
      { k06, k07, k08, k09, k10, k11, k12, k13, k14, k15 }, \
      { k22, k23, k24, k25, k26, k27, k28, k29, k30, k31 },  \
      { k38, k39, k40, k41, k42, k43, k44, k45, k46, k47 },  \
      { k54, k55, k56, k57, k58, k59, k60, KC_NO, KC_NO, KC_NO },  \
      { k67, k68, k69, k70, k71, KC_NO, k72, KC_NO, k73, KC_NO },  \
      { k80, k81, KC_NO, k82, k83, k84, k85, k86, k87, k88 }  \
}
