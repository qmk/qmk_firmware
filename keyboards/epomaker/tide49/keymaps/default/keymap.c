// Copyright 2025 EPOMAKER (@EPOMAKER)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "rgb_record/rgb_record.h"

enum layers {
    _BL = 0,
    _FBL,
    _FL,
    _MBL,
    _FFL,
    _MFL,
    _DEFA
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BL] = LAYOUT(
        KC_ESC ,  KC_Q,      KC_W,      KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,      KC_P,     KC_LBRC,  KC_RBRC, KC_BSPC,
        KC_TAB,   KC_A,      KC_S,      KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,      KC_SCLN,  KC_QUOT,           KC_ENT,
        KC_LSFT,  KC_Z,      KC_X,      KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,    KC_SLSH,                     KC_RSFT,
        KC_LCTL,  KC_LCMD,   KC_LALT,   KC_SPC,   KC_SPC,   KC_SPC,             KC_SPC,   KC_RALT,  KC_RCMD,   KC_RCTL,                     MO(_FL)
        ),

    [_FBL] = LAYOUT(
        KC_ESC ,  KC_F1,     KC_F2,     KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,     KC_F10,   KC_F11,   KC_F12, KC_BSPC,
        KC_TAB,   KC_A,      KC_S,      KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,      KC_SCLN,  KC_QUOT,           KC_ENT,
        KC_LSFT,  KC_Z,      KC_X,      KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,    KC_SLSH,                     KC_RSFT,
        KC_LCTL,  KC_LCMD,   KC_LALT,   KC_SPC,   KC_SPC,   KC_SPC,             KC_SPC,   KC_RALT,  KC_RCMD,   KC_RCTL,                     MO(_FL)
        ),

    [_FL] = LAYOUT(
        KC_GRV,   KC_1,      KC_2,      KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,      KC_0,     KC_MINS,  KC_EQL,  KC_DEL,
        KC_USB,   KC_BT1,    KC_BT2,    KC_BT3,   KC_2G4,   KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,   KC_VOLU,  KC_BSLS,           EE_CLR,
        _______,  LED_TOG,   HS_BATQ,   KC_CAPS,  RP_P0,    RP_END,   KC_NO,    TO(_MBL), RM_HUEU,  RM_NEXT,   RM_VALU,                     MO(_DEFA),
        KC_FTOG,  GU_TOGG,   _______,   _______,  _______,  _______,            _______,  RM_SPDD,  RM_VALD,   RM_SPDU,                     _______
        ),

    [_MBL] = LAYOUT(
        KC_ESC ,  KC_Q,      KC_W,      KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,      KC_P,     KC_LBRC,  KC_RBRC, KC_BSPC,
        KC_TAB,   KC_A,      KC_S,      KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,      KC_SCLN,  KC_QUOT,           KC_ENT,
        KC_LSFT,  KC_Z,      KC_X,      KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,    KC_SLSH,                     KC_RSFT,
        KC_LCTL,  KC_LALT,   KC_LCMD,   KC_SPC,   KC_SPC,   KC_SPC,             KC_SPC,   KC_RCMD,  KC_RALT,   KC_RCTL,                     MO(_MFL)
        ),

    [_FFL] = LAYOUT(
        KC_ESC ,  KC_F1,     KC_F2,     KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,     KC_F10,   KC_F11,   KC_F12,  KC_BSPC,
        KC_TAB,   KC_A,      KC_S,      KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,      KC_SCLN,  KC_QUOT,           KC_ENT,
        KC_LSFT,  KC_Z,      KC_X,      KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,    KC_SLSH,                     KC_RSFT,
        KC_LCTL,  KC_LALT,   KC_LCMD,   KC_SPC,   KC_SPC,   KC_SPC,             KC_SPC,   KC_RCMD,  KC_RALT,   KC_RCTL,                     MO(_MFL)
        ),

    [_MFL] = LAYOUT(
        KC_GRV,   KC_1,      KC_2,      KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,      KC_0,     KC_MINS,  KC_EQL,  KC_DEL,
        KC_USB,   KC_BT1,    KC_BT2,    KC_BT3,   KC_2G4,   KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,   KC_VOLU,  KC_BSLS,           EE_CLR,
        _______,  LED_TOG,   HS_BATQ,   KC_CAPS,  RP_P0,    RP_END,   TO(_BL),  KC_NO,    RM_HUEU,  RM_NEXT,   RM_VALU,                     MO(_DEFA),
        KC_FTOG,  GU_TOGG,   _______,   _______,  _______,  _______,            _______,  RM_SPDD,  RM_VALD,   RM_SPDU,                     _______
        ),

    [_DEFA] = LAYOUT(
        KC_TILD,  _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  KC_TEST,   _______,   _______,  _______, QK_BOOT,
        _______,  _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  KC_TEST,   _______,   _______,           _______,
        _______,  _______,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,                      _______,
        _______,  _______,   _______,   _______,  _______,  KC_PGUP,            _______,  _______,  _______,   _______,                      _______
        ),
};

const uint16_t PROGMEM rgbrec_default_effects[RGBREC_CHANNEL_NUM][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        ________, ________,  HS_GREEN,  ________, ________, ________, ________, ________, ________, ________,  ________,  ________, ________,________,
        ________, HS_GREEN,  HS_GREEN,  HS_GREEN, ________, ________, ________, ________, ________, ________,  ________,  ________,          ________,
        ________, ________,  ________,  ________, ________, ________, ________, ________, ________, ________,  HS_GREEN,                     ________,
        ________, ________,  ________,  ________, ________, ________,           ________, HS_GREEN, HS_GREEN,  HS_GREEN,                     ________
        ),

    [1] = LAYOUT(
        ________, ________,  HS_RED,    ________, ________, ________, ________, ________, ________, ________,  ________,  ________, ________,________,
        ________, HS_RED,    HS_RED,    HS_RED,   ________, ________, ________, ________, ________, ________,  ________,  ________,          ________,
        ________, ________,  ________,  ________, ________, ________, ________, ________, ________, ________,  HS_RED,                       ________,
        ________, ________,  ________,  ________, ________, ________,           ________, HS_RED,   HS_RED,    HS_RED,                       ________
        ),

    [2] = LAYOUT(
        ________, ________,  HS_BLUE,   ________, ________, ________, ________, ________, ________, ________,  ________,  ________, ________,________,
        ________, HS_BLUE,   HS_BLUE,   HS_BLUE,  ________, ________, ________, ________, ________, ________,  ________,  ________,          ________,
        ________, ________,  ________,  ________, ________, ________, ________, ________, ________, ________,  HS_BLUE,                      ________,
        ________, ________,  ________,  ________, ________, ________,           ________, HS_BLUE,  HS_BLUE,   HS_BLUE,                      ________
        ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = {ENCODER_CCW_CW(_______, _______)},
    [2] = {ENCODER_CCW_CW(_______, _______)},
    [3] = {ENCODER_CCW_CW(_______, _______)},
    [4] = {ENCODER_CCW_CW(_______, _______)},
    [5] = {ENCODER_CCW_CW(_______, _______)},
    [6] = {ENCODER_CCW_CW(_______, _______)}
};
#endif
// clang-format on
