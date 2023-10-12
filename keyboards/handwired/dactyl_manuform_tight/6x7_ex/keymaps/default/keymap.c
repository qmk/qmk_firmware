// Copyright 2023 Duncan Sutherland (@dunk2k)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _RAISE,
    _LOWER,
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define APP_X A(KC_F4)
#define TSKMGR RCS(KC_ESC)
#define APPMGR G(KC_TAB)
#define APP_P LSA(KC_TAB)
#define APP_N A(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        APP_X,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, KC_F6,                      KC_F7,  KC_F8, KC_F9,   KC_F10,  KC_F11,  KC_F12,  TSKMGR,
        APPMGR,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,  KC_5,                       KC_6,   KC_7,  KC_8,    KC_9,    KC_0,    KC_PAUS, KC_INS,
        KC_MYCM, KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,                       KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSLS, KC_PSCR,
        KC_CAPS, KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,  KC_G,                       KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_CALC,
        KC_MEH,  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,                       KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_HYPR,
        APP_P,   KC_LCTL, KC_LALT, KC_LGUI, KC_HOME,                                                   KC_END,  KC_RGUI, KC_RALT, KC_RCTL, APP_N,
                                                     LOWER, KC_SPC, KC_BSPC,    KC_DEL, KC_ENT, RAISE
    ),

    [_LOWER] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, _______, _______,                              _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                              _______, _______, _______, _______, KC_PSLS, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                              _______, KC_P7,   KC_P8,   KC_P9,   KC_PAST, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                              KC_NUM,  KC_P4,   KC_P5,   KC_P6,   KC_PMNS, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                              _______, KC_P1,   KC_P2,   KC_P3,   KC_PPLS, _______, _______,
        _______, _______, _______, _______, _______,                                                                  KC_P0,   KC_PDOT, _______, _______, _______,
                                                     _______, KC_LGUI, A(KC_PSCR),    RCS(KC_LEFT), KC_PENT, RCS(KC_RIGHT)
    ),

    [_RAISE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, QK_BOOT,
        _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_PLUS, KC_UNDS, KC_LCBR, KC_RCBR, _______,                      _______, KC_PGUP, _______, _______, _______, _______, _______,
        _______, _______, KC_EQL,  KC_MINS, KC_LBRC, KC_RBRC, _______,                      _______, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                      _______, KC_PGDN, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                                                          _______, _______, _______, _______, _______,
                                                     
                                                     KC_VOLD, KC_MUTE, KC_VOLU,    _______, _______, RAISE
    ),
};
