// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┬───┬───┐                     ┌───┬───┬───┬───┬───┬───┬───┐
      * │   │F1 │F2 │F3 │F4 │F5 │F6 │                     │F7 │F8 │F9 │F10│F11│F12│   │
      * ├───┼───┼───┼───┼───┼───┼───┤                     ├───┼───┼───┼───┼───┼───┼───┤
      * │   │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │                     │ 6 │ 7 │ 8 │ 9 │ 0 │ \ │   │
      * ├───┼───┼───┼───┼───┼───┼───┤                     ├───┼───┼───┼───┼───┼───┼───┤
      * │   │   │ Q │ W │ E │ R │ T │                     │ Y │ U │ I │ O │ P │ - │   │
      * ├───┼───┼───┼───┼───┼───┼───┤                     ├───┼───┼───┼───┼───┼───┼───┤
      * │   │   │ A │ S │ D │ F │ G │                     │ H │ J │ K │ L │ ; │ = │   │
      * ├───┼───┼───┼───┼───┼───┼───┤                     ├───┼───┼───┼───┼───┼───┼───┤
      * │   │Alt│ Z │ X │ C │ V │ B │                     │ N │ M │ , │ . │ / │Alt│   │
      * ├───┼───┼───┼───┼───┼───┴───┘                     └───┴───┼───┼───┼───┼───┼───┤
      * │   │Del│ ' │ ← │ → │                                     │ ↑ │ ↓ │ [ │ ] │   │
      * └───┴───┴───┴───┴───┘┌───┐                           ┌───┐└───┴───┴───┴───┴───┘
      *                      │ ˽ ├───┐                   ┌───┤Ent│
      *                      └───┤Tab│ ┌───┐       ┌───┐ │Bsp├───┘
      *                          └─┬─┴─┤Sft│       │Sft├─┴─┬─┘
      *                            │Ctl├─┬─┴─┐   ┌─┴─┬─┤Ctl│
      *                            └─┬─┴─┤End│   │Esc├─┴─┬─┘
      *                              │Hom├───┘   └───┤GUI│
      *                              └───┘           └───┘
      */
    [0] = LAYOUT_6x7_fullrows(
        _______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   ,                  KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , _______ ,
        _______ , KC_GRV  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,                  KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_BSLS , _______ ,
        _______ , _______ , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    ,                  KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_MINS , _______ ,
        _______ , _______ , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    ,                  KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_EQL  , _______ ,
        _______ , KC_LALT , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    ,                  KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_RALT , _______ ,
        _______ , KC_DEL  , KC_QUOT , KC_LEFT , KC_RGHT ,                                                          KC_UP   , KC_DOWN , KC_LBRC , KC_RBRC , _______ ,
                                                          KC_SPC  , KC_TAB  ,                  KC_BSPC , KC_ENT  ,
                                                          KC_LCTL , KC_LSFT ,                  KC_RSFT , KC_RCTL ,
                                                          KC_HOME , KC_END  ,                  KC_ESC  , KC_LGUI
    )
};
