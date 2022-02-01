/* Copyright 2018 Milton Griffin
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
 *
 */

#include QMK_KEYBOARD_H

// Keyboard Layers
#define _QW 0
#define _FN 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | MENU   | CAP LK | 6      | 7      | 8      | 9      | 0      | -      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------|
 * | TAB    | Q      | W      | E      | R      | T      | INS    | DEL    | Y      | U      | I      | O      | P      | \      | =      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------|
 * | `      | A      | S      | D      | F      | G      | LALT   | MENU   | H      | J      | K      | L      | ;      | '      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | [      | ]      | N      | M      | ,      | .      | /      | RSHIFT | RSHIFT |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+--------+--------|
 * | LCTRL  | PG UP  | PG DN  | BACKSP | FN     | SPACE  | LGUI   | LGUI   | SPACE  | FN     | ENTER  | HOME   | END    | RALT   | RCTRL  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_QW] = LAYOUT_ortho_5x15( /* QWERTY */
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_APP,  KC_CAPS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_INS,  KC_DEL,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, KC_EQL,
    KC_GRV,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LALT, KC_APP,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT,
    KC_LCTL, KC_PGUP, KC_PGDN, KC_BSPC, MO(_FN), KC_SPC,  KC_LGUI, KC_LGUI, KC_SPC,  MO(_FN), KC_ENT,  KC_HOME, KC_END,  KC_RALT, KC_RCTL
 ),

/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        | F1     | F2     | F3     | F4     | F5     |        |        | F6     | F7     | F8     | F9     | F10    | F11    | F12    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        | UP     | RGB TG | RGB HD | RGB HI |        |        |        |        |        |        | PR SCR | SCR LK | PAUSE  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | LEFT   | DOWN   | RIGHT  | RGB SD | RGB SI |        |        | LEFT   | DOWN   | UP     | RIGHT  |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | PREV   | PLAY   | NEXT   | STOP   | RGB VD | RGB VI |        |        |        |        | CALC   | MYCOMP | MAIL   |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | VOL-   | MUTE   | VOL+   |        | RGB RMD| RGB MD |        |        |        |        |        | RALT   |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_FN] = LAYOUT_ortho_5x15( /* FUNCTION */
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______, _______, KC_UP,   RGB_TOG, RGB_HUD, RGB_HUI, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, RGB_SAD, RGB_SAI, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______,
    KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP, RGB_VAD, RGB_VAI, _______, _______, _______, _______, KC_CALC, KC_MYCM, KC_MAIL, _______, _______,
    KC_VOLD, KC_MUTE, KC_VOLU, _______, RGB_RMOD,RGB_MOD, _______, _______, _______, _______, _______, _______, _______, _______, _______
 ),
};


