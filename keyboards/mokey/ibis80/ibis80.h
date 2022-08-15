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
 *  ┌───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┐ ┌───┬───┬───┐
 *  │00 ││01 │02 │03 │04 ││05 │06 │07 │08 ││09 │0A │0B │0C ││0D │ │0E │0F │0G │
 *  └───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┘ └───┴───┴───┘
 *  ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
 *  │10 │11 │12 │13 │14 │15 │16 │17 │18 │19 │1A │1B │1C │1D     │ │1E │1F │1G │
 *  ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤    ┌─────┐
 *  │20   │21 │22 │23 │24 │25 │26 │27 │28 │29 │2A │2B │2C │2D   │ │2E │2F │2G │    │3D   │
 *  ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘ ┌──┴┐    │ ISO Enter
 *  │30    │31 │32 │33 │34 │35 │36 │37 │38 │39 │3A │3B │3D      │               │2D │    │
 *  ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐     └───┴────┘
 *  │40      │41 │42 │43 │44 │45 │46 │47 │48 │49 │4A │4D        │     │4F │     
 *  ├─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─────┤ ┌───┼───┼───┐ 
 *  │50   │51 │52   │56                         │5A   │5B │5D   │ │5E │5F │5G │
 *  └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘ └───┴───┴───┘           
 *  ┌─────┐   ┌─────┬───────────────────────────┬─────┐   ┌─────┐
 *  │50   │   │52   │56                         │5A   │   │5D   │
 *  └─────┘   └─────┴───────────────────────────┴─────┘   └─────┘
 */

#define LAYOUT(\
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a,           k4d,      k4f, \
    k50, k51, k52,                k56,                k5a, k5b,      k5d, k5e, k5f, k5g \
) \
{ \
    { k00, k01, k02, k03,   k04,   k05,   k06, k07,   k08,   k09,   k0a, k0b,   k0c,   k0d, k0e,   k0f,   k0g }, \
    { k10, k11, k12, k13,   k14,   k15,   k16, k17,   k18,   k19,   k1a, k1b,   k1c,   k1d, k1e,   k1f,   k1g }, \
    { k20, k21, k22, k23,   k24,   k25,   k26, k27,   k28,   k29,   k2a, k2b,   k2c,   k2d, k2e,   k2f,   k2g }, \
    { k30, k31, k32, k33,   k34,   k35,   k36, k37,   k38,   k39,   k3a, k3b,   KC_NO, k3d, KC_NO, KC_NO, KC_NO }, \
    { k40, k41, k42, k43,   k44,   k45,   k46, k47,   k48,   k49,   k4a, KC_NO, KC_NO, k4d, KC_NO, k4f,   KC_NO },  \
    { k50, k51, k52, KC_NO, KC_NO, KC_NO, k56, KC_NO, KC_NO, KC_NO, k5a, k5b,   KC_NO,   k5d, k5e,   k5f,   k5g }  \
}

#define LAYOUT_all(\
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k3d, k2e, k2f, k2g, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k2d, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a,           k4d,      k4f, \
    k50,      k52,                k56,                k5a,           k5d, k5e, k5f, k5g \
) \
{ \
    { k00, k01,   k02, k03,   k04,   k05,   k06, k07,   k08,   k09,   k0a, k0b,   k0c,   k0d,   k0e,   k0f,   k0g }, \
    { k10, k11,   k12, k13,   k14,   k15,   k16, k17,   k18,   k19,   k1a, k1b,   k1c,   k1d,   k1e,   k1f,   k1g }, \
    { k20, k21,   k22, k23,   k24,   k25,   k26, k27,   k28,   k29,   k2a, k2b,   k2c,   k3d,   k2e,   k2f,   k2g }, \
    { k30, k31,   k32, k33,   k34,   k35,   k36, k37,   k38,   k39,   k3a, k3b,   KC_NO, k2d,   KC_NO, KC_NO, KC_NO }, \
    { k40, k41,   k42, k43,   k44,   k45,   k46, k47,   k48,   k49,   k4a, KC_NO, KC_NO, k4d,   KC_NO, k4f,   KC_NO },  \
    { k50, KC_NO, k52, KC_NO, KC_NO, KC_NO, k56, KC_NO, KC_NO, KC_NO, k5a, KC_NO, KC_NO, k5d,   k5e,   k5f,   k5g }  \
}

