/* Copyright 2019 worthlessowl
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
#define LAYOUT_owlet60_split_bsp( \
    k50, k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, \
    k51, k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      k1e, \
    k52, k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c,           k2d, \
         k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d,      k3e, \
         k40,      k41,      k42, k43, k44,           k45,          k46,  k47,      k48 \
) { \
    { k50, k11, k13, k15, k07, k19, k1b, k1d}, \
    { k51, k21, k23, k25, k17, k29, k2b, k3d}, \
    { k52, k31, k33, k35, k27, k39, k3b, k47}, \
    { k40, k41, k42, k43, k37, k45, k46, k48}, \
    { k30, k32, k34, k44, k38, k3a, k3c, k3e}, \
    { k20, k22, k24, k36, k28, k2a, k2c, k2d}, \
    { k10, k12, k14, k26, k18, k1a, k1c, k1e}, \
    { k00, k02, k04, k16, k08, k0a, k0c, k0f}, \
    { k01, k03, k05, k06, k09, k0b, k0d, k0e} \
}

#define LAYOUT_owlet60_full_bsp( \
    k50,  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,    k0d,   k0f, \
    k51,  k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      k1e, \
    k52,  k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c,           k2d, \
          k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d,      k3e, \
          k40,      k41,      k42, k43, k44,           k45,          k46,  k47,      k48 \
) { \
    { k50, k11, k13, k15, k07, k19, k1b, k1d}, \
    { k51, k21, k23, k25, k17, k29, k2b, k3d}, \
    { k52, k31, k33, k35, k27, k39, k3b, k47}, \
    { k40, k41, k42, k43, k37, k45, k46, k48}, \
    { k30, k32, k34, k44, k38, k3a, k3c, k3e}, \
    { k20, k22, k24, k36, k28, k2a, k2c, k2d}, \
    { k10, k12, k14, k26, k18, k1a, k1c, k1e}, \
    { k00, k02, k04, k16, k08, k0a, k0c, k0f}, \
    { k01, k03, k05, k06, k09, k0b, k0d, KC_NO} \
}

#define LAYOUT_alice_split_bs( \
    k50, k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k51, k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k52, k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c,           \
         k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d,      \
         k40,      k41,      k42, k43, k44,           k45,                k47      \
) { \
    { k50, k11, k13, k15, k07, k19, k1b, k1d}, \
    { k51, k21, k23, k25, k17, k29, k2b, k3d}, \
    { k52, k31, k33, k35, k27, k39, k3b, k47}, \
    { k40, k41, k42, k43, k37, k45, KC_NO, KC_NO}, \
    { k30, k32, k34, k44, k38, k3a, k3c, KC_NO}, \
    { k20, k22, k24, k36, k28, k2a, k2c, KC_NO}, \
    { k10, k12, k14, k26, k18, k1a, k1c, KC_NO}, \
    { k00, k02, k04, k16, k08, k0a, k0c, KC_NO}, \
    { k01, k03, k05, k06, k09, k0b, k0d, k0e} \
}

#define LAYOUT_alice( \
    k50, k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d,  \
    k51, k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,  \
    k52, k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c,       \
         k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d,  \
         k40,      k41,      k42, k43, k44,           k45,                k47  \
) { \
    { k50, k11, k13, k15, k07, k19, k1b, k1d}, \
    { k51, k21, k23, k25, k17, k29, k2b, k3d}, \
    { k52, k31, k33, k35, k27, k39, k3b, k47}, \
    { k40, k41, k42, k43, k37, k45, KC_NO, KC_NO}, \
    { k30, k32, k34, k44, k38, k3a, k3c, KC_NO}, \
    { k20, k22, k24, k36, k28, k2a, k2c, KC_NO}, \
    { k10, k12, k14, k26, k18, k1a, k1c, KC_NO}, \
    { k00, k02, k04, k16, k08, k0a, k0c, KC_NO}, \
    { k01, k03, k05, k06, k09, k0b, k0d, KC_NO} \
}

#define LAYOUT_owlet60_60_percent_split_bsp LAYOUT_alice_split_bs
#define LAYOUT_owlet60_60_percent_full_bsp LAYOUT_alice
