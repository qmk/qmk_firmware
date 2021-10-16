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
{ KC_NO, k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1a,   }, \
{ k21,   KC_NO, k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2a,   }, \
{ k31,   k32,   KC_NO, k34,   k35,   k36,   k37,   k38,   k39,   k3a,   }, \
{ k41,   k42,   k43,   KC_NO, k45,   k46,   k47,   k48,   k49,   k4a,   }, \
{ k51,   k52,   k53,   k54,   KC_NO, k56,   k57,   k58,   k59,   k5a,   }, \
{ k61,   k62,   k63,   k64,   k65,   KC_NO, k67,   k68,   k69,   k6a,   }, \
{ k71,   k72,   k73,   k74,   k75,   k76,   KC_NO, k78,   k79,   k7a,   }, \
{ k81,   k82,   k83,   k84,   k85,   k86,   k87,   KC_NO, k89,   k8a,   }, \
{ k91,   k92,   k93,   k94,   k95,   k96,   k97,   k98,   KC_NO, k9a,   }, \
{ ka1,   ka2,   ka3,   ka4,   ka5,   ka6,   ka7,   ka8,   ka9,   KC_NO, }  \
*/

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT_all( \
    k61,k12,k62,k13,k63,k14,k64,k15,k65,k16,k67,k17,k68,k18,k69,k19,k6a, \
    k71,  k21,k72,k23,k73,k24,k74,k25,k75,k26,k76,k27,k78,k28,k79,  k7a, \
    k81,  k31,k82,k32,k83,k34,k84,k35,k85,k36,k86,k37,k87,k38,k89,  k8a, \
    k91,k41,k92,k42,k93,k43,k94,k45,k95,k46,k96,k47,k97,k48,k98,k49,k9a, \
    ka1,k51,ka2,k52,ka3,k53,ka4,k54,ka5,k56,ka6,k57,ka7,k58,ka8,k59,ka9  \
) \
{ \
    { KC_NO, k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   KC_NO, }, \
    { k21,   KC_NO, k23,   k24,   k25,   k26,   k27,   k28,   KC_NO, KC_NO, }, \
    { k31,   k32,   KC_NO, k34,   k35,   k36,   k37,   k38,   KC_NO, KC_NO, }, \
    { k41,   k42,   k43,   KC_NO, k45,   k46,   k47,   k48,   k49,   KC_NO, }, \
    { k51,   k52,   k53,   k54,   KC_NO, k56,   k57,   k58,   k59,   KC_NO, }, \
    { k61,   k62,   k63,   k64,   k65,   KC_NO, k67,   k68,   k69,   k6a,   }, \
    { k71,   k72,   k73,   k74,   k75,   k76,   KC_NO, k78,   k79,   k7a,   }, \
    { k81,   k82,   k83,   k84,   k85,   k86,   k87,   KC_NO, k89,   k8a,   }, \
    { k91,   k92,   k93,   k94,   k95,   k96,   k97,   k98,   KC_NO, k9a,   }, \
    { ka1,   ka2,   ka3,   ka4,   ka5,   ka6,   ka7,   ka8,   ka9,   KC_NO, }  \
}
#define LAYOUT_music( \
            k62,    k63,k14,k64,k15,    k16,    k17,    k18,    k19,     \
    k71,k21,k72,k23,k73,  k24,k74,k25,k75,k26,k76,k27,k78,k28,k79,  k7a, \
    k81,k31,k82,k32,k83,  k34,k84,k35,k85,k36,k86,k37,k87,k38,k89,  k8a, \
    k91,k41,k92,k42,k93,k43,k94,k45,k95,k46,k96,k47,k97,k48,k98,k49,k9a, \
    ka1,k51,ka2,k52,ka3,k53,ka4,k54,ka5,k56,ka6,k57,ka7,k58,ka8,k59,ka9  \
) \
{ \
    { KC_NO, KC_NO, KC_NO, k14,   k15,   k16,   k17,   k18,   k19,   KC_NO, }, \
    { k21,   KC_NO, k23,   k24,   k25,   k26,   k27,   k28,   KC_NO, KC_NO, }, \
    { k31,   k32,   KC_NO, k34,   k35,   k36,   k37,   k38,   KC_NO, KC_NO, }, \
    { k41,   k42,   k43,   KC_NO, k45,   k46,   k47,   k48,   k49,   KC_NO, }, \
    { k51,   k52,   k53,   k54,   KC_NO, k56,   k57,   k58,   k59,   KC_NO, }, \
    { KC_NO, k62,   k63,   k64,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, }, \
    { k71,   k72,   k73,   k74,   k75,   k76,   KC_NO, k78,   k79,   k7a,   }, \
    { k81,   k82,   k83,   k84,   k85,   k86,   k87,   KC_NO, k89,   k8a,   }, \
    { k91,   k92,   k93,   k94,   k95,   k96,   k97,   k98,   KC_NO, k9a,   }, \
    { ka1,   ka2,   ka3,   ka4,   ka5,   ka6,   ka7,   ka8,   ka9,   KC_NO, }  \
}
