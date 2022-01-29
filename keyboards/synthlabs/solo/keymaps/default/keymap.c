// Copyright 2022 Aaron Hong (@hongaaronc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
                                       KC_J,    KC_U,    KC_K,    KC_I,    KC_L,    KC_O, KC_SCLN,
        KC_VOLD, KC_MUTE, KC_VOLU,
                                       KC_J,    KC_U,    KC_K,    KC_I,    KC_L,    KC_O, KC_SCLN
    ),
    [1] = LAYOUT_all(
                                    _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,
                                    _______, _______, _______, _______, _______, _______, _______
    ),
    [2] = LAYOUT_all(
                                    _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,
                                    _______, _______, _______, _______, _______, _______, _______
    ),
    [3] = LAYOUT_all(
                                    _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,
                                    _______, _______, _______, _______, _______, _______, _______
    )
};

const keypos_t keypos_cw  = { .row=1, .col=2 };
const keypos_t keypos_ccw = { .row=1, .col=0 };

uint16_t get_keycode_at_pos(keypos_t keypos) {
    return keymap_key_to_keycode(layer_switch_get_layer(keypos), keypos);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    tap_code(get_keycode_at_pos(clockwise ? keypos_cw : keypos_ccw));
    return true;
}
