/* Copyright 2023 Christoph Jabs (BifbofII)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2020 @jola5
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

#include "bifbofii.h"

/*
Since our quirky block definitions are basically a list of comma separated
arguments, we need a wrapper in order for these definitions to be
expanded before being used as arguments to the LAYOUT_xxx macro.
*/

/*
Blocks for each of the four major keyboard layouts
Organized so we can quickly adapt and modify all of them
at once, rather than for each keyboard, one at a time.
And this allows for much cleaner blocks in the keymaps.
For instance Tap/Hold for Control on all of the layouts

NOTE: These are all the same length.  If you do a search/replace
  then you need to add/remove underscores to keep the
  lengths consistent.
*/

// clang-format off
#define _________________QWERTY_L1_________________       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________       KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT
#define _________________QWERTY_R3_________________       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH


#define _________________COLEMAK_L1________________       KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
#define _________________COLEMAK_L2________________       KC_A,    KC_R,    KC_S,    KC_T,    KC_D
#define _________________COLEMAK_L3________________       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________COLEMAK_R1________________       KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define _________________COLEMAK_R2________________       KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT
#define _________________COLEMAK_R3________________       KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH


#define _________________DVORAK_L1_________________       KC_QUOT, KC_COMM, KC_DOT, KC_P,     KC_Y
#define _________________DVORAK_L2_________________       KC_A,    KC_O,    KC_E,   KC_U,     KC_I
#define _________________DVORAK_L3_________________       KC_SCLN, KC_Q,    KC_J,   KC_K,     KC_X

#define _________________DVORAK_R1_________________       KC_F,    KC_G,    KC_C,    KC_R,    KC_L
#define _________________DVORAK_R2_________________       KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH
#define _________________DVORAK_R3_________________       KC_B,    KC_M,    KC_W,    KC_V,    KC_Z


#define ________________NUMBER_LEFT________________       KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ________________NUMBER_RIGHT_______________       KC_6,    KC_7,    KC_8,    KC_9,    KC_0
#define _________________FN_LEFT___________________       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define _________________FN_RIGHT__________________       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10

#define ___________________BLANK___________________       _______, _______, _______, _______, _______
#define ___________________BLOCK___________________       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX


#define _________________FUNC_L1___________________       _______, _______, _______, _______, KC_MUTE
#define _________________FUNC_L2___________________       _______, KC_WBAK, _______, _______, KC_WFWD
#define _________________FUNC_L3___________________       ___________________BLANK___________________

#define _________________FUNC_R1___________________       KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY
#define _________________FUNC_R2___________________       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______
#define _________________FUNC_R3___________________       KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______


#define _________________LOWER_L1__________________       KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC
#define _________________LOWER_L2__________________       ___________________BLANK___________________
#define _________________LOWER_L3__________________       ___________________BLANK___________________

#define _________________LOWER_R1__________________       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN
#define _________________LOWER_R2__________________       _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR
#define _________________LOWER_R3__________________       ___________________BLANK___________________



#define _________________UPPER_L1__________________       ________________NUMBER_LEFT________________
#define _________________UPPER_L2__________________       _________________FN_LEFT___________________
#define _________________UPPER_L3__________________       KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11

#define _________________UPPER_R1__________________       ________________NUMBER_RIGHT_______________
#define _________________UPPER_R2__________________       KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC
#define _________________UPPER_R3__________________       KC_F12,  _______, _______, _______, _______



#define _________________UNICODE_L1________________       _______, _______, KC_EUR,  _______, _______
#define _________________UNICODE_L2________________       KC_AE,   KC_SS,   _______, _______, _______
#define _________________UNICODE_L3________________       _______, _______, KC_CPR,  _______, _______

#define _________________UNICODE_R1________________       _______, KC_UE,   _______, KC_OE,   _______
#define _________________UNICODE_R2________________       ___________________BLANK___________________
#define _________________UNICODE_R3________________       ___________________BLANK___________________



#define _________________ADJUST_L1_________________       QWERTY,  UC_WIN,  XXXXXXX, XXXXXXX, XXXXXXX
#define _________________ADJUST_L2_________________       XXXXXXX, XXXXXXX, DVORAK,  XXXXXXX, GAMING
#define _________________ADJUST_L3_________________       XXXXXXX, XXXXXXX, COLEMAK, XXXXXXX, QK_BOOT

#define _________________ADJUST_R1_________________       XXXXXXX, XXXXXXX, XXXXXXX, UC_MAC,  XXXXXXX
#define _________________ADJUST_R2_________________       XXXXXXX, XXXXXXX, XXXXXXX, UC_LINX, XXXXXXX
#define _________________ADJUST_R3_________________       ___________________BLOCK___________________

// clang-format on
