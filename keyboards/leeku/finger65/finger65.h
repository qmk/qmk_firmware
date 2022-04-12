/* Copyright 2018 Rasmus Schults <rasmusx@gmail.com>
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
    K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I, K4J, K4K, K4L, K4M, K4N, K4O, K4P, \
    K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M, K3N,      K3P, \
    K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L, K2M, K2N,      K2P, \
    K1A, K1B, K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K, K1L, K1M,      K1O, K1P, \
    K0A, K0B, K0C,           K0D, K0G, K0I,           K0J, K0M,      K0N, K0O, K0P  \
) { \
    { K4A, K4B, K4C, K4D, K4E,   K4F,   K4G, K4H,   K4I, K4J, K4K,   K4L,   K4M, K4N,   K4O,   K4P }, \
    { K3A, K3B, K3C, K3D, K3E,   K3F,   K3G, K3H,   K3I, K3J, K3K,   K3L,   K3M, K3N,   KC_NO, K3P }, \
    { K2A, K2B, K2C, K2D, K2E,   K2F,   K2G, K2H,   K2I, K2J, K2K,   K2L,   K2M, K2N,   KC_NO, K2P }, \
    { K1A, K1B, K1C, K1D, K1E,   K1F,   K1G, K1H,   K1I, K1J, K1K,   K1L,   K1M, KC_NO, K1O,   K1P }, \
    { K0A, K0B, K0C, K0D, KC_NO, KC_NO, K0G, KC_NO, K0I, K0J, KC_NO, KC_NO, K0M, K0N,   K0O,   K0P }  \
}

#define LAYOUT_65_ansi( \
    K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I, K4J, K4K, K4L, K4M,      K4O, K4P, \
    K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M, K3N,      K3P, \
    K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L,      K2N,      K2P, \
    K1A,      K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K, K1L, K1M,      K1O, K1P, \
    K0A, K0B, K0C,                K0G,                K0J, K0M,      K0N, K0O, K0P  \
) { \
    { K4A, K4B,   K4C, K4D,   K4E,   K4F,   K4G, K4H,   K4I,   K4J, K4K,   K4L,   K4M,   KC_NO, K4O,   K4P }, \
    { K3A, K3B,   K3C, K3D,   K3E,   K3F,   K3G, K3H,   K3I,   K3J, K3K,   K3L,   K3M,   K3N,   KC_NO, K3P }, \
    { K2A, K2B,   K2C, K2D,   K2E,   K2F,   K2G, K2H,   K2I,   K2J, K2K,   K2L,   KC_NO, K2N,   KC_NO, K2P }, \
    { K1A, KC_NO, K1C, K1D,   K1E,   K1F,   K1G, K1H,   K1I,   K1J, K1K,   K1L,   K1M,   KC_NO, K1O,   K1P }, \
    { K0A, K0B,   K0C, KC_NO, KC_NO, KC_NO, K0G, KC_NO, KC_NO, K0J, KC_NO, KC_NO, K0M,   K0N,   K0O,   K0P }  \
}

#define LAYOUT_65_ansi_split_bs( \
    K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I, K4J, K4K, K4L, K4M, K4N, K4O, K4P, \
    K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M, K3N,      K3P, \
    K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L,      K2N,      K2P, \
    K1A,      K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K, K1L, K1M,      K1O, K1P, \
    K0A, K0B, K0C,                K0G,                K0J, K0M,      K0N, K0O, K0P  \
) { \
    { K4A, K4B,   K4C, K4D,   K4E,   K4F,   K4G, K4H,   K4I,   K4J, K4K,   K4L,   K4M,   K4N,   K4O,   K4P }, \
    { K3A, K3B,   K3C, K3D,   K3E,   K3F,   K3G, K3H,   K3I,   K3J, K3K,   K3L,   K3M,   K3N,   KC_NO, K3P }, \
    { K2A, K2B,   K2C, K2D,   K2E,   K2F,   K2G, K2H,   K2I,   K2J, K2K,   K2L,   KC_NO, K2N,   KC_NO, K2P }, \
    { K1A, KC_NO, K1C, K1D,   K1E,   K1F,   K1G, K1H,   K1I,   K1J, K1K,   K1L,   K1M,   KC_NO, K1O,   K1P }, \
    { K0A, K0B,   K0C, KC_NO, KC_NO, KC_NO, K0G, KC_NO, KC_NO, K0J, KC_NO, KC_NO, K0M,   K0N,   K0O,   K0P }  \
}
