// Copyright 2022 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_number {
  _QWERTY,
  _LOWER,
  _RAISE
};

// Define the 8-pin layout with only one row (1 row, 8 columns)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* QWERTY Layer
    *        .----------------------------------.                    ,----------------------------------.
    *        |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |
    * .------+------+------+------+------+------|                    |------+------+------+------+------+------.
    * | LCTRL|   A  |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |   ;  | BSPC |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * | LSFT |   Z  |   X  |   C  |   V  |   B  |-------.    .-------|   N  |   M  |   ,  |   .  |   /  | RSFT |
    * `-----------------------------------------/       /    \       \-----------------------------------------'
    *                        | LALT  | LOWER|  / Space /      \ Enter \  | RAISE| RGUI |
    *                        `-------------' '-------'         '-------' '-------------'
    */
    [_QWERTY] = LAYOUT(
                  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I
    ),

    [_LOWER] = LAYOUT(
                 KC_ESC,   KC_7,   KC_8,   KC_9,   KC_0,   KC_BSLS,  KC_F7,   KC_F8
    ),

    [_RAISE] = LAYOUT(
                 KC_TAB,        LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_0),               LSFT(KC_BSLS),  KC_DEL,  KC_PGDN
    ),
};
