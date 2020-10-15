/**
  * dp60.h
  *
  Copyright 2020 astro <yuleiz@gmail.com>
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

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define LAYOUT_60_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0e, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, \
	k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2e, \
	k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, \
	k40,      k42, k43,                k47, k48, k49, k4a, k4b       \
) \
{ \
    {k00,   k01, k02,   k03,   k04,   k05, k06, k08,   k09,   k0a, k0b, k0c, KC_NO, k0e}, \
    {k10,   k11, k12,   k13,   k14,   k15, k16, k17,   k18,   k19, k1a, k1b,   k1c, k1e}, \
    {k20,   k22, k23,   k24,   k25,   k26, k27, k28,   k29,   k2a, k2b, k2c, KC_NO, k2e}, \
    {k30, KC_NO, k32,   k33,   k34,   k35, k36, k37,   k38,   k39, k3a, k3b,   k3c, KC_NO}, \
    {k40,   k42, k43, KC_NO, KC_NO, KC_NO, k47, k07, KC_NO, KC_NO, k48, k49,   k4a, k4b}  \
}

#define LAYOUT_60_iso( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0e, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, \
	k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, \
	k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c,\
	k40,      k42, k43,                k47, k48, k49, k4a, k4b       \
) \
{ \
    {k00,   k01, k02,   k03,   k04,   k05, k06, k08,   k09,   k0a, k0b, k0c, KC_NO, k0e}, \
    {k10,   k11, k12,   k13,   k14,   k15, k16, k17,   k18,   k19, k1a, k1b,   k1c, KC_NO}, \
    {k20,   k22, k23,   k24,   k25,   k26, k27, k28,   k29,   k2a, k2b, k2c,   k2d, k2e}, \
    {k30,   k31, k32,   k33,   k34,   k35, k36, k37,   k38,   k39, k3a, k3b,   k3c, KC_NO}, \
    {k40,   k42, k43, KC_NO, KC_NO, KC_NO, k47, k07, KC_NO, KC_NO, k48, k49,   k4a, k4b}  \
}

#define LAYOUT_60_wkl( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0e, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, \
	k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2e, \
	k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, \
	k40,      k42, k43,                k47,      k49, k4a, k4b       \
) \
{ \
    {k00,   k01, k02,   k03,   k04,   k05, k06, k08,   k09,   k0a,   k0b, k0c, KC_NO, k0e}, \
    {k10,   k11, k12,   k13,   k14,   k15, k16, k17,   k18,   k19,   k1a, k1b,   k1c, k1e}, \
    {k20,   k22, k23,   k24,   k25,   k26, k27, k28,   k29,   k2a,   k2b, k2c, KC_NO, k2e}, \
    {k30, KC_NO, k32,   k33,   k34,   k35, k36, k37,   k38,   k39,   k3a, k3b,   k3c, k3d}, \
    {k40,   k42, k43, KC_NO, KC_NO, KC_NO, k47, k07, KC_NO, KC_NO, KC_NO, k49,   k4a, k4b}  \
}

#define LAYOUT_60_hhkb( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, \
	k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2e, \
	k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, \
       k42, k43,                     k47,                k49, k4a \
) \
{ \
    {k00,   k01, k02,   k03,   k04,   k05, k06, k08,   k09,   k0a, k0b, k0c,   k0d, k0e}, \
    {k10,   k11, k12,   k13,   k14,   k15, k16, k17,   k18,   k19, k1a, k1b,   k1c, k1e}, \
    {k20,   k22, k23,   k24,   k25,   k26, k27, k28,   k29,   k2a, k2b, k2c, KC_NO, k2e}, \
    {k30, KC_NO, k32,   k33,   k34,   k35, k36, k37,   k38,   k39, k3a, k3b,   k3c, k3d}, \
    {KC_NO, k42, k43, KC_NO, KC_NO, KC_NO, k47, k07, KC_NO, KC_NO, KC_NO, k49,   k4a, KC_NO}  \
}
#define LAYOUT_60_wkl_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, \
	k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2e, \
	k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, \
	k40,      k42, k43,                k47,      k49, k4a, k4b       \
) \
{ \
    {k00,   k01, k02,   k03,   k04,   k05, k06, k08,   k09,   k0a,   k0b, k0c,   k0d, k0e}, \
    {k10,   k11, k12,   k13,   k14,   k15, k16, k17,   k18,   k19,   k1a, k1b,   k1c, k1e}, \
    {k20,   k22, k23,   k24,   k25,   k26, k27, k28,   k29,   k2a,   k2b, k2c, KC_NO, k2e}, \
    {k30, KC_NO, k32,   k33,   k34,   k35, k36, k37,   k38,   k39,   k3a, k3b,   k3c, k3d}, \
    {k40,   k42, k43, KC_NO, KC_NO, KC_NO, k47, k07, KC_NO, KC_NO, KC_NO, k49,   k4a, k4b}  \
}
#define LAYOUT_60_ansi_split_bs_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e, \
	k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2e, \
	k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, \
	k40,      k42, k43,                k47,      k48,  k49, k4a, k4b       \
) \
{ \
    {k00,   k01, k02,   k03,   k04,   k05, k06, k08,   k09,   k0a, k0b, k0c,   k0d, k0e}, \
    {k10,   k11, k12,   k13,   k14,   k15, k16, k17,   k18,   k19, k1a, k1b,   k1c, k1e}, \
    {k20,   k22, k23,   k24,   k25,   k26, k27, k28,   k29,   k2a, k2b, k2c, KC_NO, k2e}, \
    {k30, KC_NO, k32,   k33,   k34,   k35, k36, k37,   k38,   k39, k3a, k3b,   k3c, k3d}, \
    {k40,   k42, k43, KC_NO, KC_NO, KC_NO, k47, k07, KC_NO, KC_NO, k48, k49,   k4a, k4b}  \
}
