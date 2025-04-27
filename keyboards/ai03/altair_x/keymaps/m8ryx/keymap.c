/* Copyright 2024 ai03 Design Studio */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

#define _BASE 0
#define _SYM 3
#define _FN 2
#define _NOHRMOD 5
#define _QWERTY 1


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        LT(MO(_QWERTY), KC_TAB),  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    XXXXXXX, XXXXXXX, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,    KC_SLSH,
        MEH_T(KC_ESC), LGUI_T(KC_A), LALT_T(KC_R),LCTL_T(KC_S),LSFT_T(KC_T), HYPR_T(KC_G),    XXXXXXX, XXXXXXX, HYPR_T(KC_M), RSFT_T(KC_N), RCTL_T(KC_E), RALT_T(KC_I), RGUI_T(KC_O), KC_QUOT,
        KC_LSFT, KC_X,    KC_C,    KC_D,    KC_V,    KC_Z, QK_MAKE, QK_BOOT, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
                                   KC_LGUI, MO(_FN), KC_BSPC, LT(MO(_SYM), KC_SPC), LT(MO(_SYM), KC_SPC), KC_ENT, MO(_FN),  KC_DEL
    ),

    [_QWERTY] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    QK_LAYER_LOCK, QK_LAYER_LOCK, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        MEH_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    XXXXXXX, XXXXXXX, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
                                   KC_LGUI, MO(_FN), KC_BSPC, LT(MO(_SYM), KC_SPC), LT(MO(_SYM), KC_SPC), KC_ENT, MO(_FN),  KC_DEL
    ),

    [_SYM] = LAYOUT(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        /*        _______, LGUI_T(KC_GRV),  LALT_T(KC_LBRC), LCTL_T(LSFT(KC_LBRC)), LSFT_T(S(KC_9)), KC_MINS, _______, _______, KC_EQL,  RSFT_T(LSFT(KC_0)), RCTL_T(S(KC_RCBR)), RALT_T(KC_RBRC), RGUI_T(KC_BSLS), _______,*/
                _______, LGUI_T(KC_GRV),  LALT_T(KC_LBRC), CTL_T(LSFT(KC_LBRC)), SFT_T(KC_LEFT_PAREN), KC_MINS, _______, _______, KC_EQL,  SFT_T(KC_RIGHT_PAREN), CTL_T(S(KC_RCBR)), RALT_T(KC_RBRC), RGUI_T(KC_BSLS), _______,
        _______, KC_TILD, _______, _______, _______, KC_UNDS, _______, _______, KC_PLUS, _______, _______, _______, KC_PIPE, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_FN] = LAYOUT(
        _______, _______, _______, KC_PGUP, _______, _______, _______, _______, _______, _______, KC_UP,   _______, _______, _______,
        _______, _______, KC_HOME, KC_PGDN, KC_END,  _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, _______,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______
    ),

};
