// Copyright 2021 weteor | 2022 Conor Burns (@Conor-Burns)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
enum layers {
    _ALPHA_QWERTY = 0,
    _ALPHA_COLEMAK,
    _SYM,
    _NAV,
    _NUM,
    _CFG,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // clang-format off

    [_ALPHA_QWERTY] = LAYOUT_split_3x5_3(
        KC_Q,         KC_W,    KC_E,    KC_R,    KC_T,                                                KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,         KC_S,    KC_D,    KC_F,    KC_G,                                                KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        LSFT_T(KC_Z), KC_X,    KC_C,    KC_V,    KC_B,                                                KC_N,    KC_M,    KC_COMM, KC_DOT,  RSFT_T(KC_SLSH),

                        LCTL_T(KC_ESC), LT(_NUM,KC_SPC), LT(_NAV, KC_TAB),     LT(_SYM, KC_BSPC), KC_ENT, LALT_T(KC_DEL)
    ),
    [_ALPHA_COLEMAK] = LAYOUT_split_3x5_3(
        KC_Q,         KC_W,    KC_F,    KC_P,    KC_G,                                                KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
        KC_A,         KC_R,    KC_S,    KC_T,    KC_D,                                                KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
        LSFT_T(KC_Z), KC_X,    KC_C,    KC_V,    KC_B,                                                KC_K,    KC_M,    KC_COMM, KC_DOT,  RSFT_T(KC_SCLN),
                        LCTL_T(KC_ENT), LT(_NUM,KC_SPC), LT(_NAV, KC_TAB),     LT(_SYM, KC_BSPC), KC_ENT, LALT_T(KC_DEL)
    ),
    [_SYM] = LAYOUT_split_3x5_3(
        KC_GRV , KC_CIRC,   KC_AT,  KC_DLR, KC_TILD,                                KC_AMPR, KC_EXLM, KC_PIPE, KC_UNDS, KC_HASH,
        KC_SLSH, KC_LBRC, KC_LCBR, KC_LPRN,  KC_EQL,                                KC_ASTR, KC_RPRN, KC_RCBR, KC_RBRC, KC_BSLS,
        _______, KC_QUES, KC_PLUS, KC_PERC, XXXXXXX,                                XXXXXXX, XXXXXXX, KC_MINS, XXXXXXX, _______,
                                        XXXXXXX, MO(_CFG), XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_NAV] = LAYOUT_split_3x5_3(
        XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX,                                XXXXXXX, KC_PGDN,   KC_UP, KC_PGUP,  KC_DEL,
        KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT, XXXXXXX,                                KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, MO(_CFG), XXXXXXX
    ),
    // clang-format on
};
