/* Copyright 2018 Ryan "Izzy" Bales
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

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
/* YD68 ANSI layout
   * ,----------------------------------------------------------------.
   * | 00 |01| 02| 03| 04| 05| 06| 07| 08| 09| 0a| 0b| 0c|  0e   | 48 |
   * |----------------------------------------------------------------|
   * | 10  | 11| 12| 13| 14| 15| 16| 17| 18| 19| 1a| 1b| 1c|  1d | 1e |
   * |----------------------------------------------------------------|
   * | 20    | 21| 22| 23| 24| 25| 26| 27| 28| 29| 2a| 2b|  2d   | 2e |
   * |----------------------------------------------------------------|
   * | 30     | 32| 33| 34| 35| 36| 37| 38| 39| 3a| 3b|  3c  | 3d| 3e |
   * |----------------------------------------------------------------|
   * | 40 | 41 | 42 |            46         | 49| 4a|  4b| 4c| 4d| 4e |
   * `----------------------------------------------------------------'
 */
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array

#define LAYOUT_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0E, k48, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B,      k2D, k2E, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, \
    k40, k41, k42,                k46,           k49, k4A, k4B, k4C, k4D, k4E \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, XXX, k0E }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, XXX, k2D, k2E }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E }, \
    { k40, k41, k42, XXX, XXX, XXX, k46, XXX, k48, k49, k4A, k4B, k4C, k4D, k4E } \
}
