// Copyright 2022 mjohns
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_layers {
    _BASE,
    _RAISE,
    _LOWER,
    _SYS,
};

#define MG_A LGUI_T(KC_A)
#define MA_S LALT_T(KC_S)
#define MC_D LCTL_T(KC_D)
#define MS_F LSFT_T(KC_F)
#define MS_J RSFT_T(KC_J)
#define MC_K RCTL_T(KC_K)
#define MA_L LALT_T(KC_L)
#define MG_SCLN RGUI_T(KC_SCLN)
#define APP_N A(KC_TAB)
#define APP_P LSA(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_Q, KC_W,    KC_E,    KC_R,   KC_T,                         KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,
        MG_A, MA_S,    MC_D,    MS_F,   KC_G,                         KC_H,   MS_J,   MC_K,    MA_L,    MG_SCLN,
        KC_Z, KC_X,    KC_C,    KC_V,   KC_B,                         KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_QUOT,
              KC_LEFT, KC_RGHT,                 KC_HOME,     KC_END,                  KC_UP,   KC_DOWN,
                                KC_TAB, KC_SPC, KC_DEL,      KC_BSPC, KC_ENT, KC_ESC,
                                        MO(1),                        MO(2)
    ),

    [_RAISE] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_LBRC,                      KC_RBRC, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR,
        KC_PIPE, KC_GRV,  KC_BSLS, KC_LPRN, KC_LCBR,                      KC_RCBR, KC_RPRN, KC_SLSH, KC_QUES, KC_TILD,
                 KC_MINS, KC_PLUS,                   KC_NO,      KC_LALT,                   KC_EQL,  KC_UNDS,
                                   KC_NO,   KC_NO,   KC_NO,      KC_RCTL, KC_RSFT, KC_RGUI,
                                            _______,                      MO(3)
    ),

    [_LOWER] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_F11,  KC_INS,  KC_PAUS, KC_PGUP, KC_PSCR,                      KC_MUTE, KC_VOLU, KC_MNXT, KC_MPRV, KC_F12,
        KC_SCRL, KC_NO,   KC_NO,   KC_PGDN, KC_NO,                        KC_NO,   KC_VOLD, KC_MPLY, KC_MSTP, KC_NO,
                 KC_BRID, KC_BRIU,                   KC_LALT,      KC_NO,                   APP_N,   APP_P,
                                   KC_LGUI, KC_LSFT, KC_LCTL,      KC_NO, KC_NO,   KC_NO,
                                            MO(3),                        _______
    ),

    [_SYS] = LAYOUT(
        KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,                      KC_NO,  KC_NO,   KC_NO, KC_NO, KC_NO,
        KC_NO, QK_BOOT, KC_NO, KC_NO, KC_NO,                      KC_NO,  KC_SLEP, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,                      KC_NO,  KC_NO,   KC_NO, KC_NO, KC_NO,
               KC_NO,   KC_NO,                 KC_NO,      KC_NO,                  KC_NO, KC_NO,
                               KC_NO, KC_NO,   KC_NO,      KC_NO, KC_NO,  KC_NO,
                                      _______,                    _______
    ),
};
