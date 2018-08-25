/* Copyright 2018 MechMerlin
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
#ifndef JETFIRE_H
#define JETFIRE_H

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguments representing the physical
// layout of the board and position of the keys
// The second converts the arguments into a two-dimensional array which
// represents the switch matrix.

#define LAYOUT( \
    K5A,      K5C, K5D, K5E, K5F,      K5H, K5I, K5J, K5K, K5L, K5M, K5N, K5O, K5P, K5Q, K5R, K5S, K5T,\
    K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I, K4J, K4K, K4L, K4M,      K4O, K4P, K4Q, K4R, K4S, K4T,\
    K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M,      K3O, K3P, K3Q, K3R, K3S, K3T,\
    K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L,           K2O,      K2Q, K2R, K2S,\
    K1A,      K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K,      K1M, K1N,      K1P, K1Q, K1R, K1S, K1T,\
    K0A, K0B, K0C,                          K0I,                K0M, K0N, K0O, K0P, K0Q, K0R, K0S \
) { \
  { KC_##K5A, KC_NO,    KC_##K5C, KC_##K5D, KC_##K5E, KC_##K5F, KC_NO,    KC_##K5H, KC_##K5I, KC_##K5J, KC_##K5K, KC_##K5L, KC_##K5M, KC_##K5N, KC_##K5O, KC_##K5P, KC_##K5Q, KC_##K5R, KC_##K5S, KC_##K5T }, \
  { KC_##K4A, KC_##K4B, KC_##K4C, KC_##K4D, KC_##K4E, KC_##K4F, KC_##K4G, KC_##K4H, KC_##K4I, KC_##K4J, KC_##K4K, KC_##K4L, KC_##K4M, KC_NO,    KC_##K4O, KC_##K4P, KC_##K4Q, KC_##K4R, KC_##K4S, KC_##K4T }, \
  { KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E, KC_##K3F, KC_##K3G, KC_##K3H, KC_##K3I, KC_##K3J, KC_##K3K, KC_##K3L, KC_##K3M, KC_NO,    KC_##K3O, KC_##K3P, KC_##K3Q, KC_##K3R, KC_##K3S, KC_##K3T }, \
  { KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_##K2E, KC_##K2F, KC_##K2G, KC_##K2H, KC_##K2I, KC_##K2J, KC_##K2K, KC_##K2L, KC_NO,    KC_NO,    KC_##K2O, KC_NO,    KC_##K2Q, KC_##K2R, KC_##K2S, KC_NO    }, \
  { KC_##K1A, KC_NO,    KC_##K1C, KC_##K1D, KC_##K1E, KC_##K1F, KC_##K1G, KC_##K1H, KC_##K1I, KC_##K1J, KC_##K1K, KC_NO,    KC_##K1M, KC_##K1N, KC_NO,    KC_##K1P, KC_##K1Q, KC_##K1R, KC_##K1S, KC_##K1T }, \
  { KC_##K0A, KC_##K0B, KC_##K0C, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##K0I, KC_NO,    KC_NO,    KC_NO,    KC_##K0M, KC_##K0N, KC_##K0O, KC_##K0P, KC_##K0Q, KC_##K0R, KC_##K0S, KC_NO    }  \
}

#endif
