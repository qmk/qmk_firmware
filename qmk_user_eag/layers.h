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

#include "core_keys.h"
/*********************************************************************/
/* Non-Base Layer Definitions.                                       */
/*                                                                   */
/* Keypads, sympads, funcpads, symbols, RGB, Layers, Controls, etc.  */
/* Qwerty and Bepo versions exist as needed.                         */
/*                                                                   */
/* This file defines every auxillary layer I use on every keyboard   */
/* Ergodox, keebio/viterbi, xd75, rebound, crkbd, morpho, dactyl,..  */
/*********************************************************************/
/********************************************************************************/
/* The following Transient/Non-Base Layers are provided within.                 */
/* Each layer is named with the size of Keymatrix it has entries for.           */
/* 3x10 are usual for these.  I had 3x12's but I didn't need the edges really.  */
/* It was an attempt to accommodate Bepo which is 13 columns wide.              */
/* Even in a 3x12 Bepo is wonky. So I gave up on it. I also gave up on 4 row    */
/* layers, I really want my keys in that 3x5 space. Everything on the edges can */
/* stay as it is.  Splitting is managed in the macros as                        */
/* needed. BP indicates the Bepo equivalent to the Qwerty layer when needed.    */
/********************************************************************************/
/*                                                                              */
/* Explore below to see what they all are.                                      */
/* Naming gives the sizes of things, a prefix number is the length.             */
/* BP is the bepo version of things.                                            */
/* BKL is the beakl 15 version of a layout or chunk.                            */
/* C on the end of a name means its a compact version of something.             */
/* Compact meaning for use on a 3 row layout.                                   */
/*                                                                              */
/* TOPROWS - numbers, symbols, functions, all on one layer.                     */
/* ___TOPROWS_3x10___                                                           */
/* ___TOPROWS_BP_3x10___                                                        */
/*    // just numbers on the home row                                           */
/* ___NUM_HOME_BEAKL_3x10___                                                    */
/* ___NUM_HOME_BEAKL_BP_3x10___                                                 */
/* ___NUM_HOME_3x10___                                                          */
/* ___NUM_HOME_BP_3x10___                                                       */
/*                                                                              */
/* KEYPADS/FUNCPADS.                                                            */
/* ___KP_C_3x10___                                                              */
/* ___KP_C_BP_3x10___                                                           */
/* ___KP_C_BKL_FUNC_3x10___  -- BEAKL key/func pads.                            */
/* ___KP_C_BKL_FUNC_BP_3x10___                                                  */
/*                                                                              */
/* SYMBOLS   -Beakl or Beakl extended                                           */
/* ___SYMB_BEAKL_3x10___                                                        */
/* ___SYMB_BEAKL_BP_3x10___                                                     */
/*                                                                              */
/* Beakl extended symbol layer with additional corner symbols.                  */
/* For use with non-beakl base layers.                                          */
/* ___SYMB_BEAKLA_3x10___                                                       */
/* ___SYMB_BEAKLA_BP_3x10___                                                    */
/* For use with vi bindings optimized                                           */
/* ___SYMB_BEAKLB_3x10___                                                       */
/* ___SYMB_BEAKLB_BP_3x10___                                                    */
/*                                                                              */
/* NAVIGATION                                                                   */
/* ___NAV_3x10___                                                               */
/*                                                                              */
/* CONTROLS                                                                     */
/* ___RGB_3x10___                                                               */
/* ___ADJUST_3x10___                                                            */
 /* ___LAYERS_3x10___                                                            */
 /********************************************************************************/
 /*********************************************************************/
 /* XXXXXX Layer chunk  -- These are the final layers.                */
 /*                                                                   */
/* Each section defines the necessary pieces to create a layer.      */
/* It builds them up into consistently shaped lists for the layout   */
/* wrapper.                                                          */
/*                                                                   */
/* Each Section ends with a _Layer Chunk_. This is so the            */
/* layer can be easily given to the Layout Wrapper macros which      */
/* takes a list of keys in lengths of 2x3x5, 2x3x6, 2x4x5, or 2x4x6. */
/*                                                                   */
/* All of my keyboard definitions use these same chunks with similar */
/* macros. The differences between keyboards are all managed in the  */
/* macro. Here we just have nice rectangular sets of keys to         */
/* complete a layout.                                                */
/*********************************************************************/


/*******************************************************************/
/* A Top Rows layer.  Pick your parts.  Bepo and Qwerty            */
/*                                                                 */
/* This is, to me, a stop gap layer. If I need symbols, numbers or */
/* function keys these rows are nicely predictable to most people. */
/* I currently use the beakl number row with regular symbols.      */
/* I never use function keys for anything.                         */
/*******************************************************************/
// Kinesis function key row. I don't use them. but might as well define them.
#define ___KINTFUNC_L___ KC_ESC, ___FUNC_1_6___, KC_F7, KC_F8
// #define ___KINTFUNC_RIGHT___ KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_SLCK, KC_PAUS, KC_FN0, RESET
#define ___KINTFUNC_R___ KC_F9, KC_F10, KC_F11, KC_F12, XXX, XXX, XXX, XXX, RESET

// A TOPROWS Layer.
// set it how you like it, if you like it.
#define ___10TOPROW_1___    ___SYMS___
#define ___10TOPROW_2___    ___BKLNUMS___
#define ___10TOPROW_3___    ___FUNCS_1_10___

#define ___10TOPROW_1_FR___ ___SYMBOL_L_FR___, ___SYMBOL_R_FR___

#define ___10TOPROW_1_BP___ ___SYMBOL_BEPO_L___, ___SYMBOL_BEPO_R___
#define ___10TOPROW_2_BP___ ___BKLNUMS_BP___
#define ___10TOPROW_3___    ___FUNCS_1_10___

/********************************************************************************/
/* TOPROWS Layer chunk                                                          */
/********************************************************************************/
// altogether in a chunk.
#define ___TOPROWS_3x10___    ___10TOPROW_1___,    ___10TOPROW_2___,    ___10TOPROW_3___
#define ___TOPROWS_BP_3x10___ ___10TOPROW_1_BP___, ___10TOPROW_2_BP___, ___10TOPROW_3___
#define ___RAISE_3x10___      ___10TOPROW_1___,    ___NUMS___,      ___10TOPROW_3___
#define ___RAISE_BP_3x10___   ___10TOPROW_1_BP___, ___NUMS_BP___,   ___10TOPROW_3___

/********************************************************************************/
/*  KEYPADS.  Mostly all in Bepo and Qwerty versions                            */
/*      4 row Pads:                                                             */
/*         * The BEAKL 15 Number pad, for the left hand.                        */
/*         * Regular Number pad, for the right hand.                            */
/*         * 12 Function pad.                                                   */
/*      3 row pads:                                                             */
/*         keypad                                                               */
/*         function pad - 3x4, 12 function keys.                                */
/*                                                                              */
/*  LAYERS:                                                                     */
/*      4 Row:                                                                  */
/*         * BEAKL with a compact FuncPad on the right.                         */
/*         * Funcpad on the left, keypad on the right.                          */
/*      3 Row:                                                                  */
/*         * Funcpad on the left, keypad on the right.                          */
/*         * BEAKL with a compact FuncPad on the right.                         */
/*                                                                              */
/********************************************************************************/

// BEAKL 15 (numpad layer):
/*    +=*   ^%~ */
/*   ↹523:      */
/* - 7.104      */
/*   /698,      */

// Keypads
#define ___KEYPAD_BEAKL_L1___  _X_,        KC_PLUS,  KC_PEQL,  KC_ASTR, _X_
#define ___KEYPAD_BEAKL_L2___  TAB_BKTAB,  KC_5,     KC_2,     KC_3,   KC_COLON
#define ___KEYPAD_BEAKL_L3___  KC_7,       KC_DOT,   KC_1,     KC_0,   KC_4
#define ___KEYPAD_BEAKL_L4___  KC_SLASH,   KC_6,     KC_9,     KC_8,   KC_COMM

#define ___6KEYPAD_BEAKL_L1___     ___, _X_,        KC_PLUS,  KC_PEQL,  KC_ASTR, _X_
#define ___6KEYPAD_BEAKL_L2___     ___, TAB_BKTAB,  KC_5,     KC_2,     KC_3,   KC_COLON
#define ___6KEYPAD_BEAKL_L3___ KC_MINS, KC_7,       KC_DOT,   KC_1,     KC_0,   KC_4
#define ___6KEYPAD_BEAKL_L4___     ___, KC_SLASH,   KC_6,     KC_9,     KC_8,   KC_COMM

#define ___KEYPAD_BEAKL_R1___     ___, KC_CIRC,  KC_PERC,  KC_TILD, ___

#define ___KEYPAD_BEAKL_L1_BP___ _X_,        BP_PLUS,  BP_EQL,  BP_ASTR, _X_
#define ___KEYPAD_BEAKL_L2_BP___ TAB_BKTAB,  BP_5,     BP_2,     BP_3,   BP_COLN
#define ___KEYPAD_BEAKL_L3_BP___ BP_7,       BP_DOT,   BP_1,     BP_0,   BP_4
#define ___KEYPAD_BEAKL_L4_BP___ BP_SLSH,   BP_6,     BP_9,     BP_8,   BP_COMM

#define ___6KEYPAD_BEAKL_L1_BP___     ___, _X_,        BP_PLUS,  BP_EQL,  BP_ASTR, _X_
#define ___6KEYPAD_BEAKL_L2_BP___     ___, TAB_BKTAB,  BP_5,     BP_2,     BP_3,   BP_COLN
#define ___6KEYPAD_BEAKL_L3_BP___ BP_MINS, BP_7,       BP_DOT,   BP_1,     BP_0,   BP_4
#define ___6KEYPAD_BEAKL_L4_BP___     ___, BP_SLSH,   BP_6,     BP_9,     BP_8,   BP_COMM

#define ___KEYPAD_BEAKL_R1_BP___     ___, BP_CIRC,  BP_PERC,  BP_TILD, ___

#define ___5KEYPAD_1___ _X_, KC_7,  KC_8,    KC_9,     KC_PSLS
#define ___5KEYPAD_2___ _X_, KC_4,  KC_5,    KC_6,     KC_PAST
#define ___5KEYPAD_3___ _X_, KC_1,  KC_2,    KC_3,     KC_PMNS
#define ___5KEYPAD_4___ _X_, KC_0,  KC_DOT,  KC_PEQL,  KC_PPLS
// For Bepo
#define ___5KEYPAD_1_BP___ _X_, DB_7,  DB_8,    DB_9,     BP_SLSH
#define ___5KEYPAD_2_BP___ _X_, DB_4,  DB_5,    DB_6,     BP_ASTR
#define ___5KEYPAD_3_BP___ _X_, DB_1,  DB_2,    DB_3,     DB_MINS
#define ___5KEYPAD_4_BP___ _X_, DB_0,  DB_DOT,  DB_EQL,   BP_PLUS

// Keypad from the default keymap.c of the xd75
#define ___4KEYPAD_1_ALT___ _X_, KC_P7, KC_P8,  KC_P9,   KC_MINS
#define ___4KEYPAD_2_ALT___ _X_, KC_P4, KC_P5,  KC_P6,   KC_PLUS
#define ___4KEYPAD_3_ALT___ _X_, KC_P1, KC_P2,  KC_P3,   KC_PENT
#define ___4KEYPAD_4_ALT___ _X_, KC_P0, KC_DOT, KC_PENT, KC_PENT

// Function pad.  Same idea as above, but for function keys.
// For the left side.
#define ___5FUNCPAD_T___   _X_, KC_F10,  KC_F11,  KC_F12, _X_
#define ___5FUNCPAD_1___   _X_, KC_F7,   KC_F8,   KC_F9, _X_
#define ___5FUNCPAD_2___   _X_, KC_F4,   KC_F5,   KC_F6, _X_
#define ___5FUNCPAD_3___   _X_, KC_F1,   KC_F2,   KC_F3, _X_


// Put them together for complete left and right layers.
// Beakl keypad with a funcpad
#define ___10_KEYPAD_BKL_FUNCPAD_1___ ___KEYPAD_BEAKL_L1___, ___KEYPAD_BEAKL_R1___
#define ___10_KEYPAD_BKL_FUNCPAD_2___ ___KEYPAD_BEAKL_L2___, ___5_FUNCPADC_1___
#define ___10_KEYPAD_BKL_FUNCPAD_3___ ___KEYPAD_BEAKL_L3___, ___5_FUNCPADC_2___
#define ___10_KEYPAD_BKL_FUNCPAD_4___ ___KEYPAD_BEAKL_L4___, ___5_FUNCPADC_3___

#define ___10_KEYPAD_BKL_FUNCPAD_1_BP___ ___KEYPAD_BEAKL_L1_BP___, ___KEYPAD_BEAKL_R1_BP___
#define ___10_KEYPAD_BKL_FUNCPAD_2_BP___ ___KEYPAD_BEAKL_L2_BP___, ___5_FUNCPADC_1___
#define ___10_KEYPAD_BKL_FUNCPAD_3_BP___ ___KEYPAD_BEAKL_L3_BP___, ___5_FUNCPADC_2___
#define ___10_KEYPAD_BKL_FUNCPAD_4_BP___ ___KEYPAD_BEAKL_L4_BP___, ___5_FUNCPADC_3___

#define ___10_FUNCPAD_KEYPAD_1___   ___5FUNCPAD_T___,  ___5KEYPAD_1___
#define ___10_FUNCPAD_KEYPAD_2___   ___5FUNCPAD_1___,  ___5KEYPAD_2___
#define ___10_FUNCPAD_KEYPAD_3___   ___5FUNCPAD_2___,  ___5KEYPAD_3___
#define ___10_FUNCPAD_KEYPAD_4___   ___5FUNCPAD_3___,  ___5KEYPAD_4___

#define ___10_FUNCPAD_KEYPAD_BP_1___      ___5FUNCPAD_T_BP___,  ___5KEYPAD_1_BP___
#define ___10_FUNCPAD_KEYPAD_BP_2___      ___5FUNCPAD_1_BP___,  ___5KEYPAD_2_BP___
#define ___10_FUNCPAD_KEYPAD_BP_3___      ___5FUNCPAD_2_BP___,  ___5KEYPAD_3_BP___
#define ___10_FUNCPAD_KEYPAD_BP_4___      ___5FUNCPAD_3_BP___,  ___5KEYPAD_4_BP___

/********************************************************************************/
/* COMPACT - KEYPAD and FUNCPAD.  3 Rows.                                       */
/********************************************************************************/
// Compact versions of each. 3 rows.
//Compact keypad, 3 rows.
#define ___KEYPADC_1___ ___,    KC_7,  KC_8,    KC_9,     KC_PSLS
#define ___KEYPADC_2___ KC_DOT, KC_4,  KC_5,    KC_6,     KC_PAST
#define ___KEYPADC_3___ KC_0,   KC_1,  KC_2,    KC_3,     KC_PMNS
// For Bepo
#define ___KEYPADC_1_BP___ ___,    DB_7,  DB_8,    DB_9,  BP_SLSH
#define ___KEYPADC_2_BP___ DB_DOT, DB_4,  DB_5,    DB_6,  BP_ASTR
#define ___KEYPADC_3_BP___ DB_0,   DB_1,  DB_2,    DB_3,  DB_MINS

#define ___6KEYPADC_1___ ___,    KC_7,  KC_8,    KC_9,     KC_PSLS, ___
#define ___6KEYPADC_2___ KC_DOT, KC_4,  KC_5,    KC_6,     KC_PAST, KC_PEQL
#define ___6KEYPADC_3___ KC_0,   KC_1,  KC_2,    KC_3,     KC_PMNS, KC_PPLS
// For Bepo
#define ___6KEYPADC_1_BP___ ___,    DB_7,  DB_8,    DB_9,  BP_SLSH,  ___
#define ___6KEYPADC_2_BP___ DB_DOT, DB_4,  DB_5,    DB_6,  BP_ASTR,  DB_EQL
#define ___6KEYPADC_3_BP___ DB_0,   DB_1,  DB_2,    DB_3,  DB_MINS,  DB_PLUS

// compact 1-12 funcpad for 3 row keyboards.
#define ___5_FUNCPADC_1___   KC_F9, KC_F10, KC_F11, KC_F12, ___
#define ___5_FUNCPADC_2___   KC_F5, KC_F6,  KC_F7,  KC_F8,  ___
#define ___5_FUNCPADC_3___   KC_F1, KC_F2,  KC_F3,  KC_F4,  ___

// Compact funcpads/keypad Layer
#define ___10_KP_1C___   ___5_FUNCPADC_1___,   ___5KEYPAD_1___
#define ___10_KP_2C___   ___5_FUNCPADC_2___,   ___5KEYPAD_2___
#define ___10_KP_3C___   ___5_FUNCPADC_3___,   ___5KEYPAD_3___
// Reversed keypand-funcpad
#define ___10_KP_FP_1C___   ___5KEYPAD_1___,   ___5_FUNCPADC_1___
#define ___10_KP_FP_2C___   ___5KEYPAD_2___,   ___5_FUNCPADC_2___
#define ___10_KP_FP_3C___   ___5KEYPAD_3___,   ___5_FUNCPADC_3___

//Bepo funcpad and keypad Layer
#define ___10_KP_1_BP___ ___5_FUNCPADC_1___, ___5KEYPAD_1_BP___
#define ___10_KP_2_BP___ ___5_FUNCPADC_2___, ___5KEYPAD_2_BP___
#define ___10_KP_3_BP___ ___5_FUNCPADC_3___, ___5KEYPAD_3_BP___
// Reversed keypad-funcpad  Swap hands ?
#define ___10_KP_FP_1C_BP___   ___5KEYPAD_1_BP___,   ___5_FUNCPADC_1___
#define ___10_KP_FP_2C_BP___   ___5KEYPAD_2_BP___,   ___5_FUNCPADC_2___
#define ___10_KP_FP_3C_BP___   ___5KEYPAD_3_BP___,   ___5_FUNCPADC_3___

/********************************************************************************/
/* FUNCPAD and Keypad Layer chunks                                              */
/********************************************************************************/
// Compact, 3x10
#define ___KP_C_BKL_FUNC_3x10___                \
  ___10_KEYPAD_BKL_FUNCPAD_2___,                \
    ___10_KEYPAD_BKL_FUNCPAD_3___,              \
    ___10_KEYPAD_BKL_FUNCPAD_4___
#define ___KP_C_BKL_FUNC_BP_3x10___             \
  ___10_KEYPAD_BKL_FUNCPAD_2_BP___,             \
    ___10_KEYPAD_BKL_FUNCPAD_3_BP___,           \
    ___10_KEYPAD_BKL_FUNCPAD_4_BP___

#define ___KP_C_3x10___    ___10_KP_1C___,   ___10_KP_2C___,   ___10_KP_3C___
#define ___KP_FP_C_3x10___  ___10_KP_FP_1C___,   ___10_KP_FP_2C___,   ___10_KP_FP_3C___
#define ___KP_C_BP_3x10___ ___10_KP_1_BP___, ___10_KP_2_BP___, ___10_KP_3_BP___
#define ___KP_FP_C_BP_3x10___  ___10_KP_FP_1C_BP___,   ___10_KP_FP_2C_BP___,   ___10_KP_FP_3C_BP___



/******************************************************************/
/*                                                                */
/* Symbol layers:                                                 */
/*                                                                */
/* The BEAKL15 Symbol layer with or without additions.            */
/*                                                                */
/* There is the offical beakl symbol layer, an extended symbol    */
/* layer which is expanded with: !?@`'/-;.                        */
/*                                                                */
/* Placing these 8 keys in the pinky and index corners            */
/* at the edges of the, 3x3, BEAKL home Region.                   */
/*                                                                */
/* Beakl has these keys in it's base layer which isn't the case   */
/* for other layouts like dvorak, colemak, etc.                   */
/*                                                                */
/* The third layer moves /:? to more accessible places.           */
/* to make vi keybindings more accessible.                        */
/*                                                                */
/* Note that there are 2 widths. 12 and 10. The wider layer adds  */
/* - and ; to the middle row edges.                               */
/*                                                                */
/* Official:                                                      */
/*         <$>   [_]                                              */
/*      - \(")# %{=}| ;                                           */
/*         :*+   &^~                                              */
/*                                                                */
/* BEAKL Extended symbol layer                                    */
/* Expanded with: !?@`'/-;                                        */
/*                                                                */
/* A:                                                             */
/*        `<$>' ?[_]-                                              */
/*      - \(")# %{=}| ;                                           */
/*        @:*+; !&^~/                                             */
/*                                                                */
/* Optimized for Vi.                                              */
/* B:                                                             */
/*                                                                */
/*        `<$>' ?[_]-                                             */
/*      - \(")# !{:}/ ;                                           */
/*        @=*+; %&^~|                                             */
/*                                                                */
/*                                                                */
/* Both ; and ' could have found their dvorak positions. Analysis showed */
/* that only caused pinky overuse. Rotating the symbols around Put better */
/* keys on the index finger which showed a huge improvement in efficiency. */
/* The same is true of the exclamation point.                     */
/*                                                                */
/******************************************************************/

// Left
#define ___SB_L1___               KC_OCLTGT, KC_DLR,   KC_GT
#define ___SB_L2___ KC_BACKSLASH, KC_OCPRN,  KC_OCDQUO,   KC_RPRN,  KC_HASH
#define ___SB_L3___               KC_COLON,  KC_ASTR,  KC_PLUS
#define ___SB_L3b___              KC_EQL,    KC_ASTR,  KC_PLUS

// Bepo
#define ___SB_L1_BP___           BP_OCLTGT, BP_DLR,    DB_GRTR
#define ___SB_L2_BP___  DB_BSLS, DB_LPRN,   BP_OCDQUO, DB_RPRN,  DB_HASH
#define ___SB_L3_BP___           KC_COLON,  BP_ASTR,   BP_PLUS
#define ___SB_L3b_BP___          BP_EQL,    BP_ASTR,   BP_PLUS

// Right
#define ___SB_R1___               KC_OCBRC,   KC_UNDS,  KC_RBRC
#define ___SB_R2___    KC_PERC,   KC_OCCBR,   KC_EQL,   KC_RCBR,  KC_PIPE
#define ___SB_R3___               KC_AMPR,    KC_CIRC,  KC_TILD

#define ___SB_R2a___   KC_PERC, KC_OCCBR,   KC_EXLM,   KC_RCBR,  KC_PIPE
#define ___SB_R2b___   KC_EXLM,   KC_OCCBR,   KC_COLN,  KC_RCBR,  KC_SLASH

// Bepo
#define ___SB_R1_BP___            BP_OCBRC,   BP_UNDS,  DB_RBRC
#define ___SB_R2_BP___  BP_PERC, BP_OCCBR,   BP_EQL,   DB_RCBR,  DB_PIPE
#define ___SB_R3_BP___            BP_AMPR,   DB_CIRC,  DB_TILD

#define ___SB_R2a_BP___ BP_PERC, BP_OCCBR,   BP_EXLM,   DB_RCBR,  DB_PIPE
#define ___SB_R2b_BP___ BP_EXLM, BP_OCCBR,   KC_COLON,   DB_RCBR,  DB_SLASH

// ---------------------------
// ---------------------------

// Square it to 5,  No - or ; on the home row outer pinkies.
#define ___SYMBOLS_BEAKL_L1___  ___,  ___SB_L1___, ___
#define ___SYMBOLS_BEAKL_L2___  ___SB_L2___
#define ___SYMBOLS_BEAKL_L3___  ___,  ___SB_L3___, ___

#define ___SYMBOLS_BEAKL_R1___  ___, ___SB_R1___,  ___
#define ___SYMBOLS_BEAKL_R2___  ___SB_R2___
#define ___SYMBOLS_BEAKL_R3___  ___, ___SB_R3___,  ___
// ---------------------------
#define ___SYMBOLS_BEAKL_L1a___  KC_OCGRV,  ___SB_L1___,  KC_OCQUOT
#define ___SYMBOLS_BEAKL_L2a___  ___SB_L2___
#define ___SYMBOLS_BEAKL_L3a___  KC_AT,  ___SB_L3___,  KC_SCLN

#define ___SYMBOLS_BEAKL_R1a___  LSFT(KC_SLASH), ___SB_R1___,  KC_MINS
#define ___SYMBOLS_BEAKL_R2a___  ___SB_R2a___
#define ___SYMBOLS_BEAKL_R3a___  KC_EXLM, ___SB_R3___,  KC_SLASH
// ---------------------------
#define ___SYMBOLS_BEAKL_L1b___  ___SYMBOLS_BEAKL_L1a___
#define ___SYMBOLS_BEAKL_L2b___  ___SB_L2___
#define ___SYMBOLS_BEAKL_L3b___  KC_AT,  ___SB_L3b___,  KC_SCLN

#define ___SYMBOLS_BEAKL_R1b___ ___SYMBOLS_BEAKL_R1a___
#define ___SYMBOLS_BEAKL_R2b___  ___SB_R2b___
#define ___SYMBOLS_BEAKL_R3b___  KC_PERC, ___SB_R3___,  KC_PIPE

// BEPO
#define ___SYMBOLS_BEAKL_L1_BP___  ___,  ___SB_L1___, ___
#define ___SYMBOLS_BEAKL_L2_BP___  ___SB_L2___
#define ___SYMBOLS_BEAKL_L3_BP___  ___,  ___SB_L3___, ___

#define ___SYMBOLS_BEAKL_R1_BP___  ___, ___SB_R1___,  ___
#define ___SYMBOLS_BEAKL_R2_BP___  ___SB_R2___
#define ___SYMBOLS_BEAKL_R3_BP___  ___, ___SB_R3___,  ___
// ---------------------------
#define ___SYMBOLS_BEAKL_L1a_BP___  BP_OCGRV,  ___SB_L1___,  BP_OCQUOT
#define ___SYMBOLS_BEAKL_L2a_BP___  ___SB_L2___
#define ___SYMBOLS_BEAKL_L3a_BP___  BP_AT,  ___SB_L3___,  KC_SCLN

#define ___SYMBOLS_BEAKL_R1a_BP___  BP_QUES, ___SB_R1___,  BP_MINS
#define ___SYMBOLS_BEAKL_R2a_BP___  ___SB_R2a___
#define ___SYMBOLS_BEAKL_R3a_BP___  BP_EXLM, ___SB_R3___,  BP_SLASH
// ---------------------------
#define ___SYMBOLS_BEAKL_L1b_BP___  ___SYMBOLS_BEAKL_L1a_BP___
#define ___SYMBOLS_BEAKL_L2b_BP___  ___SB_L2___
#define ___SYMBOLS_BEAKL_L3b_BP___  BP_AT,  ___SB_L3b___,  BP_SCLN

#define ___SYMBOLS_BEAKL_R1b_BP___  ___SYMBOLS_BEAKL_R1a___
#define ___SYMBOLS_BEAKL_R2b_BP___  ___SB_R2b___
#define ___SYMBOLS_BEAKL_R3b_BP___  BP_PERC, ___SB_R3___,  KC_PIPE

// ---------------------------

// Some 10 column rows.
#define ___10_SYM_BKL_1_BP___ ___SYMBOLS_BEAKL_L1_BP___,  ___SYMBOLS_BEAKL_R1_BP___
#define ___10_SYM_BKL_2_BP___ ___SYMBOLS_BEAKL_L2_BP___,  ___SYMBOLS_BEAKL_R2_BP___
#define ___10_SYM_BKL_3_BP___ ___SYMBOLS_BEAKL_L3_BP___,  ___SYMBOLS_BEAKL_R3_BP___

#define ___10_SYM_BKL_1___    ___SYMBOLS_BEAKL_L1___,  ___SYMBOLS_BEAKL_R1___
#define ___10_SYM_BKL_2___    ___SYMBOLS_BEAKL_L2___,  ___SYMBOLS_BEAKL_R2___
#define ___10_SYM_BKL_3___    ___SYMBOLS_BEAKL_L3___,  ___SYMBOLS_BEAKL_R3___

// Some 12 column rows.
#define ___10_SYM_BKL_A1_BP___ ___SYMBOLS_BEAKL_L1a_BP___,  ___SYMBOLS_BEAKL_R1a_BP___
#define ___10_SYM_BKL_A2_BP___ ___SYMBOLS_BEAKL_L2a_BP___,  ___SYMBOLS_BEAKL_R2a_BP___
#define ___10_SYM_BKL_A3_BP___ ___SYMBOLS_BEAKL_L3a_BP___,  ___SYMBOLS_BEAKL_R3a_BP___

#define ___10_SYM_BKL_A1___ ___SYMBOLS_BEAKL_L1a___,  ___SYMBOLS_BEAKL_R1a___
#define ___10_SYM_BKL_A2___ ___SYMBOLS_BEAKL_L2a___,  ___SYMBOLS_BEAKL_R2a___
#define ___10_SYM_BKL_A3___ ___SYMBOLS_BEAKL_L3a___,  ___SYMBOLS_BEAKL_R3a___

#define ___10_SYM_BKL_B1_BP___ ___SYMBOLS_BEAKL_L1b_BP___, ___SYMBOLS_BEAKL_R1b_BP___
#define ___10_SYM_BKL_B2_BP___ ___SYMBOLS_BEAKL_L2b_BP___, ___SYMBOLS_BEAKL_R2b_BP___
#define ___10_SYM_BKL_B3_BP___ ___SYMBOLS_BEAKL_L3b_BP___, ___SYMBOLS_BEAKL_R3b_BP___

#define ___10_SYM_BKL_B1___ ___SYMBOLS_BEAKL_L1b___, ___SYMBOLS_BEAKL_R1b___
#define ___10_SYM_BKL_B2___ ___SYMBOLS_BEAKL_L2b___, ___SYMBOLS_BEAKL_R2b___
#define ___10_SYM_BKL_B3___ ___SYMBOLS_BEAKL_L3b___, ___SYMBOLS_BEAKL_R3b___

/********************************************************************************/
/* The BEAKL and BEAKL-A SYMBOL LAYER Chunks                                    */
/********************************************************************************/
// The Official beakl symbol layer as a chunk, Bepo and Qwerty
// 3x10
#define ___SYMB_BEAKL_BP_3x10___ ___10_SYM_BKL_1_BP___, \
    ___10_SYM_BKL_2_BP___,                              \
    ___10_SYM_BKL_3_BP___

#define ___SYMB_BEAKL_3x10___    ___10_SYM_BKL_1___,    \
    ___10_SYM_BKL_2___,                                 \
    ___10_SYM_BKL_3___

// Alternate Beakle symbol layer with additional corner symbols.
#define ___SYMB_BEAKLA_BP_3x10___ ___10_SYM_BKL_A1_BP___,       \
    ___10_SYM_BKL_A2_BP___,                                     \
    ___10_SYM_BKL_A3_BP___

#define ___SYMB_BEAKLA_3x10___    ___10_SYM_BKL_A1___,  \
    ___10_SYM_BKL_A2___,                                \
    ___10_SYM_BKL_A3___

#define ___SYMB_BEAKLB_BP_3x10___ ___10_SYM_BKL_B1_BP___,       \
    ___10_SYM_BKL_B2_BP___,                                     \
    ___10_SYM_BKL_B3_BP___

#define ___SYMB_BEAKLB_3x10___    ___10_SYM_BKL_B1___,  \
    ___10_SYM_BKL_B2___,                                \
    ___10_SYM_BKL_B3___

/********************************************************************************/
/* NAVIGATION  - MOUSE, Scroll, Buttons, Arrows, Tab, Home, page up/down, End   */
/* Navigation layers:                                                           */
/*    3 row Layer                                                               */
/*    4 Row Layer with repeated and swapped VI arrows, and Scroll wheel.        */
/********************************************************************************/
/*                                                                              */
/* Navigation layer with optional 4th Row....                                   */
/*                                                                              */
/* M = Mouse                                                                    */
/* B = Button                                                                   */
/* W = Wheel                                                                    */
/* AC   = Acceleration                                                          */
/* CCCV = Tap -> Ctrl-C, hold for double tap duration -> Ctrl-V                 */
/* CTCN = Tap -> Ctrl-T, hold for double tap duration -> Ctrl-N                 */
/* CWCQ = Tap -> Ctrl-W, hold for double tap duration -> Ctrl-Q                 */
/* TAB  = Tap -> Tab,    Double-tap -> Back Tab                                 */
/* HOME = Tap -> Home,   Double-tap -> End                                      */
/*                                                                              */
/* MB5  MB4    MB3    MB2  MB1     MAC0  |  CTCN  MB1    MB2    MB3  MB4   MB5 */
/* TAB  MLeft  MDown  MUp  MRight  MAC1  |  CCCV  Left   Down   UP   Right TAB */
/*      WLeft  WDown  WUp  WRight  MAC2  |  CWCQ  HOME   PGDN   PGUP END       */
/*                                                                              */
/*      Left   Down   Up   Right   CCCV  |  CCCV   MLeft  MDown  MUp  MRight    */
/*                                                                              */
/********************************************************************************/

#define ___MOUSE_LDUR___      KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R
#define ___MWHEEL_LDUR___     KC_WH_L,  KC_WH_D,  KC_WH_U,  KC_WH_R
//  really BTN 1, 2, 3, 8, 9 - according to xev.
#define ___MOUSE_BTNS_R___    KC_BTN1,  KC_BTN3,  KC_BTN2,  KC_BTN4,  KC_BTN5
#define ___4MOUSE_BTNS_R___    KC_BTN1,  KC_BTN3,  KC_BTN2,  KC_BTN4
//  really BTN 9, 8, 3, 2, 1 - according to xev
#define ___4MOUSE_BTNS_L___   KC_BTN4,  KC_BTN2,  KC_BTN3,  KC_BTN1
#define ___MOUSE_BTNS_L___    KC_BTN5,  KC_BTN4,  KC_BTN2,  KC_BTN3,  KC_BTN1
#define ___MOUSE_ACCL_012___  KC_ACL0,  KC_ACL1,  KC_ACL2
#define ___MACCL___ ___MOUSE_ACCL_012___


#define ___VI_ARROWS___          KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
#define ___HOME_PGDN_PGUP_END___ KC_HOME, KC_PGDN, KC_PGUP, KC_END

#define ___NAV_L_1___ ___4MOUSE_BTNS_L___, KC_ACL0
#define ___NAV_L_2___ ___MOUSE_LDUR___,  KC_ACL1
#define ___NAV_L_3___ ___MWHEEL_LDUR___, KC_ACL2
#define ___NAV_L_4___ ___VI_ARROWS___,   KC_CCCV

#define ___NAV_R_1___ KC_CTCN, ___4MOUSE_BTNS_R___
#define ___NAV_R_2___ KC_CCCV, ___VI_ARROWS___
#define ___NAV_R_3___ KC_CWCQ, ___HOME_PGDN_PGUP_END___
#define ___NAV_R_4___ KC_CCCV, ___MOUSE_LDUR___

#define ___6NAV_L_1___ ___MOUSE_BTNS_L___,           KC_ACL0
#define ___6NAV_L_2___ TAB_BKTAB, ___MOUSE_LDUR___,  KC_ACL1
#define ___6NAV_L_3___ ___,       ___MWHEEL_LDUR___, KC_ACL2
#define ___6NAV_L_4___ ___,       ___VI_ARROWS___,   KC_CCCV

#define ___6NAV_R_1___ KC_CTCN, ___MOUSE_BTNS_R___
#define ___6NAV_R_2___ KC_CCCV, ___VI_ARROWS___,          TAB_BKTAB
#define ___6NAV_R_3___ KC_CWCQ, ___HOME_PGDN_PGUP_END___, ___
#define ___6NAV_R_4___ KC_CCCV, ___MOUSE_LDUR___, ___

// compact. 3x10 per layer.
#define ___10_NAV_1___ ___NAV_L_1___, ___NAV_R_1___
#define ___10_NAV_2___ ___NAV_L_2___, ___NAV_R_2___
#define ___10_NAV_3___ ___NAV_L_3___, ___NAV_R_3___


/********************************************************************************/
/* The Navigation LAYER Chunks                                                  */
/********************************************************************************/
// A Navigation Layer
#define ___NAV_3x10___ ___10_NAV_1___, ___10_NAV_2___, ___10_NAV_3___
#define ___NAV_3x12___ ___12_NAV_1___, ___12_NAV_2___, ___12_NAV_3___


/********************************************************************************/
/* MEDIA  - Mute, Vol, play, pause, stop, next, prev, etc.   */
/********************************************************************************/
#define ___PRV_PLAY_NXT_STOP___ KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP
#define ___VDN_MUTE_VUP___ KC_VOLD, KC_MUTE, KC_VOLU

#define ___MUTE_PRV_PLAY_NXT_STOP___  KC_MUTE,  KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP
#define ___MUTE_PLAY_STOP___  KC_MUTE,  KC_MPLY,  KC_MSTP


/********************************************************************************/
/* RGB  - Control those lights.                                                 */

/* ___, HUE SAT_INT MOD (UP),            | */
/* ___, HUE SAT INT MOD (DOWN), RGB_TOG  | P_B_R_SW_SN___, ___ */
/* ___6___,                              | ___, ___RGB_KXGT___, ___ */
/********************************************************************************/
// RGB FUNCTION Keysets
// RGB row for the _FN layer from the redo of the default keymap.c
#define ___RGB_HUE_SAT_INT_UP___ RGB_HUI, RGB_SAI, RGB_VAI, RGB_RMOD
#define ___RGB_HUE_SAT_INT_DN___ RGB_HUD, RGB_SAD, RGB_VAD, RGB_MOD
#define ___RGB_MODE_PRV_NXT___   RGB_RMOD, RGB_MOD
#define ___RGB_TOGGLE___         RGB_TOG
#define ___RGB_P_B_R_SW_SN___    RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN
#define ___RGB_KXGT___           RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T

/// An RGB Layer
#define ___10_RGB_1___ ___RGB_HUE_SAT_INT_UP___, ___,     ___5___
#define ___10_RGB_2___ ___RGB_HUE_SAT_INT_DN___, RGB_TOG, ___RGB_P_B_R_SW_SN___
#define ___10_RGB_3___ ___5___,                                ___, ___RGB_KXGT___

/********************************************************************************/
/* The RGB LAYER Chunk                                                          */
/********************************************************************************/
#define ___RGB_3x10___ ___10_RGB_1___, ___10_RGB_2___, ___10_RGB_3___


/********************************************************************************/
/* ADJUST - Miscellaneous Melange.                                              */
/********************************************************************************/
// For an Adjust layer. Like RBB with audio, flash, etc.
#define ___ADJUST_L1___ ___RGB_HUE_SAT_INT_UP___,       RGB_TOG
#define ___ADJUST_L2___ MU_TOG, CK_TOGG, AU_ON, AU_OFF, CG_NORM
#define ___ADJUST_L3___ ___RGB_HUE_SAT_INT_DN___,       KC_RGB_T

#define ___ADJUST_R1___  ___, KC_MAKE, VRSN, MG_NKRO, KC_RESET
#define ___ADJUST_R2___  EEP_RST, ___PRV_PLAY_NXT_STOP___,
#define ___ADJUST_R3___  MG_NKRO, ___VDN_MUTE_VUP___, RGB_IDL
/********************************************************************************/
/* The Adjust LAYER Chunks                                                      */
/********************************************************************************/
#define ___ADJUST_3x10___  ___ADJUST_L1___, ___ADJUST_R1___,    \
    ___ADJUST_L2___, ___ADJUST_R2___,                           \
    ___ADJUST_L3___, ___ADJUST_R3___


/********************************************************************************/
/* LAYERS - Define a base layer, switch to any layer. Get around. Experiment.   */
/*                                                                              */
/* Base Layers on the left hand,                                                */
/* transient layers on the right. Centered on the home region.                  */
/* A good place to attach an experimental layer.                                */
/*                                                                              */
/********************************************************************************/
//  Base Layers
// this was kc_dvorak et al. But since its configurable as to who would be here
// that no longer makes sense. So next keys for locale and base layer. and a set to
// make it permanent. Cycling of layers is based on current locale.
#define ___BASE_LAYERS___ ___, KC_SET_BASE, KC_NEXT_BASE_LAYER, KC_NEXT_LOCALE, ___

// transient layers.
#define ___5_LAYERS_T___     ___, MO(_NAV),  MO(_SYMB),     MO(_KEYPAD),       MO(_TOPROWS)
#ifdef BEPO_ENABLE
#define ___5_LAYERS_T_BP___  ___, MO(_NAV),  MO(_SYMB_BP),  MO(_KEYPAD_BP),    MO(_TOPROWS_BP)
#else
#define ___5_LAYERS_T_BP___  ___, MO(_NAV),  ___3___
#endif

#ifdef RGB_LAYER_ENABLE
#define MO_RGB MO(_RGB)
#else
#define MO_RGB ___
#endif

#ifdef ADJUST_LAYER_ENABLE
#define MO_ADJUST MO(_RGB)
#else
#define MO_ADJUST ___
#endif

#define ___5_LAYERS_T_CTL___ ___, MO_RGB, ___, ___, MO_ADJUST


/// A Layers Layer
#define ___10_LAYERS_1___ ___5___,  ___5_LAYERS_T_BP___
#define ___10_LAYERS_2___ ___BASE_LAYERS___,  ___5_LAYERS_T___
#define ___10_LAYERS_3___ ___5___,            ___5_LAYERS_T_CTL___

/********************************************************************************/
/* The LAYERS LAYER Chunk                                                       */
/********************************************************************************/
#define ___LAYERS_3x10___ ___10_LAYERS_1___, ___10_LAYERS_2___, ___10_LAYERS_3___
