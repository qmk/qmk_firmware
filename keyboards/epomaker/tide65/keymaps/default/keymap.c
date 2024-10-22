// Copyright 2024 SDK (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "rgb_record/rgb_record.h"

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

    [_BL] = LAYOUT( /* win Base */
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,    KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,    KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_PGUP,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,    KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,   KC_PGDN, 
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,    KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,             KC_SLSH,  KC_RSFT,  KC_UP,    KC_END,
        KC_LCTL,  KC_LCMD,  KC_LALT,  KC_SPC,   KC_SPC,  KC_SPC,   KC_SPC,                       KC_RALT,            MO(_FL),  KC_LEFT,  KC_DOWN,  KC_RGHT
    ),  

    [_FL] = LAYOUT( /* win FN */
        KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,   KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,
        _______,  KC_BT1,   KC_BT2,   KC_BT3,   _______, KC_USB,   _______,  _______,  _______,  _______,  KC_2G4,   KC_HOME,  KC_SCRL,  RGB_MOD,  _______,
        _______,  KC_NO,    TO(_MBL), _______,  _______, _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,            HS_BATQ,  _______,
        _______,  RGB_TOG,  _______,  _______,  _______, _______,  _______,  _______,  RGB_HUI,  _______,            _______,  MO(_DEFA),RGB_VAI,  _______,
        KC_FTOG,  GU_TOGG,  _______,  EE_CLR,   EE_CLR,  EE_CLR,   EE_CLR,                       KC_RCTL,            _______,  RGB_SPD,  RGB_VAD,  RGB_SPI
    ),

    [_MBL] = LAYOUT(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,    KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,    KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_PGUP,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,    KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,   KC_PGDN, 
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,    KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,             KC_SLSH,  KC_RSFT,  KC_UP,    KC_END,
        KC_LCTL,  KC_LALT,  KC_LCMD,  KC_SPC,   KC_SPC,  KC_SPC,   KC_SPC,                       KC_RCMD,            MO(_MFL), KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

    [_MFL] = LAYOUT(
        KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,   KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,
        _______,  KC_BT1,   KC_BT2,   KC_BT3,   _______, KC_USB,   _______,  _______,  _______,  _______,  KC_2G4,   KC_HOME,  KC_SCRL,  RGB_MOD,  _______,
        _______,  TO(_BL),  KC_NO,    _______,  _______, _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,            HS_BATQ,  _______,
        _______,  RGB_TOG,  _______,  _______,  _______, _______,  _______,  _______,  RGB_HUI,  _______,            _______,  MO(_DEFA),RGB_VAI,  _______,
        KC_FTOG,  _______,  _______,  EE_CLR,   EE_CLR,  EE_CLR,   EE_CLR,                       KC_RCTL,            _______,  RGB_SPD,  RGB_VAD,  RGB_SPI
    ),

    [_FBL] = LAYOUT(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,   KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_BSPC,  KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,    KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_PGUP,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,    KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,   KC_PGDN, 
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,    KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,             KC_SLSH,  KC_RSFT,  KC_UP,    KC_END,
        KC_LCTL,  KC_LCMD,  KC_LALT,  KC_SPC,   KC_SPC,  KC_SPC,   KC_SPC,                       KC_RALT,            MO(_FFL), KC_LEFT,  KC_DOWN,  KC_RGHT
    ),  

    [_FFL] = LAYOUT( 
        KC_GRV,   KC_MYCM,  KC_WHOM,  KC_MAIL,  KC_CALC, KC_MSEL,  KC_MSTP,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,
        _______,  KC_BT1,   KC_BT2,   KC_BT3,   _______, KC_USB,   _______,  _______,  _______,  _______,  KC_2G4,   KC_HOME,  KC_SCRL,  RGB_MOD,  _______,
        _______,  KC_NO,    TO(_FMBL),_______,  _______, _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,            HS_BATQ,  _______,
        _______,  RGB_TOG,  _______,  _______,  _______, _______,  _______,  _______,  RGB_HUI,  _______,            _______,  MO(_DEFA),RGB_VAI,  _______,
        KC_FTOG,  GU_TOGG,  _______,  EE_CLR,   EE_CLR,  EE_CLR,   EE_CLR,                       KC_RCTL,            _______,  RGB_SPD,  RGB_VAD,  RGB_SPI
    ),

    [_FMBL] = LAYOUT(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,   KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_BSPC,  KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,    KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_PGUP,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,    KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,   KC_PGDN, 
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,    KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,             KC_SLSH,  KC_RSFT,  KC_UP,    KC_END,
        KC_LCTL,  KC_LALT,  KC_LCMD,  KC_SPC,   KC_SPC,  KC_SPC,   KC_SPC,                       KC_RCMD,            MO(_FMFL),KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

    [_FMFL] = LAYOUT(
        KC_GRV,   KC_BRID,  KC_BRIU,  KC_F3,    KC_F4,   RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,
        _______,  KC_BT1,   KC_BT2,   KC_BT3,   _______, KC_USB,   _______,  _______,  _______,  _______,  KC_2G4,   KC_HOME,  KC_SCRL,  RGB_MOD,  _______,
        _______,  TO(_FBL), KC_NO,    _______,  _______, _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,            HS_BATQ,  _______,
        _______,  RGB_TOG,  _______,  _______,  _______, _______,  _______,  _______,  RGB_HUI,  _______,            _______,  MO(_DEFA),RGB_VAI,  _______,
        KC_FTOG,  _______,  _______,  EE_CLR,   EE_CLR,  EE_CLR,   EE_CLR,                       KC_RCTL,            _______,  RGB_SPD,  RGB_VAD,  RGB_SPI
    ),

    [_DEFA] = LAYOUT(  
        KC_TILD,  _______,  _______,  _______,  _______, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______, _______,  _______,  _______,  _______,  KC_W_T,   _______,  _______,  _______,  _______,  QK_BOOT,
        _______,  _______,  _______,  _______,  _______, _______,  _______,  _______,  _______,  KC_W_T,   _______,  _______,            _______,  _______,
        _______,  _______,  _______,  _______,  _______, _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______, _______,  _______,                      _______,            _______,  _______,  _______,  _______
    ),

};

const uint16_t PROGMEM rgbrec_default_effects[RGBREC_CHANNEL_NUM][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        HS_GREEN, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________, 
        ________, ________,   HS_GREEN,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________, 
        ________, HS_GREEN,   HS_GREEN,   HS_GREEN, ________, ________, ________, ________, ________, ________, ________,   ________,           ________,  ________,
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________,             ________, ________, HS_GREEN,  ________,
        ________, ________,   ________,   ________, ________, ________, ________,                     ________,             ________, HS_GREEN, HS_GREEN,  HS_GREEN),

    [1] = LAYOUT(
        ________, HS_RED,     HS_RED,     HS_RED,   HS_RED,   HS_RED,   ________, ________, ________, ________, ________,   ________, ________, ________,  ________, 
        HS_RED,   HS_RED,     HS_RED,     HS_RED,   HS_RED,   ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________, 
        ________, HS_RED,     HS_RED,     HS_RED,   ________, HS_RED,   ________, ________, ________, ________, ________,   ________,           ________,  ________,
        HS_RED,   ________,   ________,   ________, ________, HS_RED,   ________, ________, ________, ________,             ________, ________, ________,  ________,
        HS_RED,   ________,   HS_RED,     ________, ________, ________, ________,                     ________,             ________, ________, ________,  ________),

    [2] = LAYOUT(
        ________, HS_BLUE,    HS_BLUE,    HS_BLUE,  HS_BLUE,  HS_BLUE,  HS_BLUE,  HS_BLUE,  ________, ________, ________,   ________, ________, ________,  ________, 
        ________, HS_BLUE,    HS_BLUE,    HS_BLUE,  HS_BLUE,  HS_BLUE,  ________, ________, ________, ________, ________,   ________, ________, ________,  ________, 
        ________, HS_BLUE,    HS_BLUE,    HS_BLUE,  HS_BLUE,  HS_BLUE,  ________, ________, ________, ________, ________,   ________,           ________,  ________,
        ________, ________,   ________,   HS_BLUE,  HS_BLUE,  ________, ________, ________, ________, ________,             ________, ________, ________,  ________,
        ________, ________,   ________,   ________, ________, ________, ________,                     ________,             ________, ________, ________,  ________),
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
