// Copyright 2024 Leon Sieber (@lesieber)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_keycodes {
    LAYER_CYCLE = QK_USER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // Layer 0: Base - Letters
    [0] = LAYOUT_ortho_3x3(
        KC_A,    KC_B,    KC_C,
        KC_D,    KC_E,    KC_F,
        KC_G,    KC_H,    LAYER_CYCLE
    ),

    // Layer 1: Numbers
    [1] = LAYOUT_ortho_3x3(
        KC_1,    KC_2,    KC_3,
        KC_4,    KC_5,    KC_6,
        KC_7,    KC_8,    LAYER_CYCLE
    ),

    // Layer 2: Function Keys
    [2] = LAYOUT_ortho_3x3(
        KC_F1,   KC_F2,   KC_F3,
        KC_F4,   KC_F5,   KC_F6,
        KC_F7,   KC_F8,   LAYER_CYCLE
    ),

    // Layer 3: Media
    [3] = LAYOUT_ortho_3x3(
        KC_MPLY, KC_MPRV, KC_MNXT,
        KC_VOLU, KC_VOLD, KC_MUTE,
        QK_BOOT, KC_NO,   LAYER_CYCLE
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == LAYER_CYCLE && record->event.pressed) {
        uint8_t current = get_highest_layer(layer_state);
        uint8_t next = (current + 1) % 4;
        layer_move(next);
        return false;
    }
    return true;
}
