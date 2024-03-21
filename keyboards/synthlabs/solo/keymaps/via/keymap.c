// Copyright 2022 Aaron Hong (@hongaaronc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
                                       KC_J,    KC_U,    KC_K,    KC_I,    KC_L,    KC_O, KC_SCLN,
        KC_MUTE,
                                       KC_J,    KC_U,    KC_K,    KC_I,    KC_L,    KC_O, KC_SCLN
    ),
    [1] = LAYOUT_all(
                                    _______, _______, _______, _______, _______, _______, _______,
        _______,
                                    _______, _______, _______, _______, _______, _______, _______
    ),
    [2] = LAYOUT_all(
                                    _______, _______, _______, _______, _______, _______, _______,
        _______,
                                    _______, _______, _______, _______, _______, _______, _______
    ),
    [3] = LAYOUT_all(
                                    _______, _______, _______, _______, _______, _______, _______,
        _______,
                                    _______, _______, _______, _______, _______, _______, _______
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(_______, _______) },
    [2] = { ENCODER_CCW_CW(_______, _______) },
    [3] = { ENCODER_CCW_CW(_______, _______) },
};
#endif
