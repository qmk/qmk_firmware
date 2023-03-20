// Copyright 2022 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_number {
  _QWERTY,
  _LOWER,
  _RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* QWERTY
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
                  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,                KC_Y,  KC_U,  KC_I,    KC_O,    KC_P,
        KC_LCTL,  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,                KC_H,  KC_J,  KC_K,    KC_L,    KC_SCLN,  KC_BSPC,
        KC_LSFT,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,                KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                             KC_LALT, MO(_LOWER), KC_SPC,     KC_ENT, MO(_RAISE), KC_RGUI
    ),

    [_LOWER] = LAYOUT(
                 KC_ESC,   KC_7,   KC_8,   KC_9,   KC_0,                KC_BSLS,  KC_F7,   KC_F8,   KC_F9,  KC_F12,
        _______, KC_EQL,   KC_4,   KC_5,   KC_6,   KC_LBRC,             KC_QUOT,  KC_F4,   KC_F5,   KC_F6,  KC_F11,  _______,
        _______, KC_MINS,  KC_1,   KC_2,   KC_3,   KC_RBRC,             KC_GRV,   KC_F1,   KC_F2,   KC_F3,  KC_F10,  _______,
                                    _______, _______, XXXXXXX,       KC_MPLY, _______, _______
    ),

    [_RAISE] = LAYOUT(
                 KC_TAB,        LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_0),               LSFT(KC_BSLS),  KC_DEL,  KC_PGDN, KC_PGUP, KC_INS,
        _______, LSFT(KC_EQL),  LSFT(KC_4), LSFT(KC_5), LSFT(KC_6), LSFT(KC_LBRC),            LSFT(KC_QUOT),  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  _______,
        _______, LSFT(KC_MINS), LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_RBRC),            LSFT(KC_GRV),   KC_HOME, KC_END,  XXXXXXX, XXXXXXX,  _______,
                                                           _______, _______, KC_CAPS,      XXXXXXX, _______, _______
    ),
};
