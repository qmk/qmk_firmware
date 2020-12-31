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
FULL 10x10 ROUND-ROBIN MATRIX for Reference
{ KC_NO, k21,   k31,   k41,   k51,   k61,   k71,   k81,   k91,   ka1,   }, \
{ k12,   KC_NO, k32,   k42,   k52,   k62,   k72,   k82,   k92,   ka2,   }, \
{ k13,   k23,   KC_NO, k43,   k53,   k63,   k73,   k83,   k93,   ka3,   }, \
{ k14,   k24,   k34,   KC_NO, k54,   k64,   k74,   k84,   k94,   ka4,   }, \
{ k15,   k25,   k35,   k45,   KC_NO, k65,   k75,   k85,   k95,   ka5,   }, \
{ k16,   k26,   k36,   k46,   k56,   KC_NO, k76,   k86,   k96,   ka6,   }, \
{ k17,   k27,   k37,   k47,   k57,   k67,   KC_NO, k87,   k97,   ka7,   }, \
{ k18,   k28,   k38,   k48,   k58,   k68,   k78,   KC_NO, k98,   ka8,   }, \
{ k19,   k29,   k39,   k49,   k59,   k69,   k79,   k89,   KC_NO, ka9,   }, \
{ k1a,   k2a,   k3a,   k4a,   k5a,   k6a,   k7a,   k8a,   k9a,   KC_NO, }  \
*/

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
            ka1,                ka2,    ka3,    ka4,    ka5,    k92,     \
    k16,k21,k26,k31,k36,k41,k46,k51,k56,k61,k76,k71,k86,k81,k96,k91,ka6, \
    k17,k12,k27,k32,k37,k42,k47,k52,k57,k62,k67,k72,k87,k82,k97,    ka7, \
    k18,k13,k28,k23,k38,k43,k48,k53,k58,k63,k68,k73,k78,k83,k98,    ka8, \
    k19,k14,k29,k24,k39,k34,k49,k54,k59,k64,k69,k74,k79,k84,k89,k94,ka9, \
    k1a,k15,k2a,k25,k3a,k35,k4a,k45,k5a,k65,k6a,k75,k7a,k85,k8a,k95,k9a  \
) \
{ \
    { KC_NO, k21,   k31,   k41,   k51,   k61,   k71,   k81,   k91,   ka1,   }, \
    { k12,   KC_NO, k32,   k42,   k52,   k62,   k72,   k82,   k92,   ka2,   }, \
    { k13,   k23,   KC_NO, k43,   k53,   k63,   k73,   k83,   KC_NO, ka3,   }, \
    { k14,   k24,   k34,   KC_NO, k54,   k64,   k74,   k84,   k94,   ka4,   }, \
    { k15,   k25,   k35,   k45,   KC_NO, k65,   k75,   k85,   k95,   ka5,   }, \
    { k16,   k26,   k36,   k46,   k56,   KC_NO, k76,   k86,   k96,   ka6,   }, \
    { k17,   k27,   k37,   k47,   k57,   k67,   KC_NO, k87,   k97,   ka7,   }, \
    { k18,   k28,   k38,   k48,   k58,   k68,   k78,   KC_NO, k98,   ka8,   }, \
    { k19,   k29,   k39,   k49,   k59,   k69,   k79,   k89,   KC_NO, ka9,   }, \
    { k1a,   k2a,   k3a,   k4a,   k5a,   k6a,   k7a,   k8a,   k9a,   KC_NO, }  \
}
