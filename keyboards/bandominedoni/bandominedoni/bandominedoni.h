/* Copyright 2021 3araht
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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

//  oc: for Open Close selection pedal
//  fn: function layer

#define LAYOUT( \
              l00, l01, l02, l03, l04, \
      l10, l11, l12, l13, l14, l15, l16, \
         l20, l21, l22, l23, l24, l25, l26, \
      l30, l31, l32, l33, l34, l35, l36, \
    l40, l41, l42, l43, l44, l45, l46, l47,  \
    \
    oc,         r00, r01, r02, r03,         fn, \
             r10, r11, r12, r13, r14, \
           r20, r21, r22, r23, r24, r25, \
    r30, r31, r32, r33, r34, r35, r36, r37, \
      r40, r41, r42, r43, r44, r45, r46, r47, \
    r50, r51, r52, r53, r54, r55, r56, r57, r58 \
) { \
    {   l40,   l00,   l01,   l02,   l03,   l04, KC_NO }, \
    {   l10,   l11,   l12,   l13,   l14,   l15,   l16 }, \
    {   l20,   l21,   l22,   l23,   l24,   l25,   l26 }, \
    {   l30,   l31,   l32,   l33,   l34,   l35,   l36 }, \
    {   l41,   l42,   l43,   l44,   l45,   l46,   l47 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    {   r50,   r40,   r31,   r20,   r10,   r00,   r30 }, \
    {   r51,   r41,   r32,   r21,   r11,   r01,    oc }, \
    {   r52,   r42,   r33,   r22,   r12,   r02,    fn }, \
    {   r53,   r43,   r34,   r23,   r13,   r03,   r58 }, \
    {   r54,   r44,   r35,   r24,   r14,   r47,   r57 }, \
    {   r55,   r45,   r36,   r25,   r37,   r46,   r56 }  \
}

//  Uncomment below if a pedal used for Open/Close is normally-on type (such as Yamaha's.)
// #define PEDAL_NORMALLY_CLOSED

#ifdef PEDAL_NORMALLY_CLOSED
#   define MO_SWAP  MO(_OPEN)
#   define DF_SWAP  DF(_CLOSE)
#   define TG_SWAP  TG(_OPEN)
#else
#   define MO_SWAP  MO(_CLOSE)
#   define DF_SWAP  DF(_OPEN)
#   define TG_SWAP  TG(_CLOSE)
#endif

// Long press: go to _FN layer, tap: MUTE
#define FN_MUTE  LT(_FN, KC_MUTE)
#define DF_QWER  DF(_QWERTY)
#define MIS_EIS  LT(_MISC,KC_LANG2)
#define MIS_KAN  LT(_MISC,KC_LANG1)

#define _________________QWERTY_L1_________________ KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________ KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________ KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________ KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________ KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________ KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH

#define _________________COLEMAK_L1________________ KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
#define _________________COLEMAK_L2________________ KC_A,    KC_R,    KC_S,    KC_T,    KC_D
#define _________________COLEMAK_L3________________ KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________COLEMAK_R1________________ KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define _________________COLEMAK_R2________________ KC_H,    KC_N,    KC_E,    KC_I,    KC_O
#define _________________COLEMAK_R3________________ KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH

#define _________________NUMBER_L__________________ KC_1,    KC_2,    KC_3,    KC_4,    KC_5
// #define _________________NUMBER_R__________________ KC_6,    KC_7,    KC_8,    KC_9,    KC_0

#define _________________FUNC__L___________________ KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
// #define _________________FUNC__R___________________ KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10

//  Overriding is_keyboard_left() in qmk_firmware/quantum/split_common/split_util.c to limit the handedness check only once.
//  reason: bandoMIneDonI has no space on right hand side to use "SPLIT_HAND_MATRIX_GRID".
//          However, It enables to decide the handedness by the HW by adding one condition: "not to press any keys (especially r30) dusing startup."
bool is_keyboard_left(void);
