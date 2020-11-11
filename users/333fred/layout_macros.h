#pragma once

#define SIX_TRNS  _______, _______, _______, _______, _______, _______
#define FOUR_TRNS _______, _______, _______, _______

// Row 5: 6 keys
#define ROW5_LEFT_BASE KC_GRV,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5
#define ROW5_RGHT_BASE KC_6,    KC_7,  KC_8,  KC_9,  KC_0,  KC_MINS
#define ROW5_LEFT_SYMB _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5
#define ROW5_RGHT_SYMB KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11
#define ROW5_LEFT_VIM  SIX_TRNS
#define ROW5_RGHT_VIM  SIX_TRNS

// Row 4: 6 keys
#define ROW4_LEFT_BASE KC_TAB,  KC_Q,    KC_W,  KC_E,    KC_R,    KC_T
#define ROW4_RGHT_BASE KC_Y,    KC_U,    KC_I,  KC_O,    KC_P,    KC_BSLS
#define ROW4_LEFT_SYMB _______, KC_EXLM, KC_AT, KC_LPRN, KC_RPRN, KC_PIPE
#define ROW4_RGHT_SYMB KC_UP,   KC_7,    KC_8,  KC_9,    KC_ASTR, KC_F12
#define ROW4_LEFT_VIM  SIX_TRNS
#define ROW4_RGHT_VIM  SIX_TRNS

// Row 3: 6 keys
#define ROW3_LEFT_BASE CTL_T(KC_ESC), KC_A,    KC_S,   KC_D,     KC_F,    KC_G
#define ROW3_RGHT_BASE KC_H,          KC_J,    KC_K,   KC_L,     KC_SCLN, KC_QUOT
#define ROW3_LEFT_SYMB _______,       KC_HASH, KC_DLR, KC_LCBR,  KC_RCBR, KC_GRV
#define ROW3_RGHT_SYMB KC_DOWN,       KC_4,    KC_5,   KC_6,     KC_PLUS, _______
#define ROW3_LEFT_VIM  _______,       DLEFT,   DRIGHT, KC_LCTL,  KC_LGUI, _______
#define ROW3_RGHT_VIM  KC_LEFT,       KC_DOWN, KC_UP,  KC_RIGHT, _______, _______

// Row 2: 6 keys
#define ROW2_LEFT_BASE OSM(MOD_LSFT), CTL_T(KC_Z), KC_X,    KC_C,     KC_V,           KC_B
#define ROW2_RGHT_BASE KC_N,          KC_M,        KC_COMM, KC_DOT,   CTL_T(KC_SLSH), OSM(MOD_RSFT)
#define ROW2_LEFT_SYMB _______,       KC_PERC,     KC_CIRC, KC_LBRC,  KC_RBRC,        KC_TILD
#define ROW2_RGHT_SYMB KC_AMPR,       KC_1,        KC_2,    KC_3,     KC_BSLS,        _______
#define ROW2_LEFT_VIM  _______,       _______,     KC_TAB,  _______,  _______,        _______
#define ROW2_RGHT_VIM  SIX_TRNS

// Row 1: 4 keys
#define ROW1_LEFT_BASE OSM(MOD_LCTL), KC_F4,   KC_F5,    KC_LALT
#define ROW1_RGHT_BASE KC_DOWN,       KC_EQL,  KC_RIGHT, KC_RGUI
#define ROW1_LEFT_SYMB _______,       _______, _______,  _______
#define ROW1_RGHT_SYMB KC_0,          KC_DOT,  KC_EQL,   _______
#define ROW1_LEFT_VIM  FOUR_TRNS
#define ROW1_RGHT_VIM  FOUR_TRNS
