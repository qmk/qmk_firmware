// Copyright 2022 Shem Sedrick (@ssedrick)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum key_layers {
    _BASE,
    _RAISE,
    _LOWER,
    _BLANK
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define SH_ESC SFT_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,                           KC_Y,    KC_U,    KC_I,   KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,   KC_F,    KC_G,                           KC_H,    KC_J,    KC_K,   KC_L, KC_SCLN,
        KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,                           KC_N,    KC_M, KC_COMM, KC_DOT, KC_SLSH,
              KC_LBRC, KC_RBRC,                                                           KC_QUOT, KC_GRV,
                                SH_ESC, KC_LGUI,  KC_TAB,       KC_RSFT, KC_SPC, KC_BSPC,
                                          RAISE, KC_LCTL,         LOWER, KC_ENT
                                             
    ),
    [_RAISE] = LAYOUT(
        
           KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                           KC_6,    KC_7, KC_8,   KC_9,    KC_0,
        _______, _______, KC_LCBR, KC_RCBR,  KC_EQL,                        KC_MINS,    KC_4, KC_5,   KC_6, KC_QUOT,
        QK_RBT, QK_BOOT,  KC_LBRC, KC_RBRC, _______,                        _______,    KC_1, KC_2,   KC_3, _______,
                _______, _______,                                                             KC_0, KC_DOT,
                                  _______, _______, _______,       _______, _______, _______,
                                           _______, _______,       _______, _______
    ),

    [_LOWER] = LAYOUT(
        KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
        _______, _______, KC_LBRC, KC_RBRC,  KC_EQL,                          _______, KC_MINS,  KC_EQL, KC_PIPE, _______,
        _______, _______, _______, _______, _______,                          _______, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,
                 _______,  _______,                                                             _______, _______,
                                   _______, _______, _______,        _______, _______, _______,
                                            _______, _______,        _______, _______
    ),

    [_BLANK] = LAYOUT(
        _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______,
                 _______, _______,                                                              _______, _______,
                                   _______, _______, _______,        _______, _______, _______,
                                            _______, _______,        _______, _______
    )
};
