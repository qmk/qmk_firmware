/* Copyright 2021 Paul James
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

#include "rosaline.h"

#define LAYOUT_all( \
	k00, k01, k10, k20, k21, k30, k31, k40, k41, k50, k60, k61, k70, k71, \
	k02, k11, k12, k22, k23, k32, k33, k42, k51, k52, k62, k63, k72, \
	k03, k13, k14, k24, k34, k35, k43, k44, k53, k54, k64, k73, k74, \
	k04, k05, k15, k25, k45, k55, k56, k65, k66, k75, k76 \
) \
{ \
	{ k00, k10, k20, k30, k40, k50, k60, k70 }, \
	{ k01, k11, k21, k31, k41, k51, k61, k71 }, \
	{ k02, k12, k22, k32, k42, k52, k62, k72 }, \
	{ k03, k13, k23, k33, k43, k53, k63, k73 }, \
	{ k04, k14, k24, k34, k44, k54, k64, k74 }, \
	{ k05, k15, k25, k35, k45, k55, k65, k75 }, \
	{ XXX, XXX, XXX, XXX, XXX, k56, k66, k76 }, \
	{ XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX } \
}

#define LED1 C5
#define LED2 C4
