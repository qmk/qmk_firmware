/* Copyright 2017 MechMerlin <mechmerlin@gmail.com>
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

#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k3b,  \
    k10, k1f, k11, k12, k13, k14, k110, k15, k16, k17, k18, k19, k1a, k1b, k1d, k1e, k1c,  \
    k20, k2f, k21, k22, k23, k24, k210, k25, k26, k27, k28, k29, k2a, k2b, k2d, k2e, k2c,  \
    k30, k3f, k31, k32, k33, k34, k310, k35, k36, k37, k38, k39, k3a,  \
    k40, k4f, k41, k42, k43, k44, k410, k45, k46, k47, k48, k49, k4e,  \
    k50, k5f, k51, k53, k56, k57, k58, k59, k5d, k5e, k5c \
){ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, ___, ___ },  \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k110 },  \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k210 },  \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, ___, ___, ___, k3f, k310 },  \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, ___, ___, ___, ___, k4e, k4f, k410 },  \
    { k50, k51, ___, k53, ___, ___, k56, k57, k58, k59, ___, ___, k5c, k5d, k5e, k5f, ___ }, \
}



