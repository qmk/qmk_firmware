/* Copyright 2018 Jack Humbert <jack.humb@gmail.com>
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

#include "planck.h"

#define LAYOUT_planck_1x2uC( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
    k30, k31, k32, k33, k34,    k36,   k37, k38, k39, k3a, k3b \
) \
{ \
    { k00, k01, k02, k03, k04, k05   }, \
    { k10, k11, k12, k13, k14, k15   }, \
    { k20, k21, k22, k23, k24, k25   }, \
    { k30, k31, k32, k39, k3a, k3b   }, \
    { k06, k07, k08, k09, k0a, k0b   }, \
    { k16, k17, k18, k19, k1a, k1b   }, \
    { k26, k27, k28, k29, k2a, k2b   }, \
    { k36, k37, k38, k33, k34, KC_NO } \
}

#define LAYOUT_planck_1x2uR( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
    k30, k31, k32, k33, k34, k35,   k37,    k38, k39, k3a, k3b \
) \
{ \
    { k00,   k01, k02, k03, k04, k05 }, \
    { k10,   k11, k12, k13, k14, k15 }, \
    { k20,   k21, k22, k23, k24, k25 }, \
    { k30,   k31, k32, k39, k3a, k3b }, \
    { k06,   k07, k08, k09, k0a, k0b }, \
    { k16,   k17, k18, k19, k1a, k1b }, \
    { k26,   k27, k28, k29, k2a, k2b }, \
    { KC_NO, k37, k38, k33, k34, k35 } \
}

#define LAYOUT_planck_1x2uL( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
    k30, k31, k32, k33,   k35,    k36, k37, k38, k39, k3a, k3b \
) \
{ \
    { k00, k01, k02, k03, k04,   k05 }, \
    { k10, k11, k12, k13, k14,   k15 }, \
    { k20, k21, k22, k23, k24,   k25 }, \
    { k30, k31, k32, k39, k3a,   k3b }, \
    { k06, k07, k08, k09, k0a,   k0b }, \
    { k16, k17, k18, k19, k1a,   k1b }, \
    { k26, k27, k28, k29, k2a,   k2b }, \
    { k36, k37, k38, k33, KC_NO, k35 } \
}

#define LAYOUT_planck_2x2u( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
    k30, k31, k32, k33,   k35,      k37,    k38, k39, k3a, k3b \
) \
{ \
    { k00,   k01, k02, k03, k04,   k05 }, \
    { k10,   k11, k12, k13, k14,   k15 }, \
    { k20,   k21, k22, k23, k24,   k25 }, \
    { k30,   k31, k32, k39, k3a,   k3b }, \
    { k06,   k07, k08, k09, k0a,   k0b }, \
    { k16,   k17, k18, k19, k1a,   k1b }, \
    { k26,   k27, k28, k29, k2a,   k2b }, \
    { KC_NO, k37, k38, k33, KC_NO, k35 } \
}

#define LAYOUT_ortho_4x12( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b \
) \
{ \
    { k00, k01, k02, k03, k04, k05 }, \
    { k10, k11, k12, k13, k14, k15 }, \
    { k20, k21, k22, k23, k24, k25 }, \
    { k30, k31, k32, k39, k3a, k3b }, \
    { k06, k07, k08, k09, k0a, k0b }, \
    { k16, k17, k18, k19, k1a, k1b }, \
    { k26, k27, k28, k29, k2a, k2b }, \
    { k36, k37, k38, k33, k34, k35 } \
}


#define LAYOUT LAYOUT_ortho_4x12
#define LAYOUT_planck_mit LAYOUT_planck_1x2uC
#define LAYOUT_planck_grid LAYOUT_ortho_4x12
