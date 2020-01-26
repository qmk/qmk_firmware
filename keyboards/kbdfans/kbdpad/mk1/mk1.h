/* Copyright 2019 MechMerlin
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

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array

#define LAYOUT(   \
  k52,  k53,           \
  k40, k41, k42, k43,  \
  k30, k31, k32,       \
  k20, k21, k22, k23,  \
  k10, k11, k12,       \
  k00, k02, k03        \
){ \
  { k00,   KC_NO, k02, k03   }, \
  { k10,   k11,   k12, KC_NO }, \
  { k20,   k21,   k22, k23   }, \
  { k30,   k31,   k32, KC_NO }, \
  { k40,   k41,   k42, k43   }, \
  { KC_NO, KC_NO, k52, k53   }, \
}
