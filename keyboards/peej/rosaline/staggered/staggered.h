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
 * ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
 * │00   │10 │01 │02 │12 │03 │13 │04 │14 │05 │06 │16 │07 │17   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │20    │11 │21 │22 │32 │23 │33 │24 │15 │25 │26 │36 │27      │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤   ┌───┬──────────┐                  ┌──────┬───┬───┐
 * │30      │31 │41 │42 │43 │53 │34 │44 │35 │45 │46 │37    │47 │   │46 │37        │ 1u/2.75u RShift  │46    │37 │47 │ 1.75u/1u/1u RShift
 * ├─────┬──┴┬──┴──┬┴───┴───┴─┬─┴───┴──┬┴──┬┴──┬┴──┬┴──┬───┼───┤   └───┴──────────┘                  └──────┴───┴───┘
 * │40   │50 │51   │52        │54      │55 │65 │56 │66 │57 │67 │
 * └─────┴───┴─────┴──────────┴────────┴───┴───┴───┴───┴───┴───┘
 *                 ┌───────────────────────────┬─────┬───┬─────┐
 *        7u Space │54                         │56   │66 │57   │ Tsangan Right Mods
 *                 └───────────────────────────┴─────┴───┴─────┘
 *                 ┌──────────┬───┬────────┬───┐
 *  2.75/1/2.25/1u │52        │54 │55      │65 │
 *                 └──────────┴───┴────────┴───┘
 */

#define LAYOUT_all( \
	k00, k10, k01, k02, k12, k03, k13, k04, k14, k05, k06, k16, k07, k17, \
	k20, k11, k21, k22, k32, k23, k33, k24, k15, k25, k26, k36,      k27, \
	k30,      k31, k41, k42, k43, k53, k34, k44, k35, k45, k46, k37, k47, \
	k40, k50, k51,           k52, k54,      k55, k65, k56, k66, k57, k67  \
) \
{ \
	{ k00, k01, k02, k03, k04, k05, k06, k07 }, \
	{ k10, k11, k12, k13, k14, k15, k16, k17 }, \
	{ k20, k21, k22, k23, k24, k25, k26, k27 }, \
	{ k30, k31, k32, k33, k34, k35, k36, k37 }, \
	{ k40, k41, k42, k43, k44, k45, k46, k47 }, \
	{ k50, k51, k52, k53, k54, k55, k56, k57 }, \
	{ XXX, XXX, XXX, XXX, XXX, k65, k66, k67 }, \
	{ XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX } \
}

#define LED1 C5
#define LED2 C4
