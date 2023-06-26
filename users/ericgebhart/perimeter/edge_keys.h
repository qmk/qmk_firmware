#pragma once
/*
  Copyright 2018-2023 Erica Gebhart <e.a.gebhart@gmail.com>

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

#define CONCATENATEE(a, ...) a ## __VA_ARGS__
#define CATE(a, ...) CONCATENATEE(a, __VA_ARGS__)
// EDGES
// outside pinky keys row 0-3.
// Qwerty and Bepo, - Applies
// to foreign layouts on bepo. dvorak_bp, beakl_bp.
// Use by Wrapping the root like so. LANG_N(LEFT0)
// Add more languages by adding more definitions.
#define EDGE_KEY(KNAME) CATE(LANG_N(KNAME), EDGE_KEY_SFX)
#define LEFT_0 EDGE_KEY(LEFT0)
#define LEFT_1 EDGE_KEY(LEFT1)
#define LEFT_2 EDGE_KEY(LEFT2)
#define LEFT_3 EDGE_KEY(LEFT3)
#define RIGHT_0 EDGE_KEY(RIGHT0)
#define RIGHT_1 EDGE_KEY(RIGHT1)
#define RIGHT_2 EDGE_KEY(RIGHT2)
#define RIGHT_3 EDGE_KEY(RIGHT3)

// The edge key set name suffixes.
#define EDGE_KEY_SFX CATE(CATE(EDGE_KEY_SET_IS, _), SFX)
#define SML_SFX _sml
#define NOKC_SFX _nokc
#define NORM_SFX _norm
#define TEST_SFX _test
#define REF1_SFX _ref1
#define REF2_SFX _ref2

// Edge key sets
// a mostly normalish set of edge keys.
#define LEFT0_EN_norm KC_GRV
#define LEFT1_EN_norm KC_GRV
#define LEFT2_EN_norm KC_TAB
#define LEFT3_EN_norm KC_BSLS

#define RIGHT0_EN_norm KC_EQL
#define RIGHT1_EN_norm KC_EQL
#define RIGHT2_EN_norm KC_MINS
#define RIGHT3_EN_norm KC_SLSH

// smart lock edges mostly
#define LEFT0_EN_sml SML_NAV
#define LEFT1_EN_sml SML_NAV
#define LEFT2_EN_sml KC_TAB
#ifdef ACCENTS_MORTE_LAYER_ENABLE
#define LEFT3_EN_sml TT(_ACCENTS_MORTE_EN)
#else
#define LEFT3_EN_sml ___
#endif

#define RIGHT0_EN_sml SML_KEYPAD
#define RIGHT1_EN_sml SML_KEYPAD
#define RIGHT2_EN_sml KC_MINS
#define RIGHT3_EN_sml TT(_LAYERS)

// empty no kc edges
#define LEFT0_EN_nokc KC_NO
#define LEFT1_EN_nokc KC_NO
#define LEFT2_EN_nokc KC_NO
#define LEFT3_EN_nokc KC_NO

#define RIGHT0_EN_nokc KC_NO
#define RIGHT1_EN_nokc KC_NO
#define RIGHT2_EN_nokc KC_NO
#define RIGHT3_EN_nokc KC_NO

//test edge keys
#define LEFT0_EN_test KC_NO
#define LEFT1_EN_test KC_NO
#define LEFT2_EN_test KC_NO
#define LEFT3_EN_test KC_NO

#define RIGHT0_EN_test KC_NO
#define RIGHT1_EN_test KC_NO
#define RIGHT2_EN_test KC_NO
#define RIGHT3_EN_test KC_NO

// bepo
// mostly normal expected things
#define LEFT0_BP_norm BP_GRV
#define LEFT1_BP_norm BP_GRV
#define LEFT2_BP_norm BP_TAB
#define LEFT3_BP_norm BP_BSLS

#define RIGHT0_BP_norm BP_EQL
#define RIGHT1_BP_norm BP_EQL
#define RIGHT2_BP_norm BP_DV_MINS
#define RIGHT3_BP_norm BP_SLSH

// smart locks mostly, tab, mins
#define LEFT0_BP_sml SML_NAV
#define LEFT1_BP_sml SML_NAV
#define LEFT2_BP_sml KC_TAB
#define LEFT3_BP_sml TT(_ACCENTS_MORTE_BP)

#define RIGHT0_BP_sml SML_KEYPAD_BP
#define RIGHT1_BP_sml SML_KEYPAD_BP
#define RIGHT2_BP_sml BP_MINS
#define RIGHT3_BP_sml TT(_LAYERS)

// empty nokc edges
#define LEFT0_BP_nokc KC_NO
#define LEFT1_BP_nokc KC_NO
#define LEFT2_BP_nokc KC_NO
#define LEFT3_BP_nokc KC_NO

#define RIGHT0_BP_nokc KC_NO
#define RIGHT1_BP_nokc KC_NO
#define RIGHT2_BP_nokc KC_NO
#define RIGHT3_BP_nokc KC_NO

// test edges
#define LEFT0_BP_test KC_NO
#define LEFT1_BP_test KC_NO
#define LEFT2_BP_test KC_NO
#define LEFT3_BP_test KC_NO

#define RIGHT0_BP_test KC_NO
#define RIGHT1_BP_test KC_NO
#define RIGHT2_BP_test KC_NO
#define RIGHT3_BP_test KC_NO

// bepo

// Edges for the combo reference layers.
#define LEFT0_CB_ref1 L0_CB
#define LEFT1_CB_ref1 L1_CB
#define LEFT2_CB_ref1 L2_CB
#define LEFT3_CB_ref1 L3_CB

#define RIGHT0_CB_ref1 R0_CB
#define RIGHT1_CB_ref1 R1_CB
#define RIGHT2_CB_ref1 R2_CB
#define RIGHT3_CB_ref1 R3_CB

#define LEFT0_CB_ref2 L0_CB2
#define LEFT1_CB_ref2 L1_CB2
#define LEFT2_CB_ref2 L2_CB2
#define LEFT3_CB_ref2 L3_CB2

#define RIGHT0_CB_ref2 R0_CB2
#define RIGHT1_CB_ref2 R1_CB2
#define RIGHT2_CB_ref2 R2_CB2
#define RIGHT3_CB_ref2 R3_CB2

/******************************************************************/
/* Middle Keysets for various keyboards                           */
// MIDDLES
/// Middle left and right keys.
/******************************************************************/
#define ___MIDDLE_LT___ OSL(_LAYERS)
#define ___MIDDLE_L1___ LANG_KC(_CCCV)
#define ___MIDDLE_L2___ TO(LN_SYMB)
#define ___MIDDLE_L3___ TO(_NAV)

#define ___MIDDLE_RT___ _X_
#define ___MIDDLE_R1___ LANG_KC(_CCCV)
#define ___MIDDLE_R2___ TO(LN_TOPROWS)
#define ___MIDDLE_R3___ ___

// There are 3 keys in the middle of a 15x matrix
#define ___3_MIDDLE_T___ ___MIDDLE_LT___,    LCTL(LANG_KC(_A)), ___MIDDLE_RT___
#define ___3_MIDDLE_1___ ___MIDDLE_L1___,    LCTL(LANG_KC(_X)), ___MIDDLE_R1___
#define ___3_MIDDLE_2___ ___MIDDLE_L2___,    TO_RGB,            ___MIDDLE_R2___
#define ___3_MIDDLE_3___ ___MIDDLE_L3___,    TO(LN_SYMB),       ___MIDDLE_R3___

// 2 keys in the middle of a 14x matrix  - For viterbi and ergodox.
#define ___3_MIDDLE_T_EN___ ___3_MIDDLE_T___
#define ___3_MIDDLE_1_EN___ ___3_MIDDLE_1___
#define ___3_MIDDLE_2_EN___ ___3_MIDDLE_2___
#define ___3_MIDDLE_3_EN___ ___3_MIDDLE_3___

#define ___3_MIDDLE_T_BP___ ___3_MIDDLE_T___
#define ___3_MIDDLE_1_BP___ ___3_MIDDLE_1___
#define ___3_MIDDLE_2_BP___ ___3_MIDDLE_2___
#define ___3_MIDDLE_3_BP___ ___3_MIDDLE_3___

// 2 keys in the middle of a 14x matrix  - For viterbi and ergodox.
#define ___2_MIDDLE_T___ ___MIDDLE_LT___,    ___MIDDLE_RT___
#define ___2_MIDDLE_1___ ___MIDDLE_L1___,    ___MIDDLE_R1___
#define ___2_MIDDLE_2___ ___MIDDLE_L2___,    ___MIDDLE_R2___
#define ___2_MIDDLE_3___ ___MIDDLE_L3___,    ___MIDDLE_R3___

#define ___2_MIDDLE_T_EN___ ___2_MIDDLE_T___
#define ___2_MIDDLE_1_EN___ ___2_MIDDLE_1___
#define ___2_MIDDLE_2_EN___ ___2_MIDDLE_2___
#define ___2_MIDDLE_3_EN___ ___2_MIDDLE_3___

#define ___2_MIDDLE_T_BP___ ___2_MIDDLE_T___
#define ___2_MIDDLE_1_BP___ ___2_MIDDLE_1___
#define ___2_MIDDLE_2_BP___ ___2_MIDDLE_2___
#define ___2_MIDDLE_3_BP___ ___2_MIDDLE_3___

#define ___2_MIDDLE_T_CB___ CB_0M1, CB_0M2
#define ___2_MIDDLE_1_CB___ CB_1M1, CB_1M2
#define ___2_MIDDLE_2_CB___ CB_2M1, CB_2M2
#define ___2_MIDDLE_3_CB___ CB_3M1, CB_3M2
#define ___2_MIDDLE_4_CB___ CB_4M1, CB_4M2

#define ___2_MIDDLE_T_CB2___ CB2_0M1, CB2_0M2
#define ___2_MIDDLE_1_CB2___ CB2_1M1, CB2_1M2
#define ___2_MIDDLE_2_CB2___ CB2_2M1, CB2_2M2
#define ___2_MIDDLE_3_CB2___ CB2_3M1, CB2_3M2
#define ___2_MIDDLE_4_CB2___ CB2_4M1, CB2_4M2

#define ___3_MIDDLE_T_CB___ CB_0M1, CB_0M2, CB_0M3
#define ___3_MIDDLE_1_CB___ CB_1M1, CB_1M2, CB_1M3
#define ___3_MIDDLE_2_CB___ CB_2M1, CB_2M2, CB_2M3
#define ___3_MIDDLE_3_CB___ CB_3M1, CB_3M2, CB_3M3
#define ___3_MIDDLE_4_CB___ CB_4M1, CB_4M2, CB_4M3

#define ___3_MIDDLE_T_CB2___ CB2_0M1, CB2_0M2, CB2_0M3
#define ___3_MIDDLE_1_CB2___ CB2_1M1, CB2_1M2, CB2_1M3
#define ___3_MIDDLE_2_CB2___ CB2_2M1, CB2_2M2, CB2_2M3
#define ___3_MIDDLE_3_CB2___ CB2_3M1, CB2_3M2, CB2_3M3
#define ___3_MIDDLE_4_CB2___ CB2_4M1, CB2_4M2, CB2_4M3

#define ___4_MIDDLE_4_CB___ CB_4M1, CB_4M2, CB_4M3, CB_4M4
#define ___5_MIDDLE_4_CB___ ___4_MIDDLE_4_CB___, CB_4M5

#define ___4_MIDDLE_4_CB2___ CB2_4M1, CB2_4M2, CB2_4M3, CB2_4M4
#define ___5_MIDDLE_4_CB2___ ___4_MIDDLE_4_CB2___, CB2_4M5

#define ___4_LEFT_4_CB___  CB_4L1, CB_4L2, CB_4L3, CB_4L4
#define ___4_RIGHT_4_CB___ CB_4R1, CB_4R2, CB_4R3, CB_4R4

#define ___4_LEFT_4_CB2___ CB2_4L1, CB2_4L2, CB2_4L3, CB2_4L4
#define ___4_RIGHT_4_CB2___ CB2_4R1, CB2_4R2, CB2_4R3, CB2_4R4

#define ___5_LEFT_4_CB___ ___4_LEFT_4_CB___, CB_4L5
#define ___5_RIGHT_4_CB___ ___4_RIGHT_4_CB___, CB_4R5

#define ___5_LEFT_4_CB2___ ___4_LEFT_4_CB2___, CB2_4L5
#define ___5_RIGHT_4_CB2___ ___4_RIGHT_4_CB2___, CB2_4R5

#define ___13_BOTTOM_CB___ ___5_LEFT_4_CB___,    \
    ___3_MIDDLE_4_CB___,                         \
    ___5_RIGHT_4_CB___

#define ___12_BOTTOM_CB___ ___5_LEFT_4_CB___,    \
    ___2_MIDDLE_4_CB___,                         \
    ___5_RIGHT_4_CB___

#define ___13_BOTTOM_CB2___ ___5_LEFT_4_CB2___,  \
    ___3_MIDDLE_4_CB2___,                        \
    ___5_RIGHT_4_CB2___

#define ___12_BOTTOM_CB2___ ___5_LEFT_4_CB2___,  \
    ___2_MIDDLE_4_CB2___,                 \
    ___5_RIGHT_4_CB2___

#define ___4_BOTTOM_LEFT_CB___ ___4_LEFT_4_CB___
#define ___4_BOTTOM_RIGHT_CB___ ___4_RIGHT_4_CB___

#define ___4_BOTTOM_LEFT_CB2___ ___4_LEFT_4_CB2___
#define ___4_BOTTOM_RIGHT_CB2___ ___4_RIGHT_4_CB2___

#define ___5_BOTTOM_LEFT_CB___ ___5_LEFT_4_CB___
#define ___5_BOTTOM_RIGHT_CB___ ___5_RIGHT_4_CB___

#define ___5_BOTTOM_LEFT_CB2___ ___5_LEFT_4_CB2___
#define ___5_BOTTOM_RIGHT_CB2___ ___5_RIGHT_4_CB2___

// basically a 5th row in a 5x matrix. but maybe a 4th if there isnt a number row.
#define ___15_BOTTOM_CB___  ___5_LEFT_4_CB___,    ___5_MIDDLE_4_CB___, ___5_RIGHT_4_CB___
#define ___15_BOTTOM_CB2___  ___5_LEFT_4_CB2___,    ___5_MIDDLE_4_CB2___, ___5_RIGHT_4_CB2___

#define ___14_BOTTOM_CB___ ___5_LEFT_4_CB___, ___4_MIDDLE_4_CB___, ___5_RIGHT_4_CB___
#define ___14_BOTTOM_CB2___ ___5_LEFT_4_CB2___, ___4_MIDDLE_4_CB2___, ___5_RIGHT_4_CB2___

// becomes the upper thumbs, the real 4th row if we throw away
// the number row at the top.
// this is the 4th row on the viterbi above the thumbrow if the number
// row is not used for numbers.
#define ___4_MIDDLE_4___    LSFT(KC_TAB),    HOME_END,    KC_PGDN, KC_TAB
#define ___4_MIDDLE_4b___   TAB_BKTAB,       HOME_END,    KC_PGDN, KC_PGUP

// bottom middle row of 15 column layout.
// #define ___5_MIDDLE_THUMBS___ CTL_BSPC,    ALT_DEL,     XMONAD_ESC,  ALT_ENT,   CTL_SPC
#define ___5_MIDDLE_THUMBS___ ALT_DEL, BSPC_TOPR, ESC_SYMB, ENT_NAV, SPC_TOPR

/********************************************************************/
/*  The bottom row and thumbs as needed.                            */
/********************************************************************/
// Only the 14 and 15 wide bottom rows have bepo versions.
// all others are handled through macros.

#define ___5_BOTTOM_LEFT___  ___X2___,  KC_INS,  KC_LEFT, KC_RIGHT
#define ___5_BOTTOM_RIGHT___ KC_UP,  KC_DOWN,  KC_BSLS, ___X2___

#define ___5_BOTTOM_LEFT_EN___  ___5_BOTTOM_LEFT___
#define ___5_BOTTOM_RIGHT_EN___  ___5_BOTTOM_RIGHT___

#define ___4_BOTTOM_LEFT___  LCTL(KC_V),  SML_NAV,  KC_LEFT,   KC_RIGHT
#define ___4_BOTTOM_RIGHT___ KC_UP,       KC_DOWN, SML_KEYPAD, LCTL(KC_C)

#define ___4_BOTTOM_LEFT_EN___  ___4_BOTTOM_LEFT___
#define ___4_BOTTOM_RIGHT_EN___ ___4_BOTTOM_RIGHT___

// the bottom rows  for keyboards on bepo.
// bepo on bepo - not enough space to go around....
#define ___5_BOTTOM_LEFT_BP___  _X_,    BP_EACU,  _X_,           KC_LEFT, KC_RIGHT
#define ___5_BOTTOM_RIGHT_BP___ KC_UP,  KC_DOWN,  BP_BSLS,  BP_CCED,  BP_PERC

#define ___4_BOTTOM_LEFT_BP___  LCTL(BP_C),  SML_NAV,  KC_LEFT, KC_RIGHT
#define ___4_BOTTOM_RIGHT_BP___ KC_UP,  KC_DOWN, SML_KEYPAD_BP,  BP_CCED

// for combo ref layers for kinesis, dactyl and kinesis.
#define ___5_BOTTOM_LEFT_FR___  ___X3___,  KC_LEFT, KC_RIGHT
#define ___5_BOTTOM_RIGHT_FR___ KC_UP,  KC_DOWN,  BP_BSLS, ___X2___

// basically a 5th row in a 5x matrix. but maybe a 4th if there isnt a number row.
// need an en, because we a have a BP and we used it directly in the layout.
#define ___15_BOTTOM_EN___  ___5_BOTTOM_LEFT___,    ___5_MIDDLE_THUMBS___, ___5_BOTTOM_RIGHT___
#define ___15_BOTTOM_FR___  ___5_BOTTOM_LEFT_FR___, ___5_MIDDLE_THUMBS___, ___5_BOTTOM_RIGHT_FR___
#define ___15_BOTTOM_BP___  ___5_BOTTOM_LEFT_BP___, ___5_MIDDLE_THUMBS___, ___5_BOTTOM_RIGHT_BP___

// need an en, because we a have a BP and we used it directly in the layout.
#define ___14_BOTTOM_EN___    ___5_BOTTOM_LEFT___,    ___4_MIDDLE_4b___, ___5_BOTTOM_RIGHT___
#define ___14_BOTTOM_FR___ ___5_BOTTOM_LEFT_FR___, ___4_MIDDLE_4b___, ___5_BOTTOM_RIGHT_FR___
#define ___14_BOTTOM_BP___ ___5_BOTTOM_LEFT_BP___, ___4_MIDDLE_4b___, ___5_BOTTOM_RIGHT_BP___

// for the viterbi, turn off everything, just give the basic thumbs.
#define ___14_THUMBS_BOTTOM___   ___X4___, ___6_ERGO_THUMBS___, ___X4___

/********************************************************************/
/* BOTTOMS, sorta like THUMBS                                       */
/********************************************************************/
// for xd75 or other layouts with a center column.

  // for a last, 4th thumb row. for rebound.
  // backtab, home end, ----, pgup, pgdn, tab ?
#define ___13_BOTTOM___                                           \
  KC_BKTAB, HOME_END, KC_TAB, TT(_NAV), BSPC_SYMB, ESC_TOPR,      \
    OSL(_LAYERS),                                               \
    ENT_NAV, SPC_TOPR, KC_LEFT, KC_PGUP, KC_PGDN, KC_RIGHT

#define ___13_BOTTOM_EN___ ___13_BOTTOM___
#define ___13_BOTTOM_BP___ ___13_BOTTOM___

#define ___12_BOTTOM___                                         \
  KC_BKTAB, HOME_END, KC_TAB, TT(_NAV), BSPC_SYMB, ESC_TOPR,    \
    ENT_NAV, SPC_TOPR, KC_LEFT, KC_PGUP, KC_PGDN, KC_RIGHT

#define ___12_BOTTOM_EN___ ___12_BOTTOM___
#define ___12_BOTTOM_BP___ ___12_BOTTOM___
