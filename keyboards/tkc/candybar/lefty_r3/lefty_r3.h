/* Copyright 2021 Terry Mathews
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


#define LAYOUT( \
    k0d, k0e, k0f, k0g, k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, \
    k1d, k1e, k1f, k1g, k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a,      k1c, \
    k2d, k2e, k2f, k2g, k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, \
    k3d, k3e, k3f, k3g, k30, k31, k32,           k35,      k37, k38, k39, k3a, k3b, k3c \
) { \
    { k00, k01  , k02, k03  , k04  , k05, k06  , k07, k08, k09, k0a, k0b  , k0c, k0d, k0e, k0f, k0g }  , \
    { k10, k11  , k12, k13  , k14  , k15, k16  , k17, k18, k19, k1a, KC_NO, k1c, k1d, k1e, k1f, k1g }  , \
    { k20, KC_NO, k22, k23  , k24  , k25, k26  , k27, k28, k29, k2a, k2b  , k2c, k2d, k2e, k2f, k2g }  , \
    { k30, k31  , k32, KC_NO, KC_NO, k35, KC_NO, k37, k38, k39, k3a, k3b  , k3c, k3d, k3e, k3f, k3g } \
}
