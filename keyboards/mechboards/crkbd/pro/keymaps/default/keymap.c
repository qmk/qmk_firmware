// Copyright 2025 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_BSPC,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                          KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_ESC,
                                        KC_LGUI, MO(1),  KC_SPC,      KC_ENT,   MO(2), KC_RALT

),

  [1] = LAYOUT_split_3x6_3(
    KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
    KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        KC_LGUI, _______, KC_SPC,      KC_ENT,  MO(3),   KC_RALT
),

  [2] = LAYOUT_split_3x6_3(
    KC_TAB,  KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
    KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV,
    KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
                                        KC_LGUI, MO(3),   KC_SPC,      KC_ENT,  _______, KC_RALT
),

  [3] = LAYOUT_split_3x6_3(
    QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    RM_NEXT, RM_HUED, RM_SATD, RM_VALD, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        KC_LGUI, _______, KC_SPC,      KC_ENT,  _______, KC_RALT
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
