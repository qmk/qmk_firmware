// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _NUMPAD,
    _ARROWS,
    _MOUSE,
    _GAMING,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT(
    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5,                                   KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                                   KC_Y, KC_U, KC_I, KC_O, KC_P, KC_EQL,
    KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G,                                   KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,                                  KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                C_S_T(KC_LEFT), SGUI_T(KC_RGHT),                                        KC_LBRC, KC_RBRC,
                                  KC_SPC, KC_ENT,                   TT(2), KC_BSPC,
                                  KC_LCTL, KC_LGUI,                 KC_BSLS, KC_RALT,
                                  KC_LALT, TT(_NUMPAD),             KC_DEL, TO(_GAMING)),

	[_NUMPAD] = LAYOUT(
    KC_PWR, SGUI(KC_1), SGUI(KC_2), SGUI(KC_3), SGUI(KC_4), SGUI(KC_5),     KC_HOME, KC_NUM, KC_PSLS, KC_PAST, KC_PMNS, KC_LPRN,
    KC_SLEP, KC_TRNS, KC_TRNS, KC_CAPS, KC_LBRC, KC_RBRC,                   KC_END, KC_P7, KC_P8, KC_P9, KC_PPLS, KC_RPRN,
    KC_BRIU, KC_HOME, KC_PGDN, KC_PGUP, KC_END, SGUI(KC_E),                 KC_LT, KC_P4, KC_P5, KC_P6, KC_PENT, KC_PEQL,
    KC_BRID, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V),                LCTL(KC_F), KC_GT, KC_P1, KC_P2, KC_P3, KC_PCMM, KC_CALC,
                TO(_MOUSE), KC_PSCR,                                                    KC_P0, KC_PDOT,
                                  KC_TRNS, KC_TRNS,                 KC_TRNS, LCTL(KC_BSPC),
                                  KC_TRNS, KC_TRNS,                 KC_TRNS, KC_TRNS,
                                  KC_TRNS, TO(_QWERTY),             KC_TRNS, KC_TRNS),

	[_ARROWS] = LAYOUT(
    KC_F12, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                              KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
    KC_NUM, KC_TRNS, KC_LPRN, KC_RPRN, KC_TRNS, KC_TRNS,                    LCTL(KC_LEFT), LCTL(KC_DOWN), LCTL(KC_UP), LCTL(KC_RGHT), KC_CAPS, KC_NUM,
    KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV,                     KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_END, KC_SCRL,
    KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,                   KC_HOME, KC_MPLY, KC_MPRV, KC_MNXT, KC_MUTE, KC_INS,
                KC_TRNS, KC_TRNS,                                                       KC_VOLD, KC_VOLU,
                                  LALT(KC_SPC), LGUI(KC_ENT),       TO(_QWERTY), KC_TRNS,
                                  KC_TRNS, LGUI(KC_SPC),                 KC_TRNS, KC_TRNS,
                                  KC_TRNS, KC_TRNS,                 KC_TRNS, KC_TRNS),

	[_MOUSE] = LAYOUT(
    KC_ACL0, KC_NO, KC_BTN4, KC_BTN3, KC_BTN5, KC_NO,                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT,
    KC_ACL1, KC_NO, KC_BTN1, KC_MS_U, KC_BTN2, KC_NO,                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_ACL2, KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO,                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_NO, KC_NO, KC_WH_L, KC_WH_U, KC_WH_D, KC_WH_R,                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                KC_TRNS, KC_NO,                                                         KC_TRNS, KC_TRNS,
                                  KC_TRNS, KC_TRNS,                 KC_TRNS, KC_TRNS,
                                  KC_TRNS, KC_TRNS,                 KC_TRNS, KC_TRNS,
                                  KC_TRNS, TO(_QWERTY),             KC_TRNS, TO(_QWERTY)),

	[_GAMING] = LAYOUT(
    KC_6, KC_1, KC_2, KC_3, KC_4, KC_5,                                     KC_HOME, KC_NUM, KC_PSLS, KC_PAST, KC_PMNS, KC_LPRN,
    KC_7, KC_TAB, KC_Q, KC_W, KC_E, KC_R,                                   KC_END, KC_P7, KC_P8, KC_P9, KC_PPLS, KC_RPRN,
    KC_ESC, KC_LSFT, KC_A, KC_S, KC_D, KC_F,                                KC_LT, KC_P4, KC_P5, KC_P6, KC_PENT, KC_PEQL,
    KC_8, KC_LCTL, KC_Z, KC_X, KC_C, KC_V,                                  KC_GT, KC_P1, KC_P2, KC_P3, KC_PCMM, KC_CALC,
                KC_9, KC_0,                                                             KC_P0, KC_PDOT,
                                  KC_SPC, KC_ENT,                   KC_TRNS, KC_TRNS,
                                  KC_G, KC_M,                       KC_TRNS, KC_TRNS,
                                  KC_LALT, TO(_QWERTY),             KC_TRNS, TO(_QWERTY))
};
