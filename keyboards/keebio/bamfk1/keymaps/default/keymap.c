// Copyright 2021 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _MAIN,
    _FN1,
    _FN2,
    _FN3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAIN] = LAYOUT(
        KC_A,               // Big Switch
        FN_MO13, KC_MUTE,   // Encoder presses
        KC_UP, KC_DOWN,     // Left encoder turns
        KC_VOLU, KC_VOLD    // Right encoder turns
    ),
    [_FN1] = LAYOUT(
        KC_B,               // Big Switch
        _______, KC_C,   // Encoder presses
        KC_UP, KC_DOWN,     // Left encoder turns
        KC_VOLU, KC_VOLD    // Right encoder turns
    ),
    [_FN2] = LAYOUT(
        KC_B,               // Big Switch
        _______, KC_C,   // Encoder presses
        KC_UP, KC_DOWN,     // Left encoder turns
        KC_VOLU, KC_VOLD    // Right encoder turns
    ),
    [_FN3] = LAYOUT(
        KC_B,               // Big Switch
        _______, KC_C,   // Encoder presses
        KC_UP, KC_DOWN,     // Left encoder turns
        KC_VOLU, KC_VOLD    // Right encoder turns
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t layer = get_highest_layer(layer_state);
    if (clockwise) {
        tap_code16(dynamic_keymap_get_keycode(layer, 1, 2 * index + 1));
    } else {
        tap_code16(dynamic_keymap_get_keycode(layer, 1, 2 * index));
    }
    return true;
}
