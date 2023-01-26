/* Copyright 2022 somepin
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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT_all( \
    K0A,      K0C, K0D, K0E, K0F, K0G, K0H, K0I, K0J, K0K, K0L,      K0N,          K0P, K0Q, K0R, K0S, \
              K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K, K1L,                    K1P, K1Q, K1R, K1S, \
                                                                                   K2P, K2Q, K2R, K2S, \
    K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L, K2M, K2N, K1N,     K3P, K3Q, K3R, K3S, \
    K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M, K3N,          K4P, K4Q, K4R, K4S, \
    K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I, K4J, K4K, K4L,      K4N,             K5Q, K5R, K5S,   \
    K5A, K5B, K5C, K5D, K5E, K5F, K5G, K5H, K5I, K5J, K5K, K5L, K5M, K4M, K5N,        K6Q, K6R, K6S,   \
    K6A, K6B, K6C,      K6E, K6F,      K6H, K6I, K6J, K6K,           K6L, K6M, K6N,      K5P, K6P      \
) { \
    { K0A,  XXX,  K0C,  K0D,  K0E,  K0F,  K0G,  K0H,  K0I,  K0J,  K0K,  K0L,  XXX,  K0N,  K0P,  K0Q,  K0R,  K0S }, \
    { XXX,  XXX,  K1C,  K1D,  K1E,  K1F,  K1G,  K1H,  K1I,  K1J,  K1K,  K1L,  XXX,  K1N,  K1P,  K1Q,  K1R,  K1S }, \
    { K2A,  K2B,  K2C,  K2D,  K2E,  K2F,  K2G,  K2H,  K2I,  K2J,  K2K,  K2L,  K2M,  K2N,  K2P,  K2Q,  K2R,  K2S }, \
    { K3A,  K3B,  K3C,  K3D,  K3E,  K3F,  K3G,  K3H,  K3I,  K3J,  K3K,  K3L,  K3M,  K3N,  K3P,  K3Q,  K3R,  K3S }, \
    { K4A,  K4B,  K4C,  K4D,  K4E,  K4F,  K4G,  K4H,  K4I,  K4J,  K4K,  K4L,  K4M,  K4N,  K4P,  K4Q,  K4R,  K4S }, \
    { K5A,  K5B,  K5C,  K5D,  K5E,  K5F,  K5G,  K5H,  K5I,  K5J,  K5K,  K5L,  K5M,  K5N,  K5P,  K5Q,  K5R,  K5S }, \
    { K6A,  K6B,  K6C,  XXX,  K6E,  K6F,  XXX,  K6H,  K6I,  K6J,  K6K,  K6L,  K6M,  K6N,  K6P,  K6Q,  K6R,  K6S }  \
}
