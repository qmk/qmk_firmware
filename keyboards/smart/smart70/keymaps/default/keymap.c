#include QMK_KEYBOARD_H






/* Standard Arrangement
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │  00  │  01  │  02  │  03  │  04  │  05  │  06  │  07  │  08  │  09  │  0a  │  0b  │  0c  │      0d      │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     10   │  11  │  12  │  13  │  14  │  15  │  16  │  17  │  18  │  19  │  1a  │  1b  │  1c  │  1d      │  
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      20    │  21  │  22  │  23  │  24  │  25  │  26  │  27  │  28  │  29  │  2a  │  2b  │      2c        │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤    
 * │       30       │  31  │  32  │  33  │  34  │  35  │  36  │  37  │  38  │  39  │  3a  │        3b          │ 
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │   40   │   41   │   42   │                      43                        │   48   │   49   │   4a   │   4b   │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
/*
 *  ESC  1    2    3    4    5    6    7    8    9    0    -    =    BSpc
 *  Tab  Q    W    E    R    T    Y    U    I    O    P    [    ]    \\
 *  Caps A    S    D    F    G    H    J    K    L    ;    '         Enter
 *  Sh_L      Z    X    C    V    B    N    M    ,    .    /       Sh_R
 *  Ct_L    Win_L   Alt_L      SPACE          Alt_R   FN  KC_RGUI  Ct_R
 */
/*
#define MATRIX_ROW_PINS \
    { A0, A1, A2, A3, A4 }
#define MATRIX_COL_PINS \
    { B0, B1, B2, B3, B4, B5, B6, B7, B10, B11, B12, B15, A15, C14 }
*/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {



	[0] = LAYOUT(
		KC_ESC , KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL, KC_BSPC, 
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,     KC_ENT,  
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,             KC_RSFT,                
		KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT,  KC_APP, KC_RCTL, MO(1)
	),
	[1] = LAYOUT(
		 KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_MUTE,
		_______, KC_WHOM, KC_MYCM, KC_MAIL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,              _______,              
		_______, _______, _______,                            _______,                            _______, _______, _______, _______
	),

};



