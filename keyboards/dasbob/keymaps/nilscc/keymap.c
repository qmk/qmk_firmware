// Copyright 2021 weteor | 2022 Conor Burns (@Conor-Burns)
// Copyright 2023 Ben Roe (@keycapsss)
// Copyright 2023 Tom Barnes (@keyboard-magpie)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
enum layers {
    _ALPHA_NORDRASSIL,
    _ALPHA_QWERTY,
    _ALPHA_COLEMAK,
    _SYM,
    _NAV,
    _NUM,
    _CFG,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // clang-format off

    [_ALPHA_NORDRASSIL] = LAYOUT_split_3x5_3(
        KC_Q,   KC_Y,           KC_O,           KC_U,           KC_MINS,                                KC_J,       KC_G,           KC_N,           KC_W,           KC_K,
        KC_H,   KC_I,           LSFT_T(KC_E),   LCTL_T(KC_A),   KC_DOT,                                 KC_P,       LCTL_T(KC_D),   LSFT_T(KC_R),   RALT_T(KC_S),   KC_L,
        KC_Z,   KC_X,           KC_QUOT,        KC_COMM,        KC_SCLN,                                KC_B,       KC_C,           KC_M,           KC_F,           KC_V,
                        RALT_T(KC_ESC), LT(_NUM,KC_SPC), QK_REP,                             LT(_SYM, KC_T), LT(_NAV, KC_BSPC), LALT_T(KC_DEL)
    ),

    // default layers

    [_ALPHA_QWERTY] = LAYOUT_split_3x5_3(
        KC_Q,         KC_W,    KC_E,    KC_R,    KC_T,                                                  KC_Y,       KC_U,           KC_I,           KC_O,           KC_P,
        KC_A,         KC_S,    KC_D,    KC_F,    KC_G,                                                  KC_H,       KC_J,           KC_K,           KC_L,           KC_SCLN,
        LSFT_T(KC_Z), KC_X,    KC_C,    KC_V,    KC_B,                                                  KC_N,       KC_M,           KC_COMM,        KC_DOT,         RSFT_T(KC_SLSH),
                        LCTL_T(KC_ESC), LT(_NUM,KC_SPC), LT(_NAV, KC_TAB),                  LT(_SYM, KC_BSPC), KC_ENT, LALT_T(KC_DEL)
    ),

    [_ALPHA_COLEMAK] = LAYOUT_split_3x5_3(
        KC_Q,         KC_W,    KC_F,    KC_P,    KC_G,                                                  KC_J,       KC_L,           KC_U,           KC_Y,           KC_QUOT,
        KC_A,         KC_R,    KC_S,    KC_T,    KC_D,                                                  KC_H,       KC_N,           KC_E,           KC_I,           KC_O,
        LSFT_T(KC_Z), KC_X,    KC_C,    KC_V,    KC_B,                                                  KC_K,       KC_M,           KC_COMM,        KC_DOT,         RSFT_T(KC_SCLN),
                        LCTL_T(KC_ENT), LT(_NUM,KC_SPC), LT(_NAV, KC_TAB),                  LT(_SYM, KC_BSPC), KC_ENT, LALT_T(KC_DEL)
    ),

    // special layers

    [_SYM] = LAYOUT_split_3x5_3(
        KC_GRV , KC_CIRC, KC_AT,   KC_DLR,  KC_TILD,                                KC_AMPR, KC_EXLM, KC_PIPE, KC_UNDS, KC_HASH,
        KC_SLSH, KC_LBRC, KC_LCBR, KC_LPRN, KC_EQL,                                 KC_ASTR, KC_RPRN, KC_RCBR, KC_RBRC, KC_BSLS,
        XXXXXXX, KC_QUES, KC_PLUS, KC_PERC, XXXXXXX,                                XXXXXXX, XXXXXXX, KC_MINS, XXXXXXX, XXXXXXX,
                                        XXXXXXX, KC_TAB, KC_ENT,        _______, _______, _______
    ),

    [_NAV] = LAYOUT_split_3x5_3(
        XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX,                                KC_CAPS, KC_NUM,  XXXXXXX, XXXXXXX, XXXXXXX,
        KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT, XXXXXXX,                                KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX,
                                        _______, _______, _______,      XXXXXXX, _______, _______
    ),

    [_NUM] = LAYOUT_split_3x5_3(
        XXXXXXX,  KC_F9,  KC_F10, KC_F11, KC_F12,                                   KC_PPLS,  KC_P7,  KC_P8,  KC_P9,  KC_PSLS,
        XXXXXXX,  KC_F5,  KC_F6,  KC_F7,  KC_F8,                                    KC_P0,    KC_P4,  KC_P5,  KC_P6,  KC_PDOT,
        XXXXXXX,  KC_F1,  KC_F2,  KC_F3,  KC_F4,                                    KC_PMNS,  KC_P1,  KC_P2,  KC_P3,  KC_PAST,
                                        XXXXXXX, _______, XXXXXXX,      KC_PEQL, KC_PENT, XXXXXXX
    ),

    [_CFG] = LAYOUT_split_3x5_3(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                XXXXXXX, XXXXXXX, XXXXXXX,DF(_ALPHA_QWERTY), DF(_ALPHA_COLEMAK),
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                         XXXXXXX, _______, XXXXXXX,     XXXXXXX, _______, XXXXXXX
    )
    // clang-format on
};
