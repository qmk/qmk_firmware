/* Copyright 2020 MelGeek <melgeek001365@gmail.com>
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

#define LAYOUT_60_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d, \
    k40, k41, k42,           k45,                     k4a, k4b, k4c, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, XXX, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, XXX }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, XXX, k4e }  \
}

#define LAYOUT_60_ansi_arrow( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,	  k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,		 k3d, k3e, \
    k40, k41, k42,           k45,                     k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, XXX, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, k3e }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_60_ansi_arrow_6u_spc( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,	  k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,		 k3d, k3e, \
    k40, k41, k42,           k45,                     k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, XXX, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, k3e }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_60_ansi_arrow_3u_spc( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,	  k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,		 k3d, k3e, \
    k40, k41, k42, k43,      k45,                k49, k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, XXX, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, k3e }, \
    { k40, k41, k42, k43, XXX, k45, XXX, XXX, XXX, k49, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_60_ansi_arrow_split_3u_spc( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,	  k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,		 k3d, k3e, \
    k40, k41, k42, k43,                     k48,      k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, XXX, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, k3e }, \
    { k40, k41, k42, k43, XXX, XXX, XXX, XXX, k48, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_60_ansi_7u_spc( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,	  k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,		 k3d,	   \
    k40, k41, k42,                     k47,                k4b, k4c,	  k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, XXX, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, XXX }, \
    { k40, k41, k42, XXX, XXX, XXX, XXX, k47, XXX, XXX, XXX, k4b, k4c, XXX, k4e }  \
}

#define LAYOUT_64_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,	  k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
    k40, k41, k42,           k45,                     k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, XXX, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_64_ansi_6u_spc( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,	  k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
    k40, k41, k42,           k45,                     k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, XXX, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_64_ansi_3u_spc( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,	  k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
    k40, k41, k42, k43,      k45,                k49, k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, XXX, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e }, \
    { k40, k41, k42, k43, XXX, k45, XXX, XXX, XXX, k49, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_64_ansi_split_3u_spc( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,	  k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
    k40, k41, k42, k43,                     k48,      k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, XXX, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e }, \
    { k40, k41, k42, k43, XXX, XXX, XXX, XXX, k48, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_60_iso( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,	  k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,		 k3d,	   \
    k40, k41, k42,           k45,                     k4a, k4b, k4c,	  k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, XXX }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, XXX, k4e }  \
}

#define LAYOUT_60_iso_split_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,	  k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,	k3c,	  k3e, \
    k40, k41, k42,           k45,                     k4a, k4b, k4c,	  k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, XXX, k3e }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, XXX, k4e }  \
}

#define LAYOUT_60_iso_7u_spc_split_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,	  k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,	k3c,	  k3e, \
    k40, k41, k42,                     k47,                k4b, k4c,	  k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, XXX, k3e }, \
    { k40, k41, k42, XXX, XXX, XXX, XXX, k47, XXX, XXX, XXX, k4b, k4c, XXX, k4e }  \
}

#define LAYOUT_60_iso_arrow( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,	  k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,		 k3d, k3e, \
    k40, k41, k42,           k45,                     k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, k3e }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_60_iso_arrow_6u_spc( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,	  k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,		 k3d, k3e, \
    k40, k41, k42,           k45,                     k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, k3e }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_60_iso_arrow_3u_spc( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,	  k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,		 k3d, k3e, \
    k40, k41, k42, k43,      k45,                k49, k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, k3e }, \
    { k40, k41, k42, k43, XXX, k45, XXX, XXX, XXX, k49, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_60_iso_arrow_split_3u_spc( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,	  k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,		 k3d, k3e, \
    k40, k41, k42, k43,                     k48,      k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, k3e }, \
    { k40, k41, k42, k43, XXX, XXX, XXX, XXX, k48, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_60_iso_7u_spc( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,	  k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,		 k3d,	   \
    k40, k41, k42,                     k47,                k4b, k4c,	  k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, XXX }, \
    { k40, k41, k42, XXX, XXX, XXX, XXX, k47, XXX, XXX, XXX, k4b, k4c, XXX, k4e }  \
}

#define LAYOUT_64_iso( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,	  k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
    k40, k41, k42,           k45,                     k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_64_iso_6u_spc( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,	  k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
    k40, k41, k42,           k45,                     k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_64_iso_3u_spc( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,	  k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
    k40, k41, k42, k43,      k45,                k49, k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e }, \
    { k40, k41, k42, k43, XXX, k45, XXX, XXX, XXX, k49, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_64_iso_split_3u_spc( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,	  k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
    k40, k41, k42, k43,                     k48,      k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e }, \
    { k40, k41, k42, k43, XXX, XXX, XXX, XXX, k48, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_60_iso_1u_lshift_split_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,	  k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,	k3c,	  k3e, \
    k40, k41, k42,           k45,                     k4a, k4b, k4c,	  k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, XXX, k3e }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, XXX, k4e }  \
}

#define LAYOUT_60_iso_1u_lshift_7u_spc_split_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,	  k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,	k3c,	  k3e, \
    k40, k41, k42,                     k47,                k4b, k4c,	  k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, XXX, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, XXX, k3e }, \
    { k40, k41, k42, XXX, XXX, XXX, XXX, k47, XXX, XXX, XXX, k4b, k4c, XXX, k4e }  \
}

#define LAYOUT_60_ansi_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,		 k3d,	   \
    k40, k41, k42,           k45,                     k4a, k4b, k4c,	  k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, XXX, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, XXX }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, XXX, k4e }  \
}

#define LAYOUT_60_ansi_arrow_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,		 k3d, k3e, \
    k40, k41, k42,           k45,                     k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, XXX, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, k3e }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_60_ansi_arrow_6u_spc_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,		 k3d, k3e, \
    k40, k41, k42,           k45,                     k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, XXX, k2d, XXX }, \
	{ k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, k3e }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_60_ansi_arrow_3u_spc_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,		 k3d, k3e, \
    k40, k41, k42, k43,      k45,                k49, k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, XXX, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, k3e }, \
    { k40, k41, k42, k43, XXX, k45, XXX, XXX, XXX, k49, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_60_ansi_arrow_split_bs_3u_spc( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,		 k3d, k3e, \
    k40, k41, k42, k43,                     k48,      k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, XXX, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, k3e }, \
    { k40, k41, k42, k43, XXX, XXX, XXX, XXX, k48, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_60_ansi_7u_spc_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,		 k3d,	   \
    k40, k41, k42,                     k47,                k4b, k4c,	  k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, XXX, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, XXX }, \
    { k40, k41, k42, XXX, XXX, XXX, XXX, k47, XXX, XXX, XXX, k4b, k4c, XXX, k4e }  \
}

#define LAYOUT_64_ansi_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
    k40, k41, k42,           k45,                     k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, XXX, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_64_ansi_6u_spc_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
    k40, k41, k42,           k45,                     k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, XXX, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_64_ansi_3u_spc_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
    k40, k41, k42, k43,      k45,                k49, k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, XXX, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e }, \
    { k40, k41, k42, k43, XXX, k45, XXX, XXX, XXX, k49, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_64_ansi_split_bs_3u_spc( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
    k40, k41, k42, k43,                     k48,      k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, XXX, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e }, \
    { k40, k41, k42, k43, XXX, XXX, XXX, XXX, k48, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_60_iso_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,		 k3d,	   \
    k40, k41, k42,           k45,                     k4a, k4b, k4c,	  k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, XXX }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, XXX, k4e }  \
}

#define LAYOUT_60_iso_split_bs_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,	k3c,	  k3e, \
    k40, k41, k42,           k45,                     k4a, k4b, k4c,	  k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, XXX, k3e }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, XXX, k4e }  \
}

#define LAYOUT_60_iso_7u_spc_split_bs_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,	k3c,	  k3e, \
    k40, k41, k42,                     k47,                k4b, k4c,	  k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, XXX, k3e }, \
	{ k40, k41, k42, XXX, XXX, XXX, XXX, k47, XXX, XXX, XXX, k4b, k4c, XXX, k4e }  \
}

#define LAYOUT_60_iso_arrow_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,		 k3d, k3e, \
    k40, k41, k42,           k45,                     k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, k3e }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_60_iso_arrow_6u_spc_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,		 k3d, k3e, \
    k40, k41, k42,           k45,                     k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, k3e }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_60_iso_arrow_3u_spc_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,		 k3d, k3e, \
    k40, k41, k42, k43,      k45,                k49, k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, k3e }, \
    { k40, k41, k42, k43, XXX, k45, XXX, XXX, XXX, k49, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_60_iso_arrow_split_bs_3u_spc( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,		 k3d, k3e, \
    k40, k41, k42, k43,                     k48,      k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, k3e }, \
    { k40, k41, k42, k43, XXX, XXX, XXX, XXX, k48, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_60_iso_7u_spc_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,		 k3d,	   \
    k40, k41, k42,                     k47,                k4b, k4c,	  k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, XXX }, \
    { k40, k41, k42, XXX, XXX, XXX, XXX, k47, XXX, XXX, XXX, k4b, k4c, XXX, k4e }  \
}

#define LAYOUT_64_iso_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
    k40, k41, k42,           k45,                     k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_64_iso_6u_spc_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
    k40, k41, k42,           k45,                     k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_64_iso_3u_spc_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
    k40, k41, k42, k43,      k45,                k49, k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e }, \
    { k40, k41, k42, k43, XXX, k45, XXX, XXX, XXX, k49, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_64_iso_split_bs_3u_spc( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,	  k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
    k40, k41, k42, k43,                     k48,      k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e }, \
    { k40, k41, k42, k43, XXX, XXX, XXX, XXX, k48, XXX, k4a, k4b, k4c, k4d, k4e }  \
}

#define LAYOUT_60_iso_1u_lshift_split_bs_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,	k3c,	  k3e, \
    k40, k41, k42,           k45,                     k4a, k4b, k4c,	  k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, XXX, k3e }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, XXX, k4e }  \
}

#define LAYOUT_60_iso_1u_lshift_7u_spc_split_bs_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,           \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,	k3c,	  k3e, \
    k40, k41, k42,                     k47,                k4b, k4c,	  k4e  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, XXX }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, XXX, k3e }, \
    { k40, k41, k42, XXX, XXX, XXX, XXX, k47, XXX, XXX, XXX, k4b, k4c, XXX, k4e }  \
}
