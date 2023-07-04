// Copyright 2023 Nico Stuhlmueller (@ThePurox)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_german.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*             ┌───┐
     *             │MUT│
     * ┌───┬───┬───┼───┤
     * │ 7 │ 8 │ 9 │ + │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ - │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ * │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ / │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT(                                 LT(1, KC_MUTE),
                            KC_7, KC_8,   KC_9,   DE_PLUS,
                            KC_4, KC_5,   KC_6,   DE_MINS,
                            KC_1, KC_2,   KC_3,   DE_ASTR,
                            KC_0, KC_DOT, KC_ENT, DE_SLSH),

    [1] = LAYOUT(                                         _______,
                            RGB_M_P,  RGB_M_B,  RGB_M_R,  RGB_HUI,
                            RGB_M_SW, RGB_M_SN, RGB_M_K,  RGB_HUD,
                            RGB_M_X,  RGB_M_G,  RGB_M_TW, RGB_VAI,
                            RGB_TOG,  RGB_SAI,  RGB_SAD,  RGB_VAD)};
