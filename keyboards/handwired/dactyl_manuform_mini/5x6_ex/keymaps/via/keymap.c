// Copyright 2023 Duncan Sutherland (@dunk2k)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

enum layer_names {
    _BASE,
    _RAISE,
    _LOWER,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_GRV,  KC_1,   KC_2,    KC_3,     KC_4,    KC_5,                           KC_6,  KC_7,   KC_8,    KC_9,   KC_0,    KC_PSCR,
        KC_ESC,  KC_Q,   KC_W,    KC_E,     KC_R,    KC_T,                           KC_Y,  KC_U,   KC_I,    KC_O,   KC_P,    KC_BSLS,
        KC_TAB,  KC_A,   KC_S,    KC_D,     KC_F,    KC_G,                           KC_H,  KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,   KC_X,    KC_C,     KC_V,    KC_B,                           KC_N,  KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LALT, KC_LBRC, KC_RBRC,                                                         KC_MINS, KC_EQL, KC_RALT,  KC_RCTL,
                                            LOWER,  KC_SPC,  KC_BSPC,      KC_DEL,  KC_ENT, RAISE,
                                                    KC_LGUI, KC_HOME,      KC_END, KC_RGUI
    ),

    [_LOWER] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, QK_BOOT,
        _______, _______, _______, _______, _______, KC_LBRC,                       KC_RBRC, KC_P7,   KC_P8,   KC_P9,   _______, KC_PLUS,
        _______, _______, _______, _______, _______, KC_LPRN,                       KC_RPRN, KC_P4,   KC_P5,   KC_P6,   KC_MINS, KC_PIPE,
        _______, _______, _______, _______, _______, _______,                       _______, KC_P1,   KC_P2,   KC_P3,   KC_EQL, KC_UNDS,
        _______, _______, _______, _______,                                                           KC_P0,   KC_PDOT, _______, _______,
                                            _______, _______, _______,     _______, _______, _______,
                                                     _______, _______,     _______, _______
    ),

    [_RAISE] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, KC_PGUP, KC_VOLU,                       _______, _______,  KC_NUM, KC_INS,  KC_SCRL, _______,
        _______, KC_LEFT, KC_UP  , KC_DOWN, KC_RGHT, KC_MUTE,                       _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP, _______,
        _______, _______, _______, _______, KC_PGDN, KC_VOLD,                       _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,                                                           _______, _______, _______, _______,
                                            _______, _______, _______,     _______, _______, _______,
                                                     _______, _______,     _______, _______
    )
};
