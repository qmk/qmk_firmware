// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌──────┬───┬───┬───┬───┬───┐                     ┌───┬───┬───┬───┬───┬──────┐
     * │ `    │ 1 │ 2 │ 3 │ 4 │ 5 ├───┐             ┌───┤ 6 │ 7 │ 8 │ 9 │ 0 │PrtScn│
     * ├──────┼───┼───┼───┼───┼───│ - │             │ = │───┼───┼───┼───┼───┼──────┤
     * │ Tab  │ Q │ W │ E │ R │ T ├───┤             ├───┤ Y │ U │ I │ O │ P │   \  │
     * ├──────┼───┼───┼───┼───┼───┤ [ │             │ ] ├───┼───┼───┼───┼───┼──────┤
     * │Escape│ A │ S │ D │ F │ G │   │             │   │ H │ J │ K │ L │ ; │   '  │
     * ├──────┼───┼───┼───┼───┼───┼───┘             └───┼───┼───┼───┼───┼───┼──────┤
     * │LShift│ Z │ X │ C │ V │ B │                     │ N │ M │ , │ . │ / │RShift│
     * └──┬───┼───┼───┼───┼─┬─┴─┬─┘ ┌───┬───┐ ┌───┬───┐ └─┬─┴─┬─┼───┼───┼───┼───┬──┘
     *    │Ctl│Alt│ ← │ → │ │GUI│   │Hom│Pg↑│ │Pg↓│End│   │GUI│ │ ↑ │ ↓ │Alt│Ctl│
     *    └───┴───┴───┴───┘ └───┘   ├───┼───┤ ├───┼───┤   └───┘ └───┴───┴───┴───┘
     *                              │   │   │ │   │   │
     *                              │Spc│Del│ │Bsp│Ent│
     *                              │   │   │ │   │   │
     *                              └───┴───┘ └───┴───┘
     */
    [0] = LAYOUT_redox(
        KC_GRV,  KC_1,    KC_2,    KC_3,   KC_4, KC_5,                                          KC_6, KC_7, KC_8,    KC_9,    KC_0,    KC_PSCR,
        KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R, KC_T, KC_MINS,                        KC_EQL,  KC_Y, KC_U, KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_ESC,  KC_A,    KC_S,    KC_D,   KC_F, KC_G, KC_LBRC,                        KC_RBRC, KC_H, KC_J, KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V, KC_B, KC_HOME, KC_PGUP,      KC_PGDN, KC_END,  KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT,  KC_LGUI,  KC_SPC,  KC_DEL,       KC_BSPC, KC_ENT,    KC_RGUI,  KC_UP,   KC_DOWN, KC_RALT, KC_RCTL 
    )
};
