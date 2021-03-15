/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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
#include <stdint.h>
//#include "drivers/chibios/uart.h"
#ifdef CONSOLE_ENABLE
#    include <print.h>
#endif
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _FN 1

#define BLUETOOTH_ON()

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(/* QWERTY */
                     KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE, KC_AUDIO_VOL_UP, KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_BSPACE, KC_DEL, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRACKET, KC_RBRACKET, KC_NONUS_BSLASH, KC_PGUP, KC_CAPSLOCK, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOTE, KC_ENTER, KC_PGDOWN, KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RSHIFT, KC_UP, KC_END, KC_LCTRL, KC_LGUI, KC_LALT, KC_SPACE, KC_RALT, MO(_FN), KC_RCTRL, KC_LEFT, KC_DOWN, KC_RIGHT),

    /* FN1 - SEE readme.md
     * ,- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -.
     * |   Quit  |   F1    |    F2   |   F3    |   F4    |   F5    |    F6   |   F7    |    F8   |    F9   |   F10   |   F11   |   F12   |  Trns   |  Trns   |   DFU   |
     * |   All   |         |         |         |         |         |         |         |         |         |         |         |         |         |         |  Reset  |
     * |- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - - - - - - -+- - - - -|
     * |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |       Delete      |   Lock  |
     * |         |         |         |         |         |         |         |         |         |         |         |         |         |                   |Shortcut |
     * |- - - - - - - +- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - - - - +- - - - -|
     * |     Trns     |   RGB   |   RGB   |   RGB   |   RGB   | RGB Hue | RGB Hue | RGB Sat | RGB Sat |  Trns   |   Trns  |   Trns  |   Trns  |     Trns     |   Trns  |
     * |              |  Toggle |   Mode  | Increase| Decrease| Increase| Decrease| Increase| Decrease|         |         |         |         |              |         |
     * |- - - - - - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - - - - - - - -+- - - - -|
     * |      Trns       |   Trns  |   Trns  |   Trns  |   Trns  |   Trns  |  Trns   |  Trns   |   Trns  |   Trns  |  Trns   |   Trns  |        Trns         |   Trns  |
     * |                 |         |         |         |         |         |         |         |         |         |         |         |                     |         |
     * |- - - - - - - - - - - +- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - - - - - +- - - - -+- - - - -+
     * |         Trns         |Backlight|Backlight|Backlight|Backlight|   Trns  |  Trns   |   Trns  |   Trns  |   Trns  |   Trns  |     Trns       |  Trns   |  Trns   |
     * |                      |  Toggle | Increase| Decrease|   Step  |         |         |         |         |         |         |                |         |         |
     * |- - - - - +- - - - - - +- - - - - - + - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -+- - - - -|
     * |   Trns   |    Trns    |    Trns    |                             Trns                             |  Trns   |  Trns   |  Trns   |  Trns   |   Trns  |  Trns   |
     * |          |            |            |                                                              |         |         |         |         |         |         |
     * `- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -'
     */

    [_FN] = LAYOUT(/* FUNCTION */
                   RGB_TOG, RGB_MODE_PLAIN, RGB_MODE_BREATHE, RGB_MATRIX_CYCLE_PINWHEEL, RGB_MATRIX_GRADIENT_UP_DOWN, RGB_MODE_RAINBOW, RGB_MODE_SWIRL, RGB_MATRIX_CYCLE_ALL, RGB_HUI, RGB_SAI, RGB_VAI, KC_F11, KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_BTN1, KC_MS_BTN2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, LCTL(LALT(LGUI(KC_S))), KC_TRNS, RGB_TOG, KC_MS_UP, RGB_VAI, LCTL(RCTL(RESET)), RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_WH_UP, KC_TRNS, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_WH_DOWN, KC_TRNS, BL_TOGG, BL_INC, BL_DEC, BL_STEP, OUT_AUTO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT)};
uint8_t blueToothOn = 0;
void    keyboard_pre_init_user() {
    setPinOutput(B0);
    writePinLow(B0);
    //uart_init(9600);
}

static inline void forward_keycodes_through_bluetooth(uint16_t keycode, keyrecord_t* record) {}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
    switch (keycode) {
        case OUT_AUTO:
            blueToothOn ^= 1;
            break;

        default:
            break;
    }

    return true;
}