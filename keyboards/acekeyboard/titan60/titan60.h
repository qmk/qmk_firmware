/*
Copyright 2021 keebnewb

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

#define ___ KC_NO

#define LAYOUT_60_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d,      \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2d,           \
    k30, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c,                \
    k40, k41, k42, k46, k4a, k4b, k4c, k4d                                     \
){ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d },  \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d },  \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, ___, k2d },  \
    { k30, ___, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, ___ },  \
    { k40, k41, k42, ___, ___, ___, k46, ___, ___, ___, k4a, k4b, k4c, k4d }   \
}

// ANSI with all split options
#define LAYOUT_60_ansi_split( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k2c, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2d,           \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k43,      \
    k40, k41, k42, k46, k4a, k4b, k4c, k4d                                     \
){ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d },  \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d },  \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d },  \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, ___ },  \
    { k40, k41, k42, k43, ___, ___, k46, ___, ___, ___, k4a, k4b, k4c, k4d }   \
}

#define LAYOUT_60_iso( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d,      \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k2d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k1d,           \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c,           \
    k40, k41, k42, k46, k4a, k4b, k4c, k4d                                     \
){ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d },  \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d },  \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, ___, k2d },  \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, ___ },  \
    { k40, k41, k42, ___, ___, ___, k46, ___, ___, ___, k4a, k4b, k4c, k4d }   \
}

// ISO with all split options
#define LAYOUT_60_iso_split( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k2c, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k2d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k1d,           \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k43,      \
    k40, k41, k42, k46, k4a, k4b, k4c, k4d                                     \
){ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d },  \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d },  \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d },  \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, ___ },  \
    { k40, k41, k42, k43, ___, ___, k46, ___, ___, ___, k4a, k4b, k4c, k4d }   \
}

// Tsangan
#define LAYOUT_60_tsangan( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k2c, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2d,           \
    k30, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k43,           \
    k40, k41, k42, k46, k4b, k4c, k4d                                          \
){ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d },  \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d },  \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d },  \
    { k30, ___, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, ___ },  \
    { k40, k41, k42, k43, ___, ___, k46, ___, ___, ___, ___, k4b, k4c, k4d }   \
}

// Tsangan with split left shift
#define LAYOUT_60_tsangan_split( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k2c, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2d,           \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k43,      \
    k40, k41, k42, k46, k4b, k4c, k4d                                          \
){ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d },  \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d },  \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d },  \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, ___ },  \
    { k40, k41, k42, k43, ___, ___, k46, ___, ___, ___, ___, k4b, k4c, k4d }   \
}

#define LAYOUT_60_utilitarian( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d,      \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2d,           \
    k30, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3d, k3c, k43,      \
    k40, k41, k42, k46, k4a, k4b, k49, k4c, k4d                                \
){ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d },  \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d },  \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, ___, k2d },  \
    { k30, ___, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d },  \
    { k40, k41, k42, k43, ___, ___, k46, ___, ___, k49, k4a, k4b, k4c, k4d }   \
}

// Utilitarian with split spacebar and split backspace
#define LAYOUT_60_utilitarian_split( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k2c,  \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,       \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2d,            \
    k30, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3d, k3c, k43,       \
    k40, k41, k42, k44, k46, k48, k4a, k4b, k49, k4c, k4d                       \
){ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d },  \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d },  \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d },  \
    { k30, ___, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d },  \
    { k40, k41, k42, k43, k44, ___, k46, ___, k48, k49, k4a, k4b, k4c, k4d }   \
}

// Utilitarian with ISO enter, split spacebar and split backspace
#define LAYOUT_60_utilitarian_iso_split( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k2c, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k2d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k1d,           \
    k30, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3d, k3c, k43,      \
    k40, k41, k42, k44, k46, k48, k4a, k4b, k49, k4c, k4d                      \
){ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d },  \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d },  \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d },  \
    { k30, ___, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d },  \
    { k40, k41, k42, k43, k44, ___, k46, ___, k48, k49, k4a, k4b, k4c, k4d }   \
}
