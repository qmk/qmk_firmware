// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌──────┬───┬───┬───┬───┬───┬───┐                             ┌───┬───┬───┬───┬───┬───┬──────┐
     * │ Esc  │F1 │F2 │F3 │F4 │F5 │F6 │                             │F7 │F8 │F9 │F10│F11│F12│    - │
     * ├──────┼───┼───┼───┼───┼───┼───┤                             ├───┼───┼───┼───┼───┼───┼──────┤
     * │ `~   │ 1 │ 2 │ 3 │ 4 │ 5 │ - │                             │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │  Bsp │
     * ├──────┼───┼───┼───┼───┼───┼───┤                             ├───┼───┼───┼───┼───┼───┼──────┤
     * │ Tab  │ Q │ W │ E │ R │ T │ = │                             │ Y │ Y │ U │ I │ O │ P │    \ │
     * ├──────┼───┼───┼───┼───┼───┤   │                             │   ├───┼───┼───┼───┼───┼──────┤
     * │Escape│ A │ S │ D │ F │ G ├───┤                             ├───┤ H │ J │ K │ L │ ; │ Enter│
     * ├──────┼───┼───┼───┼───┼───┤   │                             │   ├───┼───┼───┼───┼───┼──────┤
     * │Shift │ Z │ X │ C │ V │ B │ B │                             │ N │ N │ M │ , │ . │ / │ Shift│
     * └──┬───┼───┼───┼───┼───┼───┴───┘ ┌───┬───┬───┐ ┌───┬───┬───┐ └───┴───┼───┼───┼───┼───┼───┬──┘
     *    │Ctl│F4 │F5 │GUI│Alt│         │ C │ V │ V │ │Alt│Alt│ A │         │ ← │ ↓ │ ↑ │ → │GUI│
     *    └───┴───┴───┴───┴───┘     ┌───┼───┼───┼───┤ ├───┼───┼───┼───┐     └───┴───┴───┴───┴───┘
     *                              │   │   │PgU│PgU│ │PgD│PgD│   │   │
     *                              │Bsp├───┼───┼───┤ ├───┼───┼───┤Ent│
     *                              │   │   │Del│Del│ │Ctl│Ctl│   │   │
     *                              └───┴───┴───┴───┘ └───┴───┴───┴───┘
     */
    [0] = LAYOUT_ergodox(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
        KC_LCTL, KC_LGUI, KC_LALT, KC_NO,   KC_LALT,
                                            KC_HOME, KC_DEL,  KC_PGUP,
                                   KC_SPC,  KC_END,  KC_UP,   KC_PGDN,
                                            KC_LEFT, KC_DOWN, KC_RGHT,

        KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_F13,
        KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_BSPC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_DEL,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
                 KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                          KC_QUOT, KC_LBRC, KC_RBRC, KC_RGUI, KC_RCTL,
        KC_PGUP, KC_INS,  KC_PAUS,
        KC_PGDN, KC_UP,   KC_PSCR, KC_SPC,
        KC_LEFT, KC_DOWN, KC_RGHT
    )
};
