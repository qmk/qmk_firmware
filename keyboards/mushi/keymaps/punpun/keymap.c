// Copyright 2023 Dane Lipscombe (@dlip)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum ferris_tap_dances {
  TD_1,
  TD_2,
  TD_3,
  TD_4,
  TD_5,
  TD_6,
  TD_7,
  TD_8,
  TD_9,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_1] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_ENT),
    [TD_2] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_ESC),
    [TD_3] = ACTION_TAP_DANCE_DOUBLE(KC_C, LGUI(KC_C)),
    [TD_4] = ACTION_TAP_DANCE_DOUBLE(KC_V, LGUI(KC_V)),
    [TD_5] = ACTION_TAP_DANCE_DOUBLE(KC_X, LGUI(KC_X)),
    [TD_6] = ACTION_TAP_DANCE_DOUBLE(KC_1, LCTL(KC_1)),
    [TD_7] = ACTION_TAP_DANCE_DOUBLE(KC_2, LCTL(KC_2)),
    [TD_8] = ACTION_TAP_DANCE_DOUBLE(KC_3, LCTL(KC_3)),
    [TD_9] = ACTION_TAP_DANCE_DOUBLE(KC_4, LCTL(KC_4)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x5_3( /* QWERTY */
    MT(MOD_LSFT | MOD_LGUI, KC_Q),    KC_W,    KC_E,    KC_R,    KC_T,
    KC_Y,    KC_U,  KC_I,    KC_O,   KC_P,
    LCTL_T(KC_A), LALT_T(KC_S),    LGUI_T(KC_D),    LSFT_T(KC_F),    KC_G,
    KC_H,    RSFT_T(KC_J),  RGUI_T(KC_K),    RALT_T(KC_L),   RCTL_T(KC_SCLN),
    LSFT_T(KC_Z), TD(TD_5),    TD(TD_3),    TD(TD_4),    KC_B,
    KC_N,    KC_M, KC_COMM, KC_DOT, RSFT_T(KC_SLSH),
    LT(MO(1), KC_ESC), KC_LSFT, KC_SPC,
    KC_BSPC, KC_RSFT, LT(MO(2), KC_ENT)
  ),

  [1] = LAYOUT_split_3x5_3( /* [> LOWER <] */
    TD(TD_6),    TD(TD_7),    TD(TD_8),    TD(TD_9),    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_BRID, KC_BRIU, KC_VOLD, KC_VOLU, KC_MUTE,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TAB,
    KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4, KC_BTN5,         KC_WH_U, KC_WH_D, KC_WH_L, KC_WH_R, KC_RALT,
                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [2] = LAYOUT_split_3x5_3( /* [> RAISE <] */
    KC_EXLM,   KC_AT,   KC_HASH,   KC_DLR,   KC_PERC,           KC_CIRC,   KC_AMPR,   KC_ASTR,   KC_LPRN,   KC_RPRN,
    KC_TILD,  KC_GRV, KC_QUOTE, KC_DQUO, CW_TOGG,         KC_PMNS, KC_PEQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    KC_ESC, KC_ENT, KC_TRNS, KC_TRNS, KC_TRNS,         KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  )
};
