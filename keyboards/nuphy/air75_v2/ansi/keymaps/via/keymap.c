// Copyright 2023 Persama (@Persama)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// layer Mac
[0] = LAYOUT_ansi_84(
    KC_ESC,       KC_BRID,      KC_BRIU,      KC_MCTL,      G(KC_SPC),    MAC_VOICE,    KC_LPAD,      KC_MPRV,      KC_MPLY,      KC_MNXT,      KC_MUTE,      KC_VOLD,      KC_VOLU,      S(G(KC_4)),   KC_INS,       KC_DEL,
    KC_GRV,       KC_1,         KC_2,         KC_3,         KC_4,         KC_5,         KC_6,         KC_7,         KC_8,         KC_9,         KC_0,         KC_MINS,      KC_EQL,                     KC_BSPC,      KC_PGUP,
    KC_TAB,       KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,         KC_Y,         KC_U,         KC_I,         KC_O,         KC_P,         KC_LBRC,      KC_RBRC,                    KC_BSLS,      KC_PGDN,
    KC_CAPS,      KC_A,         KC_S,         KC_D,         KC_F,         KC_G,         KC_H,         KC_J,         KC_K,         KC_L,         KC_SCLN,      KC_QUOT,                                  KC_ENT,       KC_HOME,
    KC_LSFT,                    KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,         KC_N,         KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,                    KC_RSFT,      KC_UP,        KC_END,
    KC_LCTL,      KC_LALT,      KC_LGUI,                                                KC_SPC,                                   KC_RGUI,      MO(1),        KC_RCTL,                    KC_LEFT,      KC_DOWN,      KC_RGHT),
// layer Mac Fn
[1] = LAYOUT_ansi_84(
    _______,      KC_F1,        KC_F2,        KC_F3,        KC_F4,        KC_F5,        KC_F6,        KC_F7,        KC_F8,        KC_F9,        KC_F10,       KC_F11,       KC_F12,       S(G(KC_3)),   _______,      _______,
    _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,                    _______,      _______,
    _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,                    _______,      _______,
    _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,                                  _______,      _______,
    _______,                    _______,      _______,      _______,      _______,      _______,      _______,      _______,      RGB_SPD,      RGB_SPI,      _______,                    _______,      RGB_VAI,      _______,
    _______,      _______,      _______,                                                _______,                                  _______,      _______,      _______,                    RGB_MOD,      RGB_VAD,      RGB_HUI),
// layer win
[2] = LAYOUT_ansi_84(
    KC_ESC,       KC_F1,        KC_F2,        KC_F3,        KC_F4,        KC_F5,        KC_F6,        KC_F7,        KC_F8,        KC_F9,        KC_F10,       KC_F11,       KC_F12,       KC_PSCR,      KC_INS,       KC_DEL,
    KC_GRV,       KC_1,         KC_2,         KC_3,         KC_4,         KC_5,         KC_6,         KC_7,         KC_8,         KC_9,         KC_0,         KC_MINS,      KC_EQL,                     KC_BSPC,      KC_PGUP,
    KC_TAB,       KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,         KC_Y,         KC_U,         KC_I,         KC_O,         KC_P,         KC_LBRC,      KC_RBRC,                    KC_BSLS,      KC_PGDN,
    KC_CAPS,      KC_A,         KC_S,         KC_D,         KC_F,         KC_G,         KC_H,         KC_J,         KC_K,         KC_L,         KC_SCLN,      KC_QUOT,                                  KC_ENT,       KC_HOME,
    KC_LSFT,                    KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,         KC_N,         KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,                    KC_RSFT,      KC_UP,        KC_END,
    KC_LCTL,      KC_LGUI,      KC_LALT,                                                KC_SPC,                                   KC_RALT,      MO(3),        KC_RCTL,                    KC_LEFT,      KC_DOWN,      KC_RGHT),
// layer win Fn
[3] = LAYOUT_ansi_84(
    _______,      KC_BRID,      KC_BRIU,      _______,      _______,      _______,      _______,      KC_MPRV,      KC_MPLY,      KC_MNXT,      KC_MUTE,      KC_VOLD,      KC_VOLU,      _______,      _______,      _______,
    _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,                    _______,      _______,
    _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,                    _______,      _______,
    _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,                                  _______,      _______,
    _______,                    _______,      _______,      _______,      _______,      _______,      _______,      _______,      RGB_SPD,      RGB_SPI,      _______,                    _______,      RGB_VAI,      _______,
    _______,      _______,      _______,                                                _______,                                  _______,      _______,      _______,                    RGB_MOD,      RGB_VAD,      RGB_HUI),
};
