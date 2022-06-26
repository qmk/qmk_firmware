/* Copyright 2021 Ibnu D. Aji
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
#define XXX KC_NO
#define LAYOUT( \
	k1,  k6,  k10, k15, k19, k24, k28, k33, k37, k42, k46, k51, k55, k60, k64, k65, \
	k2,  k7,  k11, k16, k20, k25, k29, k34, k38, k43, k47, k52, k56, k61,      k66, \
	k3,  k8,  k12, k17, k21, k26, k30, k35, k39, k44, k48, k53, k57,           k62, \
	k4,  k9,  k13, k18, k22, k27, k31, k36, k40, k45, k49, k54,      k58,           \
	k5,       k14,      k23, k32,      k41,      k50,           k59, k63, k67       \
) \
{ \
	{ k1, k10, k19, k28, k37, k46, k55, k64 }, \
	{ k6, k15, k24, k33, k42, k51, k60, XXX }, \
	{ k2, k11, k20, k29, k38, k47, k56, k65 }, \
	{ k7, k16, k25, k34, k43, k52, k61, XXX }, \
	{ k3, k12, k21, k30, k39, k48, k57, k66 }, \
	{ k8, k17, k26, k35, k44, k53, k62, XXX }, \
	{ k4, k13, k22, k31, k40, k49, k58, k67 }, \
	{ k9, k18, k27, k36, k45, k54, k63, XXX }, \
	{ k5, k14, k23, k32, k41, k50, k59, XXX }  \
}
