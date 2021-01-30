/* Copyright 2020 kb-elmo<mail@elmo.space>
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
    k01,        k02,  k03,  k04,  k05,  k06,  k07,  k08,  k09,  k10,  k11,  k52,  k12,    k105, k91,  k90,                      k84,  \
    k13,  k14,  k15,  k16,  k17,  k18,  k19,  k20,  k21,  k22,  k23,  k24,  k25,  k26,    k104, k78,  k79,    k80,  k81,  k83,  k85,  \
    k27,  k28,  k29,  k30,  k31,  k32,  k33,  k34,  k35,  k36,  k37,  k38,  k39,  k40,    k92,  k93,  k94,    k95,  k82,  k97,  k99,  \
    k41,  k42,  k43,  k44,  k45,  k46,  k47,  k48,  k49,  k50,  k51,  k53,        k54,                        k89,  k96,  k98,  k86,  \
    k55,  k56,  k57,  k58,  k59,  k60,  k61,  k62,  k63,  k64,  k65,              k66,          k73,          k103, k88,  k87,        \
    k67,  k68,  k69,              k70,                                k75,  k76,  k77,    k72,  k74,  k71,    k102,       k101, k100  \
) { \
    { k01,   KC_NO, k02,   k03,   k04,   k05,   k06,   k07,   k08,   k09,   KC_NO, k10,   k11,   k12  }, \
    { k13,   k14,   k15,   k16,   k17,   k18,   k19,   k20,   k21,   k22,   k23,   k24,   k25,   k26  }, \
    { k27,   k28,   k29,   k30,   k31,   k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k40  }, \
    { k41,   k42,   k43,   k44,   k45,   k46,   k47,   k48,   k49,   k50,   k51,   k52,   k53,   k54  }, \
    { k55,   k56,   k57,   k58,   k59,   k60,   k61,   k62,   k63,   k64,   k65,   KC_NO, KC_NO, k66  }, \
    { k67,   k68,   k69,   KC_NO, KC_NO, k70,   k71,   k72,   k73,   k74,   k75,   k76,   KC_NO, k77  }, \
    { k78,   k79,   k80,   k81,   k82,   k83,   k84,   k85,   k86,   k87,   k88,   k89,   k90,   k91  }, \
    { k92,   k93,   k94,   k95,   k96,   k97,   k98,   k99,   k100,  k101,  k102,  k103,  k104,  k105 }  \
}
