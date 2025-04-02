// Copyright 2025 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,   KC_P, NO_ARNG,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,   NO_OSTR, KC_ESC,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                          KC_N,    KC_M,    KC_COMM, KC_DOT, NO_MINS, KC_BSPC,
                                        KC_LGUI, MO(1),  KC_SPC,      KC_ENT,   MO(2), KC_LALT

),

  [1] = LAYOUT_split_3x6_3(
    KC_TAB,  XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX,                       NO_PLUS, KC_7, KC_8, KC_9, XXXXXXX, XXXXXXX,
    KC_LCTL, KC_LEFT, KC_DOWN, KC_RIGHT,XXXXXXX, NO_BSLS,                       NO_MINS, KC_4, KC_5, KC_6, XXXXXXX, XXXXXXX,
    KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, NO_SLSH,                       KC_0, KC_1, KC_2, KC_3,XXXXXXX, KC_DEL,
                                        KC_LGUI, _______, KC_SPC,      KC_ENT,  MO(3),   KC_LALT
),

  [2] = LAYOUT_split_3x6_3(
    KC_TAB,  XXXXXXX,   NO_AT, NO_HASH,  NO_DLR, NO_PERC,                       NO_CIRC, NO_AMPR, NO_ASTR, NO_TILD, XXXXXXX, XXXXXXX,
    KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, NO_EXLM, NO_QUOT,                       NO_EQL, NO_LPRN,  NO_LBRC, NO_LCBR, NO_GRV, XXXXXXX,
    KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, NO_LABK, NO_DQUO,                       NO_UNDS, NO_RPRN, NO_RBRC, NO_RCBR, NO_PIPE, KC_BSPC,
                                        KC_LGUI, MO(3),   KC_SPC,      KC_ENT,  _______, KC_LALT
),

  [3] = LAYOUT_split_3x6_3(
    QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    RM_NEXT, RM_HUED, RM_SATD, RM_VALD, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        KC_LGUI, _______, KC_SPC,      KC_ENT,  _______, KC_LALT
)
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
[0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT)},
[1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
[2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
[3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS)}
};
#endif

// clang-format on
