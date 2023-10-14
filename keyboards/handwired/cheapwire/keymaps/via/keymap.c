// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                              KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        LSFT_T(KC_CAPS), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        LCTL_T(KC_NUBS), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_NUHS,
                                            KC_LGUI, KC_LALT, KC_SPC,           LT(1, KC_TAB),  LT(2, KC_ENT),  KC_ESC 
    ),
    [1] = LAYOUT_split_3x6_3(
        KC_TRNS,  KC_TRNS,    KC_PMNS,    KC_PPLS,    KC_PGUP,    KC_PGDN,                               KC_TRNS,    KC_TRNS,      KC_TRNS,     KC_MRWD,    KC_MFFD,    KC_DEL,
        KC_TRNS,  KC_PLUS,    KC_ASTR,    KC_LPRN,    KC_UNDS,    KC_PIPE,                                KC_ESC,     KC_LEFT,      KC_UP,       KC_DOWN,    KC_RGHT,    KC_MPRV,
        KC_TRNS,  KC_LBRC,    KC_RBRC,    KC_INS,    KC_LSFT,    KC_RPRN,                                 KC_HOME,    KC_END,       KC_VOLD,     KC_MUTE,    KC_VOLU,    KC_MNXT,
                                                   KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS,  KC_TRNS,  KC_TRNS
    ),
    [2] = LAYOUT_split_3x6_3(
        QK_BOOT, KC_EXLM,    KC_AT,    KC_HASH,    KC_DLR,    KC_PERC,                               KC_1,    KC_2,    KC_3,    KC_PPLS,    KC_CAPS,    KC_BSPC,
        EE_CLR, KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,    LCA(KC_DEL),                               KC_4,    KC_5,    KC_6,    KC_PMNS,    LCA(KC_LBRC), KC_TRNS,
        KC_BSLS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    MO(3),                               KC_7,    KC_8,    KC_9, KC_0,  KC_PAST, KC_PENT,
                                            KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,  KC_TRNS,  KC_TRNS
    ),
    [3] = LAYOUT_split_3x6_3(
        KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                               KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_BSPC,
        KC_F1, KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,                               KC_7,    KC_F8,    KC_F9,    KC_F10,    KC_F11, KC_F12,
        KC_NO, KC_NO,    KC_NO,    KC_NO,    QK_BOOT,    KC_TRNS,                               KC_NO,    KC_NO,    KC_NO, KC_NO,  KC_NO, KC_NO,
                                            KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,  KC_TRNS,  KC_TRNS
    )
};
