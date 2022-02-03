/* Copyright 2020 Sergi Meseguer <zigotica@gmail.com>
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

#pragma once
#include "zigotica.h"

// clang-format off
#define _BLANK_ROW      _______, _______, _______, _______, _______
#define _BLANK_THUMB    _______, _______

/*
 * STENAI Layer
 *
 *   ,---------------------------------------.         ,---------------------------------------.
 *   |       |       |       |       |       |         |       |       |       |       |       |
 *   |  ` ~  |   W   |   D   |   P   |   F   |         |   K   |   Y   |   U   |   Q   |  ' "  |
 *   |       |       |       |       |       |         |       |       |       |       |       |
 *   |-------+-------+-------+-------+-------|         |-------+-------+-------+-------+-------|
 *   |       |       |       |       |       |         |       |       |       |       |       |
 *   |   H   |   R   |   S   |   T   |   G   |         |   M   |   N   |   A   |   I   |   O   |
 *   |  alt  | ctrl  | shft  | meta  |       |         |       |  meta |  shft | ctrl  |  alt  |
 *   |-------+-------+-------+-------+-------|         |-------+-------+-------+-------+-------|
 *   |       |       |       |       |       |         |       |       |       |       |       |
 *   |   B   |   X   |   C   |   V   |  [ {  |         |  , <  |   L   |   Z   |   J   |   . > |
 *   |       |       |       |       | TD ]} |         |  TD ; |       |       |       |  TD : |
 *   `-------+-------+-------+-------+-------|         |-------+-------+-------+-------+-------.
 *                           |       |       |         |       |       |
 *                           |  TAB  |  SPC  |         |   E   | INTRO |
 *                           |  num  |  nav  |         |  sym  |   fn  |
 *                           `---------------'         `---------------'
 *
 */
#define _STENAI_L1      KC_GRV,           KC_W,            KC_D,          KC_P,             KC_F
#define _STENAI_L2      LALT_T(KC_H),     LCTL_T(KC_R),    LSFT_T(KC_S),  LGUI_T(KC_T),     KC_G
#define _STENAI_L3      KC_B,             KC_X,            KC_C,          KC_V,             ZK_BRC
#define _STENAI_LT      LT(_NUM, KC_TAB), LT(_NAV, KC_SPC)

#define _STENAI_R1      KC_K,             KC_Y,            KC_U,          KC_Q,             KC_QUOT
#define _STENAI_R2      KC_M,             RGUI_T(KC_N),    RSFT_T(KC_A),  RCTL_T(KC_I),     RALT_T(KC_O)
#define _STENAI_R3      ZK_SEMI,          KC_L,            KC_Z,          KC_J,             ZK_COLON
#define _STENAI_RT      LT(_SYM, KC_E),   LT(_FN, KC_ENT)


#define _COLEMAK_L1     KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
#define _COLEMAK_L2     KC_A,    KC_R,    KC_S,    KC_T,    KC_D
#define _COLEMAK_L3     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _COLEMAK_R1     KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define _COLEMAK_R2     KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT
#define _COLEMAK_R3     KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH

#define _QWERTY_L1      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _QWERTY_L2      KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _QWERTY_L3      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _QWERTY_R1      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _QWERTY_R2      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT
#define _QWERTY_R3      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH

/*
 * NUM Layer
 *
 *   ,---------------------------------------.         ,---------------------------------------.
 *   |       |       |       |       |       |         |       |       |       |       |       |
 *   |       |   -   |   +   |   =   |       |         |       |   7   |   8   |   9   |       |
 *   |       |       |       |       |       |         |       |       |       |       |       |
 *   |-------+-------+-------+-------+-------|         |-------+-------+-------+-------+-------|
 *   |       |       |       |       |       |         |       |       |       |       |       |
 *   |       |       |       |       |       |         |       |   1   |   2   |   3   |       |
 *   |       |       |       |       |       |         |       |       |       |       |       |
 *   |-------+-------+-------+-------+-------|         |-------+-------+-------+-------+-------|
 *   |       |       |       |       |       |         |       |       |       |       |       |
 *   |       |       |   /   |   *   |       |         |       |   4   |   5   |   6   |       |
 *   |       |       |       |       |       |         |       |       |       |       |       |
 *   `-------+-------+-------+-------+-------|         |-------+-------+-------+-------+-------.
 *                           |:::::::|       |         |       |       |
 *                           |:::::::|       |         |   0   |  BACK |
 *                           |:::::::|       |         |       |       |
 *                           `---------------'         `---------------'
 *
 */
#define ____NUM_L1      _______, KC_MINS, KC_PLUS, KC_EQL,  _______
#define ____NUM_L2      _BLANK_ROW
#define ____NUM_L3      _______, _______, KC_SLSH, KC_ASTR, _______
#define ____NUM_LT      _BLANK_THUMB

#define ____NUM_R1      _______, KC_7,    KC_8,    KC_9,    _______
#define ____NUM_R2      _______, KC_1,    KC_2,    KC_3,    _______
#define ____NUM_R3      _______, KC_4,    KC_5,    KC_6,    _______
#define ____NUM_RT      KC_0,    KC_BSPC

/*
* NAVIGATION Layer
*
*   ,---------------------------------------.         ,---------------------------------------.
*   |       |       |       |       |       |         |       |       |       |       |       |
*   |       |  PREV |  PLAY |  NEXT |       |         |  WHDN |  HOME |   UP  |  PGUP |       |
*   |       |       |       |       |       |         |       |       |       |       |       |
*   |-------+-------+-------+-------+-------|         |-------+-------+-------+-------+-------|
*   |       |       |       |       |       |         |       |       |       |       |       |
*   |       |       |       |       |       |         |  WHUP |  LF   |   DN  |  RG   |       |
*   |       |       |       |       |       |         |       |       |       |       |       |
*   |-------+-------+-------+-------+-------|         |-------+-------+-------+-------+-------|
*   |       |       |       |       |       |         |       |       |       |       |       |
*   |       |       |       |       |       |         |       |  END  |       |  PGDN |       |
*   |       |       |       |       |       |         |       |       |       |       |       |
*   `-------+-------+-------+-------+-------|         |-------+-------+-------+-------+-------.
*                           |       |:::::::|         |       |       |
*                           |       |:::::::|         |       |  DEL  |
*                           |       |:::::::|         |       |       |
*                           `---------------'         `---------------'
*/
#define ____NAV_L1      _______, KC_MPRV, KC_MPLY, KC_MNXT, _______
#define ____NAV_L2      _BLANK_ROW
#define ____NAV_L3      _BLANK_ROW
#define ____NAV_LT      _BLANK_THUMB

#define ____NAV_R1      KC_WH_D, KC_HOME, KC_UP,   KC_PGUP, _______
#define ____NAV_R2      KC_WH_U, KC_LEFT, KC_DOWN, KC_RGHT, _______
#define ____NAV_R3      _______, KC_END,  _______, KC_PGDN, _______
#define ____NAV_RT      _______, KC_DEL

/*
* SYMBOLS Layer
*
*   ,---------------------------------------.         ,---------------------------------------.
*   |       |       |       |       |       |         |       |       |       |       |       |
*   |   %   |   &   |   ?   |   |   |   !   |         |       |       |       |       |       |
*   |       |       |       |       |       |         |       |       |       |       |       |
*   |-------+-------+-------+-------+-------|         |-------+-------+-------+-------+-------|
*   |       |       |       |       |       |         |       |       |       |       |       |
*   |   #   |   @   |   :   |   ;   |   $   |         |       |       |       |       |       |
*   |       |       |       |       |       |         |       |       |       |       |       |
*   |-------+-------+-------+-------+-------|         |-------+-------+-------+-------+-------|
*   |       |       |       |       |       |         |       |       |       |       |       |
*   |   (   |   ~   |   /   |   \   |   ^   |         |       |       |       |       |       |
*   |       |       |       |       |       |         |       |       |       |       |       |
*   `-------+-------+-------+-------+-------|         |-------+-------+-------+-------+-------.
*                           |       |       |         |:::::::|       |
*                           |       |  ESC  |         |:::::::|       |
*                           |       |       |         |:::::::|       |
*                           `---------------'         `---------------'
*/
#define ____SYM_L1      KC_PERC, KC_AMPR, KC_QUES, KC_PIPE, KC_EXLM
#define ____SYM_L2      KC_HASH, KC_AT,   KC_COLN, KC_SCLN, KC_DLR
#define ____SYM_L3      ZK_PRN,  KC_TILD, KC_SLSH, KC_BSLS, KC_CIRC
#define ____SYM_LT      _______, KC_ESC

#define ____SYM_R1      _BLANK_ROW
#define ____SYM_R2      _BLANK_ROW
#define ____SYM_R3      _BLANK_ROW
#define ____SYM_RT      _BLANK_THUMB

/*
* FUNCTION KEYS Layer
*
*   ,---------------------------------------.         ,---------------------------------------.
*   |       |       |       |       |       |         |       |       |       |       |       |
*   |       |       |       |       |       |         |       |  F7   |   F8  |   F9  |  F10  |
*   |       |       |       |       |       |         |       |       |       |       |       |
*   |-------+-------+-------+-------+-------|         |-------+-------+-------+-------+-------|
*   |       |       |       |       |       |         |       |       |       |       |       |
*   |       |       |       |       |       |         |       |  F1   |   F2  |   F3  |  F11  |
*   |       |       |       |       |       |         |       |       |       |       |       |
*   |-------+-------+-------+-------+-------|         |-------+-------+-------+-------+-------|
*   |       |       |       |       |       |         |       |       |       |       |       |
*   |       |       |       |       |       |         |       |  F4   |   F5  |   F6  |  F12  |
*   |       |       |       |       |       |         |       |       |       |       |       |
*   `-------+-------+-------+-------+-------|         |-------+-------+-------+-------+-------.
*                           |       |       |         |       |:::::::|
*                           |       |  ESC  |         |       |:::::::|
*                           |       |       |         |       |:::::::|
*                           `---------------'         `---------------'
*/
#define ____FN_L1       _BLANK_ROW
#define ____FN_L2       _BLANK_ROW
#define ____FN_L3       _BLANK_ROW
#define ____FN_LT       _______, KC_ESC

#define ____FN_R1       _______,  KC_F7,  KC_F8,  KC_F9,  KC_F10
#define ____FN_R2       _______,  KC_F1,  KC_F2,  KC_F3,  KC_F11
#define ____FN_R3       _______,  KC_F4,  KC_F5,  KC_F6,  KC_F12
#define ____FN_RT       _BLANK_THUMB
// clang-format on
