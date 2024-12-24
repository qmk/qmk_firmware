//  Copyright 2023 NaturalZh (@NaturalZh)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
enum layer_names {
    _WIN,
    _MAC,
    _WIN_INDEX,
    _MAC_INDEX
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_WIN] =  LAYOUT_all(
         KC_ESC,              KC_F1,    KC_F2,    KC_F3,    KC_F4,       KC_F5,     KC_F6,     KC_F7,    KC_F8,           KC_F9,   KC_F10,   KC_F11,    KC_F12,   KC_MUTE,
         KC_GRV,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,        KC_6,     KC_7,       KC_8,     KC_9,            KC_0,  KC_MINS,   KC_EQL,   KC_BSPC,    KC_INS,  KC_HOME,   KC_PGUP,
         KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,        KC_Y,     KC_U,       KC_I,     KC_O,            KC_P,  KC_LBRC,  KC_RBRC,   KC_BSLS,    KC_DEL,   KC_END,   KC_PGDN,
        KC_CAPS,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,        KC_H,     KC_J,       KC_K,     KC_L,         KC_SCLN,  KC_QUOT,              KC_ENT,
        KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,        KC_N,     KC_M,    KC_COMM,   KC_DOT,         KC_SLSH,                       KC_RSFT,               KC_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,             KC_SPC,   KC_SPC,                 KC_SPC,             KC_RALT,  MO(_WIN_INDEX),   KC_APP,             KC_RCTL,   KC_LEFT,  KC_DOWN,    KC_RGHT
    ),

     [_MAC] =  LAYOUT_all(
        _______,             KC_F14,   KC_F15, C(KC_UP),  G(KC_D),   G(KC_SPC), LAG(KC_EJCT),    KC_MPRV,  KC_MPLY,        KC_MNXT,   KC_MUTE,  KC_VOLD,  KC_VOLU,    KC_MUTE,
         KC_GRV,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,        KC_6,         KC_7,       KC_8,     KC_9,           KC_0,   KC_MINS,   KC_EQL,  KC_BSPC,     KC_INS,  KC_HOME,   KC_PGUP,
         KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,        KC_Y,         KC_U,       KC_I,     KC_O,           KC_P,   KC_LBRC,  KC_RBRC,  KC_BSLS,     KC_DEL,   KC_END,   KC_PGDN,
        KC_CAPS,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,        KC_H,         KC_J,       KC_K,     KC_L,        KC_SCLN,   KC_QUOT,             KC_ENT,
        KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,        KC_N,         KC_M,    KC_COMM,   KC_DOT,        KC_SLSH,                       KC_RSFT,                KC_UP,
        KC_LCTL,  KC_LALT,  KC_LGUI,             KC_SPC,   KC_SPC,                    KC_SPC,              KC_RCMD, MO(_MAC_INDEX),  KC_RALT,             KC_RCTL,    KC_LEFT,  KC_DOWN,    KC_RGHT
    ),

    [_WIN_INDEX] =  LAYOUT_all(
        _______,             KC_F14,   KC_F15, G(KC_TAB),  KC_WSCH, G(C(KC_S)),   KC_SLEP,   KC_MPRV,  KC_MPLY,    KC_MNXT,   KC_MUTE,  KC_VOLD,     KC_VOLU,    RM_TOGG,
        _______,  _______,  _______,  _______,  _______,  _______,    _______,   _______,   _______,  _______,    RM_TOGG,  RM_PREV,   RM_NEXT,      KC_DEL,     KC_INS,  KC_HOME,   KC_PGUP,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,   _______,  _______,     _______,     KC_DEL,   KC_END,   KC_PGDN,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,   _______,               _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,                          _______,              RM_VALU,
        _______,  _______,  _______,            _______,  _______,                _______,             _______,    _______,   _______,               _______,    RM_SPDD,  RM_VALD,   RM_SPDU
    ),

    [_MAC_INDEX] = LAYOUT_all(
        _______,              KC_F1,    KC_F2,    KC_F3,    KC_F4,       KC_F5,     KC_F6,     KC_F7,    KC_F8,      KC_F9,       KC_F10,   KC_F11,   KC_F12,    RM_TOGG,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    RM_TOGG,     RM_PREV,   RM_NEXT,   KC_DEL,     KC_INS,  KC_HOME,   KC_PGUP,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,      _______,  _______,  _______,     KC_DEL,   KC_END,   KC_PGDN,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,      _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,                          _______,              RM_VALU,
        _______,  _______,  _______,            _______,  _______,                _______,             _______,    _______,      _______,            _______,    RM_SPDD,  RM_VALD,   RM_SPDU
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_WIN] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_MAC] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_WIN_INDEX] = { ENCODER_CCW_CW(RM_VALD, RM_VALU)},
    [_MAC_INDEX] = { ENCODER_CCW_CW(RM_VALD, RM_VALU)}
};
#endif

#if defined(DIP_SWITCH_MAP_ENABLE)
const uint16_t PROGMEM dip_switch_map[NUM_DIP_SWITCHES][NUM_DIP_STATES] = {
    DIP_SWITCH_OFF_ON(DF(0), DF(1)),
};
#endif
