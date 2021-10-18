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

/********************************************************************/
/**  Parts are parts, pieces of keysets so we have some decent     **/
/** building blocks to make keymaps with.                          **/
/********************************************************************/


// Since our quirky block definitions are basically a list of comma separated
// arguments, we need a wrapper in order for these definitions to be
// expanded before being used as arguments to the LAYOUT_xxx macro.
#if (!defined(LAYOUT) && defined(KEYMAP))
#define LAYOUT KEYMAP
#endif

#define LAYOUT_ergodox_wrapper(...)          LAYOUT_ergodox(__VA_ARGS__)
#define LAYOUT_ergodox_pretty_wrapper(...)   LAYOUT_ergodox_pretty(__VA_ARGS__)
#define KEYMAP_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_wrapper(...)                  LAYOUT(__VA_ARGS__)

#define LAYOUT_ortho_5x15_wrapper(...)       LAYOUT_ortho_5x15(__VA_ARGS__)
#define LAYOUT_ortho_5x14_wrapper(...)       LAYOUT_ortho_5x14(__VA_ARGS__)


/********************************************************************/
/**  The Core rows of each given layout.                           **/
/********************************************************************/
//Dvorak on a qwerty software layer in the OS
#define ___DVORAK_L1___ KC_QUOT,    KC_COMM, KC_DOT, KC_P,   KC_Y
#define ___DVORAK_L2___ KC_SFT_T_A, KC_LT_KP_O,  KC_LT_MDIA_E,  KC_LT_SYMB_U, KC_I
#define ___DVORAK_L3___ KC_SCLN,    KC_Q,    KC_J,   KC_K,   KC_X

#define ___DVORAK_R1___ KC_F, KC_G,          KC_C, KC_R,   KC_L
#define ___DVORAK_R2___ KC_D, KC_LT_SYMB_H,  KC_LT_MDIA_T, KC_LT_KP_N, KC_SFT_T_S
#define ___DVORAK_R3___ KC_B, KC_M,          KC_W, KC_V,   KC_Z

// Qwerty based layers that I don't really use.
#define ___QWERTY_L1___ KC_Q,        KC_W,    KC_E,          KC_R,         KC_T
#define ___QWERTY_L2___ KC_SFT_T_A,  KC_S,    KC_LT_MDIA_D,  KC_LT_SYMB_F, KC_G
#define ___QWERTY_L3___ KC_Z,        KC_X,    KC_C,          KC_V,         KC_B

#define ___QWERTY_R1___ KC_Y,    KC_U,            KC_I,          KC_O,    KC_P
#define ___QWERTY_R2___ KC_H,    KC_LT_SYMB_J,    KC_LT_MDIA_K,  KC_L,    KC_SFT_T_SCLN
#define ___QWERTY_R3___ KC_N,    KC_M,            KC_COMM,       KC_DOT,  KC_SLASH

// COLEMAK
#define ___COLEMAK_L1___ KC_Q,       KC_W,    KC_F,          KC_P,          KC_G
#define ___COLEMAK_L2___ KC_SFT_T_A, KC_R,    KC_LT_MDIA_S,  KC_LT_SYMB_T,  KC_D
#define ___COLEMAK_L3___ KC_Z,       KC_X,    KC_C,          KC_V,          KC_B

#define ___COLEMAK_R1___ KC_J,    KC_L,          KC_U,          KC_Y,    KC_SCLN
#define ___COLEMAK_R2___ KC_H,    KC_LT_SYMB_N,  KC_LT_MDIA_E,  KC_I,    KC_SFT_T_O
#define ___COLEMAK_R3___ KC_K,    KC_M,          KC_COMM,       KC_DOT,  KC_SLASH

// COLEMAK-DH
#define ___COLEMAK_DH_L1___ KC_Q,        KC_W,    KC_F,          KC_P,          KC_B
#define ___COLEMAK_DH_L2___ KC_SFT_T_A,  KC_R,    KC_LT_MDIA_S,  KC_LT_SYMB_T,  KC_G
#define ___COLEMAK_DH_L3___ KC_Z,        KC_X,    KC_C,          KC_D,          KC_V

#define ___COLEMAK_DH_R1___ KC_J,  KC_L,          KC_U,          KC_Y,    KC_SCLN
#define ___COLEMAK_DH_R2___ KC_M,  KC_LT_SYMB_N,  KC_LT_MDIA_E,  KC_I,    KC_SFT_T_O
#define ___COLEMAK_DH_R3___ KC_K,  KC_H,          KC_COMM,       KC_DOT,  KC_SLASH

// WORKMAN
#define ___WORKMAN_L1___ KC_Q,        KC_D,    KC_R,          KC_W,          KC_B
#define ___WORKMAN_L2___ KC_SFT_T_A,  KC_S,    KC_LT_MDIA_H,  KC_LT_SYMB_T,  KC_G
#define ___WORKMAN_L3___ KC_Z,        KC_X,    KC_M,          KC_C,          KC_V

#define ___WORKMAN_R1___ KC_J,  KC_F,          KC_U,          KC_P,    KC_SCLN
#define ___WORKMAN_R2___ KC_Y,  KC_LT_SYMB_N,  KC_LT_MDIA_E,  KC_O,    KC_SFT_T_I
#define ___WORKMAN_R3___ KC_K,  KC_L,          KC_COMM,       KC_DOT,  KC_SLASH

// NORMAN
#define ___NORMAN_L1___ KC_Q,        KC_W,    KC_D,          KC_F,          KC_K
#define ___NORMAN_L2___ KC_SFT_T_A,  KC_S,    KC_LT_MDIA_E,  KC_LT_SYMB_T,  KC_G
#define ___NORMAN_L3___ KC_Z,        KC_X,    KC_C,          KC_V,          KC_B

#define ___NORMAN_R1___ KC_J,   KC_U,          KC_R,          KC_L,    KC_SCLN
#define ___NORMAN_R2___ KC_Y,   KC_LT_SYMB_N,  KC_LT_MDIA_I,  KC_O,    KC_SFT_T_U
#define ___NORMAN_R3___ KC_P,   KC_M,          KC_COMM,       KC_DOT,  KC_SLASH

// BEPO MAPS
// Dvorak on fr-bepo software layer in the OS.
// for dvorak and all the other qwerty like keyboards on bepo
#define ___DVORAK_FR_L1___ DB_QUOT,    DB_COMM,  DB_DOT,  BP_P,        BP_Y
#define ___DVORAK_FR_L2___ BP_SFT_T_A, BP_LT_KP_O,     BP_LT_MDIA_E,    BP_LT_SYMB_U,  BP_I
#define ___DVORAK_FR_L3___ DB_SCOLON,  BP_Q,     BP_J,    BP_K,        BP_X

#define ___DVORAK_FR_R1___ BP_F,    BP_G,        BP_C,  BP_R,  BP_L
#define ___DVORAK_FR_R2___ BP_D,    BP_LT_SYMB_H,        BP_LT_MDIA_T,  BP_LT_KP_N,  BP_SFT_T_S
#define ___DVORAK_FR_R3___ BP_B,    BP_M,        BP_W,  BP_V,  BP_Z


// Bepo on fr-bepo software layer
// for bepo on bepo
/* BP_DLR,   BP_DQUO, BP_LDAQ, BP_RDAQ, BP_LPRN, BP_RPRN, KC_DEL, */
#define ___SYMBOL_BEPO_L___ /* BP_DLR */ BP_DQUO,  BP_LDAQ,   BP_RDAQ,   BP_LPRN,   BP_RPRN
/*   KC_DEL,  BP_AT,   BP_PLUS,  BP_MINS, BP_SLSH,     BP_ASTR, BP_EQL, */
#define ___SYMBOL_BEPO_R___    BP_AT,    BP_PLUS,  BP_MINS,   BP_SLSH,  BP_ASTR /* BP_EQL,  BP_PERC */

#define ___BEPO_FR_L1___             BP_B,        BP_EACU, BP_P,           BP_O,          BP_EGRV
#define ___BEPO_FR_L2___             BP_SFT_T_A,  BP_LT_KP_U,    BP_LT_SYMB_I,   BP_LT_MDIA_E,  BP_COMM
#define ___BEPO_FR_L3___ /*BP_ECIR*/ BP_AGRV,     BP_Y,    BP_X,           BP_DOT,        BP_K

#define ___BEPO_FR_R1___  /* BP_DCIR,*/  BP_V, BP_D,  BP_L,    BP_J,  BP_Z
#define ___BEPO_FR_R2___  /* BP_C,   */  BP_T, BP_LT_SYMB_S,    BP_LT_MDIA_R,  BP_LT_KP_N, BP_SFT_T_M  //BP_CCED
#define ___BEPO_FR_R3___                 BP_QUOT,    BP_Q,    BP_G,  BP_H, BP_F //BP_SFT_T_W

/* BP_DLR,   BP_DQUO, BP_LDAQ, BP_RDAQ, BP_LPRN, BP_RPRN, KC_DEL, */
/*   KC_TAB,   BP_B,    BP_EACU, BP_P,    BP_O,    BP_EGRV, KC_BSPC, */
/*   KC_LSFT,  BP_A,    BP_U,    BP_I,    BP_E,    BP_COMM, */
/*   KC_LCTRL, BP_AGRV, BP_Y,    BP_X,    BP_DOT,  BP_K,    KC_ENT, */
/*   ESC_FN,   BP_ECIR, KC_LGUI, KC_LALT, SPC_RALT, */
/*   TT(SWAP), KC_MNXT, */
/*   KC_MPLY, */
/*   TT(FN), TT(NUMS), KC_MPRV, */

/* /\* right hand *\/ */
/*   KC_DEL,  BP_AT,   BP_PLUS,  BP_MINS, BP_SLSH,     BP_ASTR, BP_EQL, */
/*   KC_BSPC, BP_DCIR, BP_V,     BP_D,    BP_L,        BP_J,    BP_Z, */
/*   BP_C,    BP_T,     BP_S,    BP_R,        BP_N,    M_RSFT, */
/*   KC_ENT,  BP_QUOT, BP_Q,     BP_G,    BP_H,        BP_F,    W_RCTL, */


/*******************************************************************/
/** For the top rows.  Numbers for most things, symbols for Bepo. **/
/*******************************************************************/

// for everything on qwerty.
#define ___NUMBER_L___ KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ___NUMBER_R___ KC_6,    KC_7,    KC_8,    KC_9,    KC_0

// function key rows, works for everyone.
#define ___FUNC_L___   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define ___FUNC_R___   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10

#define ___FUNC_1_6___   KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6
#define ___FUNC_7_12___  KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_F11, KC_F12

// a top symbol row if someone wants it.
#define ___SYMB_L___   KC_EXLM,   KC_AT,    KC_HASH,  KC_DLR,   KC_PERC
#define ___SYMB_R___   KC_CIRC,   KC_AMPR,  KC_AST,   KC_LPRN,  KC_RPRN

// For numbers on bepo. Bepo has numbers on shifted keys, the
// reverse of most keyboard layouts.
#define ___NUMBER_BEPO_L___ DB_1,   DB_2,   DB_3,   DB_4,   DB_5
#define ___NUMBER_BEPO_R___ DB_6,   DB_7,   DB_8,   DB_9,   DB_0


/*******************************************************************/
/* keysets for the auxillary layers.                               */
/* the KC_P?  codes don't work for me. I don't use those shifted   */
/* values anyway.                                                  */
/*******************************************************************/
// Keypads
#define ___KEYPAD_1___ KC_7,  KC_8,    KC_9,     KC_PSLS
#define ___KEYPAD_2___ KC_4,  KC_5,    KC_6,     KC_PAST
#define ___KEYPAD_3___ KC_1,  KC_2,    KC_3,     KC_PMNS
#define ___KEYPAD_4___ KC_0,  KC_DOT,  KC_PEQL,  KC_PPLS

// Keypad from the default keymap.c of the xd75
#define ___KEYPAD_1_ALT___ KC_P7, KC_P8,  KC_P9,   KC_MINS
#define ___KEYPAD_2_ALT___ KC_P4, KC_P5,  KC_P6,   KC_PLUS
#define ___KEYPAD_3_ALT___ KC_P1, KC_P2,  KC_P3,   KC_PENT
#define ___KEYPAD_4_ALT___ KC_P0, KC_DOT, KC_PENT, KC_PENT

// For Bepo
#define ___KEYPAD_1_BP___ DB_7,  DB_8,    DB_9,     BP_SLSH
#define ___KEYPAD_2_BP___ DB_4,  DB_5,    DB_6,     BP_ASTR
#define ___KEYPAD_3_BP___ DB_1,  DB_2,    DB_3,     DB_MINUS
#define ___KEYPAD_4_BP___ DB_0,  DB_DOT,  DB_EQL,   BP_PLUS


// SYMBOLS
// An arrangement for the left hand with a focus on the ()[]{}s.
#define ___SYMBOLS_1___  KC_EXLM,  KC_AT,    KC_LCBR,  KC_RCBR,  KC_PIPE
#define ___SYMBOLS_2___  KC_HASH,  KC_DLR,   KC_LPRN,  KC_RPRN,  KC_GRV
#define ___SYMBOLS_3___  KC_PERC,  KC_CIRC,  KC_LBRC,  KC_RBRC,  KC_TILD

// A larger 6 column arrangement for the left hand, A merge of dvorak and the above.
#define ___SYMBOLS6_1___  KC_GRV,  KC_LT,    KC_GT,    KC_LCBR,  KC_RCBR,  KC_HASH
#define ___SYMBOLS6_2___  KC_AMPR, KC_AT,    KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_PERC
#define ___SYMBOLS6_3___  KC_DLR,  KC_DQT,   KC_QUOT,  KC_LBRC,  KC_RBRC,  KC_COLON
#define ___SYMBOLS6_4___  ___2___, KC_TILD,  KC_DOT,   KC_EXLM,  KC_SCLN

#define ___SYMBOLS5_4___  ___, KC_TILD,  KC_DOT,   KC_EXLM,  KC_SCLN


// A symbol pad.  Basically the same layout as a number pad with the symbols
// instead of the numbers with some extras around it, in familiar places for the
// right hand.
#define ___SYMPAD_1___  KC_GRV,  KC_AMPR, KC_ASTR, KC_LCBR,  KC_PLUS,  KC_PIPE
#define ___SYMPAD_2___  KC_TILD, KC_DLR,  KC_PERC, KC_CIRC,  KC_ASTR,  KC_GRV
#define ___SYMPAD_3___  ___,     KC_EXLM, KC_AT,   KC_HASH,  KC_MINUS, KC_SLASH
#define ___SYMPAD_4___  ___,     KC_RCBR, KC_DOT,  KC_EQUAL, KC_UNDS,  KC_BSLASH

#define ___5_SYMPAD_4___  KC_RCBR, KC_DOT,  KC_EQUAL, KC_UNDS,  KC_BSLASH

// Function pad.  Same idea as above, but for function keys.
#define ___FUNCPAD_T___   KC_F10,  KC_F11,  KC_F12
#define ___FUNCPAD_1___   KC_F7,   KC_F8,   KC_F9
#define ___FUNCPAD_2___   KC_F4,   KC_F5,   KC_F6
#define ___FUNCPAD_3___   KC_F1,   KC_F2,   KC_F3


//---  all over again for BEPO

// SYMBOLS FOR BEPO
// The top row.  Bepo has symbols not numbers. Numbers are the shifted values.
#define ___SYMBOL_BEPO_L___ /* BP_DLR */ BP_DQUO,  BP_LDAQ,   BP_RDAQ,   BP_LPRN,   BP_RPRN
/*   KC_DEL,  BP_AT,   BP_PLUS,  BP_MINS, BP_SLSH,     BP_ASTR, BP_EQL, */
#define ___SYMBOL_BEPO_R___    BP_AT,    BP_PLUS,  BP_MINS,   BP_SLSH,  BP_ASTR /* BP_EQL,  BP_PERC */

// An arrangement for the left hand with a focus on the ()[]{}s.
#define ___SYMBOLS_1_BP___ KC_EXLM,  BP_AT,    DB_LCBR,  DB_RCBR,  DB_PIPE
#define ___SYMBOLS_2_BP___ DB_HASH,  BP_DLR,   DB_LPRN,  DB_RPRN,  DB_GRV
#define ___SYMBOLS_3_BP___ BP_PERC,  DB_CIRC,  DB_LBRC,  DB_RBRC,  DB_TILD

// A larger 6 column arrangement for the left hand, A merge of dvorak and the above.
#define ___SYMBOLS6_1_BP___  DB_GRV,  DB_LESS, DB_GRTR, DB_LCBR,  DB_RCBR,  DB_HASH
#define ___SYMBOLS6_2_BP___  KC_AMPR, BP_AT,   BP_ASTR, DB_LPRN,  DB_RPRN,  BP_PERC
#define ___SYMBOLS6_3_BP___  BP_DLR,  BP_DQUO, DB_QUOT, DB_LBRC,  DB_RBRC,  KC_COLON
#define ___SYMBOLS6_4_BP___  ___2___, DB_TILD, DB_DOT,  KC_EXLM, DB_SCOLON

#define ___SYMBOLS5_4_BP___  ___, DB_TILD, DB_DOT,  KC_EXLM, DB_SCOLON

// A symbol pad.  Basically the same layout as a number pad with the symbols
// instead of the numbers with some extras around it, in familiar places for the
// right hand.
#define ___SYMPAD_1_BP___  DB_GRV,  BP_AMPR, BP_ASTR, DB_LCBR,  BP_PLUS,  DB_PIPE
#define ___SYMPAD_2_BP___  DB_TILD, BP_DLR,  BP_PERC, DB_CIRC,  BP_ASTR,  DB_GRV
#define ___SYMPAD_3_BP___  ___,     BP_EXLM, BP_AT,   DB_HASH,  BP_MINS,  BP_SLSH
#define ___SYMPAD_4_BP___  ___,     DB_RCBR, DB_DOT,  BP_EQL,   BP_MINS, DB_BACKSLASH

#define ___5_SYMPAD_4_BP___  DB_RCBR, DB_DOT,  BP_EQL,   BP_MINS, DB_BACKSLASH

// Parts are parts.
// MOUSE, ARROW and MEDIA KEY SETS
#define ___MOUSE_LDUR___      KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R
#define ___MWHEEL_LDUR___     KC_WH_L,  KC_WH_D,  KC_WH_U,  KC_WH_R
#define ___MOUSE_BTNS_R___    KC_BTN1,  KC_BTN2,  KC_BTN3,  KC_BTN4,  KC_BTN5
#define ___MOUSE_BTNS_L___    KC_BTN5,  KC_BTN4,  KC_BTN3,  KC_BTN2,  KC_BTN1
#define ___MOUSE_ACCL_012___  KC_ACL0,  KC_ACL1,  KC_ACL2
#define ___MACCL___ ___MOUSE_ACCL_012___

#define ___PRV_PLAY_NXT_STOP KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP
#define ___VDN_MUTE_VUP___ KC_VOLD, KC_MUTE, KC_VOLU

#define ___MUTE_PRV_PLAY_NXT_STOP___  KC_MUTE,  KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP
#define ___MUTE_PLAY_STOP___  KC_MUTE,  KC_MPLY,  KC_MSTP
#define ___VI_ARROWS___       KC_LEFT,  KC_DOWN,  KC_UP, KC_RIGHT

// RGB FUNCTION Keysets
// RGB row for the _FN layer from the redo of the default keymap.c
#define ___RGB_HUE_SAT_INT_UP___ RGB_HUI, RGB_SAI, RGB_VAI, RGB_RMOD
#define ___RGB_HUE_SAT_INT_DN___ RGB_HUD, RGB_SAD, RGB_VAD, RGB_MOD
#define ___RGB_MODE_PRV_NXT___ RGB_RMOD, RGB_MOD
#define ___RGB_TOGGLE___ RGB_TOG
#define ___RGB_P_B_R_SW_SN___ RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN
#define ___RGB_KXGT___ RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T

// Print screen, screen lock, pause
#define ___PSCR_SLCK_PAUS___ KC_PSCR, KC_SLCK, KC_PAUS

// LAYER Keyset rows. Changing the Default base layer or the transient layers.
// Some are full length. The baselayers leave the ends open. hence a 13.
// for an ORtho 15.
#define ___2_LAYERS_B1___ DF(BEPO), DF(DVORAK_ON_BEPO)
#define ___2_LAYERS_B2___ DF(COLEMAK), DF(DVORAK)
#define ___3_LAYERS_B3___ DF(QWERTY), DF(NORMAN), DF(WORKMAN)
#define ___3_LAYERS_B4___ ___X3___
// transient layers.
#define ___3_LAYERS_T_BP___ TO(MDIA), TO(SYMB_ON_BEPO), TO(KEYPAD_ON_BEPO)
#define ___3_LAYERS_T___    TO(MDIA), TO(SYMB), TO(KEYPAD)
#define ___3_LAYERS_T_CTL___ TO(_RGB), ___X2___
