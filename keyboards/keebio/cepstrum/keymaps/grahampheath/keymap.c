// Copyright 2023 Danny Nguyen (danny@keeb.io)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// #include "g/keymap_combo.h"
#include "features/mouse_turbo_click.h"
enum {
    _ALPHA,   // default
    _SPECIAL, // special characters
    _CONTROL, // special characters
    _NUMBERS,  // numbers/function/motion
    TURBO,
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_mouse_turbo_click(keycode, record, TURBO)) { return false; }
  // Your macros ...

  return true;
}

const uint16_t PROGMEM sdBspc[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM weEsc[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM dfTab[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM jkCol[] = {KC_J, KC_K, COMBO_END};

const uint16_t PROGMEM opBacksl[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM hjLess[] =   {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM klGreat[] = {KC_L, KC_K, COMBO_END};
const uint16_t PROGMEM xcAlt[] = {KC_C, KC_X, COMBO_END};
const uint16_t PROGMEM mcUnds[] = {KC_COMM, KC_M, COMBO_END};
const uint16_t PROGMEM nmQuot[] = {KC_M, KC_N, COMBO_END};
const uint16_t PROGMEM gbClic[] = {KC_B, KC_G, COMBO_END};
const uint16_t PROGMEM fvClic[] = {KC_V, KC_F, COMBO_END};


combo_t key_combos[] = {
    COMBO(sdBspc, KC_BSPC),
    COMBO(weEsc, KC_ESC),
    COMBO(dfTab, KC_TAB),
    COMBO(jkCol, KC_COLN),
        
    COMBO(hjLess, KC_LT),
    COMBO(klGreat, KC_GT),
    COMBO(xcAlt, KC_LALT),
    COMBO(mcUnds, KC_UNDS),
    COMBO(nmQuot, KC_QUOT),
    COMBO(gbClic, KC_BTN1),
    COMBO(fvClic, KC_BTN2),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ALPHA] = LAYOUT_65xt(
    KC_F1,   KC_F2,   QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
    KC_F3,   KC_F4,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
    KC_F5,   KC_F6,   KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
    KC_F7,   KC_F8,   KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN,
    KC_F9,   KC_F10,  LT(_CONTROL, KC_MS_BTN1), KC_LCTL, KC_LALT, MT(MOD_LGUI, KC_ENT), LT(_SPECIAL, KC_SPC),     LT(_NUMBERS, KC_SPC),  KC_RALT, MO(_CONTROL),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
  ),
  [_CONTROL] = LAYOUT_65xt(
    RGB_HUI, RGB_HUD, KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
    RGB_SAI, RGB_SAD, RGB_TOG, RGB_MOD, KC_UP,   _______, QK_BOOT, EE_CLR,  _______, _______, _______, _______, _______, _______, _______, _______, KC_END,
    RGB_VAI, RGB_VAD, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______, _______, _______,          _______, _______, _______, _______, _______, _______, EE_CLR,  _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______, _______
  ),
  [_SPECIAL] = LAYOUT_65xt(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PIPE, KC_GRV,  KC_TILD, KC_LCBR, KC_RCBR, KC_BSLS, _______, _______, _______, _______,
    _______, _______, _______, KC_LBRC, KC_RBRC, KC_LEFT, KC_RGHT, KC_UP,   KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_QUOT, _______,          _______, _______,
    _______, _______, _______,          KC_PERC, KC_CIRC, KC_LPRN, KC_RPRN, KC_DOWN, KC_AMPR, KC_EQL,  KC_LBRC, KC_RBRC, KC_MINS, _______, _______, _______,
    _______, _______, TURBO,   _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______, _______
  ),
  [_NUMBERS] = LAYOUT_65xt(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,     KC_8,    KC_9,    KC_0,    _______, _______, _______, _______,
    _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_VOLU, _______, _______, _______, _______,
    _______, _______, _______,          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MPLY, KC_MNXT, KC_VOLD,          _______, _______,
    _______, _______, QK_BOOT, _______, _______, _______, _______,                            KC_MPLY, KC_MNXT, _______, _______, _______, _______, _______
  ),
};
