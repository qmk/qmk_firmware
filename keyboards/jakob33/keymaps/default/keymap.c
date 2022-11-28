// Copyright 2022 Lalit Mistry (@schwarzer-geiger)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_jakob33(
        KC_ESC,                 KC_NO,
        KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,
        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,
        KC_CAPS,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,
        KC_LSFT,    KC_Y,       KC_X,       KC_C,       KC_V,       KC_B,       KC_Z,
        KC_B,      KC_LCTL,    KC_LALT,    KC_LGUI,    KC_SPC
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
        }
    return false;
}



