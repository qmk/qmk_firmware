// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _LAYER_0,
    _LAYER_1,
    _LAYER_2,
    _LAYER_3,
};

#define LAYER0 MO(_LAYER_0)
#define LAYER1 MO(_LAYER_1)
#define LAYER2 MO(_LAYER_2)
#define LAYER3 MO(_LAYER_3)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_LAYER_0] = LAYOUT_split_3x5_3(
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                        KC_LGUI, LAYER1,  KC_SPC,     KC_ENT,  LAYER2,  KC_RGUI
  ),

  [_LAYER_1] = LAYOUT_split_3x5_3(
      KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,       KC_5,    KC_6,    KC_7,    KC_8,    KC_9,
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, KC_LALT,    KC_RALT, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                        KC_LGUI, _______, KC_SPC,     KC_ENT,  LAYER3,  KC_RGUI
  ),

  [_LAYER_2] = LAYOUT_split_3x5_3(
      KC_TAB,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,     KC_RCTL, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_RALT, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC,
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                        KC_LGUI, LAYER3,  KC_SPC,     KC_ENT,  _______, KC_RGUI
  ),

  [_LAYER_3] = LAYOUT_split_3x5_3(
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      RM_NEXT, RM_HUED, RM_SATD, RM_VALD, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                        KC_LGUI, _______, KC_SPC,     KC_ENT,  _______, KC_RGUI
  )

};
