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
#define GT_SPC LGUI_T(KC_SPC)
#define GT_ENT RGUI_T(KC_ENT)
#define APP_P LSA(KC_TAB)
#define APP_N A(KC_TAB)
#define TSKMGR G(KC_TAB)
#define APP_X A(KC_F4)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_F1,   KC_F2, KC_F3,   KC_F4,   KC_F5, KC_F6, TSKMGR,      APP_X,   KC_F7,  KC_F8, KC_F9,   KC_F10, KC_F11,  KC_F12,
        KC_ESC,  KC_1,  KC_2,    KC_3,    KC_4,  KC_5,  APP_P,       APP_N,   KC_6,   KC_7,  KC_8,    KC_9,   KC_0,    KC_GRV,
        KC_TAB,  KC_Q,  KC_W,    KC_E,    KC_R,  KC_T,  KC_EQL,      KC_MINS, KC_Y,   KC_U,  KC_I,    KC_O,   KC_P,    KC_BSLS,
        KC_CAPS, KC_A,  KC_S,    KC_D,    KC_F,  KC_G,  KC_LBRC,     KC_RBRC, KC_H,   KC_J,  KC_K,    KC_L,   KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,  KC_X,    KC_C,    KC_V,  KC_B,                        KC_N,   KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                        KC_LCTL, KC_LALT,                                                   KC_RALT, KC_RCTL,
                                          LOWER, GT_SPC, KC_BSPC,    KC_DEL,  GT_ENT, RAISE
    ),

    [_LOWER] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______, _______,
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______,            _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
        _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                              _______, _______, _______, _______, _______, _______,
                          _______, _______,                                                                  _______, _______,
                                            _______, KC_LGUI, A(KC_PSCR),    RCS(KC_LEFT), _______, RCS(KC_RIGHT)

    ),

    [_RAISE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
        _______, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______, _______,    _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  _______,
        _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
                          _______, _______,                                                          _______, _______,
                                            KC_VOLD, KC_MUTE, KC_VOLU,    _______, _______, RAISE
    ),
};
