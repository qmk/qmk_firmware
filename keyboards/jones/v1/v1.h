/* Copyright 2021 Takeshi Nishio
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

/*
FULL 10x10 ROUND-ROBIN MATRIX for Reference

{ KC_NO, k01,   k02,   k03,   k04,   k05,   k06,   k07,   k08,   k09   }, \
{ k10,   KC_NO, k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19   }, \
{ k20,   k21,   KC_NO, k23,   k24,   k25,   k26,   k27,   k28,   k29   }, \
{ k30,   k31,   k32,   KC_NO, k34,   k35,   k36,   k37,   k38,   k39   }, \
{ k40,   k41,   k42,   k43,   KC_NO, k45,   k46,   k47,   k48,   k49   }, \
{ k50,   k51,   k52,   k53,   k54,   KC_NO, k56,   k57,   k58,   k59   }, \
{ k60,   k61,   k62,   k63,   k64,   k65,   KC_NO, k67,   k68,   k69   }, \
{ k70,   k71,   k72,   k73,   k74,   k75,   k76,   KC_NO, k78,   k79   }, \
{ k80,   k81,   k82,   k83,   k84,   k85,   k86,   k87,   KC_NO, k89   }, \
{ k90,   k91,   k92,   k93,   k94,   k95,   k96,   k97,   k98,   KC_NO }  \

*/

/* Keys on 6th row are used with rotary encoder. */
#define LAYOUT( \
      k09, k59, k08, k54, k04, k50, k56, k06, k05, k52, k02, k53, k07, k51, k01,  \
        k19,  k69, k18, k64, k14, k60, k10, k16, k15, k62, k12, k63, k17,  k61,   \
        k29,  k79, k28, k74, k24, k70, k20, k26, k25, k72, k23, k73, k27,  k71,   \
      k39, k89, k38, k84, k34, k80, k30, k36, k35, k82, k32, k83, k37, k81, k31,  \
      k49, k98,  k48,  k94,   k90,    k46, k45,    k92, k42, k93, k47, k91, k41,  \
    k85, k86,                                                            k95, k96 \
) \
{ \
    { KC_NO, k01,   k02,   KC_NO, k04,   k05,   k06,   k07,   k08,   k09,  }, \
    { k10,   KC_NO, k12,   KC_NO, k14,   k15,   k16,   k17,   k18,   k19,  }, \
    { k20,   KC_NO, KC_NO, k23,   k24,   k25,   k26,   k27,   k28,   k29,  }, \
    { k30,   k31,   k32,   KC_NO, k34,   k35,   k36,   k37,   k38,   k39,  }, \
    { KC_NO, k41,   k42,   KC_NO, KC_NO, k45,   k46,   k47,   k48,   k49,  }, \
    { k50,   k51,   k52,   k53,   k54,   KC_NO, k56,   KC_NO, KC_NO, k59,  }, \
    { k60,   k61,   k62,   k63,   k64,   KC_NO, KC_NO, KC_NO, KC_NO, k69,  }, \
    { k70,   k71,   k72,   k73,   k74,   KC_NO, KC_NO, KC_NO, KC_NO, k79,  }, \
    { k80,   k81,   k82,   k83,   k84,   k85,   k86,   KC_NO, KC_NO, k89,  }, \
    { k90,   k91,   k92,   k93,   k94,   k95,   k96,   KC_NO, k98,   KC_NO }  \
}
