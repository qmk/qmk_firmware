// Copyright 2025 Hawtkeys
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "hal.h" 

#define LAYER_ROTATE_PIN 4

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_A, KC_B, KC_C, RGB_MOD,    
        KC_E, KC_F, KC_G,          
        KC_H, KC_I, KC_J           
    ),
    [1] = LAYOUT(
        KC_1, KC_2, KC_3, RGB_MOD,
        KC_5, KC_6, KC_7,
        KC_8, KC_9, KC_0
    ),
    [2] = LAYOUT(
        KC_Q, KC_W, KC_E, RGB_MOD,
        KC_T, KC_Y, KC_U,
        KC_I, KC_O, KC_P
    ),
    [3] = LAYOUT(
        KC_Z, KC_X, KC_C, RGB_MOD,
        KC_B, KC_N, KC_M,
        KC_COMM, KC_DOT, KC_SLSH
    ),
    [4] = LAYOUT(
        KC_U, KC_V, KC_W, RGB_MOD,
        KC_X, KC_Y, KC_Z,
        KC_L, KC_M, KC_N
    ),
    [5] = LAYOUT(
        KC_D, KC_S, KC_T, RGB_MOD,
        KC_R, KC_A, KC_E,
        KC_G, KC_H, KC_K
    )

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] =   { ENCODER_CCW_CW(_______, _______) },
    [2] =   { ENCODER_CCW_CW(_______, _______) },
    [3] =   { ENCODER_CCW_CW(_______, _______) },
    [4] =   { ENCODER_CCW_CW(_______, _______) },
    [5] =   { ENCODER_CCW_CW(_______, _______) }
};
#endif

void keyboard_post_init_user(void) {
    palSetPadMode(IOPORT1, LAYER_ROTATE_PIN, PAL_MODE_INPUT);
    init_seven_segment();
    display_seven_segment_digit(0);
}
void matrix_scan_user(void) {
    static bool last_pressed = false;
    bool pressed = !palReadPad(IOPORT1, LAYER_ROTATE_PIN); 

    if (pressed && !last_pressed) {
        uint8_t layer = get_highest_layer(layer_state);
        uint8_t next_layer = layer >= 5 ? 0 : layer + 1;
        layer_move(next_layer);
        display_seven_segment_digit(next_layer);
    }
    last_pressed = pressed;
}
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);
    display_seven_segment_digit(layer);
    return state;
}