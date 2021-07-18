/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "quantum.h"

#define XXX KC_NO

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT(\
    k0A, k0B, k0C, k0D, k0E, k0F,    k0G, k0H, k0I, k0J,    k0K, k0L, k0M, k0N, k0O, k0P, \
    k1A, k1B, k1C, k1D, k1E, k1F,    k1G, k1H, k1I, k1J,    k1K, k1L, k1M, k1N, k1O, k1P, \
    k2A, k2B, k2C, k2D, k2E, k2F,    k2G, k2H, k2I, k2J,    k2K, k2L, k2M, k2N, k2O, k2P, \
    k3A, k3B, k3C, k3D, k3E,  k3F,   k3G, k3H, k3I, k3J,   k3K,  k3L, k3M, k3N, k3O, k3P, \
    k4A, k4B, k4C, k4D,  k4E, k4F,   k4G, k4H, k4I, k4J,   k4K, k4L,  k4M, k4N, k4O, k4P, \
	     k5B, k5C,                   k5G, k5H, k5I, k5J,                   k5N, k5O      \
) { \
    { k0A, k0B, k0C, k0D, k0E, k0F,    k0G, k0H, k0I, k0J,    k0K, k0L, k0M, k0N, k0O, k0P }, \
    { k1A, k1B, k1C, k1D, k1E, k1F,    k1G, k1H, k1I, k1J,    k1K, k1L, k1M, k1N, k1O, k1P }, \
    { k2A, k2B, k2C, k2D, k2E, k2F,    k2G, k2H, k2I, k2J,    k2K, k2L, k2M, k2N, k2O, k2P }, \
    { k3A, k3B, k3C, k3D, k3E,  k3F,   k3G, k3H, k3I, k3J,   k3K,  k3L, k3M, k3N, k3O, k3P }, \
    { k4A, k4B, k4C, k4D,  k4E, k4F,   k4G, k4H, k4I, k4J,   k4K, k4L,  k4M, k4N, k4O, k4P }, \
    { XXX, k5B, k5C, XXX, XXX, XXX,    k5G, k5H, k5I, k5J,    XXX, XXX, XXX, k5N, k5O, XXX } \
}
