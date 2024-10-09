// Copyright 2024 SDK (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _BL = 0,
    _FL,
    _MBL,
    _MFL,
    _FBL, 
    _FFL,
    _FMBL,
    _FMFL,
    _DEFA
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BL] = LAYOUT_65_ansi( /* win Base */
        KC_ESC,   KC_1,       KC_2,       KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,      KC_MINS,  KC_EQL,   KC_BSPC,   KC_DEL,
        KC_TAB,   KC_Q,       KC_W,       KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,      KC_LBRC,  KC_RBRC,  KC_BSLS,   KC_INS,
        KC_CAPS,  KC_A,       KC_S,       KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,   KC_QUOT,            KC_ENT,    KC_PGUP, 
        KC_LSFT,              KC_Z,       KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,    KC_SLSH,  KC_RSFT,  KC_UP,     KC_PGDN,
        KC_LCTL,  KC_LCMD,    KC_LALT,                                  KC_SPC,                       KC_RALT,  MO(_FL),   KC_RCTL,  KC_LEFT,  KC_DOWN,   KC_RGHT),  
    [_FL] = LAYOUT_65_ansi( /* win FN */
        EE_CLR,   KC_F1,      KC_F2,      KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,   KC_F12,   KC_BATQ,   RGB_MOD,
        _______,  KC_BT1,     KC_BT2,     KC_BT3,   KC_2G4,   KC_USB,   _______,  KC_PSCR,  KC_SCRL,  KC_PAUS,  _______,   _______,  _______,  _______,   RGB_HUI,
        _______,  KC_NO,      TO(_MBL),   _______,  _______,  _______,  _______,  _______,  KC_HOME,  KC_END,   _______,   _______,            _______,   RGB_TOG,
        _______,              _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  MO(_DEFA),RGB_VAI,   _______,
        _______,  GU_TOGG,    _______,                                  _______,                      _______,  _______,   KC_FTOG,  RGB_SPD,  RGB_VAD,   RGB_SPI),
    [_MBL] = LAYOUT_65_ansi(  /* mac Base */
        KC_ESC,   KC_1,       KC_2,       KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,      KC_MINS,  KC_EQL,   KC_BSPC,   KC_DEL,
        KC_TAB,   KC_Q,       KC_W,       KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,      KC_LBRC,  KC_RBRC,  KC_BSLS,   KC_INS,
        KC_CAPS,  KC_A,       KC_S,       KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,   KC_QUOT,            KC_ENT,    KC_PGUP, 
        KC_LSFT,              KC_Z,       KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,    KC_SLSH,  KC_RSFT,  KC_UP,     KC_PGDN,
        KC_LCTL,  KC_LALT,    KC_LCMD,                                  KC_SPC,                       KC_RCMD,  MO(_MFL),  KC_RCTL,  KC_LEFT,  KC_DOWN,   KC_RGHT),
    [_MFL] = LAYOUT_65_ansi(  /*mac FN */
        EE_CLR,   KC_F1,      KC_F2,      KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,   KC_F12,   KC_BATQ,   RGB_MOD,
        _______,  KC_BT1,     KC_BT2,     KC_BT3,   KC_2G4,   KC_USB,   _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,   RGB_HUI,
        _______,  TO(_BL),    KC_NO,      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,            _______,   RGB_TOG,
        _______,              _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  MO(_DEFA),RGB_VAI,   _______,
        _______,  _______,    _______,                                  _______,                      _______,  _______,   KC_FTOG,  RGB_SPD,  RGB_VAD,   RGB_SPI),
    [_FBL] = LAYOUT_65_ansi( /* win L Base */
        KC_GRV,   KC_F1,      KC_F2,      KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,   KC_F12,   KC_BSPC,   KC_DEL,
        KC_TAB,   KC_Q,       KC_W,       KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,      KC_LBRC,  KC_RBRC,  KC_BSLS,   KC_INS,
        KC_CAPS,  KC_A,       KC_S,       KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,   KC_QUOT,            KC_ENT,    KC_PGUP, 
        KC_LSFT,              KC_Z,       KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,    KC_SLSH,  KC_RSFT,  KC_UP,     KC_PGDN,
        KC_LCTL,  KC_LCMD,    KC_LALT,                                  KC_SPC,                       KC_RALT,  MO(_FFL),  KC_RCTL,  KC_LEFT,  KC_DOWN,   KC_RGHT), 
    [_FFL] = LAYOUT_65_ansi( /* win L FN */
        EE_CLR,   KC_MYCM,    KC_WHOM,    KC_MAIL,  KC_CALC,  KC_MSEL,  KC_MSTP,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,   KC_VOLD,  KC_VOLU,  KC_BATQ,   RGB_MOD,
        _______,  KC_BT1,     KC_BT2,     KC_BT3,   KC_2G4,   KC_USB,   _______,  KC_PSCR,  KC_SCRL,  KC_PAUS,  _______,   _______,  _______,  _______,   RGB_HUI,
        _______,  KC_NO,      TO(_FMBL),  _______,  _______,  _______,  _______,  _______,  KC_HOME,  KC_END,   _______,   _______,            _______,   RGB_TOG,
        _______,              _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  MO(_DEFA),RGB_VAI,   _______,
        _______,  GU_TOGG,    _______,                                  _______,                      _______,  _______,   KC_FTOG,  RGB_SPD,  RGB_VAD,   RGB_SPI),
    [_FMBL] = LAYOUT_65_ansi(  /* MAC L Base */
        KC_GRV,   KC_F1,      KC_F2,      KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,   KC_F12,   KC_BSPC,   KC_DEL,
        KC_TAB,   KC_Q,       KC_W,       KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,      KC_LBRC,  KC_RBRC,  KC_BSLS,   KC_INS,
        KC_CAPS,  KC_A,       KC_S,       KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,   KC_QUOT,            KC_ENT,    KC_PGUP, 
        KC_LSFT,              KC_Z,       KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,    KC_SLSH,  KC_RSFT,  KC_UP,     KC_PGDN,
        KC_LCTL,  KC_LALT,    KC_LCMD,                                  KC_SPC,                       KC_RCMD,  MO(_FMFL),  KC_RCTL, KC_LEFT,  KC_DOWN,   KC_RGHT),
    [_FMFL] = LAYOUT_65_ansi(  /* MAC L FN */
        EE_CLR,   KC_BRID,    KC_BRIU,    CTRL_UP,  KC_SIRI,  KC_F5,    KC_F6,    KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,   KC_VOLD,  KC_VOLU,  KC_BATQ,   RGB_MOD,
        _______,  KC_BT1,     KC_BT2,     KC_BT3,   KC_2G4,   KC_USB,   _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,   RGB_HUI,
        _______,  TO(_FBL),   KC_NO,      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,            _______,   RGB_TOG,
        _______,              _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  MO(_DEFA),RGB_VAI,   _______,
        _______,  _______,    _______,                                  _______,                      _______,  _______,   KC_FTOG,  RGB_SPD,  RGB_VAD,   RGB_SPI),
    [_DEFA] = LAYOUT_65_ansi(  /* FN */
        QK_BOOT,  _______,    _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,   _______,
        _______,  _______,    _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,   _______,
        _______,  _______,    _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,            _______,   _______,
        _______,              _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,   _______,
        _______,  _______,    _______,                                  _______,                      _______,  _______,   _______,  _______,  _______,   _______),
 
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = {ENCODER_CCW_CW(_______, _______)},
    [2] = {ENCODER_CCW_CW(_______, _______)},
    [3] = {ENCODER_CCW_CW(_______, _______)},
    [4] = {ENCODER_CCW_CW(_______, _______)},
    [5] = {ENCODER_CCW_CW(_______, _______)},
    [6] = {ENCODER_CCW_CW(_______, _______)},
    [7] = {ENCODER_CCW_CW(_______, _______)},
    [8] = {ENCODER_CCW_CW(_______, _______)}
};
#endif
// clang-format on
