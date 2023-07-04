// Copyright 2022-2023 alin m elena (@alinelena)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QW] = LAYOUT_ortho_2x2(
       KC_2   , KC_4     ,
      TT(_LWR), TT(_RSE)),

  [_LWR] = LAYOUT_ortho_2x2(
       RGB_TOG, KC_3     ,
       _______, _______ ),

  [_RSE] = LAYOUT_ortho_2x2(
      KC_5   , KC_6    ,
      _______, _______),

  [_ADJ] = LAYOUT_ortho_2x2(
      RGB_TOG , QK_BOOT ,
       _______, _______),

};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QW]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_LWR] = {ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
    [_RSE] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [_ADJ] = {ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)},
};
#endif

