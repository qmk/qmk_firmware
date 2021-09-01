/* Copyright 2017 MechMerlin
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

// readability
#define XXX KC_NO

// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E,   k1F, k09, k0A, k0C, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E,   k2F, k0B, k0F, k6F, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D,        k3E, k3F, k0D, k6D, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C,             k4D, k4E, k4F, k6E, \
    k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5A, k5B, k5C, k5D,        k5E, k5F, k0E, k07, \
    k60, k61, k62,                k63,                     k64, k65, k66, k68,   k69, k6A, k6B, k6C \
) { \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, k07, XXX, k09, k0A, k0B, k0C, k0D, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, k4F }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5A, k5B, k5C, k5D, k5E, k5F }, \
    { k60, k61, k62, k63, k64, k65, k66, XXX, k68, k69, k6A, k6B, k6C, k6D, k6E, k6F } \
}
