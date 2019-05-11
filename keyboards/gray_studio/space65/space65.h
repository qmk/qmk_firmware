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

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, \
    k10, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F,      \
    k20, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2F,           \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3D, k3E, k3F,      \
    k40, k41,      k43,      k45,      k47, k48,      k4A, k4B, k4D, k4E, k4F       \
) \
{ \
    { k00, k01,   k02,   k03, k04,   k05, k06,   k07, k08, k09,   k0A, k0B, k0C,   k0D, k0E,   k0F }, \
    { k10, KC_NO, k12,   k13, k14,   k15, k16,   k17, k18, k19,   k1A, k1B, k1C,   k1D, k1E,   k1F }, \
    { k20, KC_NO, k22,   k23, k24,   k25, k26,   k27, k28, k29,   k2A, k2B, k2C,   k2D, KC_NO, k2F }, \
    { k30, k31,   k32,   k33, k34,   k35, k36,   k37, k38, k39,   k3A, k3B, KC_NO, k3D, k3E,   k3F }, \
    { k40, k41,   KC_NO, k43, KC_NO, k45, KC_NO, k47, k48, KC_NO, k4A, k4B, KC_NO, k4D, k4E,   k4F }, \
}

