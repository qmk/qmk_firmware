// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _SYMBOLS,
    _GAMING,
    _ARROWS,
    _WINMGR,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT(
    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5,                                                   KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                                                   KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
    KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G,                                                   KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,                                                  KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                LALT(KC_LSFT), LALT(KC_SPC),                                                        LALT(KC_SPC), LGUI(KC_LALT),
                                  KC_SPC, TT(_SYMBOLS),                             TT(_ARROWS), LALT(KC_ENTER),
                                  KC_LCTL, KC_LGUI,                                 KC_LGUI, KC_RCTL,
                                  KC_LALT, TT(_WINMGR),                             TT(_GAMING), KC_LALT),

	[_SYMBOLS] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_CAPS_LOCK, LSFT(KC_BSLS), KC_BSLS, LSFT(KC_LBRC), LSFT(KC_RBRC), KC_TRNS,            KC_TRNS, LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LCTL(KC_EQUAL), LGUI(KC_EQUAL),
    TO(_QWERTY), LSFT(KC_EQUAL), KC_MINUS, LSFT(KC_9), LSFT(KC_0), KC_GRAVE,                KC_BSLS, LSFT(KC_4), LSFT(KC_5), LSFT(KC_6), LCTL(KC_MINUS), LGUI(KC_MINUS),
    KC_TRNS, KC_EQUAL, LSFT(KC_MINUS), KC_LBRC, KC_RBRC, LSFT(KC_GRAVE),                    LSFT(KC_BSLS), LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), KC_COMMA, KC_CALC,
                KC_TRNS, KC_TRNS,                                                                   LSFT(KC_0), KC_TRNS,
                                  KC_TRNS, KC_TRNS,                                 KC_TRNS, LSFT(KC_0),
                                  KC_TRNS, KC_TRNS,                                 KC_TRNS, KC_TRNS,
                                  QK_RBT, KC_TRNS,                                  KC_TRNS, KC_TRNS),

	[_GAMING] = LAYOUT(
    KC_6,   KC_1,    KC_2, KC_3, KC_4, KC_5,                                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_7,   KC_TAB,  KC_Q, KC_W, KC_E, KC_R,                                                KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS,
    KC_ESC, KC_LSFT, KC_A, KC_S, KC_D, KC_F,                                                KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS,
    KC_8,   KC_LCTL, KC_Z, KC_X, KC_C, KC_V,                                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                KC_9, KC_0,                                                                         KC_TRNS, KC_TRNS,
                                  KC_SPC, MO(_ARROWS),                              KC_TRNS, KC_ENTER,
                                  KC_G, KC_M,                                       KC_TRNS, KC_TRNS,
                                  KC_LALT, TO(_QWERTY),                             TO(_QWERTY), KC_TRNS),

	[_ARROWS] = LAYOUT(
    KC_F12, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                                              KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
    KC_NUM, KC_KP_SLASH, KC_P7, KC_P8, KC_P9, KC_MINUS,                                     LCTL(KC_LEFT), LCTL(KC_DOWN), LCTL(KC_UP), LCTL(KC_RGHT), KC_TRNS, KC_DELETE,
    TO(_QWERTY), KC_KP_PLUS, KC_P4, KC_P5, KC_P6, KC_DOT,                                   KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_END, KC_PSCR,
    KC_UNDS, KC_KP_MINUS, KC_P1, KC_P2, KC_P3, KC_COMMA,                                    KC_HOME, KC_MPLY, KC_MPRV, KC_MNXT, KC_MUTE, KC_INS,
                KC_KP_DOT, KC_P0,                                                                   KC_VOLD, KC_VOLU,
                                  KC_P0, TO(_WINMGR),                               KC_TRNS, KC_TRNS,
                                  KC_TRNS, KC_TRNS,                                 KC_TRNS, KC_TRNS,
                                  KC_TRNS, KC_TRNS,                                 KC_TRNS, QK_RBT),

	[_WINMGR] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,     KC_F1, LGUI(KC_7), LGUI(KC_8), LGUI(KC_9), KC_F4,                          KC_F7, SGUI(KC_7), SGUI(KC_8), SGUI(KC_9), KC_F10, KC_TRNS,
    TO(_QWERTY), KC_F2, LGUI(KC_4), LGUI(KC_5), LGUI(KC_6), KC_F5,                          KC_F8, SGUI(KC_4), SGUI(KC_5), SGUI(KC_6), KC_F11, KC_TRNS,
    KC_TRNS,     KC_F3, LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), KC_F6,                          KC_F9, SGUI(KC_1), SGUI(KC_2), SGUI(KC_3), KC_F12, KC_TRNS,
                KC_TRNS, LGUI(KC_0),                                                                SGUI(KC_0), KC_TRNS,
                                  LGUI(KC_0), KC_TRNS,                              KC_TRNS, SGUI(KC_0),
                                  KC_TRNS, KC_TRNS,                                 KC_TRNS, KC_TRNS,
                                  LCTL(LGUI(KC_Q)), KC_TRNS,                        KC_TRNS, KC_TRNS)
};

