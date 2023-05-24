/* Copyright 2021 KnoblesseOblige
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

#define kxx KC_NO

/*
 * ┌───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┐ ┌───┬───┬───┐
 * │00 ││01 │02 │03 │04 ││05 │06 │07 │08 ││09 │0a │0b │0c ││0d │ │0e │0f │0g │
 * └───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┘ └───┴───┴───┘
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐ ┌───┬───┬───┐   ┌───────┐
 * │10 │11 │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │3d │ │1e │1f │1g │   │1d     │ 2u Backspace
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤ ├───┼───┼───┤   └───────┘
 * │20   │21 │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d   │ │2e │2f │2g │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘
 * │30    │31 │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3c      │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤     ┌───┐       ┌──────────┐
 * │40      │41 │42 │43 │44 │45 │46 │47 │48 │49 │4a │4b    │4d │     │4f │       │4b        │ 2.75u RShift
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬┴───┤ ┌───┼───┼───┐   └──────────┘
 * │50  │52  │53  │55                      │58  │59  │5a  │5b  │ │5e │5f │5g │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘
 * ┌─────┬───┬─────┬───────────────────────────┬─────┬───┬─────┐
 * │50   │52 │53   │55                         │59   │5a │5b   │ Tsangan/WKL
 * └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘
 */

#define LAYOUT_tkl_f13_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c,                     \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b,                k4f,      \
    k50,      k52, k53,      k55,           k58, k59, k5a, k5b,           k5e, k5f, k5g  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, kxx, kxx, kxx, kxx },  \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, kxx, kxx, kxx, k4f, kxx },  \
    { k50, kxx, k52, k53, kxx, k55, kxx, kxx, k58, k59, k5a, k5b, kxx, kxx, k5e, k5f, k5g }  \
}

#define LAYOUT_tkl_f13_ansi_split_bs_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d,        k0e, k0f, k0g, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k3d,   k1e, k1f, k1g, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,        k2e, k2f, k2g, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3c,                       \
    k40,      k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4d,             k4f,      \
    k50, k52, k53,                k55,                k58, k59, k5a, k5b,        k5e, k5f, k5g  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, kxx, kxx, kxx }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, kxx, k4d, kxx, k4f, kxx }, \
    { k50, kxx, k52, k53, kxx, k55, kxx, kxx, k58, k59, k5a, k5b, kxx, kxx, k5e, k5f, k5g }  \
}

#define LAYOUT_tkl_f13_ansi_tsangan( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d,   k0e, k0f, k0g, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,   k1e, k1f, k1g, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,   k2e, k2f, k2g, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3c,                  \
    k40,      k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a,      k4b,        k4f,      \
    k50, k52, k53,                k55,                     k59, k5a, k5b,   k5e, k5f, k5g  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, kxx, kxx, kxx, kxx }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, kxx, kxx, kxx, k4f, kxx }, \
    { k50, kxx, k52, k53, kxx, k55, kxx, kxx, kxx, k59, k5a, k5b, kxx, kxx, k5e, k5f, k5g }  \
}

#define LAYOUT_tkl_f13_ansi_tsangan_split_bs_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d,      k0e, k0f, k0g, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k3d, k1e, k1f, k1g, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      k2e, k2f, k2g, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c,                          \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b,      k4d,           k4f,      \
    k50,      k52, k53,      k55,                k59, k5a, k5b,                k5e, k5f, k5g  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, kxx, kxx, kxx },  \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, kxx, k4d, kxx, k4f, kxx },  \
    { k50, kxx, k52, k53, kxx, k55, kxx, kxx, kxx, k59, k5a, k5b, kxx, kxx, k5e, k5f, k5g }  \
}
