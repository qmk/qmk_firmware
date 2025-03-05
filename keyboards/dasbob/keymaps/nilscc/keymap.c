// Copyright 2021 weteor | 2022 Conor Burns (@Conor-Burns)
// Copyright 2023 Ben Roe (@keycapsss)
// Copyright 2023 Tom Barnes (@keyboard-magpie)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _ALPHA_NORDRASSIL,
    // _ALPHA_QWERTY,
    // _ALPHA_COLEMAK,
    _SYM,
    _NAV,
    _NUM,
    _FNC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // clang-format off

    // default alpha layers

    [_ALPHA_NORDRASSIL] = LAYOUT_split_3x5_3(
        KC_Q,   KC_Y,           KC_O,           KC_U,           KC_MINS,                                KC_J,       KC_G,           KC_N,           KC_W,           KC_K,
        KC_H,   LALT_T(KC_I),   LSFT_T(KC_E),   LCTL_T(KC_A),   KC_DOT,                                 KC_P,       LCTL_T(KC_D),   LSFT_T(KC_R),   RALT_T(KC_S),   KC_L,
        KC_Z,   KC_X,           KC_QUOT,        KC_COMM,        KC_SCLN,                                KC_B,       KC_C,           KC_M,           KC_F,           KC_V,
                              LT(_FNC,KC_ESC), LT(_NUM,KC_SPC), QK_REP,                             LT(_SYM, KC_T), LT(_NAV, KC_BSPC), LALT_T(KC_DEL)
    ),

    // [_ALPHA_QWERTY] = LAYOUT_split_3x5_3(
    //     KC_Q,         KC_W,    KC_E,    KC_R,    KC_T,                                                  KC_Y,       KC_U,           KC_I,           KC_O,           KC_P,
    //     KC_A,         KC_S,    KC_D,    KC_F,    KC_G,                                                  KC_H,       KC_J,           KC_K,           KC_L,           KC_SCLN,
    //     LSFT_T(KC_Z), KC_X,    KC_C,    KC_V,    KC_B,                                                  KC_N,       KC_M,           KC_COMM,        KC_DOT,         RSFT_T(KC_SLSH),
    //                     LCTL_T(KC_ESC), LT(_NUM,KC_SPC), LT(_NAV, KC_TAB),                  LT(_SYM, KC_BSPC), KC_ENT, LALT_T(KC_DEL)
    // ),
    //
    // [_ALPHA_COLEMAK] = LAYOUT_split_3x5_3(
    //     KC_Q,         KC_W,    KC_F,    KC_P,    KC_G,                                                  KC_J,       KC_L,           KC_U,           KC_Y,           KC_QUOT,
    //     KC_A,         KC_R,    KC_S,    KC_T,    KC_D,                                                  KC_H,       KC_N,           KC_E,           KC_I,           KC_O,
    //     LSFT_T(KC_Z), KC_X,    KC_C,    KC_V,    KC_B,                                                  KC_K,       KC_M,           KC_COMM,        KC_DOT,         RSFT_T(KC_SCLN),
    //                     LCTL_T(KC_ENT), LT(_NUM,KC_SPC), LT(_NAV, KC_TAB),                  LT(_SYM, KC_BSPC), KC_ENT, LALT_T(KC_DEL)
    // ),

    // special layers

    [_SYM] = LAYOUT_split_3x5_3(
        KC_GRV , KC_CIRC, KC_AT,   KC_DLR,  KC_TILD,                   KC_AMPR, KC_EXLM, KC_PIPE, KC_UNDS, KC_HASH,
        KC_SLSH, KC_LBRC, KC_LCBR, KC_LPRN, KC_EQL,                    KC_ASTR, KC_RPRN, KC_RCBR, KC_RBRC, KC_BSLS,
        XXXXXXX, KC_QUES, KC_PLUS, KC_PERC, XXXXXXX,                   XXXXXXX, KC_COLN, KC_MINS, XXXXXXX, XXXXXXX,
                                   XXXXXXX, KC_TAB,  KC_ENT,  _______, _______, _______
    ),

    [_NAV] = LAYOUT_split_3x5_3(
        XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX,                   G(KC_1), G(KC_2), G(KC_3), G(KC_4), G(KC_5),
        KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, XXXXXXX,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, KC_LGUI,                   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX,
                                   _______, _______, _______, XXXXXXX, _______, _______
    ),

    // number layer with modifiers and ?! keys to avoid conflicts with TAB on
    // symbols layer when typing a fast space after a sentence
    [_NUM] = LAYOUT_split_3x5_3(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_NUM,                    KC_PEQL,  KC_7,   KC_8,   KC_9,   KC_PSLS,
        KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, XXXXXXX,                   KC_PPLS,  KC_4,   KC_5,   KC_6,   KC_PCMM,
        XXXXXXX, XXXXXXX, KC_QUES, KC_EXLM, XXXXXXX,                   KC_PMNS,  KC_1,   KC_2,   KC_3,   KC_PAST,
                                   XXXXXXX, _______, _______, KC_PENT, KC_0, XXXXXXX
    ),

    // function layer, with alt-tab and umlauts on left side
    [_FNC] = LAYOUT_split_3x5_3(
        KC_LALT, KC_TAB,    ALGR(KC_O), ALGR(KC_U), KC_CAPS,                   XXXXXXX, KC_F9,  KC_F10, KC_F11, KC_F12,
        XXXXXXX, S(KC_TAB), ALGR(KC_E), ALGR(KC_A), KC_PSCR,                   XXXXXXX, KC_F5,  KC_F6,  KC_F7,  KC_F8,
        XXXXXXX, KC_GRV,    XXXXXXX,    ALGR(KC_S), KC_LGUI,                   XXXXXXX, KC_F1,  KC_F2,  KC_F3,  KC_F4,
                                        XXXXXXX,    _______, XXXXXXX, XXXXXXX, _______, XXXXXXX
    )
    // clang-format on
};
