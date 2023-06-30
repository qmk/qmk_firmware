// Copyright 2022 Aaron Hong (@hongaaronc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
                                       KC_J,    KC_U,    KC_K,    KC_I,    KC_L,    KC_O, KC_SCLN,
        _______, KC_MUTE, _______,
                                       KC_J,    KC_U,    KC_K,    KC_I,    KC_L,    KC_O, KC_SCLN
    )
};
