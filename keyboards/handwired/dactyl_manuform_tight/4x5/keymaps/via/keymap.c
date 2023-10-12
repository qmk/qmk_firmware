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
#define GT_A LGUI_T(KC_A)
#define AT_S LALT_T(KC_S)
#define CT_D LCTL_T(KC_D)
#define ST_F LSFT_T(KC_F)
#define ST_J RSFT_T(KC_J)
#define CT_K RCTL_T(KC_K)
#define AT_L RALT_T(KC_L)
#define GT_SCLN RGUI_T(KC_SCLN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_Q,  KC_W,    KC_E,    KC_R,  KC_T,                       KC_Y,   KC_U,  KC_I,    KC_O,   KC_P,
        GT_A,  AT_S,    CT_D,    ST_F,  KC_G,                       KC_H,   ST_J,  CT_K,    AT_L,   GT_SCLN,
        KC_Z,  KC_X,    KC_C,    KC_V,  KC_B,                       KC_N,   KC_M,  KC_COMM, KC_DOT, KC_SLSH,
               KC_EQL,  KC_MINS,                                                   KC_LBRC, KC_RBRC,
                                 LOWER, KC_SPC, KC_BSPC,    KC_DEL, KC_ENT, RAISE
    ),

    [_LOWER] = LAYOUT(
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                              KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                 KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        _______, _______, KC_TILD, KC_GRV,  _______,                              _______, KC_BSLS, KC_PIPE, _______, _______,
                 QK_BOOT, _______,                                                                  _______, _______,
                                   _______, KC_LGUI, A(KC_PSCR),    RCS(KC_LEFT), _______, RCS(KC_RIGHT)

    ),

    [_RAISE] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_HOME, KC_PGUP, KC_PGDN, KC_END,  _______,                      _______, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT,
        _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______,
                 KC_F11,  KC_F12,                                                           _______, A(KC_TAB),
                                   KC_VOLD, KC_MUTE, KC_VOLU,    _______, _______, RAISE
    ),
};
