/* Copyright 2019 Ethan Durrant (emdarcher)
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
#define LAYOUT_all( \
    k00, k04, k10, k14, k20, k24, k30, k34, k40, k44, k50, k54, k60, k64, k65, \
      k01, k05, k11, k15, k21, k25, k31, k35, k41, k45, k51, k55, k61, k66,    \
      k02, k06, k12, k16, k22, k26, k32, k36, k42, k46, k52, k56,    k62,      \
       k03, k07, k13, k17, k23, k27, k37, k43, k47, k53, k57,    k63,  k67,    \
           k70,  k71,  k72,        k33,    k74,      k75,  k76,  k77           \
) \
{ \
    { k00,   k10,   k20,   k30,   k40,   k50,   k60,   k70 }, \
    { k01,   k11,   k21,   k31,   k41,   k51,   k61,   k71 }, \
    { k02,   k12,   k22,   k32,   k42,   k52,   k62,   k72 }, \
    { k03,   k13,   k23,   k33,   k43,   k53,   k63, KC_NO }, \
    { k04,   k14,   k24,   k34,   k44,   k54,   k64,   k74 }, \
    { k05,   k15,   k25,   k35,   k45,   k55,   k65,   k75 }, \
    { k06,   k16,   k26,   k36,   k46,   k56,   k66,   k76 }, \
    { k07,   k17,   k27,   k37,   k47,   k57,   k67,   k77 }  \
}


#define LAYOUT_60_hhkb( \
    k00, k04, k10, k14, k20, k24, k30, k34, k40, k44, k50, k54, k60, k64, k65, \
      k01, k05, k11, k15, k21, k25, k31, k35, k41, k45, k51, k55, k61, k66,    \
      k02, k06, k12, k16, k22, k26, k32, k36, k42, k46, k52, k56,    k62,      \
       k03, k07, k13, k17, k23, k27, k37, k43, k47, k53, k57,    k63,  k67,    \
           k70,  k71,              k33,                    k76,  k77           \
) \
{ \
    { k00,   k10,   k20,   k30,   k40,   k50,   k60,   k70 }, \
    { k01,   k11,   k21,   k31,   k41,   k51,   k61,   k71 }, \
    { k02,   k12,   k22,   k32,   k42,   k52,   k62, KC_NO }, \
    { k03,   k13,   k23,   k33,   k43,   k53,   k63, KC_NO }, \
    { k04,   k14,   k24,   k34,   k44,   k54,   k64, KC_NO }, \
    { k05,   k15,   k25,   k35,   k45,   k55,   k65, KC_NO }, \
    { k06,   k16,   k26,   k36,   k46,   k56,   k66,   k76 }, \
    { k07,   k17,   k27,   k37,   k47,   k57,   k67,   k77 }  \
}
