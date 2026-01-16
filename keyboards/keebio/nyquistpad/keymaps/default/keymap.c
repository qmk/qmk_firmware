// Copyright 2023 Danny Nguyen (danny@keeb.io)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_ortho_5x6(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
        MO(2),   KC_LCTL, KC_LGUI, KC_LALT, MO(1),   KC_SPC
    ),
    [1] = LAYOUT_ortho_5x6(
        RM_NEXT, _______, _______, _______, _______, _______,
        _______, _______, KC_UP,   _______, KC_VOLU, KC_PGUP,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, KC_PGDN,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______
    ),
    [2] = LAYOUT_ortho_5x6(
        KC_F6,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
        KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______
    )

};
