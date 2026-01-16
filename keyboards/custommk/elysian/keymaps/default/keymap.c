// Copyright 2024 customMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC, KC_ENT,
        KC_Y,   KC_U,   KC_I,     KC_O,   KC_P,
        KC_H,   KC_J,   KC_K,     KC_L,   KC_SCLN,  
        KC_N,   KC_M,   KC_COMMA, KC_DOT, KC_SLASH
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLD, MS_WHLU) }
};
#endif