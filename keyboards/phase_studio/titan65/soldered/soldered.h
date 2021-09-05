/* Copyright 2021 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#define LAYOUT_all( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e,  k0f, \
    k10,   k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,   k1e,   k1f, \
    k20,     k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,  k2e,  k2f, \
    k30,  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c,    k3d,   k3e, k3f, \
    k40, k42, k43,                k47,                   k4b, k4c,    k4d, k4e, k4f  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f }, \
    { k10, ___, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f }, \
    { k20, ___, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f }, \
    { k30, ___, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f }, \
    { k40, ___, k42, k43, ___, ___, ___, k47, ___, ___, ___, k4b, k4c, k4d, k4e, k4f }  \
}

#define LAYOUT_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,    k0d,    k0f, \
    k10,   k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,   k1e,   k1f, \
    k20,     k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c,       k2e,  k2f, \
    k30,       k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c,    k3d,   k3e, k3f, \
    k40, k42, k43,                k47,                   k4b, k4c,    k4d, k4e, k4f  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, ___, k0f }, \
    { k10, ___, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f }, \
    { k20, ___, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, ___, k2e, k2f }, \
    { k30, ___, ___, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f }, \
    { k40, ___, k42, k43, ___, ___, ___, k47, ___, ___, ___, k4b, k4c, k4d, k4e, k4f }  \
}

#define LAYOUT_ansi_split_bspc( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e,  k0f, \
    k10,   k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,   k1e,   k1f, \
    k20,     k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c,       k2e,  k2f, \
    k30,       k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c,    k3d,   k3e, k3f, \
    k40, k42, k43,                k47,                   k4b, k4c,    k4d, k4e, k4f  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f }, \
    { k10, ___, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f }, \
    { k20, ___, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, ___, k2e, k2f }, \
    { k30, ___, ___, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f }, \
    { k40, ___, k42, k43, ___, ___, ___, k47, ___, ___, ___, k4b, k4c, k4d, k4e, k4f }  \
}

#define LAYOUT_iso( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,    k0d,    k0f, \
    k10,   k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,          k1f, \
    k20,     k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,  k2e,  k2f, \
    k30,  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c,    k3d,   k3e, k3f, \
    k40, k42, k43,                k47,                   k4b, k4c,    k4d, k4e, k4f  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, ___, k0f }, \
    { k10, ___, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, ___, k1f }, \
    { k20, ___, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f }, \
    { k30, ___, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f }, \
    { k40, ___, k42, k43, ___, ___, ___, k47, ___, ___, ___, k4b, k4c, k4d, k4e, k4f }  \
}

#define LAYOUT_iso_split_bspc( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e,  k0f, \
    k10,   k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,          k1f, \
    k20,     k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,  k2e,  k2f, \
    k30,  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c,    k3d,   k3e, k3f, \
    k40, k42, k43,                k47,                   k4b, k4c,    k4d, k4e, k4f  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f }, \
    { k10, ___, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, ___, k1f }, \
    { k20, ___, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f }, \
    { k30, ___, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f }, \
    { k40, ___, k42, k43, ___, ___, ___, k47, ___, ___, ___, k4b, k4c, k4d, k4e, k4f }  \
}
