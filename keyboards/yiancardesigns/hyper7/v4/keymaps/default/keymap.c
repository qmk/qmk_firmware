// Copyright 2025 Yiancar-Designs, Bit-Shifter
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum my_keycodes {
    MACRO = QK_USER_0,
    QUOTE,
    CLRIN,
    SQUAR,
    CIRCL,
    TRIAN,
    DIAMO,
    WRITE,
    TTY,
    PLUSM,
    MODE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case MACRO:
        if (record->event.pressed) {
            // when keycode MACRO is pressed
            SEND_STRING("Hyper7 is the best thing ever!");
        }
        break;
    case QUOTE:
        if (record->event.pressed) {
            // when keycode QUOTE is pressed
            SEND_STRING("\"\"" SS_TAP(X_LEFT));
        }
        break;
    case CLRIN:
        if (record->event.pressed) {
            // when keycode CLRIN is pressed
            SEND_STRING(SS_LCTL("a") SS_TAP(X_DEL));
        }
        break;
    case SQUAR:
        if (record->event.pressed) {
            // when keycode SQUAR is pressed
            SEND_STRING("I like squares");
        }
        break;
    case CIRCL:
        if (record->event.pressed) {
            // when keycode CIRCL is pressed
            SEND_STRING("I like circles");
        }
        break;
    case TRIAN:
        if (record->event.pressed) {
            // when keycode TRIAN is pressed
            SEND_STRING("I like the illuminati");
        }
        break;
    case DIAMO:
        if (record->event.pressed) {
            // when keycode DIAMO is pressed
            SEND_STRING("Everyone likes diamonds");
        }
        break;
    case WRITE:
        if (record->event.pressed) {
            // when keycode WRITE is pressed
            SEND_STRING(SS_LGUI("x") "notepad" SS_TAP(X_ENT));
        }
        break;
    case TTY:
        if (record->event.pressed) {
            // when keycode TTY is pressed
            SEND_STRING(SS_LGUI("x") "cmd" SS_TAP(X_ENT));
        }
        break;
    case PLUSM:
        if (record->event.pressed) {
            // when keycode PLUSM is pressed
            SEND_STRING("+-");
        }
    case MODE:
        if (record->event.pressed) {
            // when keycode MODE is pressed
            SEND_STRING("Mode");
        }
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_modern(
        G(KC_F1),             MACRO,                RCS(KC_ESC),          QUOTE,                KC_INS,               CLRIN,                G(KC_D),              C(KC_S),              C(KC_C),              A(KC_F4),             KC_PAUS,              C(KC_P),              G(C(KC_Q)),           LCA(KC_DEL),
        G(KC_X),              KC_WHOM,              G(KC_PAUS),           C(KC_R),              A(KC_TAB),            SQUAR,                CIRCL,                TRIAN,                DIAMO,                C(KC_Y),              LAG(KC_R),            RCS(KC_ESC),          G(KC_L),              KC_CAPS,
        KC_F1,     KC_F2,     A(KC_F4),  G(KC_R),   KC_ESC,               KC_QUES,   KC_EXLM,   KC_AT,     KC_AT,     KC_AT,     KC_AT,     KC_GRV,    KC_GRV,    KC_GRV,    KC_GRV,    KC_UNDS,   KC_LABK,   KC_RABK,   KC_PIPE,   KC_LCBR,   KC_RCBR,   C(KC_ENT),            KC_CIRC,   KC_PERC,   KC_HASH,   KC_DLR,
        KC_F3,     KC_F4,     C(KC_F),   WRITE,     LSFT(KC_N),           PLUSM,     KC_TILD,   KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,   KC_EQL,    KC_NUBS,   KC_LBRC,   KC_RBRC,   C(KC_Z),   KC_PMNS,   KC_PSLS,   KC_PAST,   KC_PMNS,
        KC_F5,     KC_F6,     C(KC_M),   C(KC_Z),   C(KC_V),   C(KC_X),              KC_TAB,    KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_LCBR,   KC_RCBR,   KC_BSPC,              KC_CLEAR,  C(KC_HOME),KC_P7,     KC_P8,     KC_P9,     KC_PPLS,
        KC_F7,     KC_F8,     C(KC_A),   KC_F12,    MO(1),                MODE,      KC_PGUP,   KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_COLN,   KC_QUOT,              KC_ENT,    KC_HOME,   KC_PGDN,   KC_P4,     KC_P5,     KC_P6,     KC_AMPR,
        KC_F9,     KC_F10,    TTY,       G(KC_L),   C(KC_HOME),KC_END,    G(KC_DOT), KC_LSFT,   KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_RSFT,              G(KC_DOT), KC_UP,     KC_LGUI,              KC_P1,     KC_P2,     KC_P3,     KC_EQL,
        KC_F11,    KC_F12,    KC_HOME,   C(KC_END), C(KC_LEFT),C(KC_RGHT),G(KC_DOWN),KC_HYPR,   KC_LALT,                                               KC_SPC,                                                KC_RGUI,  KC_HYPR,    KC_RALT,   KC_LEFT,   KC_DOWN,   KC_RGHT,   KC_DEL,    KC_P0,     KC_PDOT,   KC_ENTER
    ),
    [1] = LAYOUT_modern(
        _______,              _______,              _______,              _______,              _______,              _______,              _______,              _______,              _______,              _______,              _______,              _______,              _______,              _______,
        _______,              _______,              _______,              _______,              _______,              _______,              _______,              _______,              _______,              _______,              _______,              _______,              _______,              _______,
        _______,   _______,   _______,   _______,   QK_BOOT,              _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,              _______,   _______,   _______,   _______,

        _______,   _______,   _______,   _______,   _______,              _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,   _______,              _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,              _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,              _______,   _______,              _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,              _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,              _______,   _______,   _______,              _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,                                               _______,                                               _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______
    ),
};
