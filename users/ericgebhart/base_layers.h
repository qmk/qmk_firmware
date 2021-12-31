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

#include "core_keysets.h"

/******************************************************************/
/* This is where I put my Keyboard layouts, Everything on the     */
/* edges, the functions on keys like LT() and SFT_T()             */
/* can be applied here. The physical shape of the keyboard is     */
/* also accounted for here. This makes it very simple to add a    */
/* new keyboard and reuse all of my layouts and layers            */
/*                                                                */
/* The particular pieces we define here (as needed) are:          */
/*     * Edge pinky keys, */
/*     * Middle section keys */
/*     * Bottom/5th row */
/*     * Thumbkeys */
/*     * Any functional additions to wrap the keys. ie. LT()      */
/*                                                                */
/* With all of that in hand, we then create a LAYOUT wrapper      */
/* macro that takes a list of keys, to create a keyboard matrix   */
/* that fits the keyboard. Simple.                                */
/*                                                                */
/* The thumb keys, the bottom rows, etc.                          */
/*                                                                */
/* An attempt has been made to adapt the kinesis and ergodox      */
/* Thumb keys to the rectangular shapes of the xd75 and viterbi.  */
/* which are 15x and 14x matrices respectively.                   */
/* The Corne was a perfect fit                                    */
/******************************************************************/

/******************************************************************/
/* * The XD75 is a 5x15 Ortholinear matrix which means it has 3   */
/*       keys inbetween the usual left and right hand keys        */
/* * The Viterbi is a split 5x14 Ortholinear with 2 middle keys.  */
/* * The Ergodox is a split 5x14 Ortholinear with 2 middle keys,  */
/*       thumbkeys. It is missing middle keys on (home) row 3.    */
/* * The Corne is a split 3x12 with 6 thumb keys. It has no       */
/*       extra middle keys                                        */
/*                                                                */
/******************************************************************/


/******************************************************************/
/*   In all cases these keyboards are defined in a matrix which is */
/*   a set of rows. Maybe like so, or not.                         */
/*                                                                 */
/*   -------------------------|------------------------ */
/*   | Left0 | Numbers L | mid|dle0 | numbers R | Right0 | */
/*   | Left1 | keys0-5   | mid|dle1 | Keys6-10  | Right1 | */
/*   | Left2 | keys11-15 | mid|dle2 | Keys16-20 | Right2 | */
/*   | Left3 | keys20-25 | mid|dle3 | Keys25-30 | Right3 | */
/*   | Row5L                  |                    Row5R | */
/*   |               ThumbsL  | ThumbsR                  | */
/*   -------------------------|------------------------ */

/* Generally speaking, the keys on the right and left don't change. */
/* Neither does the bottom row or the thumbs. Frequently the numbers */
/* row is identical across layers. Mostly, we want our Base layers to */
/* be predctable.                                                     */

// EDGES
// outside pinky keys row 0-3.
// Qwerty and Bepo, - Applies
// to foreign layouts on bepo. dvorak_bp, beakl_bp.
#define LEFT0 KC_GRV
#define LEFT1 KC_GRV
#define LEFT2 KC_TAB
#define LEFT3 KC_BSLASH
//#define LEFT3 KC_COLN

#define LEFT0_BP DB_GRV
#define LEFT1_BP DB_GRV
#define LEFT2_BP KC_TAB
#define LEFT3_BP DB_BACKSLASH
//#define LEFT3_BP BP_COLN

#define RIGHT0 KC_EQL
#define RIGHT1 KC_SLASH
#define RIGHT2 KC_MINS
#define RIGHT3 KC_SCLN

#define RIGHT0_BP BP_EQL
#define RIGHT1_BP BP_SLSH
#define RIGHT2_BP BP_MINS
#define RIGHT3_BP BP_SCLN

// define our rows for the mod layer
// takes 5 keycodes, adds mods, and left and right
// so we get keycodes in groups of 6.

//number row.
#define ROW0_LEFT(K01, K02, K03, K04, K05)      \
  LEFT0, K01, K02, K03, K04, K05

#define ROW0_RIGHT(K01, K02, K03, K04, K05)     \
  K01, K02, K03, K04, K05, RIGHT0

#define ROW1_LEFT(K01, K02, K03, K04, K05)      \
  LEFT1, K01, K02, K03, K04, K05

#define ROW1_RIGHT(K01, K02, K03, K04, K05)     \
  K01, K02, K03, K04, K05, RIGHT1

// home row, shift, alt, ctl, gui - gui, ctl, alt, shift.
// using MT so we can specify left and right.
// caps_word needs left and right shift.
#define ROW2_LEFT(K01, K02, K03, K04, K05)                              \
  LEFT2, MT(MOD_LSFT, K01), MT(MOD_LALT, K02), MT(MOD_LCTL, K03), MT(MOD_LGUI, K04), K05

#define ROW2_RIGHT(K01, K02, K03, K04, K05)                             \
  K01, MT(MOD_RGUI, K02),  MT(MOD_RCTL, K03), MT(MOD_RALT, K04), MT(MOD_RSFT, K05), RIGHT2 \

#define ROW3_LEFT(K01, K02, K03, K04, K05)      \
  LEFT3, K01, K02, LT(_NAV, K03), K04, K05

#define ROW3_RIGHT(K01, K02, K03, K04, K05)     \
  K01, K02, LT(_NAV, K03), K04, K05, RIGHT3

//bepo
#define ROW0_LEFT_BP(K01, K02, K03, K04, K05)   \
  LEFT0_BP, K01, K02, K03, K04, K05

#define ROW0_RIGHT_BP(K01, K02, K03, K04, K05)  \
  K01, K02, K03, K04, K05, RIGHT0_BP

#define ROW1_LEFT_BP(K01, K02, K03, K04, K05)   \
  LEFT1_BP, K01, K02, K03, K04, K05

#define ROW1_RIGHT_BP(K01, K02, K03, K04, K05)  \
  K01, K02, K03, K04, K05, RIGHT1_BP

#define ROW2_LEFT_BP(K01, K02, K03, K04, K05)                   \
  LEFT2_BP, MT(MOD_RSFT, K01), MT(MOD_LALT,K02), MT(MOD_RCTL, K03), MT(MOD_LGUI, K04), K05

#define ROW2_RIGHT_BP(K01, K02, K03, K04, K05)                          \
  K01, MT(MOD_RGUI, K02),  MT(MOD_RCTL, K03), MT(MOD_RALT, K04), MT(MOD_RSFT, K05), RIGHT2_BP \

#define ROW3_LEFT_BP(K01, K02, K03, K04, K05)   \
  LEFT3_BP, K01, K02, K03, K04, K05

#define ROW3_RIGHT_BP(K01, K02, K03, K04, K05)  \
  K01, K02, K03, K04, K05, RIGHT3_BP

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

/******************************************************************/
/* Middle Keysets for various keyboards                           */
// MIDDLES
/// Middle left and right keys.
/******************************************************************/
#define ___MIDDLE_LT___ OSL(_LAYERS)
#define ___MIDDLE_L1___ KC_CCCV
#define ___MIDDLE_L2___ TO(_SYMB)
#define ___MIDDLE_L3___ TO(_NAV)

#define ___MIDDLE_RT___ _X_
#define ___MIDDLE_R1___ KC_CCCV
#define ___MIDDLE_R2___ TO(_TOPROWS)
#define ___MIDDLE_R3___ OSL(_KEYPAD)

#define ___MIDDLE_L1_BP___ BP_CCCV
#define ___MIDDLE_L2_BP___  TO(_SYMB_BP)

#define ___MIDDLE_R1_BP___ BP_CCCV
#define ___MIDDLE_R2_BP___ TO(_KEYPAD_BP)
#define ___MIDDLE_R3_BP___ OSL(_KEYPAD_BP)

// 3 keys in the middle of a 15x matrix
#define ___3_MIDDLE_T___ ___MIDDLE_LT___,    LCTL(KC_A),        ___MIDDLE_RT___
#define ___3_MIDDLE_1___ ___MIDDLE_L1___,    LCTL(KC_X),        ___MIDDLE_R1___
#define ___3_MIDDLE_2___ ___MIDDLE_L2___,    TO(_RGB),          ___MIDDLE_R2___
#define ___3_MIDDLE_3___ ___MIDDLE_L3___,    TO(_SYMB),   ___MIDDLE_R3___

// The same, for BEPO
#define ___3_MIDDLE_T_BP___ ___MIDDLE_LT___,     LCTL(BP_A),         ___MIDDLE_RT___
#define ___3_MIDDLE_1_BP___ ___MIDDLE_L1_BP___,  LCTL(BP_X),         ___MIDDLE_R1_BP___
#define ___3_MIDDLE_2_BP___ ___MIDDLE_L2_BP___,  TO(_RGB),           ___MIDDLE_R2_BP___
#define ___3_MIDDLE_3_BP___ ___MIDDLE_L3___,     TO(_SYMB_BP), ___MIDDLE_R3_BP___

// 2 keys in the middle of a 14x matrix  - For viterbi and ergodox.
#define ___2_MIDDLE_T___ ___MIDDLE_LT___,    ___MIDDLE_RT___
#define ___2_MIDDLE_1___ ___MIDDLE_L1___,    ___MIDDLE_R1___
#define ___2_MIDDLE_2___ ___MIDDLE_L2___,    ___MIDDLE_R2___
#define ___2_MIDDLE_3___ ___MIDDLE_L3___,    ___MIDDLE_R3___

// The same, for BEPO
#define ___2_MIDDLE_T_BP___ ___MIDDLE_LT___,     ___MIDDLE_RT___
#define ___2_MIDDLE_1_BP___ ___MIDDLE_L1_BP___,  ___MIDDLE_R1_BP___
#define ___2_MIDDLE_2_BP___ ___MIDDLE_L2_BP___,  ___MIDDLE_R2_BP___
#define ___2_MIDDLE_3_BP___ ___MIDDLE_L3___,     ___MIDDLE_R3_BP___

/********************************************************************/
/* THUMBS  */
/* Define the thumb clusters for all the keyboards.                 */
/********************************************************************/

// for xd75 or other layouts with a center column.
// #define ___5_MIDDLE_THUMBS___ CTL_BSPC,    ALT_DEL,     XMONAD_ESC,  ALT_ENT,   CTL_SPC
#define ___5_MIDDLE_THUMBS___ ALT_DEL, BSPC_TOPR, ESC_SYMB, ENT_NAV, SPC_TOPR
#define ___5_MIDDLE_THUMBS_BP___ ALT_DEL, BSPC_TOPR_BP, ESC_SYMB_BP, ENT_NAV, SPC_TOPR_BP

// for a last, 4th thumb row. for rebound.
// backtab, home end, ----, pgup, pgdn, tab ?
#define ___13_BOTTOM___                                           \
  KC_BKTAB, HOME_END, KC_TAB, TT(_NAV), BSPC_SYMB, ESC_TOPR,      \
    OSL(_LAYERS),                                               \
    ENT_NAV, SPC_TOPR, KC_LEFT, KC_PGUP, KC_PGDN, KC_RIGHT

#define ___13_BOTTOM_BP___                                \
  KC_BKTAB, HOME_END, KC_TAB, TT(_NAV), BSPC_SYMB_BP, ESC_TOPR_BP, \
    OSL(_LAYERS),                                                  \
    ENT_NAV, SPC_TOPR_BP, KC_LEFT, KC_PGUP, KC_PGDN, KC_RIGHT

// becomes the upper thumbs, the real 4th row if we throw away
// the number row at the top.
// this is the 4th row on the viterbi above the thumbrow if the number
// row is not used for numbers.
#define ___4_MIDDLE_4___    LSFT(KC_TAB),    HOME_END,    KC_PGDN, KC_TAB
#define ___4_MIDDLE_4b___   TAB_BKTAB,       HOME_END,    KC_PGDN, KC_PGUP

/********************************************************************/
/**  The bottom row and thumbs as needed.                          **/
/********************************************************************/
// I do not use those pinky keys. I had useful things there but there
// are better more useful ways than those pinkys.
#define ___5_BOTTOM_LEFT___  ___X2___,  KC_INS,  KC_LEFT, KC_RIGHT
#define ___5_BOTTOM_RIGHT___ KC_UP,  KC_DOWN,  KC_BSLASH, ___X2___

#define ___4_BOTTOM_LEFT___  LCTL(KC_V),  KC_INS,  KC_LEFT,   KC_RIGHT
#define ___4_BOTTOM_RIGHT___ KC_UP,       KC_DOWN, KC_BSLASH, LCTL(KC_C)

// the bottom rows  for keyboards on bepo.
// bepo on bepo - not enough space to go around....
#define ___5_BOTTOM_LEFT_BP___  _X_,    BP_EACU,  _X_,           KC_LEFT, KC_RIGHT
#define ___5_BOTTOM_RIGHT_BP___ KC_UP,  KC_DOWN,  DB_BACKSLASH,  BP_CCED,  BP_PERC

#define ___4_BOTTOM_LEFT_BP___  LCTL(BP_C),  BP_EACU,  KC_LEFT, KC_RIGHT
#define ___4_BOTTOM_RIGHT_BP___ KC_UP,  KC_DOWN, DB_BACKSLASH,  BP_CCED

// for dvorak and beakl on bepo
#define ___5_BOTTOM_LEFT_FR___  ___X3___,  KC_LEFT, KC_RIGHT
#define ___5_BOTTOM_RIGHT_FR___ KC_UP,  KC_DOWN,  DB_BACKSLASH, ___X2___

// basically a 5th row in a 5x matrix. but maybe a 4th if there isnt a number row.
#define ___15_BOTTOM___     ___5_BOTTOM_LEFT___,    ___5_MIDDLE_THUMBS___, ___5_BOTTOM_RIGHT___
#define ___15_BOTTOM_FR___  ___5_BOTTOM_LEFT_FR___, ___5_MIDDLE_THUMBS___, ___5_BOTTOM_RIGHT_FR___
#define ___15_BOTTOM_BP___  ___5_BOTTOM_LEFT_BP___, ___5_MIDDLE_THUMBS___, ___5_BOTTOM_RIGHT_BP___

#define ___14_BOTTOM___    ___5_BOTTOM_LEFT___,    ___4_MIDDLE_4b___, ___5_BOTTOM_RIGHT___
#define ___14_BOTTOM_FR___ ___5_BOTTOM_LEFT_FR___, ___4_MIDDLE_4b___, ___5_BOTTOM_RIGHT_FR___
#define ___14_BOTTOM_BP___ ___5_BOTTOM_LEFT_BP___, ___4_MIDDLE_4b___, ___5_BOTTOM_RIGHT_BP___
#define ___14_THUMBS_BOTTOM___   ___X4___, ___6_MIDDLE_THUMBS___, ___X4___

// bottom row of ergodox thumbs, bottom middle of all layouts.
// start with the minimilist thumb row of 6, like the Corne, 2x3.

#define ___THUMBS_1___    TT(_KEYPAD),    MO(_ADJUST), MO(_LAYERS), OSL(_TOPROWS)
#define ___THUMBS_1_BP___ TT(_KEYPAD_BP), MO(_ADJUST), MO(_LAYERS), OSL(_TOPROWS_BP)
#define ___THUMBS_2___                      HOME_END,      KC_PGUP
#define ___THUMBS_3___                         ___6_ERGO_THUMBS___

#define ___4_THUMBS_1_BP___      TT(_KEYPAD_BP), KC_HOME, KC_PGUP, OSL(_TOPROWS_BP)
#define ___4_THUMBS_1___           TT(_KEYPAD), KC_HOME, KC_PGUP, OSL(_TOPROWS)
#define ___6_THUMBS_2___  KC_LSFT,    KC_BKTAB, KC_END,  KC_PGDN, KC_TAB, KC_RSFT

#define ___6_THUMBS_2b___    BSPC_SYMB, ESC_TOPR, KC_END,  KC_PGDN, ENT_NAV, SPC_TOPR
#define ___6_ERGO_THUMBSb___ TT(_LAYERS), BSPC_SYMB, ESC_TOPR, ENT_NAV, TT(_NAV), KC_XM_PORD
#define ___6_THUMBS_2b_BP___ BSPC_SYMB_BP, ESC_TOPR_BP, KC_END,  KC_PGDN, ENT_TOPR_BP, SPC_NAV

#define ___6_ERGO_THUMBS___ TT(_NAV), BSPC_SYMB, ESC_TOPR, ENT_NAV, SPC_ADJ, KC_XM_PORD

#define ___6_ERGO_THUMBS_BP___ TT(_NAV), BSPC_SYMB_BP, ESC_TOPR, ENT_NAV, SPC_ADJ_BP, BP_XM_PORD
#define ___6_ERGO_THUMBS2_BP___ TT(_NAV), BSPC_SYMB_BP, ESC_TOPR, ENT_NAV, SPC_ADJ_BP, BP_XM_PORD
#define ___6_MIDDLE_THUMBS___ ___6_ERGO_THUMBS___

#define ___6_CRKBD_THUMBS___ TT(_NAV) ,  BSPC_SYMB, ESC_TOPR, ENT_NAV, SPC_ADJ, TT(_LAYERS)
#define ___6_CRKBD_THUMBS_BP___ TT(_NAV),  BSPC_SYMB_BP, ESC_TOPR_BP, ENT_NAV, SPC_ADJ_BP, TT(_LAYERS)

#define ___12_DOX_ALL_THUMBS___    ___THUMBS_1___,    ___THUMBS_2___, ___THUMBS_3___
#define ___12_DOX_ALL_THUMBS_BP___ ___THUMBS_1_BP___, ___THUMBS_2___, ___THUMBS_3___

#define ___16_ALL_THUMBSb___  ___4_THUMBS_1___,   ___6_THUMBS_2b___, ___6_ERGO_THUMBSb___
#define ___16_ALL_THUMBS___   ___4_THUMBS_1___,    ___6_THUMBS_2___, ___6_ERGO_THUMBS___
#define ___16_ALL_THUMBSb_BP___ ___4_THUMBS_1_BP___, ___6_THUMBS_2b_BP___, ___6_ERGO_THUMBS___
#define ___16_ALL_THUMBS_BP___ ___4_THUMBS_1_BP___, ___6_THUMBS_2_BP___, ___6_ERGO_THUMBS_BP___



// Since our quirky block definitions are basically a list of comma separated
// arguments, we need a wrapper in order for these definitions to be
// expanded before being used as arguments to the LAYOUT_xxx macro.
#if (!defined(LAYOUT) && defined(KEYMAP))
#define LAYOUT KEYMAP
#endif

// every keyboard has it's Layout. We start there and make a var args
// out of it.

#define LVARG_ergodox(...)    LAYOUT_ergodox(__VA_ARGS__)
#define LVARG_edox(...)       LAYOUT_ergodox_pretty(__VA_ARGS__)
#define LAYOUT_VARG(...)      LAYOUT(__VA_ARGS__)
#define LAYOUT_PVARG(...)     LAYOUT_pretty(__VA_ARGS__)

#define LVARG_4x12(...)       LAYOUT_ortho_4x12(__VA_ARGS__)
#define LVARG_5x12(...)       LAYOUT_ortho_5x12(__VA_ARGS__)
#define LVARG_5x14(...)       LAYOUT_ortho_5x14(__VA_ARGS__)
#define LVARG_5x15(...)       LAYOUT_ortho_5x15(__VA_ARGS__)

/*
  | Left | Numbers L | middle | numbers R | Right |
  | Left | keys0-5   | middle | Keys6-10  | Right |
  | Left | keys11-15 | middle | Keys16-20 | Right |
  | Left | keys20-25 | middle | Keys25-30 | Right |
  |Row5L                                  Row5R   |
  |ThumbsL                                ThumbsR |
*/

/* Assuming that left, midddle, right, row5, and thumbs stay the same, */
/* numbers, no numbers, numbers never change, whatever.                */
/*   we can have a layout macro that takes a nice rectangle of keys.   */

/* Actually, because of Bepo, each keyboard currently requires four of */
/* these macros. One for Qwerty, One for foreign layouts on bepo like */
/* dvorak and beakl on bepo instead of on Qwerty. Then another for the Bepo */
/* layout because unlike the rest of the layouts Bepo doesn't fit in */
/* 3x10. It wants 3x12. So there are potentially 4 macros per keyboard here. */
/* XXXX_base, XXXX_base_bepo, XXXX_base_bepo6, The 4th macro */
/* is XXXXX_transient and generally works for all other */
/* non base layers.                                       */
/* The base and transient versions are all that is necessary, if bepo is */
/*   not needed. */


/* All layouts are relatively simple to make. */
/* The ROW macros add a universal mod layer so that mods can be defined once */
/* and used everywhere. No matter the keymap or layer. this allows actual maps */
/* like dvorak, qwerty, colemak, beakl, etc., to be defined simply. */


/* Additional, more complicated layouts can be found here.*/
/* examples can be found in crkbd/keymaps/ericgebhart */
/* examples can be found in kinesis/keymaps/ericgebhart */
/* examples can be found in ergodox/keymaps/ericgebhart */
/* examples can be found in montsinger/rebound/rev4/keymaps/ericgebhart */



/********************************************************************/
/* xiudi/xd75  - Ortholinear 5x15  */
/********************************************************************/
/// These first two base layout templates take sets of 5 keys, left and right.
// Using 4 sets allows for changing the number row if you have one.
// if you never change the number row, then use 3 sets of left and right.
// and define the number row here.
#define LAYOUT_5x15_base(                                         \
                         K01, K02, K03, K04, K05,                 \
                         K06, K07, K08, K09, K0A,                 \
                         K11, K12, K13, K14, K15,                 \
                         K16, K17, K18, K19, K1A,                 \
                         K21, K22, K23, K24, K25,                 \
                         K26, K27, K28, K29, K2A,                 \
                         K31, K32, K33, K34, K35,                 \
                         K36, K37, K38, K39, K3A)                 \
  LVARG_5x15(                                                     \
            ROW0_LEFT(K01, K02, K03, K04, K05), \
            ___3_MIDDLE_T___,                                           \
            ROW0_RIGHT(K06, K07, K08, K09, K0A),                        \
                                                                        \
            ROW1_LEFT(K11, K12, K13, K14, K15),                         \
            ___3_MIDDLE_1___,                                           \
            ROW1_RIGHT(K16, K17, K18, K19, K1A),                        \
                                                                        \
            ROW2_LEFT(K21, K22, K23, K24, K25),                         \
            ___3_MIDDLE_2___,                                           \
            ROW2_RIGHT(K26, K27, K28, K29, K2A),                        \
                                                                        \
            ROW3_LEFT(K31, K32, K33, K34, K35),                         \
            ___3_MIDDLE_3___,                                           \
            ROW3_RIGHT(K36, K37, K38, K39, K3A),                        \
            ___15_BOTTOM___                                             \
    )

#define LAYOUT_5x15_base_bepo(                                          \
                         K01, K02, K03, K04, K05,                       \
                         K06, K07, K08, K09, K0A,                       \
                         K11, K12, K13, K14, K15,                       \
                         K16, K17, K18, K19, K1A,                       \
                         K21, K22, K23, K24, K25,                   \
                         K26, K27, K28, K29, K2A,                   \
                         K31, K32, K33, K34, K35,                   \
                         K36, K37, K38, K39, K3A)                   \
  LVARG_5x15(                                                           \
             ROW0_LEFT_BP(K01, K02, K03, K04, K05),                   \
             ___3_MIDDLE_T___,                                          \
             ROW0_RIGHT_BP(K06, K07, K08, K09, K0A),                    \
                                                                        \
             ROW1_LEFT_BP(K11, K12, K13, K14, K15),                     \
             ___3_MIDDLE_1_BP___,                                       \
             ROW1_RIGHT_BP(K16, K17, K18, K19, K1A),                    \
                                                                        \
             ROW2_LEFT_BP(K21, K22, K23, K24, K25),                     \
             ___3_MIDDLE_2_BP___,                                       \
             ROW2_RIGHT_BP(K26, K27, K28, K29, K2A),                    \
                                                                        \
             ROW3_LEFT_BP(K31, K32, K33, K34, K35),                     \
             ___3_MIDDLE_3_BP___,                                       \
             ROW3_RIGHT_BP(K36, K37, K38, K39, K3A),                    \
             ___15_BOTTOM_BP___                                         \
                                                                        )

// Just for bepo because it's a 3x6 matrix on each side.
// So 3 pairs of 6 keys, left and right.
#define Layout_5x15_base_bepo6(                                         \
                               K01, K02, K03, K04, K05, K06,            \
                               K07, K08, K09, K0A, K0B, K0C,            \
                               K11, K12, K13, K14, K15, K16,            \
                               K17, K18, K19, K1A, K1B, K1C,            \
                               K21, K22, K23, K24, K25, K26,            \
                               K27, K28, K29, K2A, K2B, K2C             \
                                                   )                    \
     LVARG_5x15(                                                        \
                ___15_B_SYMB___,                                  \
                ROW1_LEFT_BP6(K01, K02, K03, K04, K05, K06),            \
                ___3_MIDDLE_1_BP___,                                    \
                ROW1_RIGHT_BP6(K07, K08, K09, K0A, K0B, K0C),           \
                                                                        \
                ROW2_LEFT_BP6(K11, K12, K13, K14, K15, K16),            \
                ___3_MIDDLE_2___,                                       \
                ROW2_RIGHT_BP6(K17, K18, K19, K1A, K1B, K1C),           \
                                                                        \
                ROW3_LEFT_BP6(K21, K22, K23, K24, K25, K26),            \
                ___3_MIDDLE_3___,                                       \
                ROW3_RIGHT_BP6(K27, K28, K29, K2A, K2B, K2C),           \
                ___15_BOTTOM_BP___                                      \
                                                                        )

     // 4  rows of 12. 3 columns transparent in the middle.
#define LAYOUT_5x15_transient(                                          \
                              K01, K02, K03, K04, K05, K06,             \
                              K07, K08, K09, K0A, K0B, K0C,           \
                              K11, K12, K13, K14, K15, K16,             \
                              K17, K18, K19, K1A, K1B, K1C,             \
                              K21, K22, K23, K24, K25, K26,             \
                              K27, K28, K29, K2A, K2B, K2C,             \
                              K31, K32, K33, K34, K35, K36,             \
                              K37, K38, K39, K3A, K3B, K3C              \
                                                                        ) \
     LVARG_5x15(                                                  \
                K01, K02, K03, K04, K05, K06,                           \
                ___3___,                                                \
                K07, K08, K09, K0A, K0B, K0C,                           \
                K11, K12, K13, K14, K15, K16,                           \
                ___3___,                                                \
                K17, K18, K19, K1A, K1B, K1C,                           \
                K21, K22, K23, K24, K25, K26,                           \
                ___3___,                                                \
                K27, K28, K29, K2A, K2B, K2C,                           \
                K31, K32, K33, K34, K35, K36,                           \
                ___3___,                                                \
                K37, K38, K39, K3A, K3B, K3C,                           \
                ___15___)                                               \

#define _5x15_base(...)       LAYOUT_5x15_base(__VA_ARGS__)
#define _5x15_base_bepo(...)  LAYOUT_5x15_base_bepo(__VA_ARGS__)
#define _5x15_base_bepo6(...) LAYOUT_5x15_base_bepo6(__VA_ARGS__)
#define _5x15_transient(...)  LAYOUT_5x15_transient(__VA_ARGS__)

/********************************************************************/


/********************************************************************/
/* viterbi  - Ortholinear 5x14  */
/********************************************************************/
#define LAYOUT_5x14_base(                                               \
                         K01, K02, K03, K04, K05,                       \
                         K06, K07, K08, K09, K0A,                       \
                         K11, K12, K13, K14, K15,                       \
                         K16, K17, K18, K19, K1A,                       \
                         K21, K22, K23, K24, K25,                       \
                         K26, K27, K28, K29, K2A,                       \
                         K31, K32, K33, K34, K35,                       \
                         K36, K37, K38, K39, K3A)                       \
  LVARG_5x14(                                                           \
             ROW0_LEFT(K01, K02, K03, K04, K05),                        \
             ___2_MIDDLE_T___,                                          \
             ROW0_RIGHT(K06, K07, K08, K09, K0A),                       \
                                                                        \
             ROW1_LEFT(K11, K12, K13, K14, K15),                        \
             ___2_MIDDLE_1___,                                          \
             ROW1_RIGHT(K16, K17, K18, K19, K1A),                       \
                                                                        \
             ROW2_LEFT(K21, K22, K23, K24, K25),                        \
             ___2_MIDDLE_2___,                                          \
             ROW2_RIGHT(K26, K27, K28, K29, K2A),                       \
                                                                        \
             ROW3_LEFT(K31, K32, K33, K34, K35),                        \
             ___2_MIDDLE_3___,                                          \
             ROW3_RIGHT(K36, K37, K38, K39, K3A),                       \
             ___14_BOTTOM___                                            \
                                                                        )

#define LAYOUT_5x14_base_bepo(                                          \
                              K01, K02, K03, K04, K05,                  \
                              K06, K07, K08, K09, K0A,                  \
                              K11, K12, K13, K14, K15,                  \
                              K16, K17, K18, K19, K1A,                  \
                              K21, K22, K23, K24, K25,                  \
                              K26, K27, K28, K29, K2A,                  \
                              K31, K32, K33, K34, K35,                  \
                              K36, K37, K38, K39, K3A)                  \
  LVARG_5x14(                                                           \
            ROW0_LEFT_BP(K01, K02, K03, K04, K05),                      \
            ___2_MIDDLE_T___,                                           \
            ROW0_RIGHT_BP(K06, K07, K08, K09, K0A),                     \
                                                                        \
            ROW1_LEFT_BP(K11, K12, K13, K14, K15),                      \
            ___2_MIDDLE_1_BP___,                                        \
            ROW1_RIGHT_BP(K16, K17, K18, K19, K1A),                     \
                                                                        \
            ROW2_LEFT_BP(K21, K22, K23, K24, K25),                      \
            ___2_MIDDLE_2_BP___,                                        \
            ROW2_RIGHT_BP(K26, K27, K28, K29, K2A),                     \
                                                                        \
            ROW3_LEFT_BP(K31, K32, K33, K34, K35),                      \
            ___2_MIDDLE_3_BP___,                                        \
            ROW3_RIGHT_BP(K36, K37, K38, K39, K3A),                     \
            ___14_BOTTOM_BP___                                          \
    )

  // Just for bepo because it's a 3x6 matrix on each side.
// So 3 pairs of 6 keys, left and right.
#define LAYOUT_5x14_base_bepo6(                                 \
                               K01, K02, K03, K04, K05, K06,    \
                               K07, K08, K09, K0A, K0B, K0C,    \
                               K11, K12, K13, K14, K15, K16,    \
                               K17, K18, K19, K1A, K1B, K1C,        \
                               K21, K22, K23, K24, K25, K26,        \
                               K27, K28, K29, K2A, K2B, K2C             \
                                                   )                    \
  LVARG_5x14(                                                           \
             ___14_B_SYMB___,                                           \
             ROW1_LEFT_BP6(K01, K02, K03, K04, K05, K06),               \
             ___2_MIDDLE_1_BP___,                                       \
             ROW1_RIGHT_BP6(K07, K08, K09, K0A, K0B, K0C),              \
                                                                        \
             ROW2_LEFT_BP6(K11, K12, K13, K14, K15, K16),               \
             ___2_MIDDLE_2___,                                          \
             ROW2_RIGHT_BP6(K17, K18, K19, K1A, K1B, K1C),              \
                                                                        \
             ROW3_LEFT_BP6(K21, K22, K23, K24, K25, K26),               \
             ___2_MIDDLE_3___,                                          \
             ROW3_RIGHT_BP6(K27, K28, K29, K2A, K2B, K2C),              \
             ___14_BOTTOM_BP___                                         \
                                                                        )

// 4  rows of 12. 2 columns transparent in the middle.
#define LAYOUT_5x14_transient(                                          \
                              K01, K02, K03, K04, K05, K06,             \
                              K07, K08, K09, K0A, K0B, K0C,             \
                              K11, K12, K13, K14, K15, K16,             \
                              K17, K18, K19, K1A, K1B, K1C,             \
                              K21, K22, K23, K24, K25, K26,             \
                              K27, K28, K29, K2A, K2B, K2C,             \
                              K31, K32, K33, K34, K35, K36,             \
                              K37, K38, K39, K3A, K3B, K3C              \
                                                                        ) \
  LVARG_5x14(                                                           \
             K01, K02, K03, K04, K05, K06,                              \
             ___2___,                                                   \
             K07, K08, K09, K0A, K0B, K0C,                              \
             K11, K12, K13, K14, K15, K16,                              \
             ___2___,                                                   \
             K17, K18, K19, K1A, K1B, K1C,                              \
             K21, K22, K23, K24, K25, K26,                              \
             ___2___,                                                   \
             K27, K28, K29, K2A, K2B, K2C,                              \
             K31, K32, K33, K34, K35, K36,                              \
             ___2___,                                                   \
             K37, K38, K39, K3A, K3B, K3C,                              \
             ___14___                                                   \
                                                                        ) \

#define _5x14_base(...)       LAYOUT_5x14_base(__VA_ARGS__)
#define _5x14_base_bepo(...)  LAYOUT_5x14_base_bepo(__VA_ARGS__)
#define _5x14_base_bepo6(...) LAYOUT_5x14_base_bepo6(__VA_ARGS__)
#define _5x14_transient(...)  LAYOUT_5x14_transient(__VA_ARGS__)

/********************************************************************/
/* Ortholinear 4x12  */
/********************************************************************/
#define LAYOUT_4x12_base(                                               \
                         K01, K02, K03, K04, K05,                       \
                         K06, K07, K08, K09, K0A,                       \
                         K11, K12, K13, K14, K15,                       \
                         K16, K17, K18, K19, K1A,                       \
                         K21, K22, K23, K24, K25,                       \
                         K26, K27, K28, K29, K2A                        \
                                                                        ) \
  LVARG_4x12(                                                     \
             ROW1_LEFT(K01, K02, K03, K04, K05),                  \
             ROW1_RIGHT(K06, K07, K08, K09, K0A),                 \
                                                                  \
             ROW2_LEFT(K11, K12, K13, K14, K15),                  \
             ROW2_RIGHT(K16, K17, K18, K19, K1A),                 \
                                                                  \
             ROW3_LEFT(K21, K22, K23, K24, K25),                  \
             ROW3_RIGHT(K26, K27, K28, K29, K2A),                 \
                                                                        \
             ___12_BOTTOM___                                            \
                                                                  )

#define LAYOUT_4x12_base_bepo(                                          \
                              K01, K02, K03, K04, K05,                  \
                              K06, K07, K08, K09, K0A,                  \
                              K11, K12, K13, K14, K15,                  \
                              K16, K17, K18, K19, K1A,                  \
                              K21, K22, K23, K24, K25,                  \
                              K26, K27, K28, K29, K2A                  \
                                                                        ) \
     LVARG_4x12(                                                  \
                ROW1_LEFT_BP(K01, K02, K03, K04, K05),              \
                ROW1_RIGHT_BP(K06, K07, K08, K09, K0A),             \
                                                                    \
                ROW2_LEFT_BP(K11, K12, K13, K14, K15),              \
                ROW2_RIGHT_BP(K16, K17, K18, K19, K1A),             \
                                                                        \
                ROW3_LEFT_BP(K21, K22, K23, K24, K25),                    \
                ROW3_RIGHT_BP(K26, K27, K28, K29, K2A),                 \
                                                                        \
                ___12_BOTTOM_BP___                                      \
                                                                  )

     // Just for bepo because it's a 3x6 matrix on each side.
     // So 3 pairs of 6 keys, left and right.
#define Layout_4x12_base_bepo6(                                 \
                               K01, K02, K03, K04, K05, K06,    \
                               K07, K08, K09, K0A, K0B, K0C,    \
                               K11, K12, K13, K14, K15, K16,           \
                               K17, K18, K19, K1A, K1B, K1C,           \
                               K21, K22, K23, K24, K25, K26,           \
                               K27, K28, K29, K2A, K2B, K2C             \
                                                                           ) \
     LVARG_4x12(                                                        \
                ROW1_LEFT_BP6(K01, K02, K03, K04, K05, K06),            \
                ROW1_RIGHT_BP6(K07, K08, K09, K0A, K0B, K0C),           \
                                                                        \
                ROW2_LEFT_BP6(K11, K12, K13, K14, K15, K16),            \
                ROW2_RIGHT_BP6(K17, K18, K19, K1A, K1B, K1C),           \
                                                                        \
                ROW3_LEFT_BP6(K21, K22, K23, K24, K25, K26),            \
                ROW3_RIGHT_BP6(K27, K28, K29, K2A, K2B, K2C),           \
                ___12_BOTTOM_BP___                                      \
                                                                        )

// takes 3 makes 4  rows of 12.
#define LAYOUT_4x12_transient(                                          \
                              K01, K02, K03, K04, K05, K06,             \
                              K07, K08, K09, K0A, K0B, K0C,             \
                              K11, K12, K13, K14, K15, K16,             \
                              K17, K18, K19, K1A, K1B, K1C,             \
                              K21, K22, K23, K24, K25, K26,             \
                              K27, K28, K29, K2A, K2B, K2C              \
                                                                        ) \
  LVARG_4x12(                                                           \
             K01, K02, K03, K04, K05, K06,                              \
             K07, K08, K09, K0A, K0B, K0C,                              \
             K11, K12, K13, K14, K15, K16,                              \
             K17, K18, K19, K1A, K1B, K1C,                              \
             K21, K22, K23, K24, K25, K26,                              \
             K27, K28, K29, K2A, K2B, K2C,                              \
             ___12___)                                                  \

#define _4x12_base(...)       LAYOUT_4x12_base(__VA_ARGS__)
#define _4x12_base_bepo(...)  LAYOUT_4x12_base_bepo(__VA_ARGS__)
#define _4x12_base_bepo6(...) LAYOUT_4x12_base_bepo6(__VA_ARGS__)
#define _4x12_transient(...)  LAYOUT_4x12_transient(__VA_ARGS__)
