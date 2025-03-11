// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
                 KC_Q   , KC_W   , KC_E   ,
        MY_JSKE, KC_A   , KC_S   , KC_D   ,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   ,
                 KC_LCTL, KC_UP  , KC_LALT, KC_ESC , KC_ENT   ,
                 KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC
    ),

    [1] = LAYOUT(
                 KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                 KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                 KC_NO  , KC_NO  , KC_NO  , KC_NO  
    ),

    [2] = LAYOUT(
                 KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                 KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                 KC_NO  , KC_NO  , KC_NO  , KC_NO  
    ),

    [3] = LAYOUT(
                 KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                 KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                 KC_NO  , KC_NO  , KC_NO  , KC_NO  
    ),

    [4] = LAYOUT(
                 KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                 KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                 KC_NO  , KC_NO  , KC_NO  , KC_NO  
    ),

    [5] = LAYOUT(
                 KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                 KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                 KC_NO  , KC_NO  , KC_NO  , KC_NO  
    ),

    [6] = LAYOUT(
                 KC_NO  , KC_NO  , KC_NO  ,
        KC_TRNS, MY_BTN2, MY_SCRL, MY_BTN1,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                 KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                 KC_NO  , KC_NO  , KC_NO  , KC_NO  
    ),

    [7] = LAYOUT(
                 KC_NO  , KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , MY_CLKD, MY_CLKI,
        QK_BOOT, KC_NO  , MY_SCDV, MY_SCDH, KC_NO  ,
                 MY_JSKD, MY_JSDD, MY_JSDI, KC_NO  , KC_NO  ,
                 KC_NO  , MY_STGE, KC_NO  , KC_NO  
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(MS_WHLD, MS_WHLU) },
    [1] =   { ENCODER_CCW_CW(MS_WHLL, MS_WHLR) },
    [2] =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [4] =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [5] =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [6] =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [7] =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};
#endif
