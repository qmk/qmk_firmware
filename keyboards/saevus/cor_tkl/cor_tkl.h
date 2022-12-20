/* Copyright 2022 Ramon Imbao
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

// ANSI layout
// Full backspace
// Full right shift
// Full left shift
#define LAYOUT_tkl_f13_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3c,                \
    k40, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c,                k4f,      \
    k50, k51, k52,                k57,                k5a, k5b, k5c, k5d, k5e, k5f, k5g  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, ___, ___, ___, ___ }, \
    { k40, ___, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, ___, ___, k4f, ___ }, \
    { k50, k51, k52, ___, ___, ___, ___, k57, ___, ___, k5a, k5b, k5c, k5d, k5e, k5f, k5g }, \
}

// ANSI layout
// Split backspace
// Split right shift
// Full left shift
#define LAYOUT_tkl_f13_ansi_split_bs_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d,      k0e, k0f, k0g, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k3d, k1e, k1f, k1g, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      k2e, k2f, k2g, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3c,                     \
    k40,      k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, k4d,           k4f,      \
    k50, k51, k52,                k57,                k5a, k5b, k5c, k5d,      k5e, k5f, k5g  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, ___, ___, ___ }, \
    { k40, ___, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, k4d, ___, k4f, ___ }, \
    { k50, k51, k52, ___, ___, ___, ___, k57, ___, ___, k5a, k5b, k5c, k5d, k5e, k5f, k5g }, \
}

// ISO layout
// Full backspace
// Full right shift
// Split left shift
#define LAYOUT_tkl_f13_iso( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c,      k2e, k2f, k2g, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k2d,                \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c,                k4f,      \
    k50, k51, k52,                k57,                k5a, k5b, k5c, k5d, k5e, k5f, k5g  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, ___, ___, ___, ___ }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, ___, ___, k4f, ___ }, \
    { k50, k51, k52, ___, ___, ___, ___, k57, ___, ___, k5a, k5b, k5c, k5d, k5e, k5f, k5g }, \
}

// ISO layout
// Split backspace
// Split right shift
// Split left shift
#define LAYOUT_tkl_f13_iso_split_bs_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d,      k0e, k0f, k0g, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k3d, k1e, k1f, k1g, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c,           k2e, k2f, k2g, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k2d,                     \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, k4d,           k4f,      \
    k50, k51, k52,                k57,                k5a, k5b, k5c, k5d,      k5e, k5f, k5g  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, ___, ___, ___ }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, k4d, ___, k4f, ___ }, \
    { k50, k51, k52, ___, ___, ___, ___, k57, ___, ___, k5a, k5b, k5c, k5d, k5e, k5f, k5g }, \
}

// Layout for VIA
// Split backspace
// Split left shift
// Split right shift
#define LAYOUT_all( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d,      k0e, k0f, k0g, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k3d, k1e, k1f, k1g, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      k2e, k2f, k2g, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3c,                     \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, k4d,           k4f,      \
    k50, k51, k52,                     k57,           k5a, k5b, k5c, k5d,      k5e, k5f, k5g  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, ___, ___, ___ }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, k4d, ___, k4f, ___ }, \
    { k50, k51, k52, ___, ___, ___, ___, k57, ___, ___, k5a, k5b, k5c, k5d, k5e, k5f, k5g }  \
}
