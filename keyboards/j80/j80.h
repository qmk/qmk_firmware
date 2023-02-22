/* Copyright 2019 JER
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

#define ____ KC_NO

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

 #define LAYOUT_all( \
   k00, k02, k03, k04, k05, k07, k08, k09, k0A, k0B, k0D, k0C, k01, k61, k62, k6D, \
   k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1D, k1C, k66, k65, k64, \
   k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2D, k2C, k6C, k68, k67, \
   k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3D, \
   k40, k3C, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4D, k4C, \
   k50, k51, k52, k54, k58, k59, k5A, k5B, k5D, k5C, k57 \
 ){ \
   { k00,  k01, k02, k03,  k04, k05,  ____, k07, k08, k09,  k0A,  k0B,  k0C, k0D }, \
   { k10,  k11, k12, k13,  k14, k15,  k16,  k17, k18, k19,  k1A,  k1B,  k1C, k1D }, \
   { k20,  k21, k22, k23,  k24, k25,  k26,  k27, k28, k29,  k2A,  k2B,  k2C, k2D }, \
   { k30,  k31, k32, k33,  k34, k35,  k36,  k37, k38, k39,  k3A,  k3B,  k3C, k3D }, \
   { k40,  k41, k42, k43,  k44, k45,  k46,  k47, k48, k49,  k4A,  k4B,  k4C, k4D }, \
   { k50,  k51, k52, ____, k54, ____, ____, k57, k58, k59,  k5A,  k5B,  k5C, k5D }, \
   { ____, k61, k62, ____, k64, k65,  k66,  k67, k68, ____, ____, ____, k6C, k6D }, \
 }

 #define LAYOUT_tkl_iso( \
   k00, k02, k03, k04, k05, k07, k08, k09, k0A, k0B, k0D, k0C, k01, k61, k62, k6D, \
   k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1D, k1C, k66, k65, k64, \
   k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2D, k6C, k68, k67, \
   k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k2C, k3D, \
   k40, k3C, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, \
   k50, k51, k52, k54, k58, k59, k5A, k5B, k5D, k5C, k57  \
 ){ \
   { k00,  k01, k02, k03,  k04, k05,  ____, k07, k08, k09,  k0A,  k0B,  k0C, k0D  }, \
   { k10,  k11, k12, k13,  k14, k15,  k16,  k17, k18, k19,  k1A,  k1B,  k1C, k1D  }, \
   { k20,  k21, k22, k23,  k24, k25,  k26,  k27, k28, k29,  k2A,  k2B,  k2C, k2D  }, \
   { k30,  k31, k32, k33,  k34, k35,  k36,  k37, k38, k39,  k3A,  k3B,  k3C, k3D  }, \
   { k40,  k41, k42, k43,  k44, k45,  k46,  k47, k48, k49,  k4A,  k4B,  k4C, ____ }, \
   { k50,  k51, k52, ____, k54, ____, ____, k57, k58, k59,  k5A,  k5B,  k5C, k5D  }, \
   { ____, k61, k62, ____, k64, k65,  k66,  k67, k68, ____, ____, ____, k6C, k6D  }, \
 }

#define LAYOUT_tkl_iso_split_rshift( \
  k00, k02, k03, k04, k05, k07, k08, k09, k0A, k0B, k0D, k0C, k01, k61, k62, k6D, \
  k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1D, k1C, k66, k65, k64, \
  k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2D, k6C, k68, k67, \
  k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k2C, k3D, \
  k40, k3C, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4D, k4C, \
  k50, k51, k52, k54, k58, k59, k5A, k5B, k5D, k5C, k57  \
){ \
  { k00,  k01, k02, k03,  k04, k05,  ____, k07, k08, k09,  k0A,  k0B,  k0C, k0D }, \
  { k10,  k11, k12, k13,  k14, k15,  k16,  k17, k18, k19,  k1A,  k1B,  k1C, k1D }, \
  { k20,  k21, k22, k23,  k24, k25,  k26,  k27, k28, k29,  k2A,  k2B,  k2C, k2D }, \
  { k30,  k31, k32, k33,  k34, k35,  k36,  k37, k38, k39,  k3A,  k3B,  k3C, k3D }, \
  { k40,  k41, k42, k43,  k44, k45,  k46,  k47, k48, k49,  k4A,  k4B,  k4C, k4D }, \
  { k50,  k51, k52, ____, k54, ____, ____, k57, k58, k59,  k5A,  k5B,  k5C, k5D }, \
  { ____, k61, k62, ____, k64, k65,  k66,  k67, k68, ____, ____, ____, k6C, k6D }, \
}

#define LAYOUT_tkl_ansi( \
  k00, k02, k03, k04, k05, k07, k08, k09, k0A, k0B, k0D, k0C, k01, k61, k62, k6D, \
  k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1D, k1C, k66, k65, k64, \
  k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2D, k2C, k6C, k68, k67, \
  k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3D, \
  k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, \
  k50, k51, k52, k54, k58, k59, k5A, k5B, k5D, k5C, k57  \
){ \
  { k00,  k01, k02, k03,  k04, k05,  ____, k07, k08, k09,  k0A,  k0B,  k0C,  k0D  }, \
  { k10,  k11, k12, k13,  k14, k15,  k16,  k17, k18, k19,  k1A,  k1B,  k1C,  k1D  }, \
  { k20,  k21, k22, k23,  k24, k25,  k26,  k27, k28, k29,  k2A,  k2B,  k2C,  k2D  }, \
  { k30,  k31, k32, k33,  k34, k35,  k36,  k37, k38, k39,  k3A,  k3B,  ____, k3D  }, \
  { k40,  k41, k42, k43,  k44, k45,  k46,  k47, k48, k49,  k4A,  k4B,  k4C,  ____ }, \
  { k50,  k51, k52, ____, k54, ____, ____, k57, k58, k59,  k5A,  k5B,  k5C,  k5D  }, \
  { ____, k61, k62, ____, k64, k65,  k66,  k67, k68, ____, ____, ____, k6C,  k6D  }, \
}

#define LAYOUT_tkl_ansi_split_rshift( \
  k00, k02, k03, k04, k05, k07, k08, k09, k0A, k0B, k0D, k0C, k01, k61, k62, k6D, \
  k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1D, k1C, k66, k65, k64, \
  k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2D, k2C, k6C, k68, k67, \
  k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3D, \
  k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4D, k4C, \
  k50, k51, k52, k54, k58, k59, k5A, k5B, k5D, k5C, k57  \
){ \
  { k00,  k01, k02, k03,  k04, k05,  ____, k07, k08, k09,  k0A,  k0B,  k0C,  k0D }, \
  { k10,  k11, k12, k13,  k14, k15,  k16,  k17, k18, k19,  k1A,  k1B,  k1C,  k1D }, \
  { k20,  k21, k22, k23,  k24, k25,  k26,  k27, k28, k29,  k2A,  k2B,  k2C,  k2D }, \
  { k30,  k31, k32, k33,  k34, k35,  k36,  k37, k38, k39,  k3A,  k3B,  ____, k3D }, \
  { k40,  k41, k42, k43,  k44, k45,  k46,  k47, k48, k49,  k4A,  k4B,  k4C,  k4D }, \
  { k50,  k51, k52, ____, k54, ____, ____, k57, k58, k59,  k5A,  k5B,  k5C,  k5D }, \
  { ____, k61, k62, ____, k64, k65,  k66,  k67, k68, ____, ____, ____, k6C,  k6D }, \
}
