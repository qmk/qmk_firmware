// Copyright 2021 Allen Choi (@thunderbird2086)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "keycodes.h"
#include "tap_dances.h"

// Layout blocks
#define ___________________COLEMAK_DH_L1_______________ KC_Q    , KC_W    , KC_F    , KC_P    , KC_B
#define ___________________COLEMAK_DH_L2_______________ CTL_A   , KC_R    , KC_S    , M_LOPT_T, KC_G
#define ___________________COLEMAK_DH_L3_______________ SFT_Z   , KC_X    , KC_C    , KC_D    , KC_V
                                      
#define ___________________COLEMAK_DH_R1_______________ KC_J    , KC_L    , KC_U    , KC_Y    , KC_SCLN 
#define ___________________COLEMAK_DH_R2_______________ KC_M    , RCMD_N  , KC_E    , KC_I    , CTL_O   
#define ___________________COLEMAK_DH_R3_______________ KC_K    , KC_H    , KC_COMM , KC_DOT  , SFT_SLSH

#define ___________________QWERTY_L1___________________ KC_Q    , KC_W    , KC_E    , KC_R    , KC_T
#define ___________________QWERTY_L2___________________ CTL_A   , KC_S    , KC_D    , M_LOPT_F, KC_G
#define ___________________QWERTY_L3___________________ SFT_Z   , KC_X    , KC_C    , KC_V    , KC_B

#define ___________________QWERTY_R1___________________ KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    
#define ___________________QWERTY_R2___________________ KC_H    , RCMD_J  , KC_K    , KC_L    , CTL_SCLN
#define ___________________QWERTY_R3___________________ KC_N    , KC_M    , KC_COMM , KC_DOT  , SFT_SLSH

#define ___________________COLEMAK_L1__________________ KC_Q    , KC_W    , KC_F    , KC_P    , KC_G
#define ___________________COLEMAK_L2__________________ CTL_A   , KC_R    , KC_S    , M_LOPT_T, KC_D
#define ___________________COLEMAK_L3__________________ SFT_Z   , KC_X    , KC_C    , KC_V    , KC_B

#define ___________________COLEMAK_R1__________________ KC_J    , KC_L    , KC_U    , KC_Y    , KC_SCLN 
#define ___________________COLEMAK_R2__________________ KC_H    , RCMD_N  , KC_E    , KC_I    , CTL_O   
#define ___________________COLEMAK_R3__________________ KC_K    , KC_M    , KC_COMM , KC_DOT  , SFT_SLSH

#define ___________________NUM_LEFT____________________ KC_1    , KC_2    , KC_3    , KC_4    , KC_5
#define ___________________NUM_RIGHT___________________ KC_6    , KC_7    , KC_8    , KC_9    , KC_0

#define ___________________FUNC_LEFT___________________ KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5
#define ___________________FUNC_RIGHT__________________ KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10

#define ________________________SYMBOL_L1________________________ KC_TILD , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC
#define ________________________SYMBOL_L2________________________ XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX

#define ________________________SYMBOL_R1________________________ KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_PIPE
#define ________________________SYMBOL_R2________________________ XXXXXXX , KC_LCBR , KC_RCBR , KC_LBRC , KC_RBRC , KC_PLUS


#define ________________________ADJUST_L1________________________ QK_BOOT , XXXXXXX , KC_PWR  , KC_WAKE , KC_SLEP , XXXXXXX

#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
#   define ________________________ADJUST_L2________________________ RGBRST  , XXXXXXX , RGB_SPI , RGB_SAI , RGB_HUI , RGB_VAI
#   define ________________________ADJUST_L3________________________ EE_CLR  , XXXXXXX , RGB_SPD , RGB_SAD , RGB_HUD , RGB_VAD
#else                                                                                                                
#   define ________________________ADJUST_L2________________________ XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
#   define ________________________ADJUST_L3________________________ EE_CLR  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
#endif

#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
#   define ________________________ADJUST_R1________________________ RGB_TOG , XXXXXXX , XXXXXXX , XXXXXXX , COLEMAK , QWERTY
#   define ________________________ADJUST_R3________________________ RGB_MOD , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
#else
#   define ________________________ADJUST_R1________________________ XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , COLEMAK , QWERTY
#   define ________________________ADJUST_R3________________________ XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
#endif
#define ________________________ADJUST_R2________________________ XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX

#define ________________________SECRET_L1________________________ M_XXX1  , XXXXXXX , M_XXX3  , XXXXXXX , M_XXX5  , XXXXXXX 
#define ________________________SECRET_L2________________________ XXXXXXX , M_XXX2  , XXXXXXX , M_XXX4  , XXXXXXX , XXXXXXX 
#define ________________________SECRET_L3________________________ XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX 
                                                                                                                  
#define ________________________SECRET_R1________________________ XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
#define ________________________SECRET_R2________________________ XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
#define ________________________SECRET_R3________________________ XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX

#define _______________NAV_1_________________ KC_LEFT , KC_UP   , KC_RGHT , KC_PGUP
#define _______________NAV_2_________________ KC_HOME , KC_DOWN , KC_END  , KC_PGDN

#define _______________MOUSE_1_______________ KC_BTN1 , KC_MS_U , KC_BTN2 , KC_WH_D
#define _______________MOUSE_2_______________ KC_MS_L , KC_MS_D , KC_MS_R , KC_WH_U

#define ____________________MEDIA_1____________________ KC_BRMU , KC_MFFD , KC_MPLY , KC_VOLU , K_BACK 
#define ____________________MEDIA_2____________________ KC_BRMD , KC_MRWD , KC_MUTE , KC_VOLD , K_FWRD  

#define _________MOD_LEFT__________ T_GUI   , FCT_DEL , RAI_SPC
#define _________MOD_RIGHT_________ RAI_ENT , FCT_BSP , KC_ROPT
#define _______MOD_TRNS_LEFT_______ KC_TRNS , T_ESC   , XXXXXXX
#define _______MOD_TRNS_RIGHT______ XXXXXXX , T_ESC   , KC_TRNS

// Layout wrappers
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)
