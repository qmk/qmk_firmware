/* Copyright 2019 Draven
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

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
  k00, k01, k02, k03, k04,           kA6, kA7, kA8, kA9, kAA, \
  k10, k11, k12, k13, k14,           kB6, kB7, kB8, kB9, kBA, \
  k20, k21, k22, k23, k24,           kC6, kC7, kC8, kC9, kCA, \
  k30, k31, k32, k33, k34, k35, kA5, kD6, kD7, kD8, kD9, kDA \
) \
{ \
  { k00,   k01,   k02,   k03,   k04,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
  { k10,   k11,   k12,   k13,   k14,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
  { k20,   k21,   k22,   k23,   k24,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
  { k30,   k31,   k32,   k33,   k34,   k35,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, kA6,   kA7,   kA8,   kA9,   kAA,  }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, kB6,   kB7,   kB8,   kB9,   kBA,  }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, kC6,   kC7,   kC8,   kC9,   kCA,  }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, kA5,   kD6,   kD7,   kD8,   kD9,   kDA   }  \
}
