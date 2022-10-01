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

// + ------------- +
// + HOME ROW MODS |
// + ------------- +

// https://precondition.github.io/home-row-mods

// Left, QWERTY
#define HM_A LCTL_T(KC_A)
#define HM_S LALT_T(KC_S)
#define HM_D LGUI_T(KC_D)
#define HM_F LSFT_T(KC_F)

// Left, COLEMAK
#define HMCMK_A LCTL_T(KC_A)
#define HMCMK_R LALT_T(KC_R)
#define HMCMK_S LGUI_T(KC_S)
#define HMCMK_T LSFT_T(KC_T)

// Right, QWERTY
#define HM_J RSFT_T(KC_J)
#define HM_K RGUI_T(KC_K)
#define HM_L LALT_T(KC_L) // LALT, not RALT
#define HM_SCLN RCTL_T(KC_SCLN)

// Right, COLEMAK
#define HMCMK_N RSFT_T(KC_N)
#define HMCMK_E RGUI_T(KC_E)
#define HMCMK_I LALT_T(KC_I) // LALT, not RALT
#define HMCMK_O RCTL_T(KC_O)

// clang-format off

// + ------ +
// + QWERTY |
// + ------ +

#define _________QWERTY_HRM_LEFT__________    HM_A,    HM_S,    HM_D,    HM_F
#define _________QWERTY_HRM_RIGHT_________    HM_J,    HM_K,    HM_L, HM_SCLN

#define _______________QWERTY_L1_x5________________    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#ifdef HOME_ROW_MODS_ENABLED
#define _______________QWERTY_L2_x5________________ _________QWERTY_HRM_LEFT__________,    KC_G
#else
#define _______________QWERTY_L2_x5________________    KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#endif
#define _______________QWERTY_L3_x5________________    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _______________QWERTY_R1_x5________________    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#ifdef HOME_ROW_MODS_ENABLED
#define _______________QWERTY_R2_x5________________    KC_H, _________QWERTY_HRM_RIGHT_________
#else
#define _______________QWERTY_R2_x5________________    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN
#endif
#define _______________QWERTY_R3_x5________________    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH

// + ------ +

#define ___________________QWERTY_L1_x6_____________________  KC_TAB, _______________QWERTY_L1_x5________________
#define ___________________QWERTY_L2_x6_____________________   TD_ED, _______________QWERTY_L2_x5________________
#define ___________________QWERTY_L3_x6_____________________ TD_LSPC, _______________QWERTY_L3_x5________________
#define ___________________QWERTY_R1_x6_____________________ _______________QWERTY_R1_x5________________, KC_BSPC
#define ___________________QWERTY_R2_x6_____________________ _______________QWERTY_R2_x5________________, KC_QUOT
#define ___________________QWERTY_R3_x6_____________________ _______________QWERTY_R3_x5________________, TD_RSPC

// + -------------- +
// + COLEMAK_MOD_DH |
// + -------------- +

#define _____COLEMAK_MOD_DH_HRM_LEFT______ HMCMK_A, HMCMK_R, HMCMK_S, HMCMK_T
#define _____COLEMAK_MOD_DH_HMR_RIGHT_____ HMCMK_N, HMCMK_E, HMCMK_I, HMCMK_O

#define ____________COLEMAK_MOD_DH_L1_x5___________    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B
#ifdef HOME_ROW_MODS_ENABLED
#define ____________COLEMAK_MOD_DH_L2_x5___________ _____COLEMAK_MOD_DH_HRM_LEFT______,    KC_G
#else
#define ____________COLEMAK_MOD_DH_L2_x5___________    KC_A,    KC_R,    KC_S,    KC_T,    KC_G
#endif
#define ____________COLEMAK_MOD_DH_L3_x5___________    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V

#define ____________COLEMAK_MOD_DH_R1_x5___________    KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN
#ifdef HOME_ROW_MODS_ENABLED
#define ____________COLEMAK_MOD_DH_R2_x5___________    KC_M, _____COLEMAK_MOD_DH_HMR_RIGHT_____
#else
#define ____________COLEMAK_MOD_DH_R2_x5___________    KC_M,    KC_N,    KC_E,    KC_I,    KC_O
#endif
#define ____________COLEMAK_MOD_DH_R3_x5___________    KC_K,    KC_H, KC_COMM,  KC_DOT,KC_SLASH

// + ------- +

#define ________________COLEMAK_MOD_DH_L1_x6________________  KC_TAB, ____________COLEMAK_MOD_DH_L1_x5___________
#define ________________COLEMAK_MOD_DH_L2_x6________________   TD_ED, ____________COLEMAK_MOD_DH_L2_x5___________
#define ________________COLEMAK_MOD_DH_L3_x6________________ TD_LSPC, ____________COLEMAK_MOD_DH_L3_x5___________
#define ________________COLEMAK_MOD_DH_R1_x6________________ ____________COLEMAK_MOD_DH_R1_x5___________, KC_BSPC
#define ________________COLEMAK_MOD_DH_R2_x6________________ ____________COLEMAK_MOD_DH_R2_x5___________, KC_QUOT
#define ________________COLEMAK_MOD_DH_R3_x6________________ ____________COLEMAK_MOD_DH_R3_x5___________, TD_RSPC

// + --------------- +
// + NUMBERS/SYMBOLS |
// + --------------- +

#define ______________NUMBER_LEFT_x5_______________    KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ______________NUMBER_RIGHT_x5______________    KC_6,    KC_7,    KC_8,    KC_9,    KC_0
#define ___________________NUMBER_LEFT_x6___________________  KC_GRV, ______________NUMBER_LEFT_x5_______________
#define ___________________NUMBER_RIGHT_x6__________________ ______________NUMBER_RIGHT_x5______________, KC_MINS

#define ______________SYMBOL_LEFT_x5_______________ KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC
#define ______________SYMBOL_RIGHT_x5______________ KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN
#define ___________________SYMBOL_LEFT_x6___________________  KC_GRV, ______________SYMBOL_LEFT_x5_______________
#define ___________________SYMBOL_RIGHT_x6__________________ ______________SYMBOL_RIGHT_x5______________, KC_TILD

#define ____________________SYMBOL_R2_x6____________________ KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV
#define ____________________SYMBOL_R3_x6____________________ KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD

// + ------- +
// + UNICODE |
// + ------- +

#ifdef UNICODEMAP_ENABLE
#define ______________UNICODE_L2_x5________________   A_GRV,   E_GRV,   I_GRV,   O_GRV,   U_GRV
#define ______________UNICODE_L3_x5________________   A_UML,   E_ACT,   I_CIR,   O_UML,   U_UML
#endif

// + ---- +
// + FUNC |
// + ---- +

#define ______________FUNC_LEFT_5x_________________   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define ______________FUNC_RIGHT_5x________________   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10
#define ____________________FUNC_LEFT_x6____________________ ______________FUNC_LEFT_5x_________________, KC_F6
#define ____________________FUNC_RIGHT_x6___________________ KC_F7, ______________FUNC_RIGHT_5x________________

// + ---- +
// + MISC |
// + ---- +

#define _________________BLANK_5x__________________ _______, _______, _______, _______, _______
#define ______________________BLANK_6x______________________ _________________BLANK_5x__________________, _______

#define _________________NONE_5x___________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ______________________NONE_6x_______________________ _________________NONE_5x___________________, XXXXXXX

#define ________________NAV_R2_x5__________________ XXXXXXX, XXXXXXX,   KC_UP, XXXXXXX, KC_PGUP
#define ________________NAV_R3_x5__________________ XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN
#define ____________NAV_VIM_x4____________ KC_LEFT, KC_DOWN,  KC_UP, KC_RIGHT

#define _______________CONFIG_R1_x5________________ UC_MOD,  KC_ASUP,   NK_ON, XXXXXXX, XXXXXXX
#define _______________CONFIG_R2_x5________________ XXXXXXX, KC_ASTG, NK_TOGG, CG_TOGG, XXXXXXX
#define _______________CONFIG_R3_x5________________ UC_RMOD, KC_ASDN,  NK_OFF, CG_NORM, XXXXXXX

#define ________________RGB_L2_x5__________________  RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI
#define ________________RGB_L3_x5__________________ RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD

// clang-format on
