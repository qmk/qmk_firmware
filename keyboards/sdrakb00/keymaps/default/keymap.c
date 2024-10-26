// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_ortho_4x3(
        KC_KP_7,    KC_KP_8,    KC_KP_9,    KC_MUTE,
        KC_KP_4,    KC_KP_5,    KC_KP_6,    MO(1),
        KC_KP_1,    KC_KP_2,    KC_KP_3,    KC_KP_0
    ),

    [1] = LAYOUT_ortho_4x3(
        KC_NO,    KC_KP_SLASH,    KC_KP_MINUS, KC_NO,
        KC_NO,    KC_KP_ASTERISK, KC_KP_PLUS,  KC_NO,
        KC_NO,    KC_NO,          KC_NO,       KC_KP_DOT
    )
};


bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
    return true;
}


layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case 0:
        rgb_matrix_sethsv(85, 255, 251); // #88FB7A for layer 0
        break;
    case 1:
        rgb_matrix_sethsv(0, 255, 255); // Red for layer 1
        break;
    }
    return state;
}


void keyboard_post_init_user(void) {
  rgb_matrix_enable();
  layer_state_set_user(layer_state);  // This will set the initial color based on the default layer
}
