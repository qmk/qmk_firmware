/* Copyright 2021 Ocean
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

#define XXX KC_NO

/*
 *                                                                ┌───────┐
 *                                                                │0E     │ 2u Backspace
 *                                                                └───────┘
 *            ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐ ┌───┬───┬───┐
 *            │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0A │0B │0C │0D │0E │ │0F │0G │0H │
 *            ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤ ├───┼───┼───┤    ┌─────┐
 *            │10   │12 │13 │14 │15 │16 │17 │18 │19 │1A │1B │1C │1D │1E   │ │1F │1G │1H │    │2D   │
 *            ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘ ┌──┴┐    │ ISO Enter
 *            │20    │22 │23 │24 │25 │26 │27 │28 │29 │2A │2B │2C │2D      │               │1E │    │
 * ┌────────┐ ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤     ┌───┐     ├───┴────┴─┐
 * │30      │ │30  │31 │32 │33 │34 │35 │36 │37 │38 │39 │3A │3B │3D    │3E │     │3G │     │3D        │
 * └────────┘ ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬┴───┤ ┌───┼───┼───┐ └──────────┘
 *            │40  │41  │43  │46                      │4A  │4B  │4D  │4E  │ │4F │4G │4H │
 *            └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘
 *            ┌─────┬───┬─────┬───────────────────────────┬─────┬───┬─────┐
 *            │40   │41 │43   │46                         │4B   │4D │4E   │
 *            └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘
 *            ┌─────┐   ┌─────┬───────────┬───┬───────────┬─────┐   ┌─────┐
 *            │40   │   │43   │44         │46 │48         │4B   │   │4E   │
 *            └─────┘   └─────┴───────────┴───┴───────────┴─────┘   └─────┘
 */

#define LAYOUT_all( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E,   k0F, k0G, k0H, \
    k10, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E,        k1F, k1G, k1H, \
    k20, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C,      k2D, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3D, k3E,             k3G, \
    k40, k41, k43,           k44, k46, k48,           k4A, k4B, k4D, k4E,        k4F, k4G, k4H \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, k0G, k0H }, \
    { k10, XXX, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H }, \
    { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, XXX, XXX, XXX, XXX }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, XXX, k3D, k3E, XXX, k3G, XXX }, \
    { k40, k41, XXX, k43, k44, XXX, k46, XXX, k48, XXX, k4A, k4B, XXX, k4D, k4E, k4F, k4G, k4H } \
}

#define LAYOUT_tkl_nofrow_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0E,   k0F, k0G, k0H, \
    k10, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E,   k1F, k1G, k1H, \
    k20, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C,      k2D, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D,        k3G, \
    k40, k41, k43,                k46,                k4A, k4B, k4D, k4E,   k4F, k4G, k4H \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, XXX, k0E, k0F, k0G, k0H }, \
    { k10, XXX, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H }, \
    { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, XXX, XXX, XXX, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, XXX, k3D, XXX, XXX, k3G, XXX }, \
    { k40, k41, XXX, k43, XXX, XXX, k46, XXX, XXX, XXX, k4A, k4B, XXX, k4D, k4E, k4F, k4G, k4H } \
}

#define LAYOUT_tkl_nofrow_iso( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0E,   k0F, k0G, k0H, \
    k10, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D,        k1F, k1G, k1H, \
    k20, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k1E, k2D, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D,        k3G, \
    k40, k41, k43,                k46,                k4A, k4B, k4D, k4E,   k4F, k4G, k4H \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, XXX, k0E, k0F, k0G, k0H }, \
    { k10, XXX, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H }, \
    { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, XXX, XXX, XXX, XXX }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, XXX, k3D, XXX, XXX, k3G, XXX }, \
    { k40, k41, XXX, k43, XXX, XXX, k46, XXX, XXX, XXX, k4A, k4B, XXX, k4D, k4E, k4F, k4G, k4H } \
}

#define LAYOUT_tkl_nofrow_ansi_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E,   k0F, k0G, k0H, \
    k10, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E,        k1F, k1G, k1H, \
    k20, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C,      k2D, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D,             k3G, \
    k40, k41, k43,                k46,                k4A, k4B, k4D, k4E,        k4F, k4G, k4H \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, k0G, k0H }, \
    { k10, XXX, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H }, \
    { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, XXX, XXX, XXX, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, XXX, k3D, XXX, XXX, k3G, XXX }, \
    { k40, k41, XXX, k43, XXX, XXX, k46, XXX, XXX, XXX, k4A, k4B, XXX, k4D, k4E, k4F, k4G, k4H } \
}

#define LAYOUT_tkl_nofrow_iso_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E,   k0F, k0G, k0H, \
    k10, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D,             k1F, k1G, k1H, \
    k20, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k1E, k2D, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D,             k3G, \
    k40, k41, k43,                k46,                k4A, k4B, k4D, k4E,        k4F, k4G, k4H \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, k0G, k0H }, \
    { k10, XXX, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H }, \
    { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, XXX, XXX, XXX, XXX }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, XXX, k3D, XXX, XXX, k3G, XXX }, \
    { k40, k41, XXX, k43, XXX, XXX, k46, XXX, XXX, XXX, k4A, k4B, XXX, k4D, k4E, k4F, k4G, k4H } \
}
