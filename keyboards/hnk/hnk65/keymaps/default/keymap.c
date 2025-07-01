// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
     *      ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬────┐
     *      │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│Home│
     *      ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼────┤
     *      │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │PgUp│
     *      ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼────┤
     *      │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │PgDn│
     *      ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼────┤
     *      │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shift│ ↑ │End │
     *      ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼────┤
     *      │Ctrl│GUI │Alt │                        │Alt│ Fn│Ctl│ ← │ ↓ │ →  │
     *      └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴────┘
     */


    [0] = LAYOUT_65_ansi(
        KC_HOME,  KC_BSPC,    KC_EQL,    KC_MINS,    KC_0,    KC_9,    KC_8,    KC_7,    KC_6,    KC_5,    KC_4,    KC_3, KC_2,  KC_1, KC_ESC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        KC_PGDN, KC_ENT,    KC_QUOT,    KC_SCLN,  KC_L,  KC_K,    KC_J,    KC_H,    KC_G,    KC_F,    KC_D,    KC_S, KC_A,            KC_CAPS,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_END,
        KC_RGHT, KC_DOWN, KC_LEFT,KC_RCTL, MO(1), KC_RALT,           KC_SPC,                                   KC_LALT,  KC_LGUI,     KC_LCTL           
    ),


    /*
     *      ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────────┬────┐
     *      │Grv│F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│  Ins   │Del │
     *      ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬──────┼────┤
     *      │     │   │Vl+│   │   │   │   │SrL│   │ 7 │ 8 │ 9 │ \ │ SAI  │HUI │
     *      ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴──────┼────┤
     *      │      │Mut│Vl-│Pau│   │   │   │   │   │ 4 │ 5 │ 6 │   SAD   │HUD │
     *      ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─────┬───┼────┤
     *      │        │ | │   │   │   │   │   │   │   │ 1 │ 2 │   3   │VAI│Tog │
     *      ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬────┼───┼────┤
     *      │    │    │    │          PScr          │SPD│   │SPI│ModR│VAD│ModF│
     *      └────┴────┴────┴────────────────────────┴───┴───┴───┴────┴───┴────┘
     */



    [1] = LAYOUT_65_ansi(
        KC_DEL,  KC_INS,   KC_F12,  KC_F11,  KC_F10,  KC_F9,   KC_F8,   KC_F7,   KC_F6,  KC_F5,   KC_F4,  KC_F3, KC_F2,   KC_F1,   KC_GRV,
        _______, _______, KC_VOLU, _______, _______, _______, _______, KC_SCRL, _______, KC_7,    KC_8,    KC_9,   KC_BSLS,  RGB_SAI,  RGB_HUI,
        RGB_HUD, RGB_SAD, KC_6, KC_5, KC_4, _______, _______, _______, _______, _______, KC_PAUS,    KC_VOLD,             KC_MUTE,  _______,
        _______, KC_PIPE, _______, _______, _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,             RGB_VAI,  RGB_TOG,
        RGB_MODE_FORWARD, RGB_VAD, RGB_MODE_REVERSE, RGB_SPI,  _______, RGB_SPD,          KC_PSCR,                _______, _______,  _______
    )
};