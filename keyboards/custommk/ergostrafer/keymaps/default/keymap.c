// Copyright 2023 customMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_F9,   KC_7,    KC_8, KC_9,   KC_0,   KC_MINUS, KC_T,
        KC_PSCR, KC_1,    KC_2, KC_3,   KC_5,   KC_6,     KC_G,
        KC_F5,   KC_TAB,  KC_Q, KC_4,   KC_E,   KC_R,     KC_B,
        KC_CAPS, KC_LALT, KC_A, KC_W,   KC_D,   KC_F,     KC_P,
        KC_LSFT, KC_Z,    KC_S, KC_V,   KC_SPC,
        KC_LCTL, KC_X,    KC_C, KC_LCTL
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};
#endif