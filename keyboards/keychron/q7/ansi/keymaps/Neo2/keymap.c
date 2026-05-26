/* Copyright 2021 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#include QMK_KEYBOARD_H

// clang-format off

enum layers {
    MAC_BASE,
    WIN_BASE,
    _FN1,       // Sonderzeichen Mac (Caps auf Mac)
    _FN1_WIN,   // Sonderzeichen Windows (Caps auf Win)
    _FN2,       // Numpad + Pfeile (Taste rechts neben Space)
    _FN3        // RGB / F-Tasten
};

// Custom Keycodes für < > auf ANSI-Layouts unter deutschem OS
enum custom_keycodes {
    NEO_LT = SAFE_RANGE,  // '<'
    NEO_GT,               // '>'
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // macOS: Neo-Buchstaben, Caps = Sonderzeichen-Layer (Mac), RCmd = Numpad-Layer
    [MAC_BASE] = LAYOUT_ansi_72(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS, KC_EQL,   KC_BSPC,           KC_INS,  RM_NEXT,
        KC_TAB,   KC_X,     KC_V,     KC_L,     KC_C,     KC_W,     KC_K,     KC_H,     KC_G,     KC_F,     KC_Q,     KC_MINS, KC_EQL,   KC_BSLS,           KC_END,  KC_DEL,
        MO(_FN1), KC_U,     KC_I,     KC_A,     KC_E,     KC_O,     KC_S,     KC_N,     KC_R,     KC_T,     KC_D,     KC_Z,                KC_ENT,            KC_HOME, KC_PGUP,
        KC_LSFT,            KC_LBRC,  KC_SCLN,  KC_QUOT,  KC_P,     KC_Y,     KC_B,     KC_M,     KC_COMM,  KC_DOT,   KC_J,               KC_RSFT,           KC_UP,   KC_PGDN,
        KC_LCTL,  KC_LOPT,  KC_LCMD,                                KC_SPC,                                  MO(_FN2), KC_RCTL, KC_RALT,  MO(_FN3), KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // Windows: gleiche Logik, aber Caps verweist auf _FN1_WIN
    [WIN_BASE] = LAYOUT_ansi_72(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS, KC_EQL,   KC_BSPC,           KC_INS,  RM_NEXT,
        KC_TAB,   KC_X,     KC_V,     KC_L,     KC_C,     KC_W,     KC_K,     KC_H,     KC_G,     KC_F,     KC_Q,     KC_MINS, KC_EQL,   KC_BSLS,           KC_END,  KC_DEL,
        MO(_FN1_WIN), KC_U, KC_I,     KC_A,     KC_E,     KC_O,     KC_S,     KC_N,     KC_R,     KC_T,     KC_D,     KC_Z,                KC_ENT,            KC_HOME, KC_PGUP,
        KC_LSFT,            KC_LBRC,  KC_SCLN,  KC_QUOT,  KC_P,     KC_Y,     KC_B,     KC_M,     KC_COMM,  KC_DOT,   KC_J,               KC_RSFT,           KC_UP,   KC_PGDN,
        KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                  MO(_FN2), KC_RCTL, KC_RALT,  MO(_FN3), KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // _FN1: Sonderzeichen-Layer - TRANSLATION FÜR MAC (Deutsches OS)
    [_FN1] = LAYOUT_ansi_72(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        // Reihe 1: …          _             [            ]            ^       !        <       >       =            &            /            _______
        _______, LALT(KC_DOT), LSFT(KC_SLSH), LALT(KC_5), LALT(KC_6), KC_GRV, LSFT(KC_1), NEO_LT, NEO_GT, LSFT(KC_0),  LSFT(KC_6),  LSFT(KC_7),  _______, _______, _______, _______,
        // Reihe 2: \                  /            {            }            * ?            (            )            -            :            @
        _______, LALT(LSFT(KC_7)), LSFT(KC_7),  LALT(KC_8),  LALT(KC_9),  LSFT(KC_RBRC), LSFT(KC_MINS), LSFT(KC_8), LSFT(KC_9),  KC_SLSH,     LSFT(KC_DOT), LALT(KC_L), _______, _______, _______,
        // Reihe 3: #          ~            `             +            %            "            '            ;            ,            .
        _______,            KC_BSLS, LALT(KC_N), LSFT(KC_EQL), KC_RBRC,     LSFT(KC_5),  LSFT(KC_2),  LSFT(KC_BSLS), LSFT(KC_COMMA), KC_COMMA, KC_DOT,               _______,           _______, _______,
        _______, _______,  _______,                                _______,                                   _______,  _______,  _______,  _______,  _______, _______, _______
    ),

    // _FN1_WIN: Sonderzeichen-Layer - TRANSLATION FÜR WINDOWS (Deutsches OS)
    [_FN1_WIN] = LAYOUT_ansi_72(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        // Reihe 1: …          _             [            ]            ^       !        <       >       =            &            /            _______
        _______, RALT(KC_DOT), LSFT(KC_SLSH), RALT(KC_8), RALT(KC_9), KC_GRV, LSFT(KC_1), NEO_LT, NEO_GT, LSFT(KC_0),  LSFT(KC_6),  LSFT(KC_7),  _______, _______,  _______, _______,
        // Reihe 2: \              /            {            }            *             ?            (            )            -            :            @
        _______, RALT(KC_MINS), LSFT(KC_7),  RALT(KC_7),  RALT(KC_0),  LSFT(KC_RBRC), LSFT(KC_MINS),  LSFT(KC_8),  LSFT(KC_9),  KC_SLSH,     LSFT(KC_DOT), RALT(KC_Q), _______, _______, _______,
        // Reihe 3: #          ~             `             +            %            "            '            ;            ,            .
        _______,            KC_BSLS, RALT(KC_EQL),  KC_GRV,    KC_EQL,      LSFT(KC_5),  LSFT(KC_2),  LSFT(KC_BSLS), LSFT(KC_COMMA), KC_COMMA, KC_DOT,               _______,           _______, _______,
        _______, _______,  _______,                                 _______,                                   _______,  _______,  _______,  _______,  _______, _______, _______
    ),

    // _FN2: Numpad + Pfeile (Taste rechts neben Space)
    [_FN2] = LAYOUT_ansi_72(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, KC_UP,   _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   _______, _______, _______, _______,          _______, _______,
        _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_P4,   KC_P5,   KC_P6,   _______, _______,          _______,          _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   _______,          _______,          _______, _______,
        _______,  _______,  _______,                                KC_P0,                                   _______,  _______,  _______,  _______,  _______, _______, _______
    ),

    // _FN3: Keychron-RGB/F-Key-Layer
    [_FN3] = LAYOUT_ansi_72(
        KC_GRAVE, KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,  KC_F12,   _______,           _______, _______,
        RM_TOGG,  RM_NEXT,  RM_VALU,  RM_HUEU,  RM_SATU,  RM_SPDU,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,           _______, _______,
        _______,  RM_PREV,  RM_VALD,  RM_HUED,  RM_SATD,  RM_SPDD,  _______,  _______,  _______,  _______,  _______,  _______,             _______,           _______, _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,           _______, _______,
        _______,  _______,  _______,                                _______,                                  _______,  _______,  _______,  _______,  _______, _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case NEO_LT:
                register_code16(KC_NONUS_BACKSLASH); 
                return false;
            case NEO_GT:
                register_code16(LSFT(KC_NONUS_BACKSLASH));
                return false;
        }
    } else {
        switch (keycode) {
            case NEO_LT:
                unregister_code16(KC_NONUS_BACKSLASH);
                return false;
            case NEO_GT:
                unregister_code16(LSFT(KC_NONUS_BACKSLASH));
                return false;
        }
    }
    return true;
}