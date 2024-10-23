// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MS_WH_DOWN,KC_MS_WH_UP)  }
    //                  Encoder 1                                     Encoder 2
};
#endif

/* void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
//   debug_keyboard=true;
//   debug_mouse=true;

} */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_P7,   KC_P8,   KC_P9,    
        KC_P4,   KC_P5,   KC_P6,     
        KC_P1,   KC_P2,   KC_P3,  
        KC_A,    KC_NO,   KC_NO, // encoder button1
        KC_D,    KC_NO,   KC_NO  // encoder button2
    )
};
