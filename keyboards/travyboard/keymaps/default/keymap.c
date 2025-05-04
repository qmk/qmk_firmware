// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _NUM,
    _FN1,
    _FN2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┬───┐
      * │Tab│ Q │ W │ E │ R │ T │EX1│   │EX1│ Y │ U │ I │ O │ P │Bsp│
      * ├───┼───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┼───┤
      * │Sft│ A │ S │ D │ F │ G │EX2│   │EX2│ H │ J │ K │ L │ ; │ ' │
      * ├───┼───┼───┼───┼───┼───┼───┘   └───┼───┼───┼───┼───┼───┼───┤
      * │Ctr│ Z │ X │ C │ V │ B │           │ N │ M │ , │ . │ / │Sft│
      * └───┴───┴───┴───┴───┴───┘           └───┴───┴───┴───┴───┴───┘
      *               ┌───┐                       ┌───┐
      *               │GUI├───┐               ┌───┤Alt│
      *               └───┤FN1├───┐       ┌───┤FN2├───┘
      *                   └───┤SPC│       │SPC├───┘
      *                       └───┘       └───┘
      */
    [_BASE] = LAYOUT_split_3x7_3(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_NO,    KC_NO,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_NO,    KC_NO,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_NO,    KC_NO,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                KC_LGUI, MO(_NUM), KC_SPC,                       KC_SPC,  MO(_FN1), KC_RALT
    ),

    [_NUM] = LAYOUT_split_3x7_3(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_NO,    KC_NO,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_LSFT, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_NO,    KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_QUOT, KC_ENT,
        KC_LCTL, KC_NO,   KC_NO,   KC_NO,   KC_V,    KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_RSFT,
                                 KC_LGUI, MO(_NUM), KC_SPC,                      KC_SPC,  MO(_FN2), KC_RALT
    ),

    [_FN1] = LAYOUT_split_3x7_3(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NO,    KC_NO,   KC_F6,   KC_F7,   KC_BSLS, KC_F9,   KC_F10,  KC_EQL,
        KC_LSFT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_HOME, KC_INS,  KC_DEL,  KC_END,  KC_NO,   KC_NO,
        KC_LCTL, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_BRID, KC_BRIU, KC_MPRV, KC_MNXT, KC_MPLY, KC_RSFT,
                                 KC_LGUI, MO(_FN2), KC_SPC,                      KC_SPC,  MO(_FN1), KC_RALT
    ),

    [_FN2] = LAYOUT_split_3x7_3(
        KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NO,    KC_NO,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_LSFT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_F12,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_RSFT,
                                 KC_LGUI, MO(_FN2), KC_SPC,                      KC_SPC,  MO(_FN2), KC_RALT
    )
};
