/* Copyright 2021 Dztech
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

#define LAYOUT_all( \
    k00,      k02, k03, k04, k05,      k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, k0G, k0H, k0I, k0J, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D,      k1F, k1G, k1H, k1I, k1J, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D,      k2F, k2G, k2H, k2I, k2J, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D,           k3G, k3H, k3I,      \
    k40,      k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B,      k4D,      k4F, k4G, k4H, k4I, k4J, \
    k50, k51, k52,                k56,                     k5B,      k5D, k5E, k5F, k5G, k5H, k5I       \
) \
{ \
    {k00, KC_NO, k02, k03,   k04,   k05,   KC_NO, k07,   k08,   k09,   k0A,   k0B, k0C,   k0D, k0E,   k0F,   k0G, k0H, k0I, k0J  }, \
    {k10, k11,   k12, k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1A,   k1B, k1C,   k1D, KC_NO, k1F,   k1G, k1H, k1I, k1J  }, \
    {k20, k21,   k22, k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2A,   k2B, k2C,   k2D, KC_NO, k2F,   k2G, k2H, k2I, k2J  }, \
    {k30, k31,   k32, k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3A,   k3B, KC_NO, k3D, KC_NO, KC_NO, k3G, k3H, k3I, KC_NO}, \
    {k40, KC_NO, k42, k43,   k44,   k45,   k46,   k47,   k48,   k49,   k4A,   k4B, KC_NO, k4D, KC_NO, k4F,   k4G, k4H, k4I, k4J  }, \
    {k50, k51,   k52, KC_NO, KC_NO, KC_NO, k56,   KC_NO, KC_NO, KC_NO, KC_NO, k5B, KC_NO, k5D, k5E,   k5F,   k5G, k5H, k5I, KC_NO}  \
}
