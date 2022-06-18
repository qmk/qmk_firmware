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
#define KC_CAD	LALT(LCTL(KC_DEL))
#define KC_MACLOCK	LGUI(LCTL(KC_Q))
#define KC_MACSHOT	LGUI(LSFT(KC_4))
// move between mac workspaces
#define KC_SPCLEFT	LCTL(KC_LEFT)
#define KC_SPCRGHT	LCTL(KC_RIGHT)
#define KC_ITRMSPCE_L  LGUI(KC_LEFT) // iterm switch spaces left
#define KC_ITRMSPCE_R  LGUI(KC_RIGHT) // iterm switch spaces right
#define KC_ITRMPANE_L  LGUI(LSFT(KC_LEFT)) // iterm switch panes left
#define KC_ITRMPANE_R  LGUI(LSFT(KC_RIGHT)) // iterm switch panes right
// move between tabs // this sort of worked...
#define KC_TAB_L	LGUI(LALT(KC_LEFT))
#define KC_TAB_R	LGUI(LALT(KC_RIGHT))

#define KC_MULTILNE	LGUI(LALT(KC_LSFT))

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
    _______,   KC_EXLM,    KC_AT,    KC_LPRN,    KC_RPRN,    KC_TILD,             KC_PPLS,    KC_1,    KC_2,    KC_3,    KC_PMNS,    KC_EQUAL,
    _______,   KC_HASH,    KC_DLR,    KC_LCBR,    KC_RCBR,    KC_GRV,           KC_PAST,    KC_4,    KC_5,    KC_6,    KC_SLASH, KC_BSLS,
    _______,   KC_PERC,    KC_CIRC,    KC_LBRC,    KC_RBRC,    KC_PIPE,         KC_AMPR,    KC_7,    KC_8,    KC_9,  KC_0, _______,
               _______, _______, _______, KC_ITRMSPCE_L, KC_ITRMSPCE_R,             _______, _______, _______, _______, _______, _______,
                                _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______
),
[_QWERTY] = LAYOUT( \
    KC_TAB,    KC_Q,    LT(0,KC_W),    KC_E, LT(0,KC_R), LT(0,KC_T),                             KC_Y,    KC_U,    LT(0,KC_I),    KC_O,    KC_P,    KC_MINUS,
    KC_LSFT,   LT(0,KC_A),    LT(0,KC_S),    KC_D,    LT(0,KC_F),    KC_G,                       KC_H,    KC_J,    LT(0,KC_K),    KC_L,    KC_QUOT, KC_SCLN,
    LT(0,KC_TILD), LT(0,KC_Z), LT(0,KC_X), LT(0,KC_C), LT(0,KC_V), LT(0,KC_B),                   LT(0,KC_N), KC_M, KC_COMM, KC_DOT, KC_SLASH, DRAGSCROLL_MODE_TOGGLE,
                KC_BSPC, KC_DEL, LT(0,KC_MPLY), KC_TAB_L, KC_TAB_R,                  KC_SPCLEFT, KC_SPCRGHT, KC_LGUI, MO(_SYMBOLS), KC_ENTER, KC_SPACE,
                                KC_LGUI, KC_LALT, MO(_SYMBOLS), KC_ESC,        KC_MULTILNE, KC_LCTL, KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT
),
[_MOUSE] = LAYOUT( \
    _______, _______, _______, _______, _______, _______,                               _______, _______, KC_MS_BTN3, _______, _______, KC_MACSHOT,
    _______, _______, _______, _______, _______, _______,                               _______, KC_MS_BTN1, KC_MS_BTN2, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                               _______, _______, _______, _______, _______, _______,
                _______, _______,  _______, KC_MACLOCK, KC_CAD,         _______, _______, _______, _______, _______, _______,
                                _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______
)
};

