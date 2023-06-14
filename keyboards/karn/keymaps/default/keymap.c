// Copyright 2023 Robert Mills (@robcmills)
// SPDX-License-Identifier: GPL-2.0

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


    // default (qwerty)
    [0] = LAYOUT_split_3x6_3(
        KC_NO,         KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                        KC_Y,  KC_U,       KC_I,          KC_O,         KC_P,           KC_NO,
        HYPR_T(KC_TAB),KC_A,       KC_S,       KC_D,       KC_F,       KC_G,                        KC_H,  KC_J,       KC_K,          KC_L,         KC_SCLN,           HYPR_T(KC_ENT),
        KC_NO,         SFT_T(KC_Z),CTL_T(KC_X),ALT_T(KC_C),CMD_T(KC_V),KC_B,                        KC_N,  CMD_T(KC_M),ALT_T(KC_COMM),CTL_T(KC_DOT),RSFT_T(KC_SLSH),KC_NO,
                                                           MO(1),      SFT_T(KC_ESC),MO(3), KC_BSPC,KC_SPC,MO(2)
    ),

    // symbols
    [1] = LAYOUT_split_3x6_3(
        _______, KC_BSLS, KC_GRV,  KC_QUOT, KC_DQT,  KC_LCBR,                    KC_RCBR, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______,
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
        _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,  KC_DEL,  _______, _______
    ),

    // nav
    [2] = LAYOUT_split_3x6_3(
        _______, _______, _______,   _______,   _______,   KC_VOLU,                    _______, _______, _______, _______, _______, _______,
        _______, C(KC_UP),C(KC_DOWN),G(KC_GRV), G(KC_TAB), KC_VOLD,                    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_CAPS, _______,
        _______, _______, _______,   _______,   _______,   KC_MUTE,                    _______, _______, _______, _______, _______, _______,
                                                _______,   _______, _______,  _______, _______, _______
    ),

    // numbers
    [3] = LAYOUT_split_3x6_3(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,  _______, _______, _______
    )
};

