/* Copyright 2017 benlyall, MechMerlin
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

#ifdef V60_POLESTAR

#include "rgblight.h"

void rgb_init(void);
void set_rgb_color(uint8_t pin, uint8_t value, uint8_t timer_value);

enum my_keycodes {
  RGB_RI = SAFE_RANGE,
  RGB_RD,
  RGB_GI,
  RGB_GD,
  RGB_BI,
  RGB_BD
};
#endif

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array

/* LAYOUT_all
 * ,-----------------------------------------------------------------------------------------.
 * | K00 | K01 | K02 | K03 | K04 | K05 | K06 | K07 | K08 | K09 | K0A | K0B | K0C | K0D | K0E |
 * |-----------------------------------------------------------------------------------------+
 * | K10    | K11 | K12 | K13 | K14 | K15 | K16 | K17 | K18 | K19 | K1A | K1B | K1C | K1D    |
 * |-----------------------------------------------------------------------------------------+
 * | K20     | K21 | K22 | K23 | K24 | K25 | K26 | K27 | K28 | K29 | K2A | K2B | K2C         |
 * |-----------------------------------------------------------------------------------------+
 * | K30       | K31 | K32 | K33 | K34 | K35 | K36 | K37 | K38 | K39 | K3A | K3B | K3C | K3D |
 * |-----------------------------------------------------------------------------------------+
 * | K40   | K41   | K42   | K43                             | K44   | K45   | K46   | K47   |
 * `-----------------------------------------------------------------------------------------'
 */

// KBP V60 Type R with ALL possible layouts

#define LAYOUT_all( \
	       k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
	       k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,      k1d, \
	       k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,           k2c, \
	       k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3c, k3d, \
	       k40, k41, k42,                k43,                     k44, k45, k46, k47 \
		) { \
      { k00, k01, k02, k03, k04, k05, k06, k07 }, \
      { k08, k09, k0a, k0b, k0c, k0d, k0e, k10 }, \
      { k11, k12, k13, k14, k15, k16, k17, k18 }, \
      { k19, k1a, k1b, k1c, k1d, k20, k21, k22 }, \
      { k23, k24, k25, k26, k27, k28, k29, k2a }, \
      { k2b, k2c, k30, k31, k32, k33, k34, k35 }, \
      { k36, k37, k38, k39, k3a, k3b, k3c, k3d }, \
      { k40, k41, k42, k43, k44, k45, k46, k47 } \
  }


/* LAYOUT_ansi
 * ,-----------------------------------------------------------------------------------------.
 * | K00 | K01 | K02 | K03 | K04 | K05 | K06 | K07 | K08 | K09 | K0A | K0B | K0C |    K0E    |
 * |-----------------------------------------------------------------------------------------+
 * | K10    | K11 | K12 | K13 | K14 | K15 | K16 | K17 | K18 | K19 | K1A | K1B | K1C | K1D    |
 * |-----------------------------------------------------------------------------------------+
 * | K20     | K21 | K22 | K23 | K24 | K25 | K26 | K27 | K28 | K29 | K2A | K2B |     K2C     |
 * |-----------------------------------------------------------------------------------------+
 * |    K30    | K32 | K33 | K34 | K35 | K36 | K37 | K38 | K39 | K3A | K3B |       K3C       |
 * |-----------------------------------------------------------------------------------------+
 * | K40   | K41   | K42   |              K43                | K44   | K45   | K46   | K47   |
 * `-----------------------------------------------------------------------------------------'
 */

  // KBP V60 Type R with ANSI layout

  #define LAYOUT_60_ansi( \
	       k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,      k0e, \
	       k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,      k1d, \
	       k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,           k2c, \
	       k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3c,  \
	       k40, k41, k42,                k43,                     k44, k45, k46, k47 \
		) { \
      { k00, k01, k02, k03,   k04, k05,   k06, k07 }, \
      { k08, k09, k0a, k0b,   k0c, KC_NO, k0e, k10 }, \
      { k11, k12, k13, k14,   k15, k16,   k17, k18 }, \
      { k19, k1a, k1b, k1c,   k1d, k20,   k21, k22 }, \
      { k23, k24, k25, k26,   k27, k28,   k29, k2a }, \
      { k2b, k2c, k30, KC_NO, k32, k33,   k34, k35 }, \
      { k36, k37, k38, k39,   k3a, k3b,   k3c, KC_NO }, \
      { k40, k41, k42, k43,   k44, k45,   k46, k47 } \
  }

