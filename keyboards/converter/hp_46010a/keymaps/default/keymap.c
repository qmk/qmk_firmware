/*
Copyright 2018 listofoptions <listofoptions@gmail.com>

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* ,---------.  ,---------------------------------------------------------.  ,---------.    ,-------------------.
     * | esc|xxxx|  |   f1|   f2|   f3|   f4|xxxx|xxxx|   f5|   f6|   f7|   f8|  |xxxx|xxxx|    |  f9| f10| f11| f12|
     * `---------'  `---------------------------------------------------------'  `---------'    `-------------------'
     * ,------------------------------------------------------------------------..---------.    ,-------------------.
     * |     `|   1|   2|   3|   4|   5|   6|   7|   8|   9|   0|   -|   =| back||ins |home|    |   *|   /|   +|   -|
     * |------------------------------------------------------------------------||---------|    |-------------------|
     * |     tab|   q|   w|   e|   r|   t|   y|   u|   i|   o|   p|   [|  ]|   \||del | end|    |   7|   8|   9|pade|
     * |------------------------------------------------------------------------||---------|    |-------------------|
     * |caps|ctrl|   a|   s|   d|   f|   g|   h|   j|   k|   l|   ;|   '|   retr||xxxx|pgup|    |   4|   5|   6|   ,|
     * |------------------------------------------------------------------------------------    |-------------------|
     * |del |lsft  |   z|   x|   c|   v|   b|   n|   m|   ,|   .|   /|rsft  | app|  up|pgdn|    |   1|   2|   3| tab|
     * |-------------------------------------------------------------------------|---------|    |---------------    |
     * | gui|      |lalt|              space                    |ralt|      |left|down|rght|    |        0|   .|    |
     * `-----------------------------------------------------------------------------------'    `-------------------'
     */
     
    [0] = LAYOUT(
        KC_ESC, KC_NO,   KC_F1, KC_F2, KC_F3, KC_F4,KC_NO,  KC_NO,   KC_F5, KC_F6, KC_F7, KC_F8,                   KC_NO,   KC_NO,     KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
        KC_GRAVE,     KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_BSPC,     KC_INS,  KC_HOME,   KC_PAST, KC_PSLS, KC_PPLS, KC_PMNS, \
        KC_TAB,          KC_Q,KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,     KC_DEL,  KC_END,    KC_P7,   KC_P8,   KC_P9,   KC_PENT, \
        KC_CAPS, KC_LCTL,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,        KC_ENT,  KC_NO,   KC_PGUP,   KC_P4,   KC_P5,   KC_P6,   KC_PCMM, \
        KC_DEL,  KC_LSFT,     KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,KC_RSFT, KC_APP,  KC_UP,   KC_PGDN,   KC_P1,   KC_P2,   KC_P3,   KC_TAB,  \
        KC_LGUI,               KC_LALT,              KC_SPACE                    ,               KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT,        KC_P0,       KC_PDOT           \
    )
} ;