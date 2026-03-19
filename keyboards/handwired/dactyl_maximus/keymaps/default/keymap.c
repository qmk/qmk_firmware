// Copyright 2021 Duncan Sutherland (https://github.com/dunk2k)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define CUT C(KC_X)
#define COPY C(KC_C)
#define PSTE C(KC_V)
#define UNDO C(KC_Z)
#define REDO C(KC_Y)
#define SALL C(KC_A)
#define APP_N A(KC_TAB)
#define APP_P LSA(KC_TAB)
#define SLFT S(KC_HOME)
#define SRGHT S(KC_END)
#define APP_X A(KC_F4)
#define TSKMG RCS(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        APP_P, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,                                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PSCR, APP_N,
        SLFT,  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,                                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, SRGHT,
        COPY,  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,   KC_G,                                           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, PSTE,
        CUT,   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,                                           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, SALL,
        UNDO,  KC_LCTL, KC_LALT, KC_LGUI, KC_MINS, KC_EQL,                                                          KC_LBRC, KC_RBRC, KC_RGUI, KC_RALT, KC_RCTL, REDO,
                                                                  KC_HOME, KC_PGUP,      KC_VOLU, KC_END,
                                                           MO(1), KC_SPC,  KC_DEL,       KC_BSPC, KC_ENT,  MO(2),
                                                           KC_UP, KC_DOWN, KC_PGDN,      KC_VOLD, KC_LEFT, KC_RGHT
    ),

    [1] = LAYOUT(
        KC_TRNS, KC_NO, KC_NO, KC_NO,   KC_NO,  KC_NO,   KC_NO,                                        KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO,  KC_TRNS,
        KC_TRNS, TSKMG, APP_X, KC_SCRL, KC_INS, KC_PAUS, KC_NO,                                        KC_NO,   KC_P7,   KC_P8, KC_P9,   KC_NO,   KC_NO,  KC_TRNS,
        KC_TRNS, KC_F1, KC_F2, KC_F3,   KC_F4,  KC_F5,   KC_F6,                                        KC_PAST, KC_P4,   KC_P5, KC_P6,   KC_PMNS, KC_NUM, KC_TRNS,
        KC_TRNS, KC_F7, KC_F8, KC_F9,   KC_F10, KC_F11,  KC_F12,                                       KC_PSLS, KC_P1,   KC_P2, KC_P3,   KC_PPLS, KC_NO,  KC_TRNS,
        KC_TRNS, KC_NO, KC_NO, KC_NO,   KC_NO,  KC_NO,                                                          KC_PCMM, KC_P0, KC_PDOT, KC_NO,   KC_NO,  KC_TRNS,
                                                                  KC_NO, KC_NO,      KC_NO,   KC_RCTL,
                                                         KC_TRNS, KC_NO, KC_NO,      KC_RSFT, KC_PENT, KC_LALT,
                                                         KC_NO,   KC_NO, KC_NO,      KC_NO,   KC_RGUI, KC_NO
    ),

    [2] = LAYOUT(
        KC_TRNS, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                      KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO,   KC_NO, KC_TRNS,
        KC_TRNS, KC_NO, KC_NO,   MS_ACL2, MS_ACL1, MS_ACL0, KC_NO,                                      KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO,   KC_NO, KC_TRNS,
        KC_TRNS, KC_NO, MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, KC_NO,                                      KC_NO,   KC_SLEP, KC_NO, KC_NO, QK_BOOT, KC_NO, KC_TRNS,
        KC_TRNS, KC_NO, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, KC_NO,                                      KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO,   KC_NO, KC_TRNS,
        KC_TRNS, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,                                                        KC_NO,   KC_NO, KC_NO, KC_NO,   KC_NO, KC_TRNS,
                                                                   KC_NO,   KC_NO,        KC_NO, KC_NO,
                                                            KC_NO, MS_BTN1, MS_BTN2,      KC_NO, KC_NO, KC_TRNS,
                                                            KC_NO, KC_NO,   KC_NO,        KC_NO, KC_NO, KC_NO
    )
};
