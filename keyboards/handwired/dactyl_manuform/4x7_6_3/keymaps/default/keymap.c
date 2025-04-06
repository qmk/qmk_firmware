/*
Copyright 2025 Agia5 <fa.giaquinto93@gmail.com>

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

#define _BASE 0
#define _RAISE 1
#define _LOWER 2

#define SFT_ESC  SFT_T(KC_ESC)
#define CTL_BSPC CTL_T(KC_BSPC)
#define ALT_SPC  ALT_T(KC_SPC)
#define SFT_ENT  SFT_T(KC_ENT)

#define KC_ML KC_MS_LEFT
#define KC_MR KC_MS_RIGHT
#define KC_MU KC_MS_UP
#define KC_MD KC_MS_DOWN
#define KC_MB1 KC_MS_BTN1
#define KC_MB2 KC_MS_BTN1

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

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
    [_BASE] = LAYOUT(
    KC_ESC,  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,  KC_MINS,
    KC_TAB,  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,  KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                 KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
             KC_LBRC, KC_RBRC,  KC_RBRC,                                                                 KC_PLUS, KC_EQL,  KC_EQL
    ),

    [_LOWER] = LAYOUT(
    KC_ESC,  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,  KC_MINS,
    KC_TAB,  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,  KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                 KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
             KC_LBRC, KC_RBRC,  KC_RBRC,                                                                 KC_PLUS, KC_EQL,  KC_EQL
    ),

    [_RAISE] = LAYOUT(
    KC_ESC,  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,  KC_MINS,
    KC_TAB,  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,  KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                 KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
             KC_LBRC, KC_RBRC,  KC_RBRC,                                                                 KC_PLUS, KC_EQL,  KC_EQL
    )
};
