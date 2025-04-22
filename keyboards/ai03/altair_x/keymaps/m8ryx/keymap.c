/* Copyright 2024 ai03 Design Studio */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

#define TAPPING_TERM 200
#define _BASE 0
#define _SYM 1
#define _FN 2
#define _NOHRMOD 3
#define _QWERTY 4


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    XXXXXXX, XXXXXXX, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,    KC_SLSH,
        MEH_T(KC_ESC), LGUI_T(KC_A), LGUI_T(KC_R),LCTL_T(KC_S),LSFT_T(KC_T), HYPR_T(KC_G),    XXXXXXX, XXXXXXX, HYPR_T(KC_M), RSFT_T(KC_N), RCTL_T(KC_E), RALT_T(KC_I), RGUI_T(KC_O), KC_QUOT,
        KC_LSFT, KC_X,    KC_C,    KC_D,    KC_V,    KC_Z, XXXXXXX, XXXXXXX, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
                                   KC_LGUI, MO(2), KC_BSPC, LT(MO(1), KC_SPC), LT(MO(1), KC_SPC), KC_ENT, MO(2),  KC_DEL
    ),

    [_SYM] = LAYOUT(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, KC_GRV,  KC_LBRC, KC_LCBR, KC_LPRN, KC_MINS, _______, _______, KC_EQL,  KC_RPRN, KC_RCBR, KC_RBRC, KC_BSLS, _______,
        _______, KC_TILD, _______, _______, _______, KC_UNDS, _______, _______, KC_PLUS, _______, _______, _______, KC_PIPE, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_FN] = LAYOUT(
        _______, _______, _______, KC_PGUP, _______, _______, _______, _______, _______, _______, KC_UP,   _______, _______, _______,
        _______, _______, KC_HOME, KC_PGDN, KC_END,  _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, _______,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______
    )

};
