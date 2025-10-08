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
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGDN,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                              KC_RALT, MO(1),   KC_RCTL, KC_LEFT,KC_DOWN, KC_RGHT
    ),


    /*
     *      ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────┬───┬──────────┬────┐
     *      │Grv│F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11 │F12│   Ins    │Del │
     *      ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴──┬─┴─┬─┴─┬────────┼────┤
     *      │     │   │Vl+│   │   │   │   │SrL│   │ 7 │ 8  │ 9 │ \ │  SATU  │HUEU│
     *      ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬───┴┬──┴┬──┴────────┼────┤
     *      │      │Mut│Vl-│Pau│   │   │   │   │   │ 4 │ 5  │ 6 │    SATD   │HUED│
     *      ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴──┬─┴─┬─┴──────┬────┼────┤
     *      │        │ | │   │   │   │   │   │   │   │ 1  │ 2 │   3    │VALU│TOGG│
     *      ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┬┴──┬┴───┬────┼────┼────┤
     *      │    │    │    │          PScr          │SPDD│   │SPDU│PREV│VALD│NEXT│
     *      └────┴────┴────┴────────────────────────┴────┴───┴────┴────┴────┴────┘
     */


    [1] = LAYOUT_65_ansi(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12,   KC_INS,   KC_DEL,
        _______, _______, KC_VOLU, _______, _______, _______, _______, KC_SCRL, _______, KC_7,    KC_8,    KC_9,   KC_BSLS,  RM_SATU,  RM_HUEU,
        _______, KC_MUTE, KC_VOLD, KC_PAUS, _______, _______, _______, _______, _______, KC_4,    KC_5,    KC_6,             RM_SATD,  RM_HUED,
        _______, KC_PIPE, _______, _______, _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,             RM_VALU,  RM_TOGG,
        _______, _______, _______,                            KC_PSCR,                   RM_SPDD, _______, RM_SPDU, RM_PREV, RM_VALD,  RM_NEXT
    )
};
