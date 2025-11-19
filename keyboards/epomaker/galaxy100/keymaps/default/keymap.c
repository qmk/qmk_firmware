// Copyright 2024 Epomaker (@Epomaker)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _BL = 0,
    _FL,
    _MBL,
    _MFL,
    _FBL,
};
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BL] = LAYOUT( /* Base */
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11 ,  KC_F12,   KC_DEL,    KC_HOME,   KC_END ,   KC_PSCR, KC_PAUSE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_INS,    KC_NUM,    KC_PSLS,   KC_PAST, KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_PGUP,   KC_P7,     KC_P8,     KC_P9,   KC_PPLS,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT ,            KC_PGDN,   KC_P4,     KC_P5,     KC_P6,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,                         KC_P1,     KC_P2,     KC_P3,   KC_PENT,
        KC_LCTL,  KC_LGUI,  KC_LALT,                      KC_SPC,                                 KC_RALT,  MO(_FL),  KC_LEFT,  KC_DOWN,            KC_RGHT,              KC_P0,     KC_PDOT),

    [_FL] = LAYOUT( /* Base */
        KC_ESC,             KC_MYCM,  KC_WHOM,  KC_CALC,  KC_MAIL,  KC_MSEL,  KC_MSTP,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_DEL,    KC_HOME,   KC_END ,   KC_PSCR, KC_PAUSE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   EE_CLR,   KC_INS,    KC_NUM,    KC_PSLS,   KC_PAST, KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     RM_TOGG,  KC_Y,     KC_U,     KC_I,     MO(_FBL), KC_P,     KC_LBRC,  KC_RBRC,  RM_HUEU,  KC_PGUP,   KC_P7,     KC_P8,     KC_P9,   KC_PPLS,
        KC_CAPS,  KC_NO,    TO(_MBL), KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     MO(_FBL), KC_SCLN,  KC_QUOT,  RM_NEXT,            KC_PGDN,   KC_P4,     KC_P5,     KC_P6,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  RM_VALU,                       KC_P1,     KC_P2,     KC_P3,   KC_PENT,
        KC_LCTL,  GU_TOGG,  KC_LALT,                      KC_SPC,                                 KC_RALT,  _______,  RM_SPDD,  RM_VALD,            RM_SPDU,              KC_P0,     KC_PDOT),

    [_MBL] = LAYOUT( /* Base */
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11 ,  KC_F12,   KC_DEL,    KC_HOME,   KC_END ,   KC_PSCR, KC_PAUSE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_INS,    KC_NUM,    KC_PSLS,   KC_PAST, KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_PGUP,   KC_P7,     KC_P8,     KC_P9,   KC_PPLS,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT ,            KC_PGDN,   KC_P4,     KC_P5,     KC_P6,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,                         KC_P1,     KC_P2,     KC_P3,   KC_PENT,
        KC_LCTL,  KC_LALT,  KC_LGUI,                      KC_SPC,                                 KC_RGUI,  MO(_MFL), KC_LEFT,  KC_DOWN,            KC_RGHT,              KC_P0,     KC_PDOT),

    [_MFL] = LAYOUT( /* Base */
        KC_ESC,             KC_BRID,  KC_BRIU,  USE_TASK, USE_PRO,  KC_F5,    KC_F6,    KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_DEL,    KC_HOME,   KC_END ,   KC_PSCR, KC_PAUSE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   EE_CLR,   KC_INS,    KC_NUM,    KC_PSLS,   KC_PAST, KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     RM_TOGG,  KC_Y,     KC_U,     KC_I,     MO(_FBL), KC_P,     KC_LBRC,  KC_RBRC,  RM_HUEU,  KC_PGUP,   KC_P7,     KC_P8,     KC_P9,   KC_PPLS,
        KC_CAPS,  TO(_BL),  KC_NO,    KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     MO(_FBL), KC_SCLN,  KC_QUOT,  RM_NEXT,            KC_PGDN,   KC_P4,     KC_P5,     KC_P6,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  RM_VALU,                       KC_P1,     KC_P2,     KC_P3,   KC_PENT,
        KC_LCTL,  KC_LALT,  KC_LGUI,                      KC_SPC,                                 KC_RGUI,  _______,  RM_SPDD,  RM_VALD,            RM_SPDU,              KC_P0,     KC_PDOT ),
    [_FBL] = LAYOUT( /* Base */
        QK_BOOT,             _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______, _______,  _______, _______,
        _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______, _______,  _______, _______,
        _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______, _______,  _______, _______,
        _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,  _______, _______,  _______,
        _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                       _______, _______,  _______, _______,
        _______,  _______,   _______,                      _______,                                _______,  _______,  _______,  _______,             _______,           _______,  _______)
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = {ENCODER_CCW_CW(_______, _______)},
    [2] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [3] = {ENCODER_CCW_CW(_______, _______)},
    [4] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},

};
#endif
// clang-format on
