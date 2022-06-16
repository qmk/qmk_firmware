/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com> */

/*
    Refactor: Removing keyboard-specific - stuff that is integral to the kb - code and config
    from userspace and moving into the kb folder.
*/

#include QMK_KEYBOARD_H
// This fixed the no-layers-working issue... :S
//#include "christrotter.h"
/* 
    putting the enum layers here might work, but it causes callbacks.c to blow up with:
Compiling: users/christrotter/callbacks.c       users/christrotter/callbacks.c: In function 'layer_state_set_user':
users/christrotter/callbacks.c:139:43: error: '_SYMBOLS' undeclared (first use in this function); did you mean 'SYMBOL_STR'?
     state = update_tri_layer_state(state, _SYMBOLS, _MOUSE, _SYMBOLS);
                                           ^~~~~~~~
                                           SYMBOL_STR
users/christrotter/callbacks.c:139:43: note: each undeclared identifier is reported only once for each function it appears in
users/christrotter/callbacks.c:139:53: error: '_MOUSE' undeclared (first use in this function); did you mean 'MCUSR'?
     state = update_tri_layer_state(state, _SYMBOLS, _MOUSE, _SYMBOLS);
                                                     ^~~~~~
                                                     MCUSR
 [ERRORS]
*/

enum custom_layers {
    _QWERTY,
    _SYMBOLS,
    _MOUSE,
};

#define XXX KC_NO

void pointing_device_init_kb(void) {
#ifdef PMW3360_CPI
    pointing_device_set_cpi(PMW3360_CPI);
#endif
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base (qwerty)
     * ,-----------------------------------------,                                           ,-----------------------------------------,
     * |  TAB |   q  |   w  |   e  |   r  |   t  |                                           |   y  |   u  |   i  |   o  |   p  |  -   |
     * |------+------+------+------+------+------|                                           |-------------+------+------+-------------|
     * |      |   a  |   s  |   d  |   f  |   g  |                               (TRACKBALL) |   h  |   j  |   k  |   l  |   '  |  ;   |
     * |------+------+------+------+------|------|------|------|------,        |------|------|------|------+------+------+-------------|
     * |      |   z  |   x  |   c  |   v  |   b  | ESC  | BACK | FWD  |        |  <   |  >   |   n  |   m  |   ,  |   .  |   /  | PLAY |
     * |------+------+------+------,------,------,------,------,------,      ,------,------,------,------,------+------+------+--------,
     *                             |  BS  |  DEL | CMD  |  LT  |             | CMD  |  LT  |ENTER |      |        ,------,
     *                             |      |      |      |      |             |      |      |  +   |SPACE |        |  up  |
     *                             |      |      |      |      |             |      |      |CMDent|      | ,------+------+-----,
     *                             '------+------+------+------'             '------'------+------+------' | left |------|right|
     *                                    '------+------'                                  '------+------' '------+------+-----'
     *                                    | SHIFT| ALT  |                                  | PLAY | CTRL |        | down |
     *                                    '------+------'                                  '------+------'        '------'
     */
[_SYMBOLS] = LAYOUT( \
    _______,   KC_EXLM,    KC_AT,    KC_LPRN,    KC_RPRN,    KC_TILD,             KC_PPLS,    KC_P1,    KC_P2,    KC_P3,    KC_PMNS,    _______,
    _______,   KC_HASH,    KC_DLR,    KC_LCBR,    KC_RCBR,    KC_GRV,           KC_PAST,    KC_P4,    KC_P5,    KC_P6,    KC_SLASH, KC_BSLS,
    _______,   KC_PERC,    KC_CIRC,    KC_LBRC,    KC_RBRC,    KC_PIPE,         KC_AMPR,    KC_P7,    KC_P8, KC_P9,  KC_P0, XXX,
               _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______,
                                _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______
),
[_QWERTY] = LAYOUT( \
    KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINUS,
    KC_LSFT,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_SCLN,
    KC_TILD,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH, KC_P,
                KC_BSPC, KC_DEL,  KC_ESC, KC_LBRC, KC_RBRC,             KC_COMM, KC_DOT, KC_LGUI, MO(_SYMBOLS), KC_ENTER, KC_SPACE,
                                KC_LSFT, KC_LALT, KC_LGUI, MO(_SYMBOLS),        KC_MPLY, KC_LCTL, KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT
),
[_MOUSE] = LAYOUT( \
    _______, _______, _______, _______, _______, _______,                               _______, _______, KC_MS_BTN3, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                               _______, KC_MS_BTN1, KC_MS_BTN2, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                               _______, _______, _______, _______, _______, _______,
                _______, _______,  _______, KC_END, KC_HOME,         KC_PGDN, KC_PGUP, _______, _______, _______, _______,
                                _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______
)
};

