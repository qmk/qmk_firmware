/* Copyright 2020 Lfgberg
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
 */

#pragma once
#include "quantum.h"

// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
  k01, k02, k03,      k05, k06,      k08, \
  k11,      k13,      k15, k16, k17, k18, \
  k21, k22, k23, k24, k25, k26,      k28 \
)\
{\
  { k01, k02,   k03, KC_NO, k05, k06, KC_NO, k08 }, \
  { k11, KC_NO, k13, KC_NO, k15, k16, k17,   k18 }, \
  { k21, k22,   k23, k24,   k25, k26, KC_NO, k28 }, \
}

/*
 * ,-------------------------------------------------,
 * | 1  | 2  |    | 3  |    | 5  |    | 6  |    | 8  |
 * |----|----|----|----|----|----|----|----|----|----|
 * | 11 |    |    | 13 |    | 15 |    | 16 | 17 | 18 |
 * |----|----|----|----|----|----|----|----|----|----|
 * | 21 | 22 |    | 23 | 24 | 25 |    | 26 |    | 28 |
 * ,-------------------------------------------------,
 */
