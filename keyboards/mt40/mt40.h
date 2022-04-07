/* Copyright 2017 REPLACE_WITH_YOUR_NAME
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

// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT_planck_mit( \
    k40, k31, k32, k33, k34, k35, k52, k5C, k6C, k62, k3A, k4E, \
    k30, k21, k22, k23, k24, k25, k53, k5D, k6D, k63, k2A, k2B, \
    k10, k11, k12, k13, k14, k15, k54, k5E, k6E, k64, k1A, k66, \
    k20, k00, k01, k02, k04,    k05,   k0B, k56, k58, k57, k59 \
) { \
    { k00, k01, k02, XXX, k04, k05, XXX, XXX, XXX, XXX, XXX, k0B, XXX, XXX, XXX }, \
    { k10, k11, k12, k13, k14, k15, XXX, XXX, XXX, XXX, k1A, XXX, XXX, XXX, XXX }, \
    { k20, k21, k22, k23, k24, k25, XXX, XXX, XXX, XXX, k2A, k2B, XXX, XXX, XXX }, \
    { k30, k31, k32, k33, k34, k35, XXX, XXX, XXX, XXX, k3A, XXX, XXX, XXX, XXX }, \
    { k40, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, k4E }, \
    { XXX, XXX, k52, k53, k54, k05, k56, k57, k58, k59, XXX, XXX, k5C, k5D, k5E }, \
    { XXX, XXX, k62, k63, k64, XXX, k66, XXX, XXX, XXX, XXX, XXX, k6C, k6D, k6E } \
}

#define LAYOUT LAYOUT_planck_mit
