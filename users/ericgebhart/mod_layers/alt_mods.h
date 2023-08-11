#pragma once
/*
  Copyright 2018-2022 Eric Gebhart <e.a.gebhart@gmail.com>

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
//
// non Home row mods, mod layer.

// MOD_ROW variants.
// input 5 get six, left and right language specific outer edge keys.

// no edge keys.
// input 5 get 5 with mods applied.

// input 6 get 6 with mods applied.

// base cols in out.  5, 5_6, 6.
// input column count, output column count, if different.

// L_5  Left                 R_5 Right.
// K01, K02, K03, K04, K05 - K01, K02, K03, K04, K05
// pky, rng, mdl, idx, idx - idx, idx, mdl, rng, pnky

// ROW0  - Number row.
// LEFT.
#define ROW0L_5_alt(K01, K02, K03, K04, K05)    \
  K01, K02, K03, K04, K05
// take and put an extra column in front. Mod K01 how you want it.
#define ROW0L_6_alt(K01, K02, K03, K04, K05, K06)  K01, \
    ROW0L_5_alt(K02, K03, K04, K05, K06)

// 5 into 6, derivitive of the first two.
#define ROW0L_5_6_alt(K01, K02, K03, K04, K05)          \
  ROW0L_6_alt(LEFT_0, K01, K02, K03, K04, K05)

// RIGHT.
#define ROW0R_5_alt(K01, K02, K03, K04, K05)    \
  K01, K02, K03, K04, K05
// take and put an extra column in front. Mod K01 how you want it.
#define ROW0R_6_alt(K01, K02, K03, K04, K05, K06)       \
  ROW0R_5_alt(K01, K02, K03, K04, K05), K06

// 5 into 6, derivitive of the first two.
#define ROW0R_5_6_alt(K01, K02, K03, K04, K05)          \
  ROW0R_6_alt(K01, K02, K03, K04, K05, RIGHT_0)


// ROW1
// LEFT.
#define ROW1L_5_alt(K01, K02, K03, K04, K05)    \
  K01, K02, K03, K04, K05
// take and put an extra column in front. Mod K01 how you want it.
#define ROW1L_6_alt(K01, K02, K03, K04, K05, K06)  K01, \
    ROW1L_5_alt(K02, K03, K04, K05, K06)

// 5 into 6, derivitive of the first two.
#define ROW1L_5_6_alt(K01, K02, K03, K04, K05)          \
  ROW1L_6_alt(LEFT_1, K01, K02, K03, K04, K05)

// RIGHT.
#define ROW1R_5_alt(K01, K02, K03, K04, K05)                            \
  K01, K02, K03, K04, K05                                               \
    // take and put an extra column in front. Mod K01 how you want it.
#define ROW1R_6_alt(K01, K02, K03, K04, K05, K06)       \
  ROW1R_5_alt(K01, K02, K03, K04, K05), K06

// 5 into 6, derivitive of the first two.
#define ROW1R_5_6_alt(K01, K02, K03, K04, K05)          \
  ROW1R_6_alt(K01, K02, K03, K04, K05, RIGHT_1)


// HOME ROW - ROW2
// LEFT.
#define ROW2L_5_alt(K01, K02, K03, K04, K05)            \
  K01, K02, LT(_NAV, K03), MT(MOD_LSFT, K04), K05
// take and put an extra column in front. Mod K01 how you want it.
#define ROW2L_6_alt(K01, K02, K03, K04, K05, K06)  K01, \
    ROW2L_5_alt(K02, K03, K04, K05, K06)

// 5 into 6, derivitive of the first two.
#define ROW2L_5_6_alt(K01, K02, K03, K04, K05)          \
  ROW2L_6_alt(LEFT_2, K01, K02, K03, K04, K05)

// RIGHT.
#define ROW2R_5_alt(K01, K02, K03, K04, K05)                            \
  K01, MT(MOD_LSFT, K02),  LT(_NAV, K03), K04, K05                      \
    // take and put an extra column in front. Mod K01 how you want it.
#define ROW2R_6_alt(K01, K02, K03, K04, K05, K06)       \
  ROW2R_5_alt(K01, K02, K03, K04, K05),  K06

// 5 into 6, derivitive of the first two.
#define ROW2R_5_6_alt(K01, K02, K03, K04, K05)          \
  ROW2R_6_alt(K01, K02, K03, K04, K05, RIGHT_2)


// ROW 3
// LEFT.
#define ROW3L_5_alt(K01, K02, K03, K04, K05)            \
  K01, K02, LT(_NAV, K03), K04, MT(MOD_LSFT, K05)
// take and put an extra column in front. Mod K01 how you want it.
#define ROW3L_6_alt(K01, K02, K03, K04, K05, K06)  K01, \
    ROW3L_5_alt(K02, K03, K04, K05, K06)

// 5 into 6, derivitive of the first two.
#define ROW3L_5_6_alt(K01, K02, K03, K04, K05)          \
  ROW3L_6_alt(LEFT_3,  K01, K02, K03, K04, K05)

// RIGHT.
#define ROW3R_5_alt(K01, K02, K03, K04, K05)    \
  K01, K02, K03, K04, K05
// take and put an extra column in front. Mod K01 how you want it.
#define ROW3R_6_alt(K01, K02, K03, K04, K05, K06)  K01, \
    ROW3R_5_alt(K02, K03, K04, K05, K06)

// 5 into 6, derivitive of the first two.
#define ROW3R_5_6_alt(K01, K02, K03, K04, K05)          \
  ROW3R_6_alt(K01, K02, K03, K04, K05, RIGHT_3)
