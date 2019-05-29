/* Copyright 2019 MechMerlin
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

// LAYOUT_all ignores the key often coded as ~# to the left of Enter on ISO layouts. 
// This is done as it shares the same row AND col as the pipe key. 

#define LAYOUT_all( \
    k50, k41, k42, k43, k44, k45, k61, k68, k78, k71, k49, k48, k47, k52, k4A, \
    k30, k31, k32, k33, k34, k35, k62, k67, k77, k72, k39, k38, k37, k36,      \
    k20, k21, k22, k23, k24, k25, k63, k66, k76, k73, k29, k28, k26,           \
    k10, k53, k11, k12, k13, k14, k15, k64, k6A, k7A, k74, k19, k18, k54,      \
    k00, k01, k02, k65, k04, k08, k09, k05                                     \
) \
{ \
    { k00,   k01,   k02,   KC_NO, k04, k05,   KC_NO, KC_NO, k08,   k09,   KC_NO }, \
    { k10,   k11,   k12,   k13,   k14, k15,   KC_NO, KC_NO, k18,   k19,   KC_NO }, \
    { k20,   k21,   k22,   k23,   k24, k25,   k26,   KC_NO, k28,   k29,   KC_NO }, \
    { k30,   k31,   k32,   k33,   k34, k35,   k36,   k37,   k38,   k39,   KC_NO }, \
    { KC_NO, k41,   k42,   k43,   k44, k45,   KC_NO, k47,   k48,   k49,   k4A   }, \
    { k50,   KC_NO, k52,   k53,   k54, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, k61,   k62,   k63,   k64, k65,   k66,   k67,   k68,   KC_NO, k6A   }, \
    { KC_NO, k71,   k72,   k73,   k74, KC_NO, k76,   k77,   k78,   KC_NO, k7A   }, \
}


#define LAYOUT_60_ansi( \
    k50, k41, k42, k43, k44, k45, k61, k68, k78, k71, k49, k48, k47, k4A, \
    k30, k31, k32, k33, k34, k35, k62, k67, k77, k72, k39, k38, k37, k36, \
    k20, k21, k22, k23, k24, k25, k63, k66, k76, k73, k29, k28, k26,      \
    k10, k11, k12, k13, k14, k15, k64, k6A, k7A, k74, k19, k18,           \
    k00, k01, k02, k65, k04, k08, k09, k05                                \
) \
{ \
    { k00,   k01,   k02,   KC_NO, k04,   k05,   KC_NO, KC_NO, k08,   k09,   KC_NO }, \
    { k10,   k11,   k12,   k13,   k14,   k15,   KC_NO, KC_NO, k18,   k19,   KC_NO }, \
    { k20,   k21,   k22,   k23,   k24,   k25,   k26,   KC_NO, k28,   k29,   KC_NO }, \
    { k30,   k31,   k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   KC_NO }, \
    { KC_NO, k41,   k42,   k43,   k44,   k45,   KC_NO, k47,   k48,   k49,   k4A   }, \
    { k50,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, k61,   k62,   k63,   k64,   k65,   k66,   k67,   k68,   KC_NO, k6A   }, \
    { KC_NO, k71,   k72,   k73,   k74,   KC_NO, k76,   k77,   k78,   KC_NO, k7A   }, \
}

#define LAYOUT_60_hhkb( \
    k50, k41, k42, k43, k44, k45, k61, k68, k78, k71, k49, k48, k47, k52, k4A, \
    k30, k31, k32, k33, k34, k35, k62, k67, k77, k72, k39, k38, k37, k36,      \
    k20, k21, k22, k23, k24, k25, k63, k66, k76, k73, k29, k28, k26,           \
    k10, k11, k12, k13, k14, k15, k64, k6A, k7A, k74, k19, k18, k54,           \
    k01, k02, k65, k08, k09                                                    \
) \
{ \
    { KC_NO, k01,   k02,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k08,   k09,   KC_NO }, \
    { k10,   k11,   k12,   k13,   k14,   k15,   KC_NO, KC_NO, k18,   k19,   KC_NO }, \
    { k20,   k21,   k22,   k23,   k24,   k25,   k26,   KC_NO, k28,   k29,   KC_NO }, \
    { k30,   k31,   k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   KC_NO }, \
    { KC_NO, k41,   k42,   k43,   k44,   k45,   KC_NO, k47,   k48,   k49,   k4A   }, \
    { k50,   KC_NO, k52,   KC_NO, k54,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, k61,   k62,   k63,   k64,   k65,   k66,   k67,   k68,   KC_NO, k6A   }, \
    { KC_NO, k71,   k72,   k73,   k74,   KC_NO, k76,   k77,   k78,   KC_NO, k7A   }, \
}

#define LAYOUT_60_tsangan( \
    k50, k41, k42, k43, k44, k45, k61, k68, k78, k71, k49, k48, k47, k52, k4A, \
    k30, k31, k32, k33, k34, k35, k62, k67, k77, k72, k39, k38, k37, k36,      \
    k20, k21, k22, k23, k24, k25, k63, k66, k76, k73, k29, k28, k26,           \
    k10, k11, k12, k13, k14, k15, k64, k6A, k7A, k74, k19, k18, k54,           \
    k00, k01, k02, k65, k08, k09, k05                                          \
) \
{ \
    { k00,   k01,   k02,   KC_NO, KC_NO, k05,   KC_NO, KC_NO, k08,   k09,   KC_NO }, \
    { k10,   k11,   k12,   k13,   k14,   k15,   KC_NO, KC_NO, k18,   k19,   KC_NO }, \
    { k20,   k21,   k22,   k23,   k24,   k25,   k26,   KC_NO, k28,   k29,   KC_NO }, \
    { k30,   k31,   k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   KC_NO }, \
    { KC_NO, k41,   k42,   k43,   k44,   k45,   KC_NO, k47,   k48,   k49,   k4A   }, \
    { k50,   KC_NO, k52,   KC_NO, k54,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, k61,   k62,   k63,   k64,   k65,   k66,   k67,   k68,   KC_NO, k6A   }, \
    { KC_NO, k71,   k72,   k73,   k74,   KC_NO, k76,   k77,   k78,   KC_NO, k7A   }, \
}
