/* Copyright 2017 Rasmus Schults <rasmusx@gmail.com>
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
#ifndef LIGHTSAVER_H
#define LIGHTSAVER_H

#include "quantum.h"

#define NO KC_NO

#define KEYMAP( \
    K5A, K5B, K5C, K5D, K5E, K5F, K5G, K5H, K5I, K5J, K5K, K5L, K5M, K5N, K5O,   K5P, K5Q, K5R, K5S, \
    K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I, K4J, K4K, K4L, K4M,      K4O,   K4P, K4Q, K4R, K4S, \
    K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M,      K3O,   K3P, K3Q, K3R, K3S, \
    K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L,           K2O,   K2P, K2Q, K2R, K2S, \
    K1A,      K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K,      K1M, K1N, K1O,   K1P, K1Q, K1R, K1S, \
    K0A, K0B, K0C,                          K0I,      K0K,      K0M, K0N, K0O,   K0P, K0Q, K0R \
) { \
/*           0    1    2    3    4    5    6    7    8    9    10   11   12   13   14     15   16   17   18  */ \
/* 0 */   { K5A, K5B, K5C, K5D, K5E, K5F, K5G, K5H, K5I, K5J, K5K, K5L, K5M, K5N, K5O,   K5P, K5Q, K5R, K5S, }, \
/* 1 */   { K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I, K4J, K4K, K4L, K4M, NO,  K4O,   K4P, K4Q, K4R, K4S, }, \
/* 2 */   { K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M, NO,  K3O,   K3P, K3Q, K3R, K3S, }, \
/* 3 */   { K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L, NO,  NO,  K2O,   K2P, K2Q, K2R, K2S, }, \
/* 4 */   { K1A, NO,  K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K, NO,  K1M, K1N, K1O,   K1P, K1Q, K1R, K1S, }, \
/* 5 */   { K0A, K0B, K0C, NO,  NO,  NO,  NO,  NO,  K0I, NO,  K0K, NO,  K0M, K0N, K0O,   K0P, K0Q, K0R } \
}

#endif
