#include QMK_KEYBOARD_H

/*
This is the c configuration file for the keymap

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

#define _QWERTY      0
#define _RIGHT2LEFT  1
#define _NUMPAD      2

/* Base (qwerty)
     * ,-------------------------------------------------------,   ,-------------------------------------------------------,
     * |  Esc |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   |   7  |   8  |   9  |   0  |   -  |   =  |   \  |  BS  |
     * |------+------+------+------+------+------+------+------|   |------+------+------+------+------+------+------+------|
     * |M_RSTP|  Tab |   q  |   w  |   e  |   r  |   t  |QKBOOT|   |  F8  |   y  |   u  |   i  |   o  |   p  |   [  |   ]  |
     * |------+------+------+------+------+------+------+------|   |------+------+------+------+------+------+------+------|
     * |M_REC1| Caps |   a  |   s  |   d  |   f  |   g  |  F7  |   |  F9  |   h  |   j  |   k  |   l  |   ;  |   "  |ENTER |
     * |------+------+------+------+------+------+------+------'   '------+------+------+------+------+------+------+------|
     * |M_REC2| Shift|   z  |   x  |   c  |   v  |   b  |                 |   n  |   m  |   ,  |   .  |   /  |Shift | Ctrl |
     * '------+------+------+------+------+------+------'                 '------+------+------+------+------+------+------'
     *        | Ctrl | Wint |  Alt | INS  |                                             |  Up  | Down | Left | Right|
     *        '------+------+------+------+------,                               ,------+------+------+------+------'
     *                             | TT(1)|SPACE |                               | SPACE|  BS  |
     *                             '------+------+------'                 ,------+------+------'
     *                                    | ESC  |ENTER |                 | HOME | END  |
     *                                    '------+------'                 '------+------'
     *                                    |  DEL |  F2  |                 | PGUP | PGDN |
     *                                    '------+------'                 '------+------'
     */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_5x8(
        // left hand
        KC_ESC,    KC_GRV,  KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,
        DM_RSTP,   KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,   QK_BOOT,
        DM_REC1,   KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,   KC_G,   KC_F7,
        DM_REC2,   KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,
                   KC_LCTL, KC_LGUI, KC_LALT, KC_INS,
				    TT(1), KC_SPC,
                                    KC_ESC, KC_ENT,
                                    KC_DEL, KC_F2,
        // right hand
                          KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSLS,   KC_BSPC,
                          KC_F8,   KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_LBRC,   KC_RBRC,
                          KC_F9,   KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT,   KC_ENT,
                                   KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,   KC_RCTL,
                                            KC_UP,    KC_DOWN, KC_LEFT,  KC_RGHT,
             KC_BSPC, KC_SPC,
             KC_HOME, KC_END,
             KC_PGUP, KC_PGDN
    ),
/* Base (right to left on hold button)
     * ,-------------------------------------------------------,   ,-------------------------------------------------------,
     * |  BS  |   \  |   =  |   -  |   0  |   9  |   8  |   7  |   |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------|   |------+------+------+------+------+------+------+------|
     * |   [  |   ]  |   p  |   o  |   i  |   u  |   y  |QKBOOT|   |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------|   |------+------+------+------+------+------+------+------|
     * |M_PLY1|   "  |   ;  |   l  |   k  |   j  |   h  |PRSCRN|   |      |      | Left | Down |  Up  | Right|      |ENTER |
     * |------+------+------+------+------+------+------+------'   '------+------+------+------+------+------+------+------|
     * |M_PLY2|MShift|   /  |   .  |   ,  |   m  |   n  |                 |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------'                 '------+------+------+------+------+------+------'
     *        |MCtrl | MAlt |  DEL |  BS  |                                             |      |      |      |      |
     *        '------+------+------+------+------,                               ,------+------+------+------+------'
     *                             |      |SPACE |                               | SPACE|  BS  |
     *                             '------+------+------'                 ,------+------+------'
     *                                    | END  |ENTER |                 | HOME | END  |
     *                                    '------+------'                 '------+------'
     *                                    | PGDN | PGUP |                 | PGUP | PGDN |
     *                                    '------+------'                 '------+------'
     */

    [_RIGHT2LEFT] = LAYOUT_5x8(
        // left hand
        KC_BSPC,   KC_BSLS,  KC_EQL,    KC_MINS,    KC_0,   KC_9,   KC_8,   KC_7,
        KC_RBRC,   KC_LBRC,  KC_P,    KC_O,    KC_I,   KC_U,   KC_Y,   QK_BOOT,
        DM_PLY1,   KC_QUOT, KC_SCLN,    KC_L,    KC_K,   KC_J,   KC_H,   KC_PSCR,
        DM_PLY2,   OSM(MOD_LSFT), KC_SLSH,    KC_DOT,    KC_COMM,   KC_M,    KC_N,
                   OSM(MOD_LCTL), OSM(MOD_LALT), KC_DEL, KC_BSPC,
                                    KC_NO, KC_SPC,
                                    KC_ESC, KC_ENT,
                                    KC_DEL, KC_F2,
        // right hand
                          KC_NO,    KC_NO,    KC_NO,    KC_NO,     KC_NO,  KC_NO,   KC_NO,   KC_BSPC,
                          KC_NO,   KC_NO,    KC_NO,    KC_NO,     KC_NO,     KC_NO,     KC_NO,   KC_NO,
                          KC_NO,   KC_LEFT,    KC_DOWN,    KC_UP,     KC_RIGHT,     KC_SCLN,  KC_NO,   KC_ENT,
                                   KC_NO,    KC_NO,    KC_NO,  KC_NO, KC_NO,  KC_NO,   KC_NO,
                                            KC_NO,    KC_NO, KC_NO,  KC_NO,
             KC_BSPC, KC_SPC,
             KC_HOME, KC_END,
             KC_PGUP, KC_PGDN
    ),

/* Base (qwerty)
     * ,-------------------------------------------------------,   ,-------------------------------------------------------,
     * |  Esc |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   |   7  |   8  |   9  |   0  |   -  |   =  |   \  |  BS  |
     * |------+------+------+------+------+------+------+------|   |------+------+------+------+------+------+------+------|
     * |  F3  |  Tab |   q  |   w  |   e  |   r  |   t  |  F6  |   |  F8  |   y  |   u  |   i  |   o  |   p  |   [  |   ]  |
     * |------+------+------+------+------+------+------+------|   |------+------+------+------+------+------+------+------|
     * |  F4  | Caps |   a  |   s  |   d  |   f  |   g  |  F7  |   |  F9  |   h  |   j  |   k  |   l  |   ;  |   "  |ENTER |
     * |------+------+------+------+------+------+------+------'   '------+------+------+------+------+------+------+------|
     * |  F5  | Shift|   z  |   x  |   c  |   v  |   b  |                 |   n  |   m  |   ,  |   .  |   '  |Shift | Ctrl |
     * |------+------+------+------+------+------+------'                 '------+------+------+------+------+------+------'
     *        | Ctrl | Wint |  Alt | PSCR |                                             |  Up  | Down | Left | Right|
     *        '------+------+------+------+------,                               ,------+------+------+------+------'
     *                             |  BS  |SPACE |                               | SPACE|  BS  |
     *                             '------+------+------'                 ,------+------+------'
     *                                    | ESC  |ENTER |                 | HOME | END  |
     *                                    '------+------'                 '------+------'
     *                                    |  DEL |  F2  |                 | PGUP | PGDN |
     *                                    '------+------'                 '------+------'
     */
/*
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_5x8(
        // left hand
        KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,
        KC_F3,   KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,   KC_F6,
        KC_F4,   KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,   KC_G,   KC_F7,
        KC_F5,   KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,
                 KC_LCTL, KC_LGUI, KC_LALT, KC_PSCR,
                                    KC_BSPC, KC_SPC,
                                    KC_ESC, KC_ENT,
                                    KC_DEL, KC_F2,
        // right hand
                          KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSLS,   KC_BSPC,
                          KC_F8,   KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_LBRC,   KC_RBRC,
                          KC_F9,   KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT,   KC_ENT,
                                   KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_QUOT,  KC_RSFT,   KC_RCTL,
                                            KC_UP,    KC_DOWN, KC_LEFT,  KC_RGHT,
             KC_BSPC, KC_SPC,
             KC_HOME, KC_END,
             KC_PGUP, KC_PGDN
    ),
	*/
};
