// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base (qwerty)
     * +------------------------------------------------+                      +------------------------------------------------+
     * | ESC  | ESC  |   q  |   w  |   e  |   r  |   t  |                      |   y  |   y  |   u  |   i  |   o  |   p  |   p  |
     * |------+------+------+------+------+------|------+                      |------+------+------+------+------+------|------+
     * | TAB  | TAB  |   a  |   s  |   d  |   f  |   g  |                      |   h  |   h  |   j  |   k  |   l  |   ;  |   ;  |
     * |------+------+------+------+------+------|------|                      |------+------+------+------+------+------|------|
     * | SHFT | SHFT |   z  |   x  |   c  |   v  |                                    |   n  |   m  |   ,  |   .  |   /  |   /  |
     * +------+------+------+------+------+------+                                    +------+------+------+------+------+------+
     *        |  [   |   ]  |      |                                                                |      |      |      |
     *        +------+------+------+                                                                +------+------+------+
     *              
     */
    [0] = LAYOUT_split_2x7_6_3(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                 KC_LGUI, KC_BSPC, KC_SPC,                                                                          KC_SPC,  KC_ENT,  KC_RALT
    )
};
