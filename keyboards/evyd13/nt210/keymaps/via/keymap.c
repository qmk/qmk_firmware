// Copyright 2022 Evelien Dekkers (@evyd13)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN1,
    _FN2,
    _FN3,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_ortho_6x4(
  KC_ESC, KC_TAB,   KC_EQL,  KC_BSPC,
  KC_NUM, KC_PSLS,  KC_PAST, KC_PMNS,
  KC_P7,  KC_P8,    KC_P9,   KC_PPLS,
  KC_P4,  KC_P5,    KC_P6,   KC_NO,
  KC_P1,  KC_P2,    KC_P3,   KC_PENT,
  KC_P0,  KC_NO,    KC_PDOT, KC_NO),

[_FN1] = LAYOUT_ortho_6x4(
  _______, _______, _______, _______,
  _______, _______, _______, _______,
  _______, _______, _______, _______,
  _______, _______, _______, _______,
  _______, _______, _______, _______,
  _______, _______, _______, _______),

[_FN2] = LAYOUT_ortho_6x4(
  _______, _______, _______, _______,
  _______, _______, _______, _______,
  _______, _______, _______, _______,
  _______, _______, _______, _______,
  _______, _______, _______, _______,
  _______, _______, _______, _______),

[_FN3] = LAYOUT_ortho_6x4(
  _______, _______, _______, _______,
  _______, _______, _______, _______,
  _______, _______, _______, _______,
  _______, _______, _______, _______,
  _______, _______, _______, _______,
  _______, _______, _______, _______),

};