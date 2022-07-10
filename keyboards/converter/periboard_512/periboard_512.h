/* Copyright 2021 Sife
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
    K5A,      K5B, K5C, K5D, K5E, K5F, K5G, K5H, K5I, K5J, K5K, K5L, K5M,   K5N, K5O, K5P, \
    \
    K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I, K4J, K4K, K4L, K4M, K4N,   K4O, K4P, K4Q,   K4R, K4S, K4T, K4U, \
    K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M, K3N,   K3O, K3P, K3Q,   K3R, K3S, K3T, K3U, \
    K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L,      K2M,                    K2N, K2O, K2P, \
    K1A, K1B, K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K,           K1L,        K1M,        K1N, K1O, K1P, K1Q, \
    K0A, K0B, K0C,      K0D,                          K0E, K0F, K0G, K0H,   K0I, K0J, K0K,   K0L,      K0M \
) \
{ \
    { KC_NO, K4L,   K5I,   K4M,   KC_NO, K5C,   K5B,   K4A,   K0A,   KC_NO, K4F,   KC_NO, K4P,   K4Q,   K3O,   K4O,   K5J,   KC_NO, K4G }, \
    { KC_NO, K4K,   K4J,   K4I,   KC_NO, K4D,   K4C,   K4B,   KC_NO, KC_NO, K4E,   K5N,   K3P,   K3Q,   K5L,   K5M,   K5K,   KC_NO, K4H }, \
    { KC_NO, K3K,   K3J,   K3I,   K3H,   K3D,   K3C,   K3B,   KC_NO, KC_NO, K3E,   K5O,   K3U,   K3T,   K3R,   K3S,   KC_NO, K0G,   KC_NO }, \
    { KC_NO, K2K,   K2J,   K2I,   K2H,   K2D,   K2C,   K2B,   KC_NO, KC_NO, K2E,   KC_NO, K1Q,   K1P,   K1N,   K1O,   K3N,   K0B,   KC_NO }, \
    { KC_NO, K3L,   K5H,   K3M,   K3G,   K5D,   K2A,   K3A,   KC_NO, K1A,   K3F,   KC_NO, KC_NO, K2P,   K2N,   K2O,   K4N,   KC_NO, KC_NO }, \
    { KC_NO, K2L,   KC_NO, K5G,   K2G,   K5E,   KC_NO, K5A,   KC_NO, KC_NO, K2F,   K0C,   K1M,   K0M,   KC_NO, K0L,   K5F,   KC_NO, KC_NO }, \
    { K0F,   KC_NO, K1J,   K1I,   K1H,   K1D,   K1C,   K1B,   K0H,   K1L,   K1E,   KC_NO, K5P,   K4T,   K4R,   K4S,   K2M,   KC_NO, KC_NO }, \
    { KC_NO, K1K,   KC_NO, KC_NO, K1G,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K1F,   K0E,   K0I,   K4U,   K0J,   K0K,   K0D,   KC_NO, KC_NO }, \
}
