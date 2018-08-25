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
  { KC_K5A, KC_NO,    KC_K5C, KC_K5D, KC_K5E, KC_K5F, KC_NO,    KC_K5H, KC_K5I, KC_K5J, KC_K5K, KC_K5L, KC_K5M, KC_K5N, KC_K5O, KC_K5P, KC_K5Q, KC_K5R, KC_K5S, KC_K5T }, \
  { KC_K4A, KC_K4B, KC_K4C, KC_K4D, KC_K4E, KC_K4F, KC_K4G, KC_K4H, KC_K4I, KC_K4J, KC_K4K, KC_K4L, KC_K4M, KC_NO,    KC_K4O, KC_K4P, KC_K4Q, KC_K4R, KC_K4S, KC_K4T }, \
  { KC_K3A, KC_K3B, KC_K3C, KC_K3D, KC_K3E, KC_K3F, KC_K3G, KC_K3H, KC_K3I, KC_K3J, KC_K3K, KC_K3L, KC_K3M, KC_NO,    KC_K3O, KC_K3P, KC_K3Q, KC_K3R, KC_K3S, KC_K3T }, \
  { KC_K2A, KC_K2B, KC_K2C, KC_K2D, KC_K2E, KC_K2F, KC_K2G, KC_K2H, KC_K2I, KC_K2J, KC_K2K, KC_K2L, KC_NO,    KC_NO,    KC_K2O, KC_NO,    KC_K2Q, KC_K2R, KC_K2S, KC_NO    }, \
  { KC_K1A, KC_NO,    KC_K1C, KC_K1D, KC_K1E, KC_K1F, KC_K1G, KC_K1H, KC_K1I, KC_K1J, KC_K1K, KC_NO,    KC_K1M, KC_K1N, KC_NO,    KC_K1P, KC_K1Q, KC_K1R, KC_K1S, KC_K1T }, \
  { KC_K0A, KC_K0B, KC_K0C, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_K0I, KC_NO,    KC_NO,    KC_NO,    KC_K0M, KC_K0N, KC_K0O, KC_K0P, KC_K0Q, KC_K0R, KC_K0S, KC_NO    }  \
}

#endif
