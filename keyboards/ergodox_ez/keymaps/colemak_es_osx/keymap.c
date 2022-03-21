/*
  Copyright 2019 Mario Arias <mario@marioarias.org>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "version.h"

#include "keymap_spanish.h"

enum layers {
    BASE = 0,   //Colemak
    QWERTY,     //Qwerty
    FN,         //Colemak but FN1 to FN12 instead of numbers
    NUM,        //Numpad
    MOUSE,      //Mouse and media controls
    IDEA        //Shortcuts for IDEA / Other tools
};

//Special paste
#define S_PASTE     LSFT(LGUI(KC_V))
//tmux prefix
#define T_PREFIX    LCTL(KC_B)
// Column mode
#define I_COLUMN    ALGR(LCTL(LGUI(ES_MINS)))
// Terminal
#define I_TERM      ALGR(KC_F12)
// Line comment
#define I_LN_COM    LCTL(LGUI(KC_7))
// Block comment
#define I_BK_COM    LCTL(LGUI(KC_8))
// Reformat code
#define I_REFORM    LALT(LGUI(KC_L))
// Rename
#define I_RENAME    LSFT(KC_F6)
// Find usages
#define I_FUSAGE    LALT(KC_F7)
// Code for Packt
#define P_CODE      LCTL(ALGR(KC_X))
// Search
#define I_SEARCH    LCTL(LSFT(KC_F))


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Colemak MacOS Spanish layer
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   Esc  |  1 ! | 2 "  | 3 ·  | 4 $  | 5 %  |  º \ |           | ¡ ¿  |  6 & | 7 /  |  8 ( | 9 )  | 0 =  | Backsp |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   TAB  |   Q  |   W  |   F  |   P  |   G  | Home |           | End  |   J  |   L  |   U  |   Y  |  Ñ   |  ' ?   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  CAPS  |   A  |   R  |   S  |   T  |   D  |------|           |------|   H  |   N  |   E  |   I  |  O   |  ENT   |
 * |--------+------+------+------+------+------|  <>  |           |  -_  |------+------+------+------+------+--------|
 * | Shift  |   Z  |   X  |   C  |   V  |   B  |      |           |      |   K  |   M  |  , ; |  . : |  UP  | Shift  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Del  | PgUp |Ctl/PD|Alt/[ |Cmd/] |                                       |Cmd/{ |Alt/} | LEFT | DOWN | RIGHT|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,--------------.        ,--------------.
 *                                        | Num  | Mouse |        | Qwer | Ctrl  |
 *                                 ,------|------|-------|        |------+-------+------.
 *                                 |      |      | FN    |        |SPaste|       |      |
 *                                 |LShift|Backsp|-------|        |------|  ENT  |Space |
 *                                 |      |      | IDEA  |        | T-pre|       |      |
 *                                 `---------------------'        `---------------------'
 */
[BASE] = LAYOUT_ergodox(
// left hand
        KC_ESC,     KC_1,       KC_2,           KC_3,           KC_4,        KC_5,        ES_LABK,
        KC_TAB,     KC_Q,       KC_W,           KC_F,           KC_P,        KC_G,        KC_HOME,
        KC_CAPS,    KC_A,       KC_R,           KC_S,           KC_T,        KC_D,
        KC_LSFT,    KC_Z,       KC_X,           KC_C,           KC_V,        KC_B,        KC_GRV,
        KC_DEL,     KC_PGUP,    CTL_T(KC_PGDN), ALT_T(ES_GRV),  GUI_T(ES_PLUS),

                                                                            DF(NUM),    DF(MOUSE),
                                                                                        DF(FN),
                                                                KC_LSFT,    KC_BSPC,    MO(IDEA),

// right hand
        ES_IEXL,        KC_6,           KC_7,       KC_8,       KC_9,       KC_0,       KC_BSPC,
        KC_END,         KC_J,           KC_L,       KC_U,       KC_Y,       ES_NTIL,    ES_QUOT,
                        KC_H,           KC_N,       KC_E,       KC_I,       KC_O,       KC_ENT,
        ES_MINS,        KC_K,           KC_M,       KC_COMM,    KC_DOT,     KC_UP,      KC_RSFT,
                                GUI_T(ES_ACUT), ALT_T(KC_BSLS), KC_LEFT,    KC_DOWN,    KC_RIGHT,

        DF(QWERTY),     KC_RCTL,
        S_PASTE,
        T_PREFIX,       KC_ENT,     KC_SPC
),
/* Keymap 1: Spanish QWERTY layer (games) //Will probably change it for a Linux/Windows Colemak layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   Ñ  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       | Base |      |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 |      |      |------|       |------|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
[QWERTY] = LAYOUT_ergodox(
  // left hand
        _______,        _______,    _______,    _______,    _______,    _______,    _______,
        _______,        KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       _______,
        _______,        KC_A,       KC_S,       KC_D,       KC_F,       KC_G,
        _______,        KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       _______,
        _______,        _______,    _______,    _______,    _______,

                                                                        _______,    _______,
                                                                                    _______,
                                                        _______,        _______,    _______,

// right hand
        _______,        _______,    _______,    _______,    _______,    _______,    _______,
        _______,        KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       _______,
                        KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    _______,
        _______,        KC_N,       KC_M,       _______,    _______,    _______,    _______,
                                    _______,    _______,    _______,    _______,    _______,
        DF(BASE),   _______,
        _______,
        _______,    _______,    _______
),
/* Keymap 2: Function Layer
*
* ,--------------------------------------------------.           ,--------------------------------------------------.
* |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  | F10  | F11  | F12  |        |
* |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
* |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
* |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
* |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
* |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
* |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
* `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
*   |      |      |      |      |      |                                       |      |      |      |      |      |
*   `----------------------------------'                                       `----------------------------------'
*                                        ,-------------.       ,-------------.
*                                        |      |      |       |      |      |
*                                 ,------|------|------|       |------+------+------.
*                                 |      |      | Base |       |      |      |      |
*                                 |      |      |------|       |------|      |      |
*                                 |      |      |      |       |      |      |      |
*                                 `--------------------'       `--------------------'
*/
[FN] = LAYOUT_ergodox(
        // left hand
        _______,        KC_F1,        KC_F2,       KC_F3,      KC_F4,       KC_F5,      KC_F6,
        _______,        _______,      _______,     _______,    _______,     _______,    _______,
        _______,        _______,      _______,     _______,    _______,     _______,
        _______,        _______,      _______,     _______,    _______,     _______,    _______,
        _______,        _______,      _______,     _______,    _______,

                                                                            _______,    _______,
        DF(BASE),
        _______,        _______,      _______,

// right hand
        KC_F7,          KC_F8,        KC_F9,        KC_F10,     KC_F11,     KC_F12,     _______,
        _______,        _______,      _______,      _______,    _______,    _______,    _______,
                        _______,      _______,      _______,    _______,    _______,    _______,
        _______,        _______,      _______,      _______,    _______,    _______,    _______,
        _______,        _______,      _______,      _______,    _______,

        _______,        _______,
        _______,
        _______,        _______,      _______
),
/* Mouse and media controls
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   Esc  |      |      |      |      |      | Play |           | Vol+ |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | Ms U |      |      |      |           |      |      |      | Wh U |      |      |        |
 * |--------+------+------+------+------+------| Rwd  |           | Vol- |------+------+------+------+------+--------|
 * |        |      | Ms L | Ms D | Ms R |      |------|           |------|      | Wh L | Wh D | Wh R |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | Acc0 | Acc1 | Acc2 |      | Fwd  |           | Mute |      | Btn1 | Btn2 | Btn3 |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  Num | Base |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------        |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[MOUSE] = LAYOUT_ergodox(
// left hand
        KC_ESC,         XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_MPLY,
        XXXXXXX,        XXXXXXX,    XXXXXXX,    KC_MS_U,    XXXXXXX,    XXXXXXX,    KC_MRWD,
        XXXXXXX,        XXXXXXX,    KC_MS_L,    KC_MS_D,    KC_MS_R,    XXXXXXX,
        XXXXXXX,        XXXXXXX,    KC_ACL0,    KC_ACL1,    KC_ACL2,    XXXXXXX,    KC_MFFD,
        XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,

                                                                            DF(NUM),   DF(BASE),
                                                                                        XXXXXXX,
                                                                XXXXXXX,    XXXXXXX,    XXXXXXX,

// right hand
        KC_VOLU,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        KC_VOLD,        XXXXXXX,    XXXXXXX,    KC_WH_U,    XXXXXXX,    XXXXXXX,    XXXXXXX,
                        XXXXXXX,    KC_WH_L,    KC_WH_D,    KC_WH_R,    XXXXXXX,    XXXXXXX,
        KC_MUTE,        XXXXXXX,    KC_BTN1,    KC_BTN2,    KC_BTN3,    XXXXXXX,    XXXXXXX,
        XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,

        XXXXXXX,        XXXXXXX,
        XXXXXXX,
        XXXXXXX,        XXXXXXX,    XXXXXXX
),
/* Num pad
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |  (   |  )   |  =   |  /   |  *   |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |  Up  |      |      |      |           |      |      |  7   |  8   |  9   |  -   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | Left | Down |Right |      |------|           |------|      |  4   |  5   |  6   |  +   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |  1   |  2   |  3   |Enter |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |  0   |  0   |  ,   |Enter |  .   |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Base |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------        |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[NUM] = LAYOUT_ergodox(
// left hand
        _______,        _______,    _______,    _______,    _______,  _______,    _______,
        _______,        _______,    _______,      KC_UP,    _______,  _______,    _______,
        _______,        _______,    KC_LEFT,    KC_DOWN,    KC_RIGHT, _______,
        _______,        _______,    _______,    _______,    _______,  _______,    _______,
        _______,        _______,    _______,    _______,    _______,

        DF(BASE),   _______,
        _______,
        _______,        _______,    _______,

// right hand
        _______,        LSFT(KC_8), LSFT(KC_9), KC_PEQL,    KC_PSLS,    KC_PAST,    _______,
        _______,        _______,    KC_P7,      KC_P8,      KC_P9,      KC_PMNS,    _______,
                        _______,    KC_P4,      KC_P5,      KC_P6,      KC_PPLS,    _______,
        _______,        _______,    KC_P1,      KC_P2,      KC_P3,      KC_PENT,    _______,
                                    KC_P0,      KC_P0,      KC_PDOT,    KC_PENT,    KC_DOT,

        _______,        _______,
        _______,
        _______,        _______,    _______
),
/* IDEA
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      | Renm |           | Usag |      | LnCm | BkCm |      | Term |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |Search|      |      |      |           |      |      | Refm |      |      |      |        |
 * |--------+------+------+------+------+------|      |           | Col  |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | Code |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------        |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[IDEA] = LAYOUT_ergodox(

//Left hand
        _______,        _______,    _______,    _______,    _______,    _______,    I_RENAME,
        _______,        _______,    _______,    I_SEARCH,   _______,    _______,    _______,
        _______,        _______,    _______,    _______,    _______,    _______,
        _______,        _______,    P_CODE,     _______,    _______,    _______,    _______,
        _______,        _______,    _______,    _______,    _______,

                                                                        _______,    DF(BASE),
                                                                                    _______,
                                                        _______,        _______,    _______,

// right hand
        I_FUSAGE,       _______,    I_LN_COM,   I_BK_COM,   _______,    I_TERM,    _______,
        I_COLUMN,       _______,    I_REFORM,   _______,    _______,    _______,    _______,
                        _______,    _______,    _______,    _______,    _______,    _______,
        _______,        _______,    _______,    _______,    _______,    _______,    _______,
                                _______,        _______,    _______,    _______,    _______,

        _______,        _______,
        _______,
        _______,        _______,    _______
)
};


void led_1_off(void) {
    ergodox_right_led_1_off();
}

void led_2_off(void) {
    ergodox_right_led_2_off();
}

void led_3_off(void) {
    ergodox_right_led_3_off();
}

//Runs just one time when the keyboard initializes
void matrix_init_use(void) {
    led_1_off();
    led_2_off();
    led_3_off();
}

// Value to use to switch LEDs on. The default value of 255 is far too bright.
static const uint8_t max_led_value = 20;


void led_1_on(void) {
    ergodox_right_led_1_on();
    ergodox_right_led_1_set(max_led_value);
}

void led_2_on(void) {
    ergodox_right_led_2_on();
    ergodox_right_led_2_set(max_led_value);
}

void led_3_on(void) {
    ergodox_right_led_3_on();
    ergodox_right_led_3_set(max_led_value);
}

layer_state_t layer_state_set_user(layer_state_t state) {

    if(layer_state_cmp(state ,IDEA)) {
        led_1_on();
        led_3_on();
    } else {
        led_1_off();
        led_3_off();
    }

  return state;
};

void matrix_scan_user(void) {

    ergodox_board_led_off();
    led_1_off();
    led_2_off();
    led_3_off();

    if(layer_state_cmp(default_layer_state, QWERTY)) {
        led_3_on();
    }

    if(layer_state_cmp(default_layer_state, FN)) {
        led_2_on();
    }

    if(layer_state_cmp(default_layer_state, NUM)) {
        led_2_on();
        led_3_on();
    }

    if(layer_state_cmp(default_layer_state, MOUSE)) {
        led_1_on();
    }
};
