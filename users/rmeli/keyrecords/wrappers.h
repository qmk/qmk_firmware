/*
Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
Copyright 2020 @jola5
Copyright 2021-2022 Rocco Meli <@RMeli>

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

#ifdef UNICODEMAP_ENABLE
#    include "keyrecords/unicode.h"
#endif

// https://precondition.github.io/home-row-mods

#define HM_A LCTL_T(KC_A)
#define HM_S LALT_T(KC_S)
#define HM_D LGUI_T(KC_D)
#define HM_F LSFT_T(KC_F)

#define HM_J RSFT_T(KC_J)
#define HM_K RGUI_T(KC_K)
#define HM_L LALT_T(KC_L)
#define HM_SCLN RCTL_T(KC_SCLN)

// clang-format off

// + ------ +
// + QWERTY |
// + ------ +

#define _________________QWERTY_L1_________________    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#ifdef HOME_ROW_MODS_ENABLE
#define _________________QWERTY_L2_________________    HM_A,    HM_S,    HM_D,    HM_F,    KC_G
#else
#define _________________QWERTY_L2_________________    KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#endif
#define _________________QWERTY_L3_________________    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#ifdef HOME_ROW_MODS_ENABLE
#define _________________QWERTY_R2_________________    KC_H,    HM_J,    HM_K,    HM_L,    HM_SCLN
#else
#define _________________QWERTY_R2_________________    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#endif
#define _________________QWERTY_R3_________________    KC_N,    KC_M, KC_COMM,  KC_DOT,    KC_SLSH

// + -------------- +
// + COLEMAK_MOD_DH |
// + -------------- +

#define ______________COLEMAK_MOD_DH_L1____________    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B
#define ______________COLEMAK_MOD_DH_L2____________    KC_A,    KC_R,    KC_S,    KC_T,    KC_G
#define ______________COLEMAK_MOD_DH_L3____________    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V

#define ______________COLEMAK_MOD_DH_R1____________    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define ______________COLEMAK_MOD_DH_R2____________    KC_M,    KC_N,    KC_E,    KC_I,    KC_O
#define ______________COLEMAK_MOD_DH_R3____________    KC_K,    KC_H, KC_COMM,  KC_DOT,    KC_SLASH

// + ------ +
// + NUMBER |
// + ------ +

#define ________________NUMBER_LEFT________________    KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ________________NUMBER_RIGHT_______________    KC_6,    KC_7,    KC_8,    KC_9,    KC_0

// + ------- +
// + UNICODE |
// + ------- +

#define _________________UNICODE_L2________________    A_GRV,   E_GRV,   I_GRV,   O_GRV,   U_GRV
#define _________________UNICODE_L3________________    A_UML,   E_ACT,   I_CIR,   O_UML,   U_UML

// + ---- +
// + FUNC |
// + ---- +

#define _________________FUNC_LEFT_________________    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define _________________FUNC_RIGHT________________    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10

// + ------- +
// + MISC |
// + ------- +

#define ___________________BLANK___________________    _______, _______, _______, _______, _______

// clang-format on