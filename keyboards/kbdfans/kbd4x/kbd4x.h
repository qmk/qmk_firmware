/* Copyright 2018 sevenseacat
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

#define LAYOUT_planck_mit( \
	k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
	k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
	k30, k31, k32, k33, k34,    k35,   k37, k38, k39, k3a, k3b  \
) \
{ \
	{ k00, k01, k02, k03, k04, k05, k06,   k07, k08, k09, k0a, k0b }, \
	{ k10, k11, k12, k13, k14, k15, k16,   k17, k18, k19, k1a, k1b }, \
	{ k20, k21, k22, k23, k24, k25, k26,   k27, k28, k29, k2a, k2b }, \
	{ k30, k31, k32, k33, k34, k35, KC_NO, k37, k38, k39, k3a, k3b }  \
}

// The PCB does support a grid layout, but the case does not.
#define LAYOUT_ortho_4x12( \
	k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
	k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
	k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b  \
) \
{ \
	{ k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b }, \
	{ k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b }, \
	{ k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b }, \
	{ k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b }  \
}

#define LAYOUT_kc_ortho_4x12( \
	k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
	k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
	k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b  \
) \
{ \
	{ KC_##k00, KC_##k01, KC_##k02, KC_##k03, KC_##k04, KC_##k05, KC_##k06, KC_##k07, KC_##k08, KC_##k09, KC_##k0a, KC_##k0b }, \
	{ KC_##k10, KC_##k11, KC_##k12, KC_##k13, KC_##k14, KC_##k15, KC_##k16, KC_##k17, KC_##k18, KC_##k19, KC_##k1a, KC_##k1b }, \
	{ KC_##k20, KC_##k21, KC_##k22, KC_##k23, KC_##k24, KC_##k25, KC_##k26, KC_##k27, KC_##k28, KC_##k29, KC_##k2a, KC_##k2b }, \
	{ KC_##k30, KC_##k31, KC_##k32, KC_##k33, KC_##k34, KC_##k35, KC_##k36, KC_##k37, KC_##k38, KC_##k39, KC_##k3a, KC_##k3b }  \
}
