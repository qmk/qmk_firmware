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
      *               ┌───┐           ┌───┐
      *               │LCd├───┐   ┌───┤MO2│
      *               └───┤Spc│   │Ent├───┘
      *                   └───┘   └───┘
      */
    [0] = LAYOUT_split_3x5_2(
        KC_Q,             KC_W,             KC_E,             KC_R,             KC_T,                               KC_Y,     KC_U,             KC_I,             KC_O,            KC_P,
        LCMD_T(KC_A),     LOPT_T(KC_S),     LCTL_T(KC_D),     LSFT_T(KC_F),     KC_G,                               KC_H,     RSFT_T(KC_J),     RCTL_T(KC_K),     ROPT_T(KC_L),    RCMD_T(KC_SCLN),
        KC_Z,             KC_X,             KC_C,             KC_V,             KC_B,                               KC_N,     KC_M,             KC_COMM,          KC_DOT,          KC_SLSH,
                                                              KC_LCMD,          LT(1,KC_SPC),                       KC_ENT,   MO(2)
    )
};
