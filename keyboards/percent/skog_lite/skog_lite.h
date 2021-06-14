/* Copyright 2019 mechmerlin
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

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array

#define LAYOUT_tkl_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k6c,       \
    k10, k1e, k11, k12, k13, k14, k1d, k15, k16, k17, k18, k19, k1a, k1b, k1c, k6b, k6a,  \
    k20, k2e, k21, k22, k23, k24, k2d, k25, k26, k27, k28, k29, k2a, k2b, k2c, k69, k68,  \
    k30, k3e, k31, k32, k33, k34, k3d, k35, k36, k37, k38, k39, k3a,                      \
    k40, k4e, k41, k42, k43, k44, k4d, k45, k46, k47, k48, k4b, k4c,                      \
    k50, k5e, k51, k54, k56, k57, k58, k5b, k5a, k5c, k67                                 \
){ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e },  \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e },  \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e },  \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, ___, ___, k3d, k3e },  \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, ___, ___, k4b, k4c, k4d, k4e },  \
    { k50, k51, ___, ___, k54, ___, k56, k57, k58, ___, k5a, k5b, k5c, ___, k5e },  \
    { ___, ___, ___, ___, ___, ___, ___, k67, k68, k69, k6a, k6b, k6c, ___, ___ },  \
}

#define LAYOUT_tkl_7u_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k6c,       \
    k10, k1e, k11, k12, k13, k14, k1d, k15, k16, k17, k18, k19, k1a, k1b, k1c, k6b, k6a,  \
    k20, k2e, k21, k22, k23, k24, k2d, k25, k26, k27, k28, k29, k2a, k2b, k2c, k69, k68,  \
    k30, k3e, k31, k32, k33, k34, k3d, k35, k36, k37, k38, k39, k3a,                      \
    k40, k4e, k41, k42, k43, k44, k4d, k45, k46, k47, k48, k4b, k4c,                      \
    k50, k5e, k51, k54, k57, k58, k5b, k5a, k5c, k67                                      \
){ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e },  \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e },  \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e },  \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, ___, ___, k3d, k3e },  \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, ___, ___, k4b, k4c, k4d, k4e },  \
    { k50, k51, ___, ___, k54, ___, ___, k57, k58, ___, k5a, k5b, k5c, ___, k5e },  \
    { ___, ___, ___, ___, ___, ___, ___, k67, k68, k69, k6a, k6b, k6c, ___, ___ },  \
}

#define LAYOUT_tkl_7u_ansi_blocker( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k6c,       \
    k10, k1e, k11, k12, k13, k14, k1d, k15, k16, k17, k18, k19, k1a, k1b, k1c, k6b, k6a,  \
    k20, k2e, k21, k22, k23, k24, k2d, k25, k26, k27, k28, k29, k2a, k2b, k2c, k69, k68,  \
    k30, k3e, k31, k32, k33, k34, k3d, k35, k36, k37, k38, k39, k3a,                      \
    k40, k4e, k41, k42, k43, k44, k4d, k45, k46, k47, k48, k4b, k4c,                      \
    k50, k51, k54, k57, k5b, k5a, k5c, k67                                                \
){ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e },  \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e },  \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e },  \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, ___, ___, k3d, k3e },  \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, ___, ___, k4b, k4c, k4d, k4e },  \
    { k50, k51, ___, ___, k54, ___, ___, k57, ___, ___, k5a, k5b, k5c, ___, ___ },  \
    { ___, ___, ___, ___, ___, ___, ___, k67, k68, k69, k6a, k6b, k6c, ___, ___ },  \
}
