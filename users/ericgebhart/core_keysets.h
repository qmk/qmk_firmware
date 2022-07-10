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
/**  The Core rows of each given layout.                           **/
/********************************************************************/
//Dvorak on a qwerty software layer in the OS
#define ___DVORAK_L1___ KC_QUOT,  KC_COMM, KC_DOT, KC_P,  KC_Y
#define ___DVORAK_L2___ KC_A,     KC_O,    KC_E,   KC_U,  KC_I
#define ___DVORAK_L3___ KC_SCLN,  KC_Q,    KC_J,   KC_K,  KC_X

#define ___DVORAK_R1___ KC_F, KC_G,  KC_C, KC_R, KC_L
#define ___DVORAK_R2___ KC_D, KC_H,  KC_T, KC_N, KC_S
#define ___DVORAK_R3___ KC_B, KC_M,  KC_W, KC_V, KC_Z

#define ___DVORAK___ ___DVORAK_L1___, ___DVORAK_R1___,  \
        ___DVORAK_L2___, ___DVORAK_R2___,  \
        ___DVORAK_L3___, ___DVORAK_R3___

/* BEAKL 15 (main layer): */
/*   40123 76598   */
/*   qhoux gcrfz   */
/* - yiea. dstnb ; */
/*   j/,k' wmlpv   */

// Remember the - and ; outside pinky keys.
// Or use the 6 size.
// Both are on the symbol layer too. So you
// wont lose them at least.
// BQ_COMM, BQ_QUOT, BQ_DOT - Beakl->Qwerty
// BB_COMM, BB_QUOT, BB_DOT - Beakl->Bepo
// take care of the different shifted chars.
/* BEAKL 15 (shift layer): */
/*   QHOUX GCRFZ   */
/* - YIEA@ DSTNB ; */
/*   J?!K` WMLPV   */
#define ___BEAKL15_L1___ KC_Q, KC_H,     KC_O,    KC_U, KC_X
#define ___BEAKL15_L2___ KC_Y, KC_I,     KC_E,    KC_A, BQ_DOT
#define ___BEAKL15_L3___ KC_J, KC_SLASH, BQ_COMM, KC_K, BQ_QUOT

#define ___BEAKL15_R1___ KC_G, KC_C,     KC_R,    KC_F, KC_Z
#define ___BEAKL15_R2___ KC_D, KC_S,     KC_T,    KC_N, KC_B
#define ___BEAKL15_R3___ KC_W, KC_M,     KC_L,    KC_P, KC_V

#define ___BEAKL15___ ___BEAKL15_L1___, ___BEAKL15_R1___,       \
        ___BEAKL15_L2___, ___BEAKL15_R2___,                     \
        ___BEAKL15_L3___, ___BEAKL15_R3___

#define ___6BEAKL15_L1___ ___,     KC_Q, KC_H,     KC_O,    KC_U, KC_X
#define ___6BEAKL15_L2___ KC_MINS, KC_Y, KC_I,     KC_E,    KC_A, BQ_DOT
#define ___6BEAKL15_L3___ ___,     KC_J, KC_SLASH, BQ_COMM, KC_K, BQ_QUOT

#define ___6BEAKL15_R1___ KC_G, KC_C,     KC_R,    KC_F, KC_Z, ___
#define ___6BEAKL15_R2___ KC_D, KC_S,     KC_T,    KC_N, KC_B, KC_SCLN
#define ___6BEAKL15_R3___ KC_W, KC_M,     KC_L,    KC_P, KC_V, ___

#define ___6BEAKL15___ ___6BEAKL15_L1___, ___6BEAKL15_R1___,    \
        ___6BEAKL15_L2___, ___6BEAKL15_R2___,                   \
        ___6BEAKL15_L3___, ___6BEAKL15_R3___

// Qwerty based layers that I don't really use.
#define ___QWERTY_L1___ KC_Q,  KC_W,  KC_E,    KC_R,   KC_T
#define ___QWERTY_L2___ KC_A,  KC_S,  KC_D,    KC_F,   KC_G
#define ___QWERTY_L3___ KC_Z,  KC_X,  KC_C,    KC_V,   KC_B

#define ___QWERTY_R1___ KC_Y,  KC_U,  KC_I,    KC_O,   KC_P
#define ___QWERTY_R2___ KC_H,  KC_J,  KC_K,    KC_L,   KC_SCLN
#define ___QWERTY_R3___ KC_N,  KC_M,  KC_COMM, KC_DOT, KC_SLASH

#define ___QWERTY___ ___QWERTY_L1___, ___QWERTY_R1___,          \
        ___QWERTY_L2___, ___QWERTY_R2___,                       \
        ___QWERTY_L3___, ___QWERTY_R3___

// Qwerty based layers that I don't really use.

// COLEMAK
#define ___COLEMAK_L1___ KC_Q, KC_W,  KC_F,    KC_P,   KC_G
#define ___COLEMAK_L2___ KC_A, KC_R,  KC_S,    KC_T,   KC_D
#define ___COLEMAK_L3___ KC_Z, KC_X,  KC_C,    KC_V,   KC_B

#define ___COLEMAK_R1___ KC_J, KC_L,  KC_U,    KC_Y,   KC_SCLN
#define ___COLEMAK_R2___ KC_H, KC_N,  KC_E,    KC_I,   KC_O
#define ___COLEMAK_R3___ KC_K, KC_M,  KC_COMM, KC_DOT, KC_SLASH

#define ___COLEMAK___ ___COLEMAK_L1___, ___COLEMAK_R1___,       \
        ___COLEMAK_L2___, ___COLEMAK_R2___,                     \
        ___COLEMAK_L3___, ___COLEMAK_R3___

// COLEMAK-DH
#define ___COLEMAK_DH_L1___ KC_Q,  KC_W,  KC_F,  KC_P,  KC_B
#define ___COLEMAK_DH_L2___ KC_A,  KC_R,  KC_S,  KC_T,  KC_G
#define ___COLEMAK_DH_L3___ KC_Z,  KC_X,  KC_C,  KC_D,  KC_V

#define ___COLEMAK_DH_R1___ KC_J,  KC_L,  KC_U,    KC_Y,    KC_SCLN
#define ___COLEMAK_DH_R2___ KC_M,  KC_N,  KC_E,    KC_I,    KC_O
#define ___COLEMAK_DH_R3___ KC_K,  KC_H,  KC_COMM, KC_DOT,  KC_SLASH

#define ___COLEMAK_DH___ ___COLEMAK_DH_L1___, ___COLEMAK_DH_R1___,      \
        ___COLEMAK_DH_L2___, ___COLEMAK_DH_R2___,                       \
        ___COLEMAK_DH_L3___, ___COLEMAK_DH_R3___


// WORKMAN
#define ___WORKMAN_L1___ KC_Q,  KC_D,  KC_R,  KC_W,  KC_B
#define ___WORKMAN_L2___ KC_A,  KC_S,  KC_H,  KC_T,  KC_G
#define ___WORKMAN_L3___ KC_Z,  KC_X,  KC_M,  KC_C,  KC_V

#define ___WORKMAN_R1___ KC_J,  KC_F,  KC_U,     KC_P,    KC_SCLN
#define ___WORKMAN_R2___ KC_Y,  KC_N,  KC_E,     KC_O,    KC_I
#define ___WORKMAN_R3___ KC_K,  KC_L,  KC_COMM,  KC_DOT,  KC_SLASH

#define ___WORKMAN___ ___WORKMAN_L1___, ___WORKMAN_R1___,       \
        ___WORKMAN_L2___, ___WORKMAN_R2___,                     \
        ___WORKMAN_L3___, ___WORKMAN_R3___


// NORMAN
#define ___NORMAN_L1___ KC_Q,  KC_W,   KC_D,  KC_F,  KC_K
#define ___NORMAN_L2___ KC_A,  KC_S,   KC_E,  KC_T,  KC_G
#define ___NORMAN_L3___ KC_Z,  KC_X,   KC_C,  KC_V,  KC_B

#define ___NORMAN_R1___ KC_J,   KC_U,  KC_R,     KC_L,    KC_SCLN
#define ___NORMAN_R2___ KC_Y,   KC_N,  KC_I,     KC_O,    KC_U
#define ___NORMAN_R3___ KC_P,   KC_M,  KC_COMM,  KC_DOT,  KC_SLASH

#define ___NORMAN___ ___NORMAN_L1___, ___NORMAN_R1___,     \
        ___NORMAN_L2___, ___NORMAN_R2___,                  \
        ___NORMAN_L3___, ___NORMAN_R3___


#define ___MALTRON_L1___ KC_Q,    KC_P,    KC_Y,    KC_C,    KC_B
#define ___MALTRON_L2___ KC_A,    KC_N,    KC_I,    KC_S,    KC_F
#define ___MALTRON_L3___ KC_SCLN, KC_SLSH, KC_J,    KC_G,    KC_COMM

#define ___MALTRON_R1___ KC_V,    KC_M,    KC_U,    KC_Z,    KC_L
#define ___MALTRON_R2___ KC_D,    KC_T,    KC_D,    KC_O,    KC_R
#define ___MALTRON_R3___ KC_DOT,  KC_W,    KC_K,    KC_MINS, KC_X

#define ___MALTRON___ ___MALTRON_L1___, ___MALTRON_R1___,       \
        ___MALTRON_L2___, ___MALTRON_R2___,                     \
        ___MALTRON_L3___, ___MALTRON_R3___


#define ___EUCALYN_L1___ KC_SLSH, KC_COMM, KC_DOT,  KC_F,    KC_Q
#define ___EUCALYN_L2___ KC_A,    KC_O,    KC_E,    KC_I,    KC_U
#define ___EUCALYN_L3___ KC_Z,    KC_X,    KC_C,    KC_V,    KC_W

#define ___EUCALYN_R1___ KC_M,    KC_R,    KC_D,    KC_Y,    KC_P
#define ___EUCALYN_R2___ KC_G,    KC_T,    KC_K,    KC_S,    KC_N
#define ___EUCALYN_R3___ KC_B,    KC_H,    KC_J,    KC_L,    KC_SCLN

#define ___EUCALYN___ ___EUCALYN_L1___, ___EUCALYN_R1___,       \
        ___EUCALYN_L2___, ___EUCALYN_R2___,                     \
        ___EUCALYN_L3___, ___EUCALYN_R3___


#define ___CARPLAX_QFMLWY_L1___ KC_Q,    KC_F,    KC_M,    KC_L,    KC_W
#define ___CARPLAX_QFMLWY_L2___ KC_D,    KC_S,    KC_T,    KC_N,    KC_R
#define ___CARPLAX_QFMLWY_L3___ KC_Z,    KC_V,    KC_G,    KC_C,    KC_X

#define ___CARPLAX_QFMLWY_R1___ KC_Y,    KC_U,    KC_O,    KC_B,    KC_J
#define ___CARPLAX_QFMLWY_R2___ KC_I,    KC_A,    KC_E,    KC_H,    KC_SCLN
#define ___CARPLAX_QFMLWY_R3___ KC_P,    KC_K,    KC_COMM, KC_DOT,  KC_SLSH

#define ___CARPLAX_QFMLWY___ ___CARPLAX_QFMLWY_L1___, ___CARPLAX_QFMLWY_R1___, \
        ___CARPLAX_QFMLWY_L2___, ___CARPLAX_QFMLWY_R2___,               \
        ___CARPLAX_QFMLWY_L3___, ___CARPLAX_QFMLWY_R3___


#define ___CARPLAX_QGMLWB_L1___ KC_Q,    KC_G,    KC_M,    KC_L,    KC_W
#define ___CARPLAX_QGMLWB_L2___ KC_D,    KC_S,    KC_T,    KC_N,    KC_R
#define ___CARPLAX_QGMLWB_L3___ KC_Z,    KC_X,    KC_C,    KC_F,    KC_J

#define ___CARPLAX_QGMLWB_R1___ KC_B,    KC_Y,    KC_U,    KC_V,    KC_SCLN
#define ___CARPLAX_QGMLWB_R2___ KC_I,    KC_A,    KC_E,    KC_O,    KC_H
#define ___CARPLAX_QGMLWB_R3___ KC_K,    KC_P,    KC_COMM, KC_DOT,  KC_SLSH

#define ___CARPLAX_QGMLWB___ ___CARPLAX_QGMLWB_L1___, ___CARPLAX_QGMLWB_R1___, \
        ___CARPLAX_QGMLWB_L2___, ___CARPLAX_QGMLWB_R2___,               \
        ___CARPLAX_QGMLWB_L3___, ___CARPLAX_QGMLWB_R3___


#define ___CARPLAX_QGMLWY_L1___ KC_Q,    KC_G,    KC_M,    KC_L,    KC_W
#define ___CARPLAX_QGMLWY_L2___ KC_D,    KC_S,    KC_T,    KC_N,    KC_R
#define ___CARPLAX_QGMLWY_L3___ KC_Z,    KC_X,    KC_C,    KC_V,    KC_J

#define ___CARPLAX_QGMLWY_R1___ KC_Y,    KC_F,    KC_U,    KC_B,    KC_SCLN
#define ___CARPLAX_QGMLWY_R2___ KC_I,    KC_A,    KC_E,    KC_O,    KC_H
#define ___CARPLAX_QGMLWY_R3___ KC_K,    KC_P,    KC_COMM, KC_DOT,  KC_SLSH

#define ___CARPLAX_QGMLWY___ ___CARPLAX_QGMLWY_L1___, ___CARPLAX_QGMLWY_R1___, \
        ___CARPLAX_QGMLWY_L2___, ___CARPLAX_QGMLWY_R2___,               \
        ___CARPLAX_QGMLWY_L3___, ___CARPLAX_QGMLWY_R3___


// BEPO Based Layouts.
// Bepo, Dvorak and Beakl on fr-bepo software layer in the OS.
// for dvorak and all the other qwerty like keyboards on bepo
#define ___DVORAK_FR_L1___ DB_QUOT,    DB_COMM,  DB_DOT,  BP_P,  BP_Y
#define ___DVORAK_FR_L2___ BP_A,       BP_O,     BP_E,    BP_U,  BP_I
#define ___DVORAK_FR_L3___ DB_SCOLON,    BP_Q,     BP_J,    BP_K,  BP_X

#define ___DVORAK_FR_R1___ BP_F, BP_G, BP_C,  BP_R,  BP_L
#define ___DVORAK_FR_R2___ BP_D, BP_H, BP_T,  BP_N,  BP_S
#define ___DVORAK_FR_R3___ BP_B, BP_M, BP_W,  BP_V,  BP_Z

#define ___DVORAK_FR___ ___DVORAK_FR_L1___, ___DVORAK_FR_R1___, \
        ___DVORAK_FR_L2___, ___DVORAK_FR_R2___,                 \
        ___DVORAK_FR_L3___, ___DVORAK_FR_R3___

/* BEAKL 15 (main layer): */

#define ___DVORAK6_FR_L1___ DB_GRV,    ___DVORAK_FR_L1___
#define ___DVORAK6_FR_L2___ TAB_BKTAB, ___DVORAK_FR_L2___
#define ___DVORAK6_FR_L3___ ___,       ___DVORAK_FR_L3___

#define ___DVORAK6_FR_R1___ ___DVORAK_FR_R1___,  BP_MIN
#define ___DVORAK6_FR_R2___ ___DVORAK_FR_R2___,  BP_SLSH
#define ___DVORAK6_FR_R3___ ___DVORAK_FR_R3___,  DB_BACKSLASH

#define ___6DVORAK_FR___ ___6DVORAK_FR_L1___, ___6DVORAK_FR_R1___,      \
        ___6DVORAK_FR_L2___, ___6DVORAK_FR_R2___,                       \
        ___6DVORAK_FR_L3___, ___6DVORAK_FR_R3___

// dont forget ; and -.  the 'a' home row is official placement.
#define ___BEAKL15_FR_L1___          BP_Q, BP_H,     BP_O,    BP_U, BP_X
#define ___BEAKL15_FR_L2___          BP_Y, BP_I,     BP_E,    BP_A, BB_DOT
#define ___BEAKL15_FR_L2a___ BP_MIN, BP_Y, BP_I,     BP_E,    BP_A, BB_DOT
#define ___BEAKL15_FR_L3___          BP_J, BP_SLSH, BB_COMM, BP_K, BB_QUOT

#define ___BEAKL15_FR_R1___  BP_G, BP_C, BP_R, BP_F, BP_Z
#define ___BEAKL15_FR_R2___  BP_D, BP_S, BP_T, BP_N, BP_B
#define ___BEAKL15_FR_R2a___ BP_D, BP_S, BP_T, BP_N, BP_B, DB_SCLN
#define ___BEAKL15_FR_R3___  BP_W, BP_M, BP_L, BP_P, BP_V

#define ___6BEAKL15_FR___ ___, ___BEAKL15_FR_L1___, ___BEAKL15_FR_R1___, ___, \
        ___BEAKL15_FR_L2a___, ___BEAKL15_FR_R2a___,                     \
        ___, ___BEAKL15_FR_L3___, ___BEAKL15_FR_R3___, ___

#define ___BEAKL15_FR___ ___BEAKL15_FR_L1___, ___BEAKL15_FR_R1___, \
        ___BEAKL15_FR_L2___, ___BEAKL15_FR_R2___,                \
        ___BEAKL15_FR_L3___, ___BEAKL15_FR_R3___

#define ___BEPO_L1___             BP_B,    BP_EACU, BP_P,   BP_O,   BP_EGRV
#define ___BEPO_L2___             BP_A,    BP_U,    BP_I,   BP_E,   BP_COMM
#define ___BEPO_L3___ /*BP_ECRC*/ BP_AGRV, BP_Y,    BP_X,   BP_DOT, BP_K

#define ___BEPO_R1___  /* BP_DCRC,*/  BP_V,     BP_D,  BP_L,  BP_J,  BP_Z
#define ___BEPO_R2___  /* BP_C,   */  BP_T,     BP_S,  BP_R,  BP_N,  BP_M  //BP_CCED
#define ___BEPO_R3___                 BP_QUOT,  BP_Q,  BP_G,  BP_H,  BP_F //BP_SFT_T_W

// Bepo for a 3x6 split.  CCED switched hands. :-(  'Altgr-c c'  does the same.
// W has to drop down to the bottom. Silly unbalanced layout.
#define ___BEPO6_L1___  BP_CCED,   ___BEPO_L1___
#define ___BEPO6_L2___  TAB_BKTAB, ___BEPO_L2___
#define ___BEPO6_L3___  BP_ECIR,   ___BEPO_L3___

#define ___BEPO6_R1___   ___BEPO_R1___, BP_PERC
#define ___BEPO6_R2___   ___BEPO_R2___,  BP_C
#define ___BEPO6_R3___   ___BEPO_R3___, BP_W

#define ___BEPO6___ ___BEPO6_L1___, ___BEPO6_R1___,  \
        ___BEPO6_L2___, ___BEPO6_R2___,              \
        ___BEPO6_L3___, ___BEPO6_R3___

#define ___BEPO___ ___BEPO_L1___, ___BEPO_R1___,  \
        ___BEPO_L2___, ___BEPO_R2___,             \
        ___BEPO_L3___, ___BEPO_R3___


/*******************************************************************/
/** TOP ROWS  Func,Symbols, Numbers you find there.               **/
/*******************************************************************/
// for everything on qwerty.
#define ___NUMBER_L___ KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ___NUMBER_R___ KC_6,    KC_7,    KC_8,    KC_9,    KC_0

#define ___NUMBER_BEAKL15_L___ KC_4, KC_0, KC_1, KC_2, KC_3
#define ___NUMBER_BEAKL15_R___ KC_7, KC_6, KC_5, KC_9, KC_8

// a top symbol row if someone wants it.
#define ___SYMB_L___   KC_EXLM,   KC_AT,    KC_HASH,  KC_DLR,   KC_PERC
#define ___SYMB_R___   KC_CIRC,   KC_AMPR,  KC_ASTR,   KC_LPRN,  KC_RPRN

/// BEPO ////
// For numbers on bepo. Bepo has numbers on shifted keys, the
// reverse of many layouts.
#define ___NUMBER_BEPO_L___ DB_1,   DB_2,   DB_3,   DB_4,   DB_5
#define ___NUMBER_BEPO_R___ DB_6,   DB_7,   DB_8,   DB_9,   DB_0

// In case you want to try BEAKL 15 Numbers
#define ___NUMBER_BEAKL15_BP_L___ DB_4, DB_0, DB_1, DB_2, DB_3
#define ___NUMBER_BEAKL15_BP_R___ DB_7, DB_6, DB_5, DB_9, DB_8

// The top row.  Bepo has symbols not numbers. Numbers are the shifted values.
// There are actually 13 keys specified for bepo.
#define ___SYMBOL_BEPO_L___ /* BP_DLR */ BP_DQUO,  BP_LDAQ,   BP_RDAQ,   BP_LPRN,   BP_RPRN
#define ___SYMBOL_BEPO_R___    BP_AT,    BP_PLUS,  BP_MINS,   BP_SLSH,  BP_ASTR /* BP_EQL,  BP_PERC */

#define ___6SYMBOL_BEPO_L___  BP_DLR, ___SYMBOL_BEPO_L___
#define ___6SYMBOL_BEPO_R___  ___SYMBOL_BEPO_R___, BP_EQL  /*  BP_PERC */

// a top qwerty style symbol row if someone wants it.
#define ___SYMB_L_FR___   DB_EXLM,   BP_AT,    BP_HASH,  BP_DLR,   BP_PERC
#define ___SYMB_R_FR___   DB_CIRC,   BP_AMPR,  BP_ASTR,  BP_LPRN,  BP_RPRN


// function key rows, works for everyone.
#define ___FUNC_L___   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define ___FUNC_R___   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10

#define ___FUNC_1_6___   KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6
#define ___FUNC_7_12___  KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_F11, KC_F12

#define ___FUNC_BEAKL_L___ KC_F4, KC_F10, KC_F1, KC_F2, KC_F3
#define ___FUNC_BEAKL_R___ KC_F7, KC_F6, KC_F5, KC_F9, KC_F8

#define ___12_FUNC_BEAKL___ KC_F11, ___FUNC_BEAKL_L___, ___FUNC_BEAKL_R___, KC_F12

// Altogether. Defines all the various top rows that
// are present with all these layouts.
// All together as blocks of 10
#define ___NUMS___      ___NUMBER_L___,         ___NUMBER_R___
#define ___SYMS___      ___SYMB_L___,           ___SYMB_R___
#define ___BKLNUMS___   ___NUMBER_BEAKL15_L___, ___NUMBER_BEAKL15_R___
#define ___NUMS_BP___    ___NUMBER_BEPO_L___,    ___NUMBER_BEPO_R___
#define ___SYMS_BEPO___ ___SYMBOL_BEPO_L___,    ___SYMBOL_BEPO_L___
#define ___BKLNUMS_BP___  ___NUMBER_BEAKL15_BP_L___, ___NUMBER_BEAKL15_BP_R___
#define ___FUNCS_1_10___ ___FUNC_L___, ___FUNC_R___
