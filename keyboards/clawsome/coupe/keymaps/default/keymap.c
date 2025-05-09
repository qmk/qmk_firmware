/* Copyright 2020 AAClawson (AlisGraveNil)
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

#define FNM LT(1, KC_APP)  // MO(1) when held, KC_APP when tapped

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   /*
    *-----------------------------------------------------------------------
    *|ESC | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 0  | -  | =  | DEL|
    *-----------------------------------------------------------------------
    *|TAB | Q  | W  | E  | R  | T  | Y  | U  | I  | O  | P  | [  | ]  | \  |
    *-----------------------------------------------------------------------
    *|CAPS | A  | S  | D  | F  | G  | H  | J  | K  | L  | ;  | "  | ENTER  |
    *-----------------------------------------------------------------------
    *|  SHIFT  | Z  | X  | C  | V  | B  | N  | M  | ,  | .  | ?  |  SHIFT  |
    *-----------------------------------------------------------------------
    *|CTRL|GUI |ALT |                SPACE            |ALT |GUI | FNM |CTRL|
    *-----------------------------------------------------------------------
    */
    [0] = LAYOUT_60_ansi(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,   KC_EQL,    KC_BSPC,
        KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   KC_LBRC, KC_RBRC,  KC_BSLS,
        KC_CAPS,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,     KC_QUOT,    KC_ENT,
        KC_LSFT,         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,   KC_DOT,    KC_SLSH,           KC_LSFT,
        KC_LCTL,   KC_LGUI,   KC_LALT,                       KC_SPC,                              KC_LALT,  KC_LGUI,  FNM,       KC_LCTL
    ),

   /*
    *-------------------------------------------------------------
    *| ` | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | DEL   |
    *-------------------------------------------------------------
    *|     |   | ^ |   |   |   |   |   |   |   |   |PSC|SLK|PAUSE|
    *-------------------------------------------------------------
    *|      | < | v | > |   |   |HOM|PGU|   |   |   |   |        |
    *-------------------------------------------------------------
    *|        |   |   |   |   |   |END|PGD|   |   |              |
    *-------------------------------------------------------------
    *|RST |    |    |                        |    |    |    |    |
    *-------------------------------------------------------------
    */
    [1] = LAYOUT_60_ansi(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,      KC_DEL,
        _______,     _______, KC_UP, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS,   _______,
        _______,        KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_HOME, KC_PGUP, _______, _______, _______, _______,       _______,
        _______,            _______, _______, _______, _______, _______, KC_END,  KC_PGDN, _______, _______, _______,            _______,
        QK_BOOT,   _______,   _______,                       _______,                             _______,  _______,  _______,   _______
    ),

};
