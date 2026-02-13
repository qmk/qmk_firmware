// Copyright 2025 sector245 (@sector245)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_A,    KC_B,    KC_C,  // GP2, GP3, GP12 (botón encoder)
        KC_D,    KC_E,    KC_F,      // GP4, GP5, GP6
        KC_G,    KC_H,    KC_I       // GP7, GP8, GP9
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) } 
    
};
#endif
