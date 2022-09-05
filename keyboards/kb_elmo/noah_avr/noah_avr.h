/* Copyright 2021 kb-elmo<mail@elmo.space>
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

#define ___ KC_NO

/*
 *              ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐      ┌───────┐
 *              │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0A │0B │0C │0D │0E │0F │      │0D     │ 2u Backspace
 *              ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤      └─┬─────┤
 *              │10   │11 │12 │13 │14 │15 │16 │17 │18 │19 │1A │1B │1C │1D   │1F │        │     │
 *  2.25u       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤     ┌──┴┐2D  │ ISO Enter
 *  LShift      │20    │21 │22 │23 │24 │25 │26 │27 │28 │29 │2A │2B │2D      │2F │     │1D │    │
 * ┌────────┐   ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤     └───┴────┘
 * │30      │   │30  │31 │32 │33 │34 │35 │36 │37 │38 │39 │3A │3B │3C    │3D │3F │
 * └────────┘   ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
 *              │40  │41  │42  │46                      │4B  │4C  │ │4D │4E │4F │
 *              └────┴────┴────┴────────────────────────┴────┴────┴─┴───┴───┴───┘
 *              ┌─────┬───┬─────┬───────────────────────────┬─────┐
 *              │40   │41 │42   │46                         │4C   │ Tsangan
 *              └─────┴───┴─────┴───────────────────────────┴─────┘
 */

#define LAYOUT_all( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1F, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B,      k2D, k2F, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3F, \
    k40, k41, k42,                k46,           k4B, k4C,      k4D, k4E, k4F  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, ___, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, ___, k2D, ___, k2F }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, ___, k3F }, \
    { k40, k41, k42, ___, ___, ___, k46, ___, ___, ___, ___, k4B, k4C, k4D, k4E, k4F }  \
}

#define LAYOUT_65_ansi_blocker( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0F, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1F, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B,      k2D, k2F, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3F, \
    k40, k41, k42,                k46,           k4B, k4C,      k4D, k4E, k4F  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, ___, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, ___, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, ___, k2D, ___, k2F }, \
    { k30, ___, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, ___, k3F }, \
    { k40, k41, k42, ___, ___, ___, k46, ___, ___, ___, ___, k4B, k4C, k4D, k4E, k4F }  \
}

#define LAYOUT_65_ansi_blocker_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1F, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B,      k2D, k2F, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3F, \
    k40, k41, k42,                k46,           k4B, k4C,      k4D, k4E, k4F  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, ___, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, ___, k2D, ___, k2F }, \
    { k30, ___, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, ___, k3F }, \
    { k40, k41, k42, ___, ___, ___, k46, ___, ___, ___, ___, k4B, k4C, k4D, k4E, k4F }  \
}

#define LAYOUT_65_iso_blocker( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0F, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C,      k1F, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k1D, k2D, k2F, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3F, \
    k40, k41, k42,                k46,           k4B, k4C,      k4D, k4E, k4F  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, ___, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, ___, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, ___, k2D, ___, k2F }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, ___, k3F }, \
    { k40, k41, k42, ___, ___, ___, k46, ___, ___, ___, ___, k4B, k4C, k4D, k4E, k4F }  \
}

#define LAYOUT_65_iso_blocker_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C,      k1F, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k1D, k2D, k2F, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3F, \
    k40, k41, k42,                k46,           k4B, k4C,      k4D, k4E, k4F  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, ___, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, ___, k2D, ___, k2F }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, ___, k3F }, \
    { k40, k41, k42, ___, ___, ___, k46, ___, ___, ___, ___, k4B, k4C, k4D, k4E, k4F }  \
}
