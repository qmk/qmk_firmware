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
        MO(1),   KC_MUTE,   // Encoder presses
        KC_DOWN, KC_UP,     // Left encoder turns
        KC_VOLD, KC_VOLU     // Right encoder turns
    ),
    [_FN1] = LAYOUT(
        KC_B,               // Big Switch
        _______, KC_C,      // Encoder presses
        KC_PGDN, KC_PGUP,   // Left encoder turns
        KC_VOLU, KC_VOLD    // Right encoder turns
    ),
    [_FN2] = LAYOUT(
        _______,            // Big Switch
        _______, _______,   // Encoder presses
        _______, _______,   // Left encoder turns
        _______, _______    // Right encoder turns
    ),
    [_FN3] = LAYOUT(
        _______,            // Big Switch
        _______, _______,   // Encoder presses
        _______, _______,   // Left encoder turns
        _______, _______    // Right encoder turns
    )
};
