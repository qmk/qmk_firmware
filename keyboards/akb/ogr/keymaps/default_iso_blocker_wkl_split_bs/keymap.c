// Copyright 2018-2022 QMK (@qmk)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
     * ┌───┬───┐    ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ F1│ F2│    │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Bsp│Del│Hom│
     * ├───┼───┤    ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
     * | F3| F4|    │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │     │PgU│
     * ├───┼───┤    ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐Ent ├───┤
     * | F5| F6|    │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ # │    │PgD│
     * ├───┼───┤    ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
     * | F7| F8|    │Sft │ \ │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shift│ ↑ │End│
     * ├───┼───┤    ├────┴┬──┼───┴─┬─┴───┴───┴───┴───┴───┴───┴─┬─┴───┼──┬───┼───┼───┤
     * | F9|F10|    │Ctrl │  │Alt  │                           │  Fn │  │ ← │ ↓ │ → │
     * └───┴───┘    └─────┘  └─────┴───────────────────────────┴─────┘  └───┴───┴───┘
     */

    [0] = LAYOUT_65_xt_iso_blocker_wkl_split_bs(
        KC_F1,   KC_F2,      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  KC_HOME,
        KC_F3,   KC_F4,      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_PGUP,
        KC_F5,   KC_F6,      KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,  KC_PGDN,
        KC_F7,   KC_F8,      KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
        KC_F9,   KC_F10,     KC_LCTL,          KC_LALT,                            KC_SPC,                             MO(1),            KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT_65_xt_iso_blocker_wkl_split_bs(
        _______, _______,    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  _______, _______,
        _______, _______,    _______, _______, _______, _______, _______, _______, KC_INS,  _______, _______, _______, _______, KC_PSCR, KC_SCRL,          _______,
        _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PAUS, _______, _______,
        _______, _______,    _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______, _______, _______,
        _______, _______,    _______,          _______,                            _______,                            _______,          _______, _______, _______
    ),

};
