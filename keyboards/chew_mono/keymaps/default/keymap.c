// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │
     * ├───┼───┼───┼───┼───┴───┼───┼───┼───┼───┤
     * │ Z │ X │ C │ V │       │ M │ , │ . │ / │
     * └───┴───┼───┼───┼───┬───┼───┼───┼───┴───┘
     *         │ B │Bsp│Alt│ ␣ │Ent│ N │
     *         └───┴───┴───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,                       KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                          KC_B, KC_BSPC, KC_RALT,   KC_SPC,    KC_ENT,  KC_N

    )
};
