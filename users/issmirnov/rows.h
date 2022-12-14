#pragma once

#include QMK_KEYBOARD_H

// This wrapper is required in order to expand the row macro inside the keymap configs.
#define LAYOUT_ergodox_wrapper(...)          LAYOUT_ergodox(__VA_ARGS__)
#define LAYOUT_ortho_4x12_wrapper(...)          LAYOUT_ortho_4x12(__VA_ARGS__)

// Share common config. We'll skip the mod rows and func rows.
// Note, it's also really neat the way the scoping works. Since we perform the expansion in the keymap.c file
// so we can use our enums for custom keycodes
#define _________________QWERTY_L1_________________        KC_Q , KC_W , KC_E   , KC_R     , KC_T
#define _________________QWERTY_L2_________________        KC_A , KC_S , KC_D   , KC_F     , KC_G
#define _________________QWERTY_L3_________________        KC_Z , KC_X , KC_C   , KC_V     , KC_B

#define _________________QWERTY_R1_________________        KC_Y , KC_U , KC_I   , KC_O     , KC_P
#define _________________QWERTY_R2_________________        KC_H , KC_J , KC_K   , KC_L     , TAP_TOG_LAYER
#define _________________QWERTY_R3_________________        KC_N , KC_M , KC_DOT , KC_COMMA , TG(_NUMP)

#define ___________________BLANK___________________        _______ , _______ , _______ , _______ , _______
#define ___________________XXXXX___________________        XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX

#define _________________SYMB_L1___________________        KC_MINS , KC_AT   , KC_LCBR     , KC_RCBR     , KC_GRV
#define _________________SYMB_L2___________________        KC_CIRC , KC_UNDS , KC_LPRN     , KC_RPRN     , KC_DLR
#define _________________SYMB_L3___________________        KC_LABK , KC_RABK , KC_LBRC     , KC_RBRC     , KC_TILD

#define _________________SYMB_R1___________________        KC_ASTR , KC_EXLM , KC_PIPE     , KC_PERC     , KC_PLUS
#define _________________SYMB_R2___________________        KC_HASH , KC_EQL  , KC_COLN     , KC_SCLN     , TAP_TOG_LAYER
#define _________________SYMB_R3___________________        KC_AMPR , KC_QUES , KC_SLASH    , KC_BSLS     , TG(_NUMP)


#define _________________NUMP_L1___________________        KC_NO   , KC_NO         , LGUI(KC_UP)   , XXXXXXX             , XXXXXXX
#define _________________NUMP_L2___________________        XXXXXXX , LGUI(KC_LEFT) , LGUI(KC_DOWN) , LGUI(KC_RIGHT)      , XXXXXXX
#define _________________NUMP_L3___________________        XXXXXXX , XXXXXXX       , XXXXXXX       , KC_AUDIO_VOL_DOWN   , KC_AUDIO_VOL_UP

#define _________________NUMP_R1___________________        KC_COMM , KC_7          , KC_8          , KC_9                , XXXXXXX
#define _________________NUMP_R2___________________        KC_0    , KC_4          , KC_5          , KC_6                , TO(_SYMB)
#define _________________NUMP_R3___________________        KC_DOT  , KC_1          , KC_2          , KC_3                , TO(_QWERTY)

// Note: These are 6x1 blocks, since modifiers are also adjusted.
#define ______________OVERWATCH_L1_________________       KC_TAB    , KC_Q  , KC_W       , KC_E , KC_R , KC_T
#define ______________OVERWATCH_L2_________________       KC_LCTL   , KC_A  , KC_S       , KC_D , KC_F , KC_P
#define ______________OVERWATCH_L3_________________       KC_LSFT   , KC_Z  , KC_X       , KC_C , KC_V , KC_GRAVE
// Ergodox only has 5 keys on bottom row:
#define ______________OVERWATCH_L4_________________       KC_LCTL   , KC_F9 , KC_PSCR , KC_H , KC_R



#define _________________NAVI_L1___________________        XXXXXXX , XXXXXXX , KC_UP   , XXXXXXX , XXXXXXX
#define _________________NAVI_L2___________________        XXXXXXX , KC_LEFT , KC_DOWN , KC_RGHT , XXXXXXX
#define _________________NAVI_L3___________________        XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX

#define _________________NAVI_R1___________________        XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
#define _________________NAVI_R2___________________        XXXXXXX , KC_LCTL , XXXXXXX , XXXXXXX , XXXXXXX
#define _________________NAVI_R3___________________        XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
