// Copyright 2025 Jakob Linke
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum Layers {
  kBase = 0,
  kOneHand,
  kNavigation,
  kNumbers,
  kFnKeys,
  kSymbols,
};

enum CustomKeycodes {
  HRM_A   = LGUI_T(KC_A),
  HRM_R   = LALT_T(KC_R),
  HRM_S   = LCTL_T(KC_S),
  HRM_T   = LSFT_T(KC_T),
  HRM_N   = LSFT_T(KC_N),
  HRM_E   = LCTL_T(KC_E),
  HRM_I   = LALT_T(KC_I),
  HRM_O   = LGUI_T(KC_O),
  BTN_ESC = LT(kOneHand, KC_ESC),
  NAV_SPC = LT(kNavigation, KC_SPC),
  NM2_TAB = LT(kNumbers, KC_TAB),
  NUM_DEL = KC_DEL,
  FUN_ENT = LT(kFnKeys, KC_ENT),
  SYM_BSP = LT(kSymbols, KC_BSPC),
  WSP_L   = G(KC_PGUP),
  WSP_R   = G(KC_PGDN),
  TAB_L   = C(KC_PGUP),
  TAB_R   = C(KC_PGDN),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [kBase] = LAYOUT(
        KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,          KC_J,     KC_L,     KC_U,     KC_Y,     KC_SCLN,
        HRM_A,    HRM_R,    HRM_S,    HRM_T,    KC_G,          KC_M,     HRM_N,    HRM_E,    HRM_I,    HRM_O,
        KC_Z,     KC_X,     KC_C,     KC_D,     KC_V,          KC_K,     KC_H,     KC_COMM,  KC_DOT,   KC_UNDS,
                  _______,  BTN_ESC,  NAV_SPC,  NM2_TAB,       FUN_ENT,  SYM_BSP,  NUM_DEL,  _______
    ),

    [kOneHand] = LAYOUT(
        C(KC_A),  C(KC_W),  A(KC_TAB),C(KC_T),  XXXXXXX,       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        WSP_L,    TAB_L,    TAB_R,    WSP_R,    KC_ENT,        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        C(KC_Z),  C(KC_X),  C(KC_C),  XXXXXXX,  C(KC_V),       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______
    ),

    [kNavigation] = LAYOUT(
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,       KC_PGUP,  _______,  _______,  _______,  XXXXXXX,
        KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXXX,       KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,
        _______,  _______,  _______,  _______,  XXXXXXX,       _______,  KC_HOME,  _______,  _______,  KC_END,
                  _______,  _______,  _______,  _______,       KC_ENT,   KC_BSPC,  KC_DEL,   _______
    ),

    [kNumbers] = LAYOUT(
        QK_BOOT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,       XXXXXXX,  KC_7,     KC_8,     KC_9,     XXXXXXX,
        KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXXX,       S(KC_G),  KC_1,     KC_2,     KC_3,     KC_0,
        QK_RBT,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,       XXXXXXX,  KC_4,     KC_5,     KC_6,     _______,
                  _______,  _______,  _______,  _______,       KC_ENT,   KC_BSPC,  KC_DEL,   _______
    ),

    [kFnKeys] = LAYOUT(
        KC_F10,   KC_F9,    KC_F8,    KC_F7,    XXXXXXX,       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        KC_F11,   KC_F3,    KC_F2,    KC_F1,    XXXXXXX,       XXXXXXX,  KC_LSFT,  KC_LCTL,  KC_LALT,  KC_LGUI,
        KC_F12,   KC_F6,    KC_F5,    KC_F4,    XXXXXXX,       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                  _______,  KC_ESC,   KC_SPC,   KC_TAB,        _______,  _______,  _______,  _______
    ),

    [kSymbols] = LAYOUT(
        KC_QUOT,  KC_LPRN,  KC_RPRN,  KC_SCLN,  KC_PERC,       KC_TILD,  KC_PIPE,  KC_AMPR,  KC_GRV,   KC_DQT,
        KC_EXLM,  KC_EQL,   KC_SLSH,  KC_PLUS,  KC_HASH,       KC_ASTR,  KC_LSFT,  KC_LCTL,  KC_LALT,  KC_LGUI,
        KC_CIRC,  KC_LCBR,  KC_RCBR,  KC_DLR,   XXXXXXX,       KC_BSLS,  KC_AT,    KC_LBRC,  KC_RBRC,  KC_QUES,
                  _______,  KC_ESC,   KC_SPC,   KC_TAB,        _______,  _______,  _______,  _______
    ),
};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [kBase] = {ENCODER_CCW_CW(KC_PGUP, KC_PGDN),
               ENCODER_CCW_CW(KC_LEFT, KC_RIGHT)},

    [kNavigation] = {ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_BSPC, KC_DEL)},
    [kSymbols] = {ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_BSPC, KC_DEL)},

    [kOneHand] = {ENCODER_CCW_CW(KC_PGUP, KC_PGDN),
                  ENCODER_CCW_CW(KC_LEFT, KC_RIGHT)},
    [kNumbers] = {ENCODER_CCW_CW(KC_PGUP, KC_PGDN),
                  ENCODER_CCW_CW(KC_LEFT, KC_RIGHT)},
    [kFnKeys]    = {ENCODER_CCW_CW(KC_PGUP, KC_PGDN),
                  ENCODER_CCW_CW(KC_LEFT, KC_RIGHT)},
};
#endif
