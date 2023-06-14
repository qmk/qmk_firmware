// Copyright 2022 Shem Sedrick (@ssedrick)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "print.h"

enum key_layers {
    _BASE,
    _COLEMAK,
    _RAISE,
    _LOWER
};

enum layer_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK,
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define SH_ESC SFT_T(KC_ESC)
#define ____ KC_TRANSPARENT

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base (qwerty)
     * ,----------------------------------,                  ,----------------------------------,
     * |   q  |   w  |   e  |   r  |   t  |                  |   y  |   u  |   i  |   o  |   p  |
     * |------+------+------+------+------|                  |------+------+------+------+------|
     * |   a  |   s  |   d  |   f  |   g  |                  |   h  |   j  |   k  |   l  |   ;  |
     * |------+------+------+------+------|                  |------+------+------+------+------|
     * |   z  |   x  |   c  |   v  |   b  |                  |   n  |   m  |   ,  |   .  |   /  |
     * '------+------+------+-------------'                  '------+------+------+------+------'
     *        |  [   |   ]  |                                              |   '  |  `~  |
     *        '-------------+------,                                ,------|-------------'
     *                      | ESC  |                                | BSPC |
     *                      |-------------,                  ,------+------|
     *                      | GUI  |  TAB |                  | SHIFT| SPACE|
     *                      |------+------|                  |------+------|
     *                      | RAISE| CTRL |                  | LOWER| ENTER|
     *                      '-------------'                  '-------------'
     */
    [_BASE] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                 KC_LBRC, KC_RBRC,                                              KC_QUOT, KC_GRV,
                                    SH_ESC,                            KC_BSPC,
                                    KC_LGUI, KC_TAB,          KC_RSFT, KC_SPC,
                                    RAISE,   KC_LCTL,         LOWER,  KC_ENT
    ),
   
    /* Colemak
     * ,----------------------------------,                  ,----------------------------------,
     * |   q  |   w  |   f  |   p  |   g  |                  |   j  |   l  |   u  |   y  |   ;  |
     * |------+------+------+------+------|                  |------+------+------+------+------|
     * |   a  |   r  |   s  |   t  |   d  |                  |   h  |   n  |   e  |   i  |   o  |
     * |------+------+------+------+------|                  |------+------+------+------+------|
     * |   z  |   x  |   c  |   v  |   b  |                  |   k  |   m  |   ,  |   .  |   /  |
     * '------+------+------+-------------'                  '------+------+------+------+------'
     *        |  [   |   ]  |                                              |   '  |  `~  |
     *        '-------------+------,                                ,------|-------------'
     *                      | ESC  |                                | BSPC |
     *                      |-------------,                  ,------+------|
     *                      | GUI  |  TAB |                  | SHIFT| SPACE|
     *                      |------+------|                  |------+------|
     *                      | RAISE| CTRL |                  | LOWER| ENTER|
     *                      '-------------'                  '-------------'
     */
    [_COLEMAK] = LAYOUT(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,             KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,
        KC_A,    KC_R,    KC_S,    KC_T,    KC_D,             KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                 KC_LBRC, KC_RBRC,                                              KC_QUOT, KC_GRV,
                                    KC_ESC,                            KC_BSPC,
                                    KC_LGUI, KC_TAB,          KC_RSFT, KC_SPC,
                                    RAISE,   KC_LCTL,         LOWER,  KC_ENT
    ),
    /*  RAISE
     * ,----------------------------------,                  ,----------------------------------,
     * |   1  |   2  |   3  |   4  |   5  |                  |   6  |   7  |   8  |   9  |   0  |
     * |------+------+------+------+------|                  |------+------+------+------+------|
     * |   (  |   )  |   {  |   }  |   =  |                  |  -   |   4  |   5  |   6  |   ;  |
     * |------+------+------+------+------|                  |------+------+------+------+------|
     * | QK_BOOT| BOOT |   [  |   ]  |      |                  |      |   1  |   2  |   3  |      |
     * |------+------+------+-------------|                  |------+------+------+------+------,
     *        |      |      |                                              |   0  |   .  |
     *        '-------------+------,                                ,------|-------------'
     *                      | ESC  |                                | BSPC |
     *                      |-------------,                  ,------+------|
     *                      | GUI  |  TAB |                  | SHIFT| SPACE|
     *                      |------+------|                  |------+------|
     *                      | RAISE| CTRL |                  | LOWER| ENTER|
     *                      '-------------'                  '-------------'
     */
    [_RAISE] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
     S(KC_9), S(KC_0), KC_LCBR, KC_RCBR,  KC_EQL,            KC_MINS,  KC_4,    KC_5,    KC_6, KC_QUOT,
      QK_RBT, QK_BOOT, KC_LBRC, KC_RBRC,    ____,             ____,    KC_1,    KC_2,    KC_3,    ____,
                 ____,    ____,                                                 KC_0,  KC_DOT,
                                   ____,                               ____,
                                   ____,    ____,             ____,    ____,
                                   ____,    ____,             ____,    ____
    ),

    /*  LOWER
     * ,----------------------------------,                  ,----------------------------------,
     * |   !  |   @  |   #  |   $  |   %  |                  |   ^  |   &  |   *  |   (  |   )  |
     * |------+------+------+------+------|                  |------+------+------+------+------|
     * |   (  |   )  |   {  |   }  |   =  |                  |      |   -  |   +  |   |  |      |
     * |------+------+------+------+------|                  |------+------+------+------+------|
     * |      |      |      |      |      |                  |      | LEFT | DOWN |  UP  | RIGHT|
     * |------+------+------+-------------|                  |------+------+------+------+------,
     *        |      |      |                                              |QWERTY|COLEMA|
     *        '-------------+------,                                ,------|-------------'
     *                      | ESC  |                                | BSPC |
     *                      |-------------,                  ,------+------|
     *                      | GUI  |  TAB |                  | SHIFT| SPACE|
     *                      |------+------|                  |------+------|
     *                      | RAISE| CTRL |                  | LOWER| ENTER|
     *                      '-------------'                  '-------------'
     */
    [_LOWER] = LAYOUT(
     KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
     S(KC_9), S(KC_0), KC_LBRC, KC_RBRC,  KC_EQL,               ____, KC_MINS,  KC_EQL, KC_PIPE,    ____,
        ____,    ____,    ____,    ____,    ____,               ____, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,
                 ____,    ____,                                              QWERTY, COLEMAK,
                                   ____,                               ____,
                                   ____,    ____,             ____,    ____,
                                   ____,    ____,             ____,    ____
    )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %d, time: %u, interrupt: %d, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif 
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_BASE);
            }
            return false;
            break;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
            break;
    }
    return true;
}

