// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = 
{
    [0] = LAYOUT(
        KC_A,   KC_B,   KC_C,   KC_D,
        KC_E,   KC_F,   KC_G,   KC_H,
        KC_I,   KC_J,   KC_K,

        KC_VOLU,   KC_VOLD,   KC_MPRV,   KC_MNXT,
        KC_MPLY,   KC_UP
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = 
{
    [0] =   
    { 
        ENCODER_CCW_CW(XXXXXXX, XXXXXXX), 
        ENCODER_CCW_CW(XXXXXXX, XXXXXXX)  
    }
};
#endif