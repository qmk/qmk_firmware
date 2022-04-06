// Copyright 2022 Michael McCoyd (@mmccoyd)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _SYM,
    _NUM,
    _ADJUST,
};


#define LY_SYM MO(_SYM)
#define LY_NUM MO(_NUM)
#define LY_ADJ MO(_ADJUST)
#define ALT_GR OSM(MOD_RALT)

#define UNDO LCTL(KC_Z)
#define CUT  LCTL(KC_X)
#define COPY LCTL(KC_C)
#define PASTE LCTL(KC_V)
// (For OS X, you'll want to change these editing keys to LGUI(KC_Z) etc.)


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
     KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
     KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_CAPS,                      KC_ESC , KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                       KC_LCTL,          KC_LGUI, KC_LALT, KC_SPC , LY_SYM ,    LY_NUM , KC_SPC , KC_LALT, KC_RGUI,          KC_QUOT
    ),
    [_SYM] = LAYOUT(
     KC_HOME, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                                        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
     KC_END,  KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_PGUP,                                        KC_MINS, KC_EQL , KC_LBRC, KC_RBRC, KC_BSLS, _______, 
     _______, UNDO   , CUT    , COPY   , PASTE  , KC_PGDN, ALT_GR ,                      KC_APP , KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, _______,
                       _______,          _______, _______, _______, _______,    LY_ADJ , _______, _______, _______,          KC_RCTL
    ),
    [_NUM] = LAYOUT(
     KC_F11 , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                        KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______,
     KC_F12 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                                        KC_VOLU, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______, 
     _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_INS ,                      KC_MUTE, KC_VOLD, KC_LEFT, KC_UP  , KC_DOWN, KC_RGHT, KC_DEL ,
                       _______,          _______, _______, _______, LY_ADJ ,    _______, _______, _______, _______,          KC_RCTL
    ),
    [_ADJUST] = LAYOUT(
     _______, _______, _______, _______, AG_SWAP, AG_NORM,                                        _______, KC_PSCR, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,                                        RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI , _______, _______, 
     RESET  , _______, KC_BRID, KC_BRIU, _______, _______, _______,                     RGB_TOG, RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD , _______, _______,
                       _______,          _______, _______, _______, _______,    _______, _______, _______, _______,          _______
    ),
};

//  Template:
//    [_INDEX] = LAYOUT(
//     _______, _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______, 
//     _______, _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______, 
//     _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
//                       _______,          _______, _______, _______, _______,    _______, _______, _______, _______,          _______
//    ),
