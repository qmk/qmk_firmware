/* Copyright 2020 adamws
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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT_all( \
    k00,      k02, k03, k04, k05,      k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, k0h, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d,                     \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b,      k4d, k4e,      k4g,      \
    k50, k51,      k53,           k56,                k5a, k5b,      k5d, k5e, k5f, k5g, k5h  \
) \
{ \
  { k00, XXX, k02, k03, k04, k05, XXX, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, k0h }, \
  { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h }, \
  { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h }, \
  { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, XXX, XXX, XXX, XXX }, \
  { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, XXX, k4d, k4e, XXX, k4g, XXX }, \
  { k50, k51, XXX, k53, XXX, XXX, k56, XXX, XXX, XXX, k5a, k5b, XXX, k5d, k5e, k5f, k5g, k5h }  \
}

#define LAYOUT_ansi( \
    k00,      k02, k03, k04, k05,      k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, k0h, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      k1f, k1g, k1h, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d,                     \
         k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b,      k4d,           k4g,      \
    k50, k51,      k53,           k56,                k5a, k5b,      k5d, k5e, k5f, k5g, k5h  \
) \
{ \
  { k00, XXX, k02, k03, k04, k05, XXX, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, k0h }, \
  { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX, k1f, k1g, k1h }, \
  { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h }, \
  { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, XXX, XXX, XXX, XXX }, \
  { XXX, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, XXX, k4d, XXX, XXX, k4g, XXX }, \
  { k50, k51, XXX, k53, XXX, XXX, k56, XXX, XXX, XXX, k5a, k5b, XXX, k5d, k5e, k5f, k5g, k5h }  \
}

#define LAYOUT_ansi_7uspace( \
    k00,      k02, k03, k04, k05,      k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, k0h, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      k1f, k1g, k1h, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d,                     \
         k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b,      k4d,           k4g,      \
    k50, k51,      k53,           k56,                     k5b,      k5d, k5e, k5f, k5g, k5h  \
) \
{ \
  { k00, XXX, k02, k03, k04, k05, XXX, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, k0h }, \
  { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX, k1f, k1g, k1h }, \
  { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h }, \
  { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, XXX, XXX, XXX, XXX }, \
  { XXX, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, XXX, k4d, XXX, XXX, k4g, XXX }, \
  { k50, k51, XXX, k53, XXX, XXX, k56, XXX, XXX, XXX, XXX, k5b, XXX, k5d, k5e, k5f, k5g, k5h }  \
}

#define LAYOUT_ansi_splitbackspace( \
    k00,      k02, k03, k04, k05,      k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, k0h, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d,                     \
         k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b,      k4d,           k4g,      \
    k50, k51,      k53,           k56,                k5a, k5b,      k5d, k5e, k5f, k5g, k5h  \
) \
{ \
  { k00, XXX, k02, k03, k04, k05, XXX, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, k0h }, \
  { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h }, \
  { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h }, \
  { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, XXX, XXX, XXX, XXX }, \
  { XXX, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, XXX, k4d, XXX, XXX, k4g, XXX }, \
  { k50, k51, XXX, k53, XXX, XXX, k56, XXX, XXX, XXX, k5a, k5b, XXX, k5d, k5e, k5f, k5g, k5h }  \
}

#define LAYOUT_ansi_splitlshift( \
    k00,      k02, k03, k04, k05,      k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, k0h, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      k1f, k1g, k1h, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d,                     \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b,      k4d,           k4g,      \
    k50, k51,      k53,           k56,                k5a, k5b,      k5d, k5e, k5f, k5g, k5h  \
) \
{ \
  { k00, XXX, k02, k03, k04, k05, XXX, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, k0h }, \
  { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX, k1f, k1g, k1h }, \
  { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h }, \
  { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, XXX, XXX, XXX, XXX }, \
  { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, XXX, k4d, XXX, XXX, k4g, XXX }, \
  { k50, k51, XXX, k53, XXX, XXX, k56, XXX, XXX, XXX, k5a, k5b, XXX, k5d, k5e, k5f, k5g, k5h }  \
}

#define LAYOUT_ansi_splitrshift( \
    k00,      k02, k03, k04, k05,      k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, k0h, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      k1f, k1g, k1h, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d,                     \
         k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b,      k4d, k4e,      k4g,      \
    k50, k51,      k53,           k56,                k5a, k5b,      k5d, k5e, k5f, k5g, k5h  \
) \
{ \
  { k00, XXX, k02, k03, k04, k05, XXX, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, k0h }, \
  { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX, k1f, k1g, k1h }, \
  { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h }, \
  { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, XXX, XXX, XXX, XXX }, \
  { XXX, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, XXX, k4d, k4e, XXX, k4g, XXX }, \
  { k50, k51, XXX, k53, XXX, XXX, k56, XXX, XXX, XXX, k5a, k5b, XXX, k5d, k5e, k5f, k5g, k5h }  \
}

#define LAYOUT_iso( \
    k00,      k02, k03, k04, k05,      k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, k0h, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      k1f, k1g, k1h, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      k2f, k2g, k2h, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k2e,                \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b,      k4d,           k4g,      \
    k50, k51,      k53,           k56,                k5a, k5b,      k5d, k5e, k5f, k5g, k5h  \
) \
{ \
  { k00, XXX, k02, k03, k04, k05, XXX, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, k0h }, \
  { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX, k1f, k1g, k1h }, \
  { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h }, \
  { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, XXX, XXX, XXX, XXX }, \
  { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, XXX, k4d, XXX, XXX, k4g, XXX }, \
  { k50, k51, XXX, k53, XXX, XXX, k56, XXX, XXX, XXX, k5a, k5b, XXX, k5d, k5e, k5f, k5g, k5h }  \
}

#define LAYOUT_iso_7uspace( \
    k00,      k02, k03, k04, k05,      k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, k0h, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      k1f, k1g, k1h, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d,                     \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b,      k4d,           k4g,      \
    k50, k51,      k53,           k56,                     k5b,      k5d, k5e, k5f, k5g, k5h  \
) \
{ \
  { k00, XXX, k02, k03, k04, k05, XXX, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, k0h }, \
  { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX, k1f, k1g, k1h }, \
  { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h }, \
  { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, XXX, XXX, XXX, XXX }, \
  { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, XXX, k4d, XXX, XXX, k4g, XXX }, \
  { k50, k51, XXX, k53, XXX, XXX, k56, XXX, XXX, XXX, XX, k5b, XXX, k5d, k5e, k5f, k5g, k5h }  \
}

#define LAYOUT_iso_splitbackspace( \
    k00,      k02, k03, k04, k05,      k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, k0h, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d,                     \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b,      k4d,           k4g,      \
    k50, k51,      k53,           k56,                k5a, k5b,      k5d, k5e, k5f, k5g, k5h  \
) \
{ \
  { k00, XXX, k02, k03, k04, k05, XXX, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, k0h }, \
  { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h }, \
  { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h }, \
  { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, XXX, XXX, XXX, XXX }, \
  { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, XXX, k4d, XXX, XXX, k4g, XXX }, \
  { k50, k51, XXX, k53, XXX, XXX, k56, XXX, XXX, XXX, k5a, k5b, XXX, k5d, k5e, k5f, k5g, k5h }  \
}

#define LAYOUT_iso_splitrshift( \
    k00,      k02, k03, k04, k05,      k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, k0h, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      k1f, k1g, k1h, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d,                     \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b,      k4d, k4e,      k4g,      \
    k50, k51,      k53,           k56,                k5a, k5b,      k5d, k5e, k5f, k5g, k5h  \
) \
{ \
  { k00, XXX, k02, k03, k04, k05, XXX, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, k0h }, \
  { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, XXX, k1f, k1g, k1h }, \
  { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h }, \
  { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, XXX, XXX, XXX, XXX }, \
  { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, XXX, k4d, k4e, XXX, k4g, XXX }, \
  { k50, k51, XXX, k53, XXX, XXX, k56, XXX, XXX, XXX, k5a, k5b, XXX, k5d, k5e, k5f, k5g, k5h }  \
}



