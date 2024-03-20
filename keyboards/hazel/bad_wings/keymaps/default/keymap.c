// Copyright 2023 Jason Hazel (@jasonhazel)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, 1, 2, 3);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x5_3(
        KC_Q,       KC_W,           KC_E,           KC_R,           KC_T,           KC_Y,       KC_U,           KC_I,       KC_O,       KC_P,         \
        KC_A,       KC_S,           KC_D,           KC_F,           KC_G,           KC_H,       KC_J,           KC_K,       KC_L,       KC_QUOT,      \
        KC_Z,       LGUI_T(KC_X),   LALT_T(KC_C),   KC_V,           KC_B,           KC_N,       KC_M,           KC_COMM,    KC_DOT,     KC_SLSH,      \
                                    KC_LCTL,        OSL(1),         OSM(MOD_LSFT),  KC_SPC,     LT(2, KC_BSPC), KC_ENT
    ),
    [1] = LAYOUT_split_3x5_3(
        KC_NO,      KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_RBRC,    KC_RCBR,        KC_RPRN,    KC_RABK,    KC_NO,        \
        KC_GRV,     KC_TILD,        KC_UNDS,        KC_EQL,         KC_NO,          KC_LBRC,    KC_LCBR,        KC_LPRN,    KC_LABK,    KC_BACKSLASH, \
        KC_NO,      KC_NO,          KC_PLUS,        KC_MINS,        KC_NO,          KC_NO,      KC_NO,          KC_COLN,    KC_DOT,     KC_SCLN,      \
                                    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,    KC_TRNS,        KC_TRNS
    ),
    [2] = LAYOUT_split_3x5_3(
        KC_EXLM,    KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,        KC_CIRC,    KC_AMPR,        KC_ASTR,    KC_PIPE,    KC_NO,        \
        KC_1,       KC_2,           KC_3,           KC_4,           KC_5,           KC_6,       KC_7,           KC_8,       KC_9,       KC_0,         \
        KC_NO,      KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,      KC_NO,          KC_NO,      KC_DOT,     KC_NO,        \
                                    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,    KC_TRNS,        KC_TRNS
    ),
    [3] = LAYOUT_split_3x5_3(
        KC_ESC,     KC_F1,          KC_F4,          KC_F7,          KC_F10,         KC_NO,      KC_HOME,        KC_UP,      KC_END,     KC_BSPC,      \
        KC_TAB,     KC_F2,          KC_F5,          KC_F8,          KC_F11,         KC_NO,      KC_LEFT,        KC_DOWN,    KC_RIGHT,   KC_ENT,       \
        KC_NO,      KC_F3,          KC_F6,          KC_F9,          KC_F12,         KC_NO,      KC_MPRV,        KC_MPLY,    KC_MNXT,    KC_DEL,       \
                                    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,    KC_TRNS,        KC_TRNS
    )
};