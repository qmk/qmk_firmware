// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x5_3(
    KC_Q,         KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    SFT_T(KC_A),  KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    SFT_T(KC_SCLN),
    CTL_T(KC_Z),  KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  CTL_T(KC_SLSH),
                  LT(3, KC_LGUI),   MO(1),   KC_SPC,       KC_BSPC, MO(2),   KC_ENT
  ),

  [1] = LAYOUT_split_3x5_3(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_ESC,  KC_TAB,  KC_CAPS, KC_TILD, KC_GRV,       KC_QUOT, KC_DQUO, KC_MPRV, KC_MPLY, KC_MNXT,
                      KC_LGUI, KC_TRNS, KC_SPC,       KC_ENT,  KC_TRNS, KC_RALT
  ),

  [2] = LAYOUT_split_3x5_3(
    KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,      KC_PSCR, KC_DEL,  KC_INS,   KC_HOME, KC_END,
    KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,      KC_LEFT, KC_DOWN, KC_RIGHT, KC_UP,   KC_VOLU,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,    KC_F9,   KC_VOLD,
                      KC_PGDN, KC_TRNS, KC_SPC,       KC_ENT,  KC_TRNS, KC_PGUP
  ),
  [3] = LAYOUT_split_3x5_3(
    QK_BOOT,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      RGB_TOG,  RGB_HUD, RGB_HUI, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      RGB_MOD,  RGB_SAD, RGB_SAI, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      RGB_RMOD, RGB_VAD, RGB_VAI, XXXXXXX, XXXXXXX,
                      KC_TRNS, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX
  )
};
