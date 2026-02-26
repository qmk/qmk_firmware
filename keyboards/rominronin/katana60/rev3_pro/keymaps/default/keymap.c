// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ / │ 6 │ 7 │ 8 │ 9 │ 0 │ ' │BSp│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
     * │ Tab │ Q │ W │ E │ R │ T │ - │ + │ Y │ U │ I │ O │ P │  \  │
     * ├────┬┴──┬┴──┬┴──┬┴──┬┴──┬┴───┼───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬────┤
     * │Ctl │ A │ S │ D │ F │ G │  [ │ ]  │ H │ J │ K │ L │ ; │ Ent│
     * ├───┬┴──┬┴──┬┴──┬┴──┬┴──┬┴──┬─┴─┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬───┤
     * │Sft│ Z │ X │ C │ V │ B │ ← │ ↑ │ → │ N │ M │ , │ . │ ↑ │Sft│
     * ├───┼───┼───┼───┼───┼───┴───┼───┼───┴───┼───┼───┼───┼───┼───┤
     * │CAP│Ctl│Ctl│Alt│Win│ Space │ ↓ │ Space │Win│Alt│ ← │ ↓ │ → │
     * └───┴───┴───┴───┴───┴───────┴───┴───────┴───┴───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_SLSH, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_QUOT, KC_BSPC,
            KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_MINS, KC_EQL,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
          KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC,     KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LEFT, KC_UP,   KC_RIGHT,KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_RSFT,
        KC_CAPS, KC_LCTL, KC_LCTL, KC_LALT, KC_LGUI,     KC_SPACE,     KC_DOWN,      KC_SPACE,    KC_RGUI, KC_RALT, KC_LEFT, KC_DOWN, KC_RIGHT
    )
};
