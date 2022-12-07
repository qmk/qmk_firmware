/* Copyright 2021 MechMerlin
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
 *              ┌───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┐ ┌───┬───┬───┐
 *              │00 ││01 │02 │03 │04 ││05 │06 │07 │08 ││09 │0A │0B │0C ││6A │ │0D │0E │6B │
 *              └───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┘ └───┴───┴───┘
 *              ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐ ┌───┬───┬───┐      ┌───────┐
 *              │10 │11 │12 │13 │14 │15 │16 │17 │18 │19 │1A │1B │1C │1D │1E │ │6C │6D │6E │      │1D     │ 2u Backspace
 *              ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤ ├───┼───┼───┤      └─┬─────┤
 *              │20   │21 │22 │23 │24 │25 │26 │27 │28 │29 │2A │2B │2C │2D   │ │7C │7D │7E │        │     │
 *  2.25u       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘     ┌──┴┐3D  │ ISO Enter
 *  LShift      │30    │31 │32 │33 │34 │35 │36 │37 │38 │39 │3A │3B │3D      │                   │3C │    │
 * ┌────────┐   ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤     ┌───┐       ┌─┴───┴────┤
 * │40      │   │40  │41 │42 │43 │44 │45 │46 │47 │48 │49 │4A │4B │4C    │4D │     │2E │       │4C        │ 2.75u RShift
 * └────────┘   ├────┼───┼───┼───┴┬──┴─┬─┴──┬┴───┼───┴┬──┴─┬─┴─┬─┴─┬───┬┴───┤ ┌───┼───┼───┐   └──────────┘
 *              │50  │51 │52 │53  │54  │55  │57  │58  │59  │5A │5B │5C │5D  │ │5E │3E │4E │
 *              └────┴───┴───┴────┴────┴────┴────┴────┴────┴───┴───┴───┴────┘ └───┴───┴───┘
 *              ┌────┬────┬────┬────────────────────────┬────┬────┬────┬────┐
 *              │50  │51  │52  │55                      │58  │59  │5A  │5D  │ Standard
 *              └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 *              ┌─────┬───┬─────┬───────────────────────────┬─────┬───┬─────┐
 *              │50   │51 │52   │55                         │58   │59 │5A   │ Tsangan/WKL
 *              └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘
 *
 * I'm not entirely convinced the LAYOUT_all bottom row is accurate, but it's
 * what was already in the code.
 *                                                               - @noroadsleft
 *                                                                 2022-12-07
 */

#define LAYOUT_all_f13( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k6A,        k0D, k0E, k6B, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E,   k6C, k6D, k6E, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D,        k7C, k7D, k7E, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D,                       \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D,             k2E,      \
    k50, k51, k52, k53, k54, k55,      k57, k58, k59, k5A, k5B, k5C, k5D,        k5E, k3E, k4E  \
){ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E }, \
    { k50, k51, k52, k53, k54, k55, XXX, k57, k58, k59, k5A, k5B, k5C, k5D, k5E }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, k6A, k6B, k6C, k6D, k6E }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, k7C, k7D, k7E }  \
}


#define LAYOUT_tkl_f13_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k6A,   k0D, k0E, k6B, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D,   k6C, k6D, k6E, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D,   k7C, k7D, k7E, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D,                  \
    k40,      k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B,      k4C,        k2E,      \
    k50, k51, k52,                k55,                k58, k59, k5A, k5D,   k5E, k3E, k4E  \
){ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, XXX, k3D, k3E }, \
    { k40, XXX, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, XXX, k4E }, \
    { k50, k51, k52, XXX, XXX, k55, XXX, XXX, k58, k59, k5A, XXX, XXX, k5D, k5E }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, k6A, k6B, k6C, k6D, k6E }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, k7C, k7D, k7E }  \
}

#define LAYOUT_tkl_f13_ansi_tsangan( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k6A,   k0D, k0E, k6B, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D,   k6C, k6D, k6E, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D,   k7C, k7D, k7E, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D,                  \
    k40,      k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B,      k4C,        k2E,      \
    k50, k51, k52,                k55,                     k58, k59, k5A,   k5E, k3E, k4E  \
){ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, XXX, k3D, k3E }, \
    { k40, XXX, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, XXX, k4E }, \
    { k50, k51, k52, XXX, XXX, k55, XXX, XXX, k58, k59, k5A, XXX, XXX, XXX, k5E }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, k6A, k6B, k6C, k6D, k6E }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, k7C, k7D, k7E }  \
}

#define LAYOUT_tkl_f13_ansi_tsangan_split_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k6A,   k0D, k0E, k6B, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D,   k6C, k6D, k6E, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D,   k7C, k7D, k7E, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D,                  \
    k40,      k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D,        k2E,      \
    k50, k51, k52,                k55,                     k58, k59, k5A,   k5E, k3E, k4E  \
){ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, XXX, k3D, k3E }, \
    { k40, XXX, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E }, \
    { k50, k51, k52, XXX, XXX, k55, XXX, XXX, k58, k59, k5A, XXX, XXX, XXX, k5E }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, k6A, k6B, k6C, k6D, k6E }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, k7C, k7D, k7E }  \
}

#define LAYOUT_tkl_f13_iso( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k6A,   k0D, k0E, k6B, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D,   k6C, k6D, k6E, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C,        k7C, k7D, k7E, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D,                  \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B,      k4C,        k2E,      \
    k50, k51, k52,                k55,                k58, k59, k5A, k5D,   k5E, k3E, k4E  \
){ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, XXX, k2E }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, XXX, k4E }, \
    { k50, k51, k52, XXX, XXX, k55, XXX, XXX, k58, k59, k5A, XXX, XXX, k5D, k5E }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, k6A, k6B, k6C, k6D, k6E }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, k7C, k7D, k7E }  \
}

#define LAYOUT_tkl_f13_iso_tsangan( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k6A,   k0D, k0E, k6B, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D,   k6C, k6D, k6E, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C,        k7C, k7D, k7E, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D,                  \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B,      k4C,        k2E,      \
    k50, k51, k52,                k55,                     k58, k59, k5A,   k5E, k3E, k4E  \
){ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, XXX, k2E }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, XXX, k4E }, \
    { k50, k51, k52, XXX, XXX, k55, XXX, XXX, k58, k59, k5A, XXX, XXX, XXX, k5E }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, k6A, k6B, k6C, k6D, k6E }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, k7C, k7D, k7E }  \
}

#define LAYOUT_tkl_f13_iso_tsangan_split_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k6A,   k0D, k0E, k6B, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D,   k6C, k6D, k6E, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C,        k7C, k7D, k7E, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D,                  \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D,        k2E,      \
    k50, k51, k52,                k55,                     k58, k59, k5A,   k5E, k3E, k4E  \
){ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, XXX, k2E }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E }, \
    { k50, k51, k52, XXX, XXX, k55, XXX, XXX, k58, k59, k5A, XXX, XXX, XXX, k5E }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, k6A, k6B, k6C, k6D, k6E }, \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, k7C, k7D, k7E }  \
}
