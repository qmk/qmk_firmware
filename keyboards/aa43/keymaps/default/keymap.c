// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┐
     * │Tab│ Q │ W │ E │ R │ T │   │ Y │ U │ I │ O │ P │ - │
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │Esc│ A │ S │ D │ F │ G │   │ H │ J │ K │ L │ ; │ ' │
     * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
     * │Sft│ Z │ X │ C │ V │ B │   │ N │ M │ , │ . │ / │Sft│
     * ├───┼───┼───┴───┼───┴───┤   ├───┴───┼───┴───┼───┼───┤
     * │Alt│Cmd│  Space │ Enter │   │ Enter │  Cmd  │Alt│   │
     * └───┴───┴───────┴───────┘   └───────┴───────┴───┴───┘
     */
    [0] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
        KC_LALT, KC_LGUI, KC_SPC,  KC_ENT,
        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_ENT,  KC_RGUI, KC_RALT
    )
};