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

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │00 │40 │01 │41 │02 │42 │03 │43 │04 │44 │05 │45 │06 │46 │07 │
 * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
 * │10 │50 │11 │51 │12 │52 │13 │53 │14 │54 │15 │55 │16 │56 │17 │
 * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
 * │20 │60 │21 │61 │22 │62 │23 │63 │24 │64 │25 │65 │26 │66 │27 │
 * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
 * │30 │70 │31 │71 │32 │72 │33 │73 │34 │74 │35 │75 │36 │76 │37 │
 * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
 *                 ┌───────────────────────────┐
 *                 │73                         │ 7u Space
 *                 └───────────────────────────┘
 *                 ┌───────┐           ┌───────┐
 *         2u Left │32     │           │35     │ 2u Right
 *                 └───────┘           └───────┘
 */

#define LAYOUT_ortho_4x15( \
	k00, k40, k01, k41, k02, k42, k03, k43, k04, k44, k05, k45, k06, k46, k07, \
	k10, k50, k11, k51, k12, k52, k13, k53, k14, k54, k15, k55, k16, k56, k17, \
	k20, k60, k21, k61, k22, k62, k23, k63, k24, k64, k25, k65, k26, k66, k27, \
	k30, k70, k31, k71, k32, k72, k33, k73, k34, k74, k35, k75, k36, k76, k37  \
) \
{ \
	{ k00, k01, k02, k03, k04, k05, k06, k07 }, \
	{ k10, k11, k12, k13, k14, k15, k16, k17 }, \
	{ k20, k21, k22, k23, k24, k25, k26, k27 }, \
	{ k30, k31, k32, k33, k34, k35, k36, k37 }, \
	{ k40, k41, k42, k43, k44, k45, k46, XXX }, \
	{ k50, k51, k52, k53, k54, k55, k56, XXX }, \
	{ k60, k61, k62, k63, k64, k65, k66, XXX }, \
	{ k70, k71, k72, k73, k74, k75, k76, XXX } \
}

#define LED1 C5
#define LED2 C4
