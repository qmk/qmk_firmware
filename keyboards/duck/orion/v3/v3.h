/* Copyright 2019 MechMerlin <mechmerlin@gmail.com>
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

#define ___ KC_NO

#define LAYOUT_tkl_ansi( \
    K5A,      K5C, K5D, K5E, K5F, K5G, K5H, K5I, K5J, K5K, K5L, K5M, K5N, K5O, K5P, K5Q,  \
    K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I, K4J, K4K, K4L, K4M,      K4R, K4O, K4P, K4Q, \
    K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M,      K3N, K3O, K3P, K3Q, \
    K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L,           K2N, \
    K1A, K1B, K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J,      K1K, K1N, K1P, \
    K0A, K0B, K0C,                     K0F, K0I,      K0K,      K0M, K0N, K0O, K0P, K0Q \
) { \
  { K5A, ___, K5C, K5D, K5E, K5F, K5G, K5H, K5I, K5J, K5K, K5L, K5M, K5N, K5O, K5P, K5Q, ___ }, \
  { K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I, K4J, K4K, K4L, K4M, ___, K4O, K4P, K4Q, K4R }, \
  { K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M, K3N, K3O, K3P, K3Q, ___ }, \
  { K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L, ___, K2N, ___, ___, ___, ___ }, \
  { K1A, K1B, K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K, ___, ___, K1N, ___, K1P, ___, ___ }, \
  { K0A, K0B, K0C, ___, ___, K0F, ___, ___, K0I, ___, K0K, ___, K0M, K0N, K0O, K0P, K0Q, ___ }  \
}
