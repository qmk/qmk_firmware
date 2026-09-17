// Copyright 2026 Keebart
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x5_3(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
                          KC_LGUI, MO(_LOWER), KC_SPC,   KC_ENT, MO(_RAISE), KC_RALT
    ),

    [_LOWER] = LAYOUT_split_3x5_3(
        QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,      KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,
        KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,       KC_5,    KC_6,    KC_7,    KC_8,    KC_9,
        KC_LSFT, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,     KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_0,
                          _______, _______, _______,    _______, _______, _______
    ),

    [_RAISE] = LAYOUT_split_3x5_3(
        KC_ESC,  KC_INS,  KC_PSCR, KC_APP,  KC_CAPS,    KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_BSPC,
        KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,    KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL,
        _______, KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE,    XXXXXXX, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,
                          _______, _______, _______,    _______, _______, _______
    ),
};
