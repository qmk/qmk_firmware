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

#define LAYOUT_tkl_iso( \
    k11, k13, k14, k15, k16, k18, k19, k1A, k1B, k1C, k10, k1D, k12, k02, k03, k00,      \
    k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k20, k2D, k07, k06, k05, \
    k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k30, k0D, k09, k08,      \
    k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k3D, k40,                \
    k51, k4D, k52, k53, k54, k55, k56, k57, k58, k59, k5A, k5B, k5C, k5D,                \
    k61, k62, k63, k65, k69, k6A, k6B, k6C, k60, k6D, k68                                \
) \
{ \
   { k00,   KC_NO, k02, k03, KC_NO, k05, k06,   k07,   k08, k09, KC_NO, KC_NO, KC_NO, k0D   }, \
   { k10,   k11,   k12, k13, k14,   k15, k16,   KC_NO, k18, k19, k1A,   k1B,   k1C,   k1D   }, \
   { k20,   k21,   k22, k23, k24,   k25, k26,   k27,   k28, k29, k2A,   k2B,   k2C,   k2D   }, \
   { k30,   k31,   k32, k33, k34,   k35, k36,   k37,   k38, k39, k3A,   k3B,   k3C,   k3D   }, \
   { k40,   k41,   k42, k43, k44,   k45, k46,   k47,   k48, k49, k4A,   k4B,   k4C,   k4D   }, \
   { KC_NO, k51,   k52, k53, k54,   k55, k56,   k57,   k58, k59, k5A,   k5B,   k5C,   k5D   }, \
   { k60,   k61,   k62, k63, KC_NO, k65, KC_NO, KC_NO, k68, k69, k6A,   k6B,   k6C,   k6D   }, \
}

#define LAYOUT_tkl_ansi( \
    k11, k13, k14, k15, k16, k18, k19, k1A, k1B, k1C, k10, k1D, k12, k02, k03, k00,      \
    k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k20, k2D, k07, k06, k05, \
    k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k30, k3D, k0D, k09, k08, \
    k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k40,                     \
    k51, k52, k53, k54, k55, k56, k57, k58, k59, k5A, k5B, k5C, k5D,                     \
    k61, k62, k63, k65, k69, k6A, k6B, k6C, k60, k6D, k68                                \
) \
{ \
   { k00,   KC_NO, k02, k03, KC_NO, k05, k06,   k07,   k08, k09, KC_NO, KC_NO, KC_NO, k0D   }, \
   { k10,   k11,   k12, k13, k14,   k15, k16,   KC_NO, k18, k19, k1A,   k1B,   k1C,   k1D   }, \
   { k20,   k21,   k22, k23, k24,   k25, k26,   k27,   k28, k29, k2A,   k2B,   k2C,   k2D   }, \
   { k30,   k31,   k32, k33, k34,   k35, k36,   k37,   k38, k39, k3A,   k3B,   k3C,   k3D   }, \
   { k40,   k41,   k42, k43, k44,   k45, k46,   k47,   k48, k49, k4A,   k4B,   k4C,   KC_NO }, \
   { KC_NO, k51,   k52, k53, k54,   k55, k56,   k57,   k58, k59, k5A,   k5B,   k5C,   k5D   }, \
   { k60,   k61,   k62, k63, KC_NO, k65, KC_NO, KC_NO, k68, k69, k6A,   k6B,   k6C,   k6D   }, \
}
