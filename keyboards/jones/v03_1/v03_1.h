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

/*
FULL 11x11 ROUND-ROBIN MATRIX for Reference
{ KC_NO, k21,   k31,   k41,   k51,   k61,   k71,   k81,   k91,   ka1,   kb1 }, \
{ k12,   KC_NO, k32,   k42,   k52,   k62,   k72,   k82,   k92,   ka2,   kb2 }, \
{ k13,   k23,   KC_NO, k43,   k53,   k63,   k73,   k83,   k93,   ka3,   kb3 }, \
{ k14,   k24,   k34,   KC_NO, k54,   k64,   k74,   k84,   k94,   ka4,   kb4 }, \
{ k15,   k25,   k35,   k45,   KC_NO, k65,   k75,   k85,   k95,   ka5,   kb5 }, \
{ k16,   k26,   k36,   k46,   k56,   KC_NO, k76,   k86,   k96,   ka6,   kb6 }, \
{ k17,   k27,   k37,   k47,   k57,   k67,   KC_NO, k87,   k97,   ka7,   kb7 }, \
{ k18,   k28,   k38,   k48,   k58,   k68,   k78,   KC_NO, k98,   ka8,   kb8 }, \
{ k19,   k29,   k39,   k49,   k59,   k69,   k79,   k89,   KC_NO, ka9,   kb9 }, \
{ k1a,   k2a,   k3a,   k4a,   k5a,   k6a,   k7a,   k8a,   k9a,   KC_NO, kba }, \
{ k1b,   k2b,   k3b,   k4b,   k5b,   k6b,   k7b,   k8b,   k9b,   kab,   KC_NO } \
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
    k17, k27, k37, k47, k57, k67, k76, k86, k96, ka6, kb6, k81, k91, ka1, kb1, \
    k18,   k38, k48, k58, k68, k78, k87, k97, ka7, kb7, k82, k92,    ka2, kb2, \
    k19,   k39, k49, k59, k69, k79, k89, k98, ka8, kb8, k83, k93,    ka3, kb3, \
    k1a,      k3a, k4a, k5a, k6a, k7a, k8a, k9a, ka9, kb9, k84, k94, ka4, kb4, \
    k1b, k2b, k3b, k4b,      k6b,      k8b,      k9b, kab, k85, k95, ka5, kb5  \
) \
{ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k81,   k91,   ka1,   kb1 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k82,   k92,   ka2,   kb2 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k83,   k93,   ka3,   kb3 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k84,   k94,   ka4,   kb4 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k85,   k95,   ka5,   kb5 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k76,   k86,   k96,   ka6,   kb6 }, \
    { k17,   k27,   k37,   k47,   k57,   k67,   KC_NO, k87,   k97,   ka7,   kb7 }, \
    { k18,   KC_NO, k38,   k48,   k58,   k68,   k78,   KC_NO, k98,   ka8,   kb8 }, \
    { k19,   KC_NO, k39,   k49,   k59,   k69,   k79,   k89,   KC_NO, ka9,   kb9 }, \
    { k1a,   KC_NO, k3a,   k4a,   k5a,   k6a,   k7a,   k8a,   k9a,   KC_NO, KC_NO }, \
    { k1b,   k2b,   k3b,   k4b,   KC_NO, k6b,   KC_NO, k8b,   k9b,   kab,   KC_NO }  \
}

#define LAYOUT_ansi( \
    k17, k27, k37, k47, k57, k67, k76, k86, k96, ka6, kb6, k81, k91, ka1, kb1, \
    k18,   k38, k48, k58, k68, k78, k87, k97, ka7, kb7, k82, k92,    ka2, kb2, \
    k19,   k39, k49, k59, k69, k79, k89, k98, ka8, kb8, k83, k93,         kb3, \
    k1a,      k3a, k4a, k5a, k6a, k7a, k8a, k9a, ka9, kb9, k84, k94, ka4, kb4, \
    k1b, k2b, k3b, k4b,      k6b,      k8b,      k9b, kab, k85, k95, ka5, kb5  \
) \
{ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k81,   k91,   ka1,   kb1 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k82,   k92,   ka2,   kb2 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k83,   k93,   KC_NO, kb3 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k84,   k94,   ka4,   kb4 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k85,   k95,   ka5,   kb5 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k76,   k86,   k96,   ka6,   kb6 }, \
    { k17,   k27,   k37,   k47,   k57,   k67,   KC_NO, k87,   k97,   ka7,   kb7 }, \
    { k18,   KC_NO, k38,   k48,   k58,   k68,   k78,   KC_NO, k98,   ka8,   kb8 }, \
    { k19,   KC_NO, k39,   k49,   k59,   k69,   k79,   k89,   KC_NO, ka9,   kb9 }, \
    { k1a,   KC_NO, k3a,   k4a,   k5a,   k6a,   k7a,   k8a,   k9a,   KC_NO, KC_NO }, \
    { k1b,   k2b,   k3b,   k4b,   KC_NO, k6b,   KC_NO, k8b,   k9b,   kab,   KC_NO }  \
}

#define LAYOUT_jp( \
    k17, k27, k37, k47, k57, k67, k76, k86, k96, ka6, kb6, k81, k91, ka1, kb1, \
    k18,   k38, k48, k58, k68, k78, k87, k97, ka7, kb7, k82,         ka2, kb2, \
    k19,   k39, k49, k59, k69, k79, k89, k98, ka8, kb8, k83,  k93,   ka3, kb3, \
    k1a,      k3a, k4a, k5a, k6a, k7a, k8a, k9a, ka9, kb9, k84, k94, ka4, kb4, \
    k1b, k2b, k3b, k4b,      k6b,      k8b,      k9b, kab, k85, k95, ka5, kb5  \
) \
{ \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k81,   k91,   ka1,   kb1 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k82,   KC_NO, ka2,   kb2 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k83,   k93,   ka3,   kb3 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k84,   k94,   ka4,   kb4 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k85,   k95,   ka5,   kb5 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k76,   k86,   k96,   ka6,   kb6 }, \
    { k17,   k27,   k37,   k47,   k57,   k67,   KC_NO, k87,   k97,   ka7,   kb7 }, \
    { k18,   KC_NO, k38,   k48,   k58,   k68,   k78,   KC_NO, k98,   ka8,   kb8 }, \
    { k19,   KC_NO, k39,   k49,   k59,   k69,   k79,   k89,   KC_NO, ka9,   kb9 }, \
    { k1a,   KC_NO, k3a,   k4a,   k5a,   k6a,   k7a,   k8a,   k9a,   KC_NO, KC_NO }, \
    { k1b,   k2b,   k3b,   k4b,   KC_NO, k6b,   KC_NO, k8b,   k9b,   kab,   KC_NO }  \
}
