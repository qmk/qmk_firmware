// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _NAV,
    _SYM
};

// The Sweep Cat drops the four corners of the top row, so Q, T, Y and P live on
// the navigation layer rather than on the base layer.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
                          KC_W,    KC_E,    KC_R,                       KC_U,    KC_I,    KC_O,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                     LT(_NAV, KC_TAB), LSFT_T(KC_SPC),     RSFT_T(KC_BSPC), LT(_SYM, KC_ENT)
    ),

    [_NAV] = LAYOUT(
                          KC_Q,    XXXXXXX, KC_T,                       KC_Y,    XXXXXXX, KC_P,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_ESC,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_INS,
                                _______, _______,     _______, _______
    ),

    [_SYM] = LAYOUT(
                          KC_EXLM, KC_AT,   KC_HASH,                    KC_ASTR, KC_LPRN, KC_RPRN,
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_GRV,  KC_BSLS, KC_MINS, KC_EQL,  KC_DLR,   KC_PERC, KC_LBRC, KC_RBRC, KC_QUOT, KC_TILD,
                                _______, _______,     _______, _______
    )
};
