// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_anchovie(
        KC_NUM,  KC_PSLS, KC_PAST, KC_BSPC, KC_ESC,  KC_1,    KC_2,  KC_3,   KC_4,  KC_5,  KC_6,    KC_7,  KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_GRV,  
        KC_PMNS, KC_P7,   KC_P8,   KC_P9,   KC_TAB,  KC_Q,    KC_W,  KC_E,   KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,  
        KC_PPLS, KC_P4,   KC_P5,   KC_P6,   KC_LCTL, KC_A,    KC_S,  KC_D,   KC_F,  KC_G,  KC_H,    KC_J,  KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_ENT,  
                 KC_P1,   KC_P2,   KC_P3,   KC_LSFT, KC_Z,    KC_X,  KC_C,   KC_V,  KC_B,  KC_N,    KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_RSFT
        KC_PENT, KC_PDOT, KC_P0,            KC_LGUI, KC_LALT, MO(1), KC_SPC,               KC_BSPC,        MO(2),   MO(3),  KC_LEFT, KC_DOWN, KC_UP, KC_RGHT
    )
};
