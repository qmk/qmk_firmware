/* Copyright 2019 MechMerlin
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

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array

#define LAYOUT_all( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, \
  k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D,      \
  k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D,      \
  k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D,      \
  k40, k41, k42, k44, k45, k47, k48, k49, k4B, k4D                           \
){ \
  { k00, k01, k02, k03,   k04, k05, k06,   k07, k08, k09, k0A,   k0B, k0C,   k0D, k0E   }, \
  { k10, k11, k12, k13,   k14, k15, k16,   k17, k18, k19, k1A,   k1B, k1C,   k1D, KC_NO }, \
  { k20, k21, k22, k23,   k24, k25, k26,   k27, k28, k29, k2A,   k2B, k2C,   k2D, KC_NO }, \
  { k30, k31, k32, k33,   k34, k35, k36,   k37, k38, k39, k3A,   k3B, k3C,   k3D, KC_NO }, \
  { k40, k41, k42, KC_NO, k44, k45, KC_NO, k47, k48, k49, KC_NO, k4B, KC_NO, k4D, KC_NO }, \
}


#define LAYOUT_60_ansi( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, \
  k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, \
  k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2D,      \
  k30, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C,           \
  k40, k41, k42, k45, k48, k49, k4B, k4D                                \
){ \
  { k00,   k01,   k02,   k03,   k04,   k05,   k06,   k07,   k08,   k09,   k0A,   k0B,   k0C,   k0D,   KC_NO  }, \
  { k10,   k11,   k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1A,   k1B,   k1C,   k1D,   KC_NO  }, \
  { k20,   k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2A,   k2B,   KC_NO, k2D,   KC_NO  }, \
  { k30,   KC_NO, k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3A,   k3B,   k3C,   KC_NO, KC_NO  }, \
  { k40,   k41,   k42,   KC_NO, KC_NO, k45,   KC_NO, KC_NO, k48,   k49,   KC_NO, k4B,   KC_NO, k4D,   KC_NO  }, \
}

#define LAYOUT_60_tsangan_hhkb( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, \
  k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D,      \
  k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2D,           \
  k30, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D,           \
  k40, k41, k42, k45, k48, k49, k4A                                          \
){ \
  { k00,   k01,   k02,   k03,   k04,   k05,   k06,   k07,   k08,   k09,   k0A,   k0B,   k0C,   k0D,   k0E  },   \
  { k10,   k11,   k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1A,   k1B,   k1C,   k1D,   KC_NO  }, \
  { k20,   k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2A,   k2B,   KC_NO, k2D,   KC_NO  }, \
  { k30,   KC_NO, k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3A,   k3B,   k3C,   k3D,   KC_NO  }, \
  { k40,   k41,   k42,   KC_NO, KC_NO, k45,   KC_NO, KC_NO, k48,   k49,   k4A,   KC_NO, KC_NO, KC_NO, KC_NO  }, \
}

