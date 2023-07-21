// Copyright 2023 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
enum layer_names {
    _WIN,
    _WIN_LOCK,
    _MAC,
    _INDEX1
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_WIN] =  LAYOUT_ansi_all(
         KC_ESC,             KC_F14,   KC_F15,  _______,  KC_WSCH,     _______,   _______,   KC_MPRV,  KC_MPLY,    KC_MNXT,      KC_MUTE,  KC_VOLD,  KC_VOLU,   KC_MUTE,
         KC_GRV,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,        KC_6,     KC_7,       KC_8,     KC_9,        KC_0,     KC_MINS,   KC_EQL,   KC_BSPC,   KC_HOME,
         KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,        KC_Y,     KC_U,       KC_I,     KC_O,        KC_P,     KC_LBRC,  KC_RBRC,   KC_BSLS,    KC_DEL,
        KC_CAPS,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,        KC_H,     KC_J,       KC_K,     KC_L,     KC_SCLN,     KC_QUOT,              KC_ENT,   KC_PGUP,
        KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,        KC_N,     KC_M,    KC_COMM,   KC_DOT,     KC_SLSH,     KC_RSFT,               KC_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,             KC_SPC,   KC_SPC,      KC_SPC,   KC_SPC,              KC_RALT,       MO(3),      KC_APP,  KC_LEFT,   KC_DOWN,   KC_RGHT
    ),

    [_WIN_LOCK] =  LAYOUT_ansi_all(
        _______,            _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,      _______,  _______,  _______,   _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,      _______,  _______,  _______,   _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,      _______,  _______,  _______,   _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,      _______,            _______,   _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,      _______,            _______,
        _______,  XXXXXXX,  _______,            _______,  _______,     _______,   _______,             _______,    _______,      _______,  _______,  _______,   _______
    ),

    [_MAC] =  LAYOUT_ansi_all(
        _______,             KC_F14,   KC_F15,  _______,  _______,     _______,   _______,   _______,  _______,    _______,      _______,  _______,  _______,   _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,      _______,  _______,  _______,   _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,      _______,  _______,  _______,   _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,      _______,            _______,   _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,      _______,            _______,
        _______,  KC_LALT,  KC_LGUI,            _______,  _______,     _______,   _______,             _______,    _______,      _______,  _______,  _______,   _______
    ),

    [_INDEX1] = LAYOUT_ansi_all(
        _______,              KC_F1,    KC_F2,    KC_F3,    KC_F4,       KC_F5,     KC_F6,     KC_F7,    KC_F8,      KC_F9,       KC_F10,   KC_F11,   KC_F12,   _______,
        _______,  _______,  _______,  _______,  _______,  _______,       TO(0),     TO(2),   _______,  _______,    RGB_TOG,     RGB_RMOD,  RGB_MOD,  _______,    KC_END,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,      _______,  _______,  _______,    KC_INS,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,      _______,            _______,   KC_PGDN,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,      _______,            RGB_VAI,
        _______,    TO(1),  _______,            _______,  _______,     _______,   _______,             _______,    _______,      _______,  RGB_SPD,  RGB_VAD,   RGB_SPI
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_WIN] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_WH_L, KC_WH_R), ENCODER_CCW_CW(KC_WH_D, KC_WH_U), ENCODER_CCW_CW(KC_LEFT, KC_RIGHT) },
    [_WIN_LOCK] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS)  },
    [_MAC] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), },
    [_INDEX1] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI), ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(RGB_SPD, RGB_SPI), ENCODER_CCW_CW(RGB_SAD, RGB_SAI) }
};
#endif

