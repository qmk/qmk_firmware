#pragma once

/*
  Copyright 2018 Eric Gebhart <e.a.gebhart@gmail.com>

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
// define our rows for the mod layer
// takes 5 keycodes, adds mods, and left and right
// so we get keycodes in groups of 6.
// There are 3 sets of 4 rows.
// 1 for normal 6 columns, qwerty, dvorak etc.
// 1 for bepo/normal 6 columns, qwerty, dvorak etc. on bepo.
// 1 for bepo 6 columns provided instead of a 5, for bepo which needs 3x12.
// A 5 column keyboard would need another set of MACROS.

// These macros are used in the layout wrapper macros to introduce a mod
// layer.  HomeRow mods and other things like that go here.


#include "core_keys.h"

//number row.
#define ROW0_LEFT(K01, K02, K03, K04, K05)      \
  LEFT0, K01, K02, K03, K04, K05

#define ROW0_RIGHT(K01, K02, K03, K04, K05)     \
  K01, K02, K03, K04, K05, RIGHT0

#define ROW1_LEFT(K01, K02, K03, K04, K05)      \
  LEFT1, K01, K02, K03, LT(_NAV, K04), K05

#define ROW1_RIGHT(K01, K02, K03, K04, K05)     \
  K01, K02, K03, K04, K05, RIGHT1

// home row, shift, alt, ctl, gui - gui, ctl, alt, shift.
// using MT so we can specify left and right.
// caps_word needs left and right shift.
#define ROW2_LEFT(K01, K02, K03, K04, K05)                              \
  LEFT2, MT(MOD_LSFT, K01), MT(MOD_LALT, K02), MT(MOD_LCTL, K03), MT(MOD_LGUI, K04), K05

#define ROW2_RIGHT(K01, K02, K03, K04, K05)                             \
  K01, MT(MOD_RGUI, K02),  MT(MOD_RCTL, K03), MT(MOD_RALT, K04), MT(MOD_RSFT, K05), RIGHT2 \

#define ROW3_LEFT(K01, K02, K03, K04, K05)                              \
  LEFT3, K01, LT(_TOPROWS, K02), K03, LT(_SYMB, K04), K05

#define ROW3_RIGHT(K01, K02, K03, K04, K05)                             \
  K01, LT(_SYMB, K02), LT(_NAV, K03), LT(_TOPROWS, K04), K05, RIGHT3


//-----------------------------------------------y
// For a 5 column keyboard - no edges added.
//number row.
#define ROW0_LEFT5(K01, K02, K03, K04, K05)     \
  K01, K02, K03, K04, K05

#define ROW0_RIGHT5(K01, K02, K03, K04, K05)    \
  K01, K02, K03, K04, K05

#define ROW1_LEFT5(K01, K02, K03, K04, K05)             \
  LT(_LAYERS, K01), K02, LT(_KEYPAD, K03), K04, K05

#define ROW1_RIGHT5(K01, K02, K03, K04, K05)            \
  K01, K02, LT(_KEYPAD, K03), K04, LT(_LAYERS, K05)

// home row, shift, alt, ctl, gui - gui, ctl, alt, shift.
// using MT so we can specify left and right.
// caps_word needs left and right shift.
#define ROW2_LEFT5(K01, K02, K03, K04, K05)                             \
  MT(MOD_LSFT, K01), MT(MOD_LALT, K02), MT(MOD_LCTL, K03), MT(MOD_LGUI, K04), K05

#define ROW2_RIGHT5(K01, K02, K03, K04, K05)                            \
  K01, MT(MOD_RGUI, K02),  MT(MOD_RCTL, K03), MT(MOD_RALT, K04), MT(MOD_RSFT, K05)

#define ROW3_LEFT5(K01, K02, K03, K04, K05)                     \
  K01, LT(_TOPROWS, K02), LT(_NAV, K03), LT(_SYMB, K04), K05

#define ROW3_RIGHT5(K01, K02, K03, K04, K05)                    \
  K01, LT(_SYMB, K02), LT(_NAV, K03), LT(_TOPROWS, K04), K05


//--------------------------------------------
//bepo
#define ROW0_LEFT_BP(K01, K02, K03, K04, K05)   \
  LEFT0_BP, K01, K02, K03, K04, K05

#define ROW0_RIGHT_BP(K01, K02, K03, K04, K05)  \
  K01, K02, K03, K04, K05, RIGHT0_BP

#define ROW1_LEFT_BP(K01, K02, K03, K04, K05)           \
  LEFT1_BP, K01, K02, K03, LT(_KEYPAD, K04), K05

#define ROW1_RIGHT_BP(K01, K02, K03, K04, K05)          \
  K01, K02, LT(_KEYPAD, K03), K04, K05, RIGHT1_BP

#define ROW2_LEFT_BP(K01, K02, K03, K04, K05)                           \
  LEFT2_BP, MT(MOD_RSFT, K01), MT(MOD_LALT,K02), MT(MOD_RCTL, K03), \
    MT(MOD_LGUI, K04), K05

#define ROW2_RIGHT_BP(K01, K02, K03, K04, K05)                   \
  K01, MT(MOD_RGUI, K02),  MT(MOD_RCTL, K03), MT(MOD_RALT, K04), \
    MT(MOD_RSFT, K05), RIGHT2_BP                                 \

#define ROW3_LEFT_BP(K01, K02, K03, K04, K05)                           \
  LEFT3_BP, K01, LT(_SYMB_BP, K02), LT(_NAV, K03), LT(_TOPROWS_BP, K04), K05

#define ROW3_RIGHT_BP(K01, K02, K03, K04, K05)                          \
  K01, LT(_SYMB_BP, K02), LT(_NAV, K03), LT(_TOPROWS_BP, K04), K05, RIGHT3_BP


//-------------------------------------------------
//bepo - 6 args, no left or right added.
#define ROW0_LEFT_BP6(K01, K02, K03, K04, K05, K06)     \
  K01, K02, K03, K04, K05, K06

#define ROW0_RIGHT_BP6(K01, K02, K03, K04, K05, K06 )   \
  K01, K02, K03, K04, K05, K06

#define ROW1_LEFT_BP6(K01, K02, K03, K04, K05, K06)     \
  K01, K02, K03, K04, K05, K06

#define ROW1_RIGHT_BP6(K01, K02, K03, K04, K05, K06 )   \
  K01, K02, K03, K04, K05, K06

#define ROW2_LEFT_BP6(K01, K02, K03, K04, K05, K06)             \
  K01, SFT_T(K02), ALT_T(K03), CTL_T(K04), GUI_T(K05), K06

#define ROW2_RIGHT_BP6(K01, K02, K03, K04, K05, K06)            \
  K01, GUI_T(K02), RCTL_T(K03), RALT_T(K04), RSFT_T(K05), K06

#define ROW3_LEFT_BP6(K01, K02, K03, K04, K05, K06)     \
  K01, K02, K03, K04, K05, K06

#define ROW3_RIGHT_BP6(K01, K02, K03, K04, K05, K06 )   \
  K01, K02, K03, K04, K05, K06


//-------------------------------------------------
// For a 5 column keyboard - no edges added.
//number row.
#define ROW0_LEFT5_BP(K01, K02, K03, K04, K05)  \
  K01, K02, K03, K04, K05

#define ROW0_RIGHT5_BP(K01, K02, K03, K04, K05) \
  K01, K02, K03, K04, K05

#define ROW1_LEFT5_BP(K01, K02, K03, K04, K05)          \
  LT(_LAYERS, K01), K02, K03, LT(_KEYPAD_BP, K04), K05

#define ROW1_RIGHT5_BP(K01, K02, K03, K04, K05)         \
  K01, LT(_KEYPAD_BP, K02), K03, K04, K05

// home row, shift, alt, ctl, gui - gui, ctl, alt, shift.
// using MT so we can specify left and right.
// caps_word needs left and right shift.
#define ROW2_LEFT5_BP(K01, K02, K03, K04, K05)                          \
  MT(MOD_LSFT, K01), MT(MOD_LALT, K02), MT(MOD_LCTL, K03), MT(MOD_LGUI, K04), K05

#define ROW2_RIGHT5_BP(K01, K02, K03, K04, K05)                         \
  K01, MT(MOD_RGUI, K02),  MT(MOD_RCTL, K03), MT(MOD_RALT, K04), MT(MOD_RSFT, K05)

#define ROW3_LEFT5_BP(K01, K02, K03, K04, K05)                  \
  K01, LT(_TOPROWS_BP, K02), LT(_NAV, K03), LT(_SYMB_BP, K04), K05

#define ROW3_RIGHT5_BP(K01, K02, K03, K04, K05)                         \
  K01, LT(_SYMB_BP, K02), LT(_NAV, K03), LT(_TOPROWS_BP, K04), K05
