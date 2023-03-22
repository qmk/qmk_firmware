#include QMK_KEYBOARD_H

enum _layer {
    _BASE,
    _RGB
};

//  ESC    F1   F2   F3   F4   F5   F6   F7   F8   F9   F10  F11  F12             Prt  Scr   Pau
//  `    1    2    3    4    5    6    7    8    9    0    -    =    BSpc         Ins  Home  PgUp
//  Tab  Q    W    E    R    T    Y    U    I    O    P    [    ]    \\           Del  End   PgDn
//  Caps A    S    D    F    G    H    J    K    L    ;    '         Enter
//  Sh_L      Z    X    C    V    B    N    M    ,    .    /       Sh_R                Up
//  Ct_L    Win_L   Alt_L      SPACE          Alt_R   FN  KC_RGUI  Ct_R          Left Down Right 0

/* Standard Arrangement
 * ┌───┐      ┌───┬───┬───┬───┐  ┌───┬───┬───┬───┐  ┌───┬───┬───┬───┐┌───┬───┬───┐
 * │  00  │      │  01  │  02  │  03  │  04  │  │  05  │  06  │  07  │  08  │  │  09  │  0a  │  0b  │  0c  ││  0d  │  0e  │  3d  │
 * └───┘      └───┴───┴───┴───┘  └───┴───┴───┴───┘  └───┴───┴───┴───┘└───┴───┴───┘
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐┌───┬───┬───┐
 * │  10  │  11  │  12  │  13  │  14  │  15  │  16  │  17  │  18  │  19  │  1a  │  1b  │  1c  │      1e      ││  5b  │  5c  │  3e  │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤├───┼───┼───┤
 * │     20   │  21  │  22  │  23  │  24  │  25  │  26  │  27  │  28  │  29  │  2a  │  2b  │  2c  │  2d      ││  2e  │  5d  │  5e  │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤└───┴───┴───┘
 * │      30    │  31  │  32  │  33  │  34  │  35  │  36  │  37  │  38  │  39  │  3a  │  3b  │      3c        │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤        ┌───┐
 * │       40       │  41  │  42  │  43  │  44  │  45  │  46  │  47  │  48  │  49  │  4a  │        4b          │        │  4c  │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤┌───┼───┼───┐
 * │   50   │   51   │   52   │                      53                        │   54   │   55   │   56   │   57   ││  58  │  59  │  5a  │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘└───┴───┴───┘
 */



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {



	[0] = LAYOUT(
		KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_PSCR, KC_SLCK, KC_PAUS, 
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,     KC_ENT,  
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,             KC_RSFT,                KC_UP,
		KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT,   MO(1), KC_APP, KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT
	),
	[1] = LAYOUT(
        _______, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______,          _______, _______, _______, 
		_______, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
		_______, _______, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT, _______, _______, _______,
		_______, _______, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______,
		_______, _______, _______, RGB_HUI, _______, _______, _______, NK_TOGG, _______, _______, _______,              _______,               RGB_MOD,
		EE_CLR, _______, _______,                            _______,                            _______, _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
	),

};



