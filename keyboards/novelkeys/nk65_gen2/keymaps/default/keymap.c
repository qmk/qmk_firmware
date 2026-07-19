// Copyright 2026 Yiancar
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_65_ansi_blocker_tsangan( /* Base */
    QK_GESC, KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
    KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
    KC_CAPS, KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGDN,
    KC_LSFT, KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_END,
    KC_LCTL, KC_LGUI, KC_LALT,                KC_SPC,                                   MO(1),            KC_LEFT, KC_DOWN, KC_RGHT),

[1] = LAYOUT_65_ansi_blocker_tsangan( /* FN */
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
    KC_TRNS, RM_TOGG, RM_NEXT, RM_HUED, RM_HUEU, RM_SATD, RM_SATU, RM_VALD, RM_VALU, RM_SPDD, RM_SPDU, KC_TRNS,          KC_TRNS, KC_TRNS,
    KC_VOLU, KC_VOLD, KC_MUTE,                KC_TRNS,                                        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS),
};

bool rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(66, 5, 2, 1);
    } else {
        rgb_matrix_set_color(66, 0, 0, 0);
    }

    if (get_highest_layer(layer_state|default_layer_state) == 1) {
        rgb_matrix_set_color(67, 3, 1, 5);
    } else {
        rgb_matrix_set_color(67, 0, 0, 0);
    }

    return false;
}
