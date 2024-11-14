// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    LDEF,
    LSYM,
    LNUM,
    LNAV
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LDEF] = LAYOUT_split_2_3x5_4_3(
        KC_TAB,          KC_Q,          KC_W,          KC_E,           KC_R,        KC_T,                                               KC_Y,           KC_U,          KC_I,          KC_O,          KC_P,     KC_DEL,
        KC_ESC,          KC_A,          KC_S,          KC_D,           KC_F,        KC_G,                                               KC_H,           KC_J,          KC_K,          KC_L,       KC_SCLN,   KC_ENTER,
                         KC_Z,          KC_X,          KC_C,           KC_V,        KC_B,                                               KC_N,           KC_M,      KC_COMMA,        KC_DOT,      KC_QUOTE,
                OSM(MOD_LSFT), OSM(MOD_LCTL), OSM(MOD_LGUI),  OSM(MOD_LALT),   OSL(LNUM), LT(LSYM,KC_SPC), TT(LNAV),  KC_NO, LT(LSYM,KC_SPC),  KC_NO,  OSM(MOD_RALT), OSM(MOD_RGUI), OSM(MOD_RCTL),  OSM(MOD_RSFT)
    ),
    [LSYM] = LAYOUT_split_2_3x5_4_3(
        KC_NO,       KC_TILDE,        KC_GRV,         KC_NO,          KC_NO,     KC_BSLS,                                            KC_PEQL,      KC_LBRC,       KC_RBRC,       KC_QUES,      KC_SLASH,       KC_TRNS,
        KC_NO,          KC_AT,       KC_HASH,     KC_DOLLAR,     KC_PERCENT,     KC_CIRC,                                            KC_AMPR,      KC_ASTR,       KC_LPRN,       KC_RPRN,      KC_COLON,       KC_BSPC,
                   KC_EXCLAIM, KC_UNDERSCORE,      KC_MINUS,        KC_PLUS,     KC_PIPE,                                            KC_LCBR,      KC_RCBR,         KC_LT,         KC_GT,       KC_DQUO,
                      KC_TRNS,       KC_TRNS,       KC_TRNS,        KC_TRNS,     KC_TRNS,  TO(LDEF),    KC_NO,       KC_NO,   KC_NO,   KC_NO,      KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS
    ),
    [LNUM] = LAYOUT_split_2_3x5_4_3(
        KC_NO,          KC_F1,         KC_F2,         KC_F3,          KC_F4,     KC_PSCR,                                               KC_0,         KC_1,          KC_2,          KC_3,         KC_NO,       KC_TRNS,
        KC_NO,          KC_F5,         KC_F6,         KC_F7,          KC_F8,       KC_NO,                                              KC_NO,         KC_4,          KC_5,          KC_6,         KC_NO,       KC_BSPC,
                        KC_F9,        KC_F10,        KC_F11,         KC_F12,       KC_NO,                                              KC_NO,         KC_7,          KC_8,          KC_9,         KC_NO,
                      KC_TRNS,       KC_TRNS,       KC_TRNS,        KC_TRNS,     KC_TRNS,  TO(LDEF),    KC_NO,       KC_NO,   KC_NO,   KC_NO,      KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS
    ),
    [LNAV] = LAYOUT_split_2_3x5_4_3(
        KC_NO,          KC_NO,         KC_NO,         KC_NO,         KC_NO,        KC_NO,                                            KC_HOME,      KC_PGDN,       KC_PGUP,        KC_END,         KC_NO,       KC_TRNS,
        KC_NO,          KC_NO,       MS_BTN2,       MS_BTN3,       MS_BTN1,        KC_NO,                                            KC_LEFT,      KC_DOWN,         KC_UP,      KC_RIGHT,         KC_NO,       KC_BSPC,
                        KC_NO,         KC_NO,         KC_NO,         KC_NO,        KC_NO,                                      RCTL(KC_LEFT),        KC_NO,         KC_NO, RCTL(KC_RIGHT),        KC_NO,
                        KC_NO,         KC_NO,         KC_NO,         KC_NO,      KC_TRNS,  TO(LDEF), TO(LDEF),       KC_NO,   KC_NO,   KC_NO,      KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS
    )
};
