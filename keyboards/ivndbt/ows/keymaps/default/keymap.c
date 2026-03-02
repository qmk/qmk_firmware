// Copyright 2026 ivndbt
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Layers declarations
enum layers {
    _PLOVER,
    _LOWER,
    _RAISE,
    _CONTROL,
    _QWERTY
};

#define LOWER TL_LOWR
#define RAISE TL_UPPR
#define QWERTY TG(_QWERTY)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_PLOVER] = LAYOUT(
    LOWER,  STN_S1, STN_TL, STN_PL, STN_HL, STN_ST1,    STN_ST3, STN_FR, STN_PR, STN_LR, STN_TR, STN_DR,
    RAISE,  STN_S2, STN_KL, STN_WL, STN_RL, STN_ST2,    STN_ST4, STN_RR, STN_BR, STN_GR, STN_SR, STN_ZR,
                            STN_N1, STN_A,  STN_O,      STN_E,   STN_U,  STN_N2
  ),

[_LOWER] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  KC_DEL,   KC_ESC,   _______,  KC_UP,    _______,  KC_PGUP,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  KC_TAB,   KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_PGDN,  _______,
                                  _______,  _______,  _______,  KC_HOME,  KC_END,   _______
  ),

[_RAISE] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_BRID,  KC_BRIU,  _______,  _______,  _______,
                                  _______,  _______,  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT
  ),

[_CONTROL] = LAYOUT(
    _______,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  QK_BOOT,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  QWERTY,
    _______,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  QK_RBT,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                    XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX
  ),

[_QWERTY] = LAYOUT(
    KC_BSPC,  KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, QWERTY,
    KC_SPC,   KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_Z, KC_ENT,
                          KC_X, KC_C, KC_V, KC_B, KC_N, KC_M
  )
};
