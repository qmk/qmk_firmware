/* Copyright 2018 REPLACE_WITH_YOUR_NAME
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

// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
            k09, k19, k1A, k29, k39, k3A, k49, k59, k5A, k69, k79, k7A,             k3G, k3H, k2G, \
            k0A, k0B, k1B, k2A, k2B, k3B, k4A, k4B, k5B, k6A, k6B, k7B,             k1G, k5G, k4G, \
k31, k32,   k34, k24, k25, k26, k27, k37, k38, k28, k2C, k2D, k2E, k3E, k3C, k3F,                   k2F, k2H, k2I, k20, \
k21, k41,   k42, k44, k45, k46, k47, k57, k58, k48, k4C, k4D, k4E, k5E, k5C, k6F,                   k4F, k4H, k4I, k40, \
k51, k52,   k62, k14, k15, k16, k17, k07, k08, k18, k1C, k1D, k1E, k0E, k6E,                        k1F, k1H, k1I, k10, \
k11, k12,   k73, k74, k64, k65, k66, k67, k77, k78, k68, k6C, k6D, k7E,      k63,        k0G,       k61, k6H, k6I, k7J, \
k02, k01,   k00,    k70,                k71,             k03,      k72,             k60, k0J, k1J,  k7H,      k7I, \
                                                                                         k0F \
) \
{ \
    {   k00,   k01,   k02,   k03,   KC_NO, KC_NO, KC_NO, k07,   k08,   k09,   k0A,   k0B,   KC_NO, KC_NO, k0E,   k0F,   k0G,   KC_NO, KC_NO, k0J   }, \
    {   k10,   k11,   k12,   KC_NO, k14,   k15,   k16,   k17,   k18,   k19,   k1A,   k1B,   k1C,   k1D,   k1E,   k1F,   k1G,   k1H,   k1I,   k1J   }, \
    {   k20,   k21,   KC_NO, KC_NO, k24,   k25,   k26,   k27,   k28,   k29,   k2A,   k2B,   k2C,   k2D,   k2E,   k2F,   k2G,   k2H,   k2I,   KC_NO }, \
    {   KC_NO, k31,   k32,   KC_NO, k34,   KC_NO, KC_NO, k37,   k38,   k39,   k3A,   k3B,   k3C,   KC_NO, k3E,   k3F,   k3G,   k3H,   KC_NO, KC_NO }, \
    {   k40,   k41,   k42,   KC_NO, k44,   k45,   k46,   k47,   k48,   k49,   k4A,   k4B,   k4C,   k4D,   k4E,   k4F,   k4G,   k4H,   k4I,   KC_NO }, \
    {   KC_NO, k51,   k52,   KC_NO, KC_NO, KC_NO, KC_NO, k57,   k58,   k59,   k5A,   k5B,   k5C,   KC_NO, k5E,   KC_NO, k5G,   KC_NO, KC_NO, KC_NO }, \
    {   k60,   k61,   k62,   k63,   k64,   k65,   k66,   k67,   k68,   k69,   k6A,   k6B,   k6C,   k6D,   k6E,   k6F,   KC_NO, k6H,   k6I,   KC_NO }, \
    {   k70,   k71,   k72,   k73,   k74,   KC_NO, KC_NO, k77,   k78,   k79,   k7A,   k7B,   KC_NO, KC_NO, k7E,   KC_NO, KC_NO, k7H,   k7I,   k7J   }, \
}
