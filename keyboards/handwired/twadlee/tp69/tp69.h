/* Copyright 2020 Tracy Wadleigh
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
    k00, k01, k02, k03, k04, k05, k06, k07, k50, k51, k52, k53, k54, k55, k56, k57, \
      k10, k11, k13, k14, k15, k16, k17, k60, k61, k62, k63, k64, k65, k66, k67, \
        k20, k21, k23, k24, k25, k27, /**/ k70, k71, k72, k73, k74, k75, k77, \
          k30, k32, k33, k34, k35, k36, k37, k81, k82, k83, k84, k85, k86, \
            k40, k41, k43, k44, k46, k47, k91, k92, k94, k95, k96, k97 \
) \
{ \
    {  k00,   k01,   k02,   k03,   k04,   k05,   k06,   k07}, \
    {  k10,   k11, KC_NO,   k13,   k14,   k15,   k16,   k17}, \
    {  k20,   k21, KC_NO,   k23,   k24,   k25, KC_NO,   k27}, \
    {  k30, KC_NO,   k32,   k33,   k34,   k35,   k36,   k37}, \
    {  k40,   k41, KC_NO,   k43,   k44, KC_NO,   k46,   k47}, \
    {  k50,   k51,   k52,   k53,   k54,   k55,   k56,   k57}, \
    {  k60,   k61,   k62,   k63,   k64,   k65,   k66,   k67}, \
    {  k70,   k71,   k72,   k73,   k74,   k75, KC_NO,   k77}, \
    {KC_NO,   k81,   k82,   k83,   k84,   k85,   k86, KC_NO}, \
    {KC_NO,   k91,   k92, KC_NO,   k94,   k95,   k96,   k97} \
}
