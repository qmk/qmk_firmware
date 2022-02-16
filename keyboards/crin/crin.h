/*
Copyright 2020 KnoblesseOblige

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum.h"

#define kxx KC_NO

/*
 *                                                                  ┌───────┐
 *                                                     2u Backspace │0d     │
 *                                                                  └───────┘
 *              ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐ ┌───┬───┬───┐
 *              │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0d │2d │ │0e │0f │0g │
 *              ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤ ├───┼───┼───┤        ┌─────┐
 *              │10   │11 │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d   │ │1e │1f │1g │        │     │ ISO
 *  2.25u       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘     ┌──┴┐2c  │ Enter
 *  LShift      │20    │21 │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c      │                   │1d │    │
 * ┌────────┐   ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤     ┌───┐       ┌─┴───┴────┤
 * │30      │   │30  │41 │31 │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b    │3d │     │3f │       │3b        │ 2.75u RShift
 * └────────┘   ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬┴───┤ ┌───┼───┼───┐   └──────────┘
 *              │40  │42  │43  │           45           │49  │4a  │4b  │4d  │ │4e │4f │4g │
 *              └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘
 *              ┌─────┬───┬─────┬───────────────────────────┬─────┬───┬─────┐
 *              │40   │42 │43   │            45             │4a   │4b │4d   │ Tsangan
 *              └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘
 */

#define LAYOUT_all( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k2d,   k0e, k0f, k0g, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,        k1e, k1f, k1g, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2c,                       \
    k30, k41, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3d,             k3f,      \
    k40, k42, k43,                k45,                k49, k4a, k4b, k4d,        k4e, k4f, k4g  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, kxx, kxx, kxx }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, kxx, k3d, kxx, k3f, kxx }, \
    { k40, k41, k42, k43, kxx, k45, kxx, kxx, kxx, k49, k4a, k4b, kxx, k4d, k4e, k4f, k4g } \
}

#define LAYOUT_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d,   k0e, k0f, k0g, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,   k1e, k1f, k1g, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2c,                  \
    k30,      k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a,      k3b,        k3f,      \
    k40, k42, k43,                k45,                k49, k4a, k4b, k4d,   k4e, k4f, k4g  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, kxx, kxx, kxx, kxx }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, kxx, kxx, kxx, k3f, kxx }, \
    { k40, kxx, k42, k43, kxx, k45, kxx, kxx, kxx, k49, k4a, k4b, kxx, k4d, k4e, k4f, k4g } \
}

#define LAYOUT_ansi_tsangan( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d,   k0e, k0f, k0g, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,   k1e, k1f, k1g, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2c,                  \
    k30,      k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a,      k3b,        k3f,      \
    k40, k42, k43,                k45,                     k4a, k4b, k4d,   k4e, k4f, k4g  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, kxx, kxx, kxx, kxx }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, kxx, kxx, kxx, k3f, kxx }, \
    { k40, kxx, k42, k43, kxx, k45, kxx, kxx, kxx, kxx, k4a, k4b, kxx, k4d, k4e, k4f, k4g } \
}

#define LAYOUT_iso( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d,   k0e, k0f, k0g, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,        k1e, k1f, k1g, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k1d, k2c,                  \
    k30, k41, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a,      k3b,        k3f,      \
    k40, k42, k43,                k45,                k49, k4a, k4b, k4d,   k4e, k4f, k4g  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, kxx, kxx, kxx, kxx }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, kxx, kxx, kxx, k3f, kxx }, \
    { k40, k41, k42, k43, kxx, k45, kxx, kxx, kxx, k49, k4a, k4b, kxx, k4d, k4e, k4f, k4g } \
}

#define LAYOUT_iso_tsangan( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d,   k0e, k0f, k0g, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,        k1e, k1f, k1g, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k1d, k2c,                  \
    k30, k41, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a,      k3b,        k3f,      \
    k40, k42, k43,                k45,                     k4a, k4b, k4d,   k4e, k4f, k4g  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, kxx, kxx, kxx, kxx }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, kxx, kxx, kxx, k3f, kxx }, \
    { k40, k41, k42, k43, kxx, k45, kxx, kxx, kxx, kxx, k4a, k4b, kxx, k4d, k4e, k4f, k4g } \
}
