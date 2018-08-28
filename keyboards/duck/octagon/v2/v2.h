/* Copyright 2017 MechMerlin <mechmerlin@gmail.com>
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
#ifndef V2_H
#define V2_H

#include "quantum.h"

#define LAYOUT( \
    K5A, K5B, K5C, K5D, K5E, K5F, K5G, K5H, K5I, K5J, K5K, K5L, K5M, K5N, K5O,     K5Q, \
    K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I, K4J, K4K, K4L, K4M,      K4O, K4P, \
    K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M,      K3O, K3P, \
    K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L, K2M,      K2O, K2P, \
    K1A, K1B, K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K,      K1M, K1N, K1O, K1P, \
    K0A, K0B, K0C,                               K0J, K0K, K0L, K0M, K0N, K0O, K0P  \
) { \
  { K5A, K5B, K5C, K5D,   K5E,   K5F,   K5G,   K5H,   K5I,   K5J,   K5K, K5L,   K5M, K5N,   K5O, KC_NO, K5Q }, \
  { K4A, K4B, K4C, K4D,   K4E,   K4F,   K4G,   K4H,   K4I,   K4J,   K4K, K4L,   K4M, KC_NO, K4O, K4P,   KC_NO    }, \
  { K3A, K3B, K3C, K3D,   K3E,   K3F,   K3G,   K3H,   K3I,   K3J,   K3K, K3L,   K3M, KC_NO, K3O, K3P,   KC_NO    }, \
  { K2A, K2B, K2C, K2D,   K2E,   K2F,   K2G,   K2H,   K2I,   K2J,   K2K, K2L,   K2M, KC_NO, K2O, K2P,   KC_NO    }, \
  { K1A, K1B, K1C, K1D,   K1E,   K1F,   K1G,   K1H,   K1I,   K1J,   K1K, KC_NO, K1M, K1N,   K1O, K1P,   KC_NO    }, \
  { K0A, K0B, K0C, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K0J,   KC_NO, K0K, K0L,   K0M, K0N,   K0O, K0P,   KC_NO    }  \
}

#define LAYOUT_75_ansi( \
    K5A, K5B, K5C, K5D, K5E, K5F, K5G, K5H, K5I, K5J, K5K, K5L, K5M, K5N, K5O,     K5Q, \
    K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I, K4J, K4K, K4L, K4M,      K4O, K4P, \
    K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M,      K3O, K3P, \
    K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L,           K2O, K2P, \
    K1A, K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K,      K1M, K1N, K1O, K1P, \
    K0A, K0B, K0C,                               K0J, K0K, K0L, K0M, K0N, K0O, K0P  \
) { \
  { K5A, K5B, K5C, K5D,   K5E,   K5F,   K5G,   K5H,   K5I,   K5J,   K5K, K5L,   K5M, K5N,   K5O, KC_NO, K5Q }, \
  { K4A, K4B, K4C, K4D,   K4E,   K4F,   K4G,   K4H,   K4I,   K4J,   K4K, K4L,   K4M, KC_NO, K4O, K4P,   KC_NO    }, \
  { K3A, K3B, K3C, K3D,   K3E,   K3F,   K3G,   K3H,   K3I,   K3J,   K3K, K3L,   K3M, KC_NO, K3O, K3P,   KC_NO    }, \
  { K2A, K2B, K2C, K2D,   K2E,   K2F,   K2G,   K2H,   K2I,   K2J,   K2K, K2L,   KC_NO, KC_NO, K2O, K2P,   KC_NO    }, \
  { K1A, KC_NO, K1C, K1D,   K1E,   K1F,   K1G,   K1H,   K1I,   K1J,   K1K, KC_NO, K1M, K1N,   K1O, K1P,   KC_NO    }, \
  { K0A, K0B, K0C, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K0J,   KC_NO, K0K, K0L,   K0M, K0N,   K0O, K0P,   KC_NO    }  \
}
#endif
