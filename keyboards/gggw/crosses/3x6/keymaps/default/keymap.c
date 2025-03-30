// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_3x6(
        KC_ESC    , KC_Q     , KC_W     , KC_F     , KC_P    , KC_B     ,                                      KC_J     , KC_L      , KC_U      , KC_Y      , KC_SCLN     , KC_BSPC    ,
        KC_TAB    , KC_A     , KC_R     , KC_S     , KC_T    , KC_G     ,                                      KC_M     , KC_N      , KC_E      , KC_I      , KC_O        , KC_ENTER   ,
        KC_LSFT   , KC_Z     , KC_X     , KC_C     , KC_D    , KC_V     ,                                      KC_K     , KC_H      , KC_COMM   , KC_DOT    , KC_SLSH     , KC_RSFT    ,
                                                               XXXXXXX  , KC_ESC   , KC_SPC   ,       KC_ENT,  KC_BSPC  , KC_DEL
    )
};

