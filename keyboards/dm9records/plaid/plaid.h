/* Copyright 2019 Takuya Urakawa (dm9records.com)
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
	k30, k31, k32, k33, k34,    k35,   k37, k38, k39, k3a, k3b \
) \
{ \
	{ k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b }, \
	{ k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b }, \
	{ k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b }, \
	{ k30, k31, k32, k33, k34, k35, k35, k37, k38, k39, k3a, k3b } \
}

#define LAYOUT_ortho_4x12( \
	k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
	k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
	k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b \
) \
{ \
	{ k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b }, \
	{ k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b }, \
	{ k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b }, \
	{ k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b } \
}

#define LAYOUT LAYOUT_ortho_4x12
#define LAYOUT_plaid_grid LAYOUT_ortho_4x12
#define LAYOUT_plaid_mit LAYOUT_planck_mit

#define LED_RED C5
#define LED_GREEN C4
