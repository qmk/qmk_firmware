// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
      * │ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │
      * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
      * │ A │ S │ D │ F │ G │       │ H │ J │ K │ L │ ; │
      * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
      * │ Z │ X │ C │ V │ B │       │ N │ M │ , │ . │ / │
      * └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
      *           ┌───┐                   ┌───┐
      *           │GUI├───┐           ┌───┤Alt│
      *           └───┤Bsp├───┐   ┌───┤Ent├───┘
      *               └───┤   │   │   ├───┘
      *                   └───┘   └───┘
      */
    // [0] = LAYOUT_SPLIT_3x5_3(
    //     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    //     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
    //     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
    //                                KC_LGUI, KC_BSPC, KC_SPC,           KC_SPC,  KC_ENT,  KC_RALT
    // )
#define LAYOUT(
  K00, K01, K02, K03, K04,           K05, K06, K07, K08, K09,
  K10, K11, K12, K13, K14,           K15, K16, K17, K18, K19,
  K20, K21, K22, K23, K24,           K25, K26, K27, K28, K29,
                 K32, K33, K34, K35, K36, K37
  )
  {
    {K00,   K01,   K02, K03, K04, K05, K06, K07, K08,   K09},
    {K10,   K11,   K12, K13, K14, K15, K16, K17, K18,   K19},
    {K20,   K21,   K22, K23, K24, K25, K26, K27, K28,   K29},
    {KC_NO, KC_NO, K32, K33, K34, K35, K36, K37, KC_NO, KC_NO},
  }
};
