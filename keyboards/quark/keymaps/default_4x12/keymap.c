/* Copyright 2020 Nathan Spears
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

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* [0]
     * ,-----------------------------------------------------------------------------------------.
     * |------------+------+------+------+------+------+------+------+------+------+------+------|
     * | TAB       |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | DEL   |
     * |------------+------+------+------+------+-------------+------+------+------+------+------|
     * | CTRL&ESC  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "    |
     * |------------+------+------+------+------+------|------+------+------+------+------+------|
     * | SHIFT     |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | ENTER |
     * |-------+-------+-------+-------+-------+-------+------+------+------+------+------+------|
     * |    PRINT   | Ctrl | ALT  | GUI  |LOWER |SPACE |SPACE|RAISE | LEFT | DOWN |  UP  |RIGHT  |
     * `-----------------------------------------------------------------------------------------'
     */
    [0] = LAYOUT_ortho_4x12(
        KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
        CTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
        KC_PSCR,       KC_LCTL, KC_LALT, KC_LGUI, TT(1),   KC_SPC,  KC_SPC,  TT(2),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

    /* [1]
     * ,---------------------------------------------------------------------------------------.
     * |------------+------+------+------+------+------+------+------+------+------+------+----|
     * |   ~    | !    |  @   |  #  |  $   |  %   |  | ^  |  &   |  *  |  (    |  )  | BCKSPC  |
     * |------------+------+------+------+------+-------------+------+------+------+------+----|
     * |   \    |    1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   /   |
     * |------------+------+------+------+------+------|------+------+------+------+------+----|
     * |       |       |      |      |      |      |      |   +   |   =  |      |      |       |
     * |-------+-------+-------+-------+-------+-------+------+------+------+------+------+----|
     * |     |    | ESC  |CTRL-ALT-DEL|TASK|    |     |     |     |    |  '|'  |   `   |       |
     * `---------------------------------------------------------------------------------------'
     */
    [1] = LAYOUT_ortho_4x12(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
        KC_SLSH, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
        _______, _______, _______, _______, _______, _______, _______, KC_PPLS, KC_EQL,  _______, _______, _______,
        _______, KC_ESC,  CALTDEL, TSKMGR,  _______, _______, _______, _______, _______, KC_NUBS, KC_GRV,  _______
    ),

    /* [2]
     * ,---------------------------------------------------------------------------------------.
     * |------------+------+------+------+------+------+------+------+------+------+------+---|
     * |       |      |      |  UP  |       |      |     |   _   |     |   [   |  ]    |      |
     * |------------+------+------+------+------+-------------+------+------+------+------+---|
     * |       |     | LEFT | DOWN  | RIGHT |     |      |   -  |      |   [   |   ]   |      |
     * |------------+------+------+------+------+-----+-----+------+------+------+------+-----|
     * |   F1  | F2 |  F3  |   F4  | F5    | F6  | F7   | F8   | F9    | F10  | F11   | F12   |
     * |-------+-------+-------+-------+-------+-------+------+------+------+------+------+---|
     * |RESET |    |      |       |       |     |      |      |       |      |       |        |
     * `---------------------------------------------------------------------------------------'
     */
    [2] = LAYOUT_ortho_4x12(
        _______, _______, _______, KC_UP,   _______, _______, _______, KC_UNDS, _______, KC_LBRC, KC_RBRC, _______,
        _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_MINS, _______, KC_LCBR, KC_RCBR, _______,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};
