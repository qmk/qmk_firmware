// Copyright 2023 @miketronic -- Mike B <mxb540@gmail.com>
// SPDX-License-Identifier: GPL-2.0+

#pragma once
#include "miketronic.h"

/*  Pattern adapted from users/drashna/wrapper.h
    Define per-layout keymap sections. Also requires a wrapper.
    Example:
        #define LAYOUT_:name_wrapper(...)            LAYOUT_:name(__VA_ARGS__)
        const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [_MODS] = LAYOUT_:name _wrapper(
            _______, ___________________BLANK___________________, ...
            ...
        ),
        }
*/


// clang-format off
#define LAYOUT_ortho_4x12_wrapper(...)  LAYOUT_ortho_4x12(__VA_ARGS__)
#define LAYOUT_planck_grid_wrapper(...)  LAYOUT_planck_grid(__VA_ARGS__)
#define LAYOUT_3x11_wrapper(...)  LAYOUT(__VA_ARGS__)


#define _________________QWERTY_L1_________________        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________        KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________        FNZ,     KC_X,    KC_C,    VLOWER,  KC_B

#define _________________QWERTY_R1_________________        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________        KC_H,    KC_J,    KRAISE,  KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH

#define _________________WORKMAN_1_________________       KC_Q,    KC_D,    KC_R,   KC_W,     KC_B,     KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN
#define _________________WORKMAN_2_________________       KC_A,    KC_S,    KC_H,   KC_T,     KC_G,     KC_Y,    KC_N,    KC_E,    KC_O,    LT_MC(KC_I)
#define _________________WORKMAN_3_________________       KC_Z,    KC_X,    KC_M,   KC_C,     KC_V,     KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLASH

#define _________________WORKMAN_L1________________       KC_Q,    KC_D,    KC_R,   KC_W,     KC_B
#define _________________WORKMAN_L2________________       KC_A,    KC_S,    KC_H,   KC_T,     KC_G
#define _________________WORKMAN_L3________________       KC_Z,    KC_X,    KC_M,   KC_C,     KC_V

#define _________________WORKMAN_R1________________       KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN
#define _________________WORKMAN_R2________________       KC_Y,    KC_N,    KC_E,    KC_O,    LT_MC(KC_I)
#define _________________WORKMAN_R3________________       KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLASH



#define ________________NUMBER_LEFT________________       KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ________________NUMBER_RIGHT_______________       KC_6,    KC_7,    KC_8,    KC_9,    KC_0
#define _________________FUNC_LEFT_________________       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define _________________FUNC_RIGHT________________       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10

#define ______________LONG_FUNC_LEFT_______________       KC_F1,  KC_F2,  KC_F3, KC_F4,  KC_F5,  KC_F6
#define ______________LONG_FUNC_RIGHT______________       KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12

#define _________________BLANK_5___________________        _______, _______, _______, _______, _______
#define _________________BLANK_6___________________        _______, _______, _______, _______, _______, _______

#define _________________LOWER_L1__________________        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC
#define _________________LOWER_L2__________________        _________________FUNC_LEFT_________________
#define _________________LOWER_L3__________________        _________________FUNC_RIGHT________________

#define _________________LOWER_R1__________________        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN
#define _________________LOWER_R2__________________        _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR
#define _________________LOWER_R3__________________        _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT

#define _______________LOWER_412_L1________________        _______, TD_XX,     TD_YY,   TD_SL, _______, _______
#define _______________LOWER_412_L2________________        _______, TD_ATH,  TD_PRAM, _______, _______, _______
#define _______________LOWER_412_L3________________        _______, _______, _______, _______, _______, _______
#define _______________LOWER_412_L4________________        _______, _______, _______, _______, _______, _______

#define _______________LOWER_412_R1________________        _______,    KC_7,    KC_8,    KC_9, _______, _______
#define _______________LOWER_412_R2________________        _______,    KC_4,    KC_5,    KC_6, _______, _______
#define _______________LOWER_412_R3________________           KC_0,    KC_1,   TD_20,    KC_3, _______,   TD_UR
#define _______________LOWER_412_R4________________        _______, _______, KC_BSPC, KC_SPC,  TD_DENT,   TD_DL



#define _________________RAISE_L1__________________        ________________NUMBER_LEFT________________
#define _________________RAISE_L2__________________        ___________________BLANK___________________
#define _________________RAISE_L3__________________        ___________________BLANK___________________

#define _________________RAISE_R1__________________        ________________NUMBER_RIGHT_______________
#define _________________RAISE_R2__________________        _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC
#define _________________RAISE_R3__________________        _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END

#define _______________RAISE_412_L1________________        QK_BOOT, DB_TOGG, _______, _______, _______, QK_MAKE
#define _______________RAISE_412_L2________________        _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, WM
#define _______________RAISE_412_L3________________        _______, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, QW

#define _______________RAISE_412_R1________________        _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10
#define _______________RAISE_412_R2________________        _______, _______, KC_F4,   KC_F5,   KC_F6,   KC_F11
#define _______________RAISE_412_R3________________        _______, TD_UMIN, KC_F1,   KC_F2,   KC_F3,   KC_F12



#define ______________EXTRAS_412_L1________________        _______, KC_EXLM, _______, _______, _______, _______
#define ______________EXTRAS_412_L2________________        KC_LSFT, _______, _______, _______, _______, _______
#define ______________EXTRAS_412_L3________________        _______, _______, _______, _______, _______, _______
#define ______________EXTRAS_412_L4________________        _______, _______, _______, _______, _______, TD_SE

#define ______________EXTRAS_412_R1________________        _______,    T_SL, KC_LBRC, KC_RBRC, KC_SCLN, _______
#define ______________EXTRAS_412_R2________________        _______, _______, KC_LPRN, KC_RPRN, KC_QUOT, _______
#define ______________EXTRAS_412_R3________________        _______, _______, KC_COMM, KC_DOT,  KC_QUES, _______
#define ______________EXTRAS_412_R4________________        TD_SE,   _______, _______, _______, _______, _______



#define _____________FUNCTION_412_L1_______________        CCCV,       CLIP,      SS, _______, _______, _______
#define _____________FUNCTION_412_L2_______________        KC_TAB,      M05,     M06,     M07,     M08, _______
#define _____________FUNCTION_412_L3_______________        _______,     M01,     M02,     M03,     M04, _______
#define _____________FUNCTION_412_L4_______________        _______, _______, _______, _______, _______, _______

#define _____________FUNCTION_412_R1_______________        _______,    T_SL,   KC_UP, _______, _______,  KC_DEL
#define _____________FUNCTION_412_R2_______________        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______,    T_UR
#define _____________FUNCTION_412_R3_______________        _______, _______,  T_QEXC, KC_COMM,  KC_DOT,    T_DL
#define _____________FUNCTION_412_R4_______________        _______, _______, _______, _______, _______, _______



#define _________________ADJUST_L1_________________        RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG
#define _________________ADJUST_L2_________________        MU_TOGG, CK_TOGG, AU_ON,   AU_OFF,  AG_NORM
#define _________________ADJUST_L3_________________        RGB_RMOD,RGB_HUD,RGB_SAD, RGB_VAD, KC_RGB_T

#define _________________ADJUST_R1_________________        KC_SEC1, KC_SEC2, KC_SEC3, KC_SEC4, KC_SEC5
#define _________________ADJUST_R2_________________        AG_SWAP, QWERTY,  COLEMAK, DVORAK,  WORKMAN
#define _________________ADJUST_R3_________________        MG_NKRO, KC_MUTE, KC_VOLD, KC_VOLU, KC_MNXT



#define _____________WORKMAN_310_001_L_____________        TD_QESC,  KC_D,    KC_R,    KC_W,     BSYM
#define _____________WORKMAN_310_001_R_____________        JSYM,     KC_F,    KC_U,    KC_P,     KC_BSPC
#define _____________WORKMAN_310_002_L_____________        ASFT,     KC_S,    KC_H,    TEX,      KC_G
#define _____________WORKMAN_310_002_R_____________        KC_Y,     KC_N,    KC_E,    KC_O,     TD_IENT
#define _____________WORKMAN_310_003_L_____________        FNZ,      CTRLX,   MGUI,    CALT,     VLOWER
#define _____________WORKMAN_310_003_R_____________        KRAISE,   L_ALT,   TD_CSPC, TD_DSPC,  KC_SLSH
#define _____________WORKMAN_310_004_L_____________        FN,       KC_LCTL, KC_LGUI, KC_LALT,  LOWER
#define _____________WORKMAN_310_004_R_____________        RAISE,    SS,      CLIP,    CCCV,     FN

#define _____________WORKMAN_410_003_L_____________        FNZ,      KC_X,    KC_M,    KC_C,    KC_V
#define _____________WORKMAN_410_003_R_____________        KC_K,     KC_L,    TD_CSPC,  TD_DSPC,  SLSHFT

#define _____________WORKMAN_311_001_L_____________        TD_QESC,   KC_D,    KC_R,    KC_W,    BSYM
#define _____________WORKMAN_311_001_R_____________        JSYM,      KC_F,    KC_U,    KC_P,    KC_BSPC
#define _____________WORKMAN_311_002_L_____________        ASFT,      KC_S,    KC_H,    TEX,     GGUI
#define _____________WORKMAN_311_002_R_____________        KC_Y,      KC_N,    KC_E,    KC_O,    TD_IENT
#define _____________WORKMAN_311_003_L_____________        FNZ,       CTRLX,   MGUI,    CALT,    VLOWER,   KC_ENT
#define _____________WORKMAN_311_003_R_____________        KRAISE,    L_ALT,   TD_CSPC, TD_DSPC, KC_SLSH

#define _____________WORKMAN_412_001_L_____________        TD_TE,    TD_QESC, KC_D,    KC_R,    KC_W,     BSYM
#define _____________WORKMAN_412_001_R_____________        JSYM,     KC_F,    KC_U,    KC_P,    KC_BSPC,  KC_BSPC
#define _____________WORKMAN_412_002_L_____________        TBSHFT,   KC_A,    KC_S,    KC_H,    TEX,      KC_G
#define _____________WORKMAN_412_002_R_____________        KC_Y,     KC_N,    KC_E,    KC_O,    TD_IENT,  KC_ENT
#define _____________WORKMAN_412_003_L_____________        KC_LSFT,  KC_Z,    KC_X,    KC_M,    KC_C,     KC_V
#define _____________WORKMAN_412_003_R_____________        KC_K,     KC_L,    TD_CSPC, TD_DSPC, KC_SLSH,  TD_UR
#define _____________WORKMAN_412_004_L_____________        FN,       KC_LCTL, KC_LGUI, KC_LALT, LOWER,    TD_SE
#define _____________WORKMAN_412_004_R_____________        TD_SE,     RAISE,   SS,      CLIP,   CCCV,     TD_DL 



// clang-format on