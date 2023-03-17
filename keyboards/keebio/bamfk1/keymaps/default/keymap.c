// Copyright 2021 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _MAIN,
    _FN1
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAIN] = LAYOUT(
        KC_A,               // Big Switch
        MO(1),   KC_MUTE    // Encoder presses
    ),
    [_FN1] = LAYOUT(
        KC_B,               // Big Switch
        _______, KC_C       // Encoder presses
    )
};


#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_MAIN] = { ENCODER_CCW_CW(KC_DOWN, KC_UP), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN1]  = { ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_VOLU, KC_VOLD) }
};
#endif
