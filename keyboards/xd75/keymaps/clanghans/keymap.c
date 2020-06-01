/* Copyright 2020 Chris Langhans
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Layer shorthand
#define _QW 0
#define _FN 1

const uint16_t PROGMEM
               keymaps[][MATRIX_ROWS][MATRIX_COLS] =
        {
            /* QWERTY
             * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
             * │  Esc │   1  │   2  │   3  │   4  │   5  │ Bsp  │   6  │   7  │   8  │   9  │   0  │  -   │  =   │ ~    │
             * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
             * │ Tab  │   Q  │   W  │   E  │   R  │   T  │ Del  │   Y  │   U  │   I  │   O  │   P  │  [   │  ]   │ \    │
             * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
             * │ Ctrl │   A  │   S  │   D  │   F  │   G  │      │   H  │   J  │   K  │   L  │   ;  │   '  │ Home │ PgUp │
             * ├──────┼──────┼──────┼──────┼──────┼──────┼Enter ┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
             * │ Shift│   Z  │   X  │   C  │   V  │   B  │      │   N  │   M  │   ,  │   .  │   /  │ Shft │ End  │ PgDn │
             * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
             * │ Ctrl │ Gui  │ Alt  │  FN  │     Bsp     │ N/A  │    Space    │ Alt  │ Ctrl │ Left │ Down │  Up  │ Right│
             * └──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘
             */

            [_QW] =
                {
                    {KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_BSPC, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_GRV},
                    {KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_DEL, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS},
                    {KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_ENT, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_HOME, KC_PGUP},
                    {KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_NO, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_END, KC_PGDN},
                    {KC_LCTL, KC_LGUI, KC_LALT, MO(_FN), KC_NO, KC_BSPC, KC_NO, KC_SPC, KC_NO, KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT},
                },

            /* FUNCTION
             * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
             * │Alt F4│  F1  │  F2  │  F3  │  F4  │  F5  │      │  F6  │  F7  │  F8  │  F9  │  F10 │  F11 │  F12 │ # Lk │
             * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
             * │      │      │      │      │RGBHUI│BL_TOG│      │  7   │  8   │  9   │  /   │      │      │      │      │
             * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
             * │      │      │      │      │RGBSAI│RGBMOD│      │  4   │  5   │  6   │  *   │      │      │      │Reset │
             * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
             * │      │      │      │      │RGBVAI│      │      │  1   │  2   │  3   │  -   │      │      │      │      │
             * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
             * │      │      │      │      │      │      │      │  0   │      │  ,   │  +   │      │      │      │      │
             * └──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘
             */

            [_FN] = {
                {LALT(KC_F4), KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, _______, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NLCK},
                {_______, _______, _______, _______, RGB_HUI, RGB_TOG, _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_SLASH, _______, _______, _______, _______},
                {_______, _______, _______, _______, RGB_SAI, RGB_MOD, _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_ASTERISK, _______, _______, _______, RESET},
                {_______, _______, _______, _______, RGB_VAI, _______, _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_MINUS, _______, _______, _______, _______},
                {_______, _______, _______, _______, _______, _______, _______, KC_KP_0, _______, KC_KP_DOT, KC_KP_PLUS, _______, _______, _______, _______},
            }};
