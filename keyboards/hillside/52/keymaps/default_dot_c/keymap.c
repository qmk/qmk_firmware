// Copyright 2022 Michael McCoyd (@mmccoyd)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _NAV,
    _SYM,
    _ADJUST,
};

#define xxxxxxx KC_NO

#define LY_NAV MO(_NAV)
#define LY_SYM MO(_SYM)
#define LY_ADJ MO(_ADJUST)
#define ALT_GR OSM(MOD_RALT)
#define OSM_SFT OSM(MOD_LSFT)
#define PLY_PAU  KC_MEDIA_PLAY_PAUSE

#define UNDO LCTL(KC_Z)
#define CUT  LCTL(KC_X)
#define COPY LCTL(KC_C)
#define PASTE LCTL(KC_V)
#define REDO LCTL(KC_Y)
// (For OS X, you'll want to change these editing keys to LGUI(KC_Z) etc.)


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
     KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
     KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_QUOT,                      KC_SLSH, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_RSFT,
     KC_MUTE, KC_ESC,  KC_LCTL,          KC_LGUI, KC_LALT, OSM_SFT, LY_NAV,     LY_SYM , KC_SPC , KC_LALT, KC_RGUI,          KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_NAV] = LAYOUT(
     COPY   , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                        KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______,
     CUT    , KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, PASTE  ,                                        KC_PGUP, KC_LEFT, KC_UP  , KC_DOWN, KC_RGHT, KC_PGDN,
     _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , UNDO   ,                      REDO   , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_TRNS,
     KC_F11 , KC_F12 , KC_LCTL,          _______, _______, _______, _______,    LY_ADJ , _______, _______, _______,          KC_RCTL, KC_HOME, KC_END
    ),
    [_SYM] = LAYOUT(
     KC_INS,  KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                                        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
     CW_TOGG, KC_BSLS, KC_MINS, KC_EQL , KC_LBRC, KC_RBRC,                                        KC_VOLU, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
     _______, KC_PIPE, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_MPLY,                      KC_MUTE, KC_VOLD, KC_0   , KC_1   , KC_2   , xxxxxxx, _______,   
     xxxxxxx, xxxxxxx, _______,          _______, _______, _______, LY_ADJ ,    _______, _______, _______, _______,          KC_RCTL, KC_APP, ALT_GR
    ),
    [_ADJUST] = LAYOUT(
     xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, AG_SWAP, CG_SWAP,                                        xxxxxxx, KC_PSCR, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,
     xxxxxxx, xxxxxxx, KC_BRIU, xxxxxxx, AG_NORM, CG_NORM,                                        UG_NEXT, UG_VALU, UG_HUEU, UG_SATU, xxxxxxx, xxxxxxx, 
     QK_BOOT, xxxxxxx, KC_BRID, xxxxxxx, xxxxxxx, xxxxxxx, EE_CLR,                       UG_TOGG, UG_PREV, UG_VALD, UG_HUED, UG_SATD, xxxxxxx, xxxxxxx,
     XXXXXXX, xxxxxxx, xxxxxxx,          xxxxxxx, xxxxxxx, xxxxxxx, _______,    _______, xxxxxxx, xxxxxxx, xxxxxxx,          xxxxxxx, xxxxxxx, xxxxxxx 
    ),
};

//  Template:
//    [_INDEX] = LAYOUT(
//     _______, _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______, 
//     _______, _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______, 
//     _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
//     _______, _______, _______,          _______, _______, _______, _______,    _______, _______, _______, _______,          _______, _______, _______
//    ),
