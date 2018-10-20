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

#define LAYOUT_all( \
    K5A,      K5C, K5D, K5E, K5F,      K5H, K5I, K5J, K5K, K5L, K5M, K5N, K5O, K5P, K5Q, K5R, K5S, K5T, \
    K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I, K4J, K4K, K4L, K4M, K4N, K4O, K4P, K4Q, K4R, K4S, K4T, \
    K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M,      K3O, K3P, K3Q, K3R, K3S, K3T, \
    K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L,           K2O,      K2Q, K2R, K2S, K2T, \
    K1A, K1B, K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K,      K1M, K1N, K1O, K1P, K1Q, K1R, K1S, K1T, \
    K0A, K0B, K0C,                          K0I,           K0L, K0M, K0N, K0O, K0P, K0Q, K0R, K0S, K0T  \
) { \
  { K5A, KC_NO,    K5C, K5D, K5E, K5F, KC_NO,     K5H, K5I, K5J,   K5K,  K5L, K5M, K5N, K5O, K5P, K5Q, K5R, K5S, K5T }, \
  { K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I,  K4J, K4K, K4L,   K4M,  K4N,    K4O, K4P, K4Q, K4R, K4S, K4T }, \
  { K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I,  K3J, K3K, K3L,   K3M,  KC_NO,    K3O, K3P, K3Q, K3R, K3S, K3T }, \
  { K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I,  K2J, K2K, K2L,   KC_NO,     KC_NO,    K2O, KC_NO,    K2Q, K2R, K2S, K2T    }, \
  { K1A, K1B, K1C, K1D, K1E, K1F, K1G, K1H, K1I,  K1J, K1K, KC_NO, K1M,  K1N, K1O,    K1P, K1Q, K1R, K1S, K1T }, \
  { K0A, K0B, K0C, KC_NO,KC_NO,KC_NO,KC_NO,KC_NO, K0I, KC_NO,KC_NO, K0L, K0M, K0N, K0O, K0P, K0Q, K0R, K0S, K0T    }  \
}

#define LAYOUT( \
    K5A,      K5C, K5D, K5E, K5F,      K5H, K5I, K5J, K5K, K5L, K5M, K5N, K5O, K5P, K5Q, K5R, K5S, K5T, \
    K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I, K4J, K4K, K4L, K4M,      K4O, K4P, K4Q, K4R, K4S, K4T, \
    K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M,      K3O, K3P, K3Q, K3R, K3S, K3T, \
    K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L,           K2O,      K2Q, K2R, K2S,      \
    K1A,      K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K,      K1M, K1N,      K1P, K1Q, K1R, K1S, K1T, \
    K0A, K0B, K0C,                          K0I,                K0M, K0N, K0O, K0P, K0Q, K0R, K0S       \
) { \
  { K5A, KC_NO,    K5C, K5D, K5E, K5F, KC_NO,    K5H, K5I, K5J, K5K, K5L, K5M, K5N, K5O, K5P, K5Q, K5R, K5S, K5T }, \
  { K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I, K4J, K4K, K4L, K4M, KC_NO,    K4O, K4P, K4Q, K4R, K4S, K4T }, \
  { K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M, KC_NO,    K3O, K3P, K3Q, K3R, K3S, K3T }, \
  { K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L, KC_NO,    KC_NO,    K2O, KC_NO,    K2Q, K2R, K2S, KC_NO    }, \
  { K1A, KC_NO,    K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K, KC_NO,    K1M, K1N, KC_NO,    K1P, K1Q, K1R, K1S, K1T }, \
  { K0A, K0B, K0C, KC_NO,KC_NO,KC_NO,KC_NO,KC_NO, K0I, KC_NO,KC_NO,KC_NO, K0M, K0N, K0O, K0P, K0Q, K0R, K0S, KC_NO    }  \
}

#endif
