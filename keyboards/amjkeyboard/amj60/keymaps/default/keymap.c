/* Copyright 2016 Toni (@toneman77)
 *           2021 James Young for QMK (@noroadsleft)
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

enum layer_names {
    _DEF,
    _FN,
};

// dual-role shortcuts
#define FN_SPC LT(_FN, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Keymap _DEF: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | \ | ~ |
     * |-----------------------------------------------------------|
     * |Tab  | Q | W | E | R | T | Y | U | I | O | P | [ | ] | Bspc|
     * |-----------------------------------------------------------|
     * |Caps  | A | S | D | F | G | H | J | K | L | ; | ' | Return |
     * |-----------------------------------------------------------|
     * |Sft | \ | Z | X | C | V | B | N | M | , | . | / |Shift |Fn |
     * |-----------------------------------------------------------|
     * |Ctrl|GUI |Alt |        Space/Fn        |Alt |GUI | Fn |RCtl|
     * `-----------------------------------------------------------'
     */
    [_DEF] = LAYOUT_all(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(1),
        KC_LCTL, KC_LGUI, KC_LALT,                            FN_SPC,                             KC_RALT, KC_RGUI, MO(1),   KC_RCTL
    ),

    /* Keymap 1: F-and-vim Layer, modified with Space (by holding space)
     * ,-----------------------------------------------------------.
     * |PSc|F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|   |   |
     * |-----------------------------------------------------------|
     * |     |Pau| Up|   |   |   |   |   | ( | ) |   |   |   | Del |
     * |-----------------------------------------------------------|
     * |      |Lft|Dwn|Rgt|   |   |Lft|Dwn|Up |Rgh|   |   |  Play  |
     * |-----------------------------------------------------------|
     * |    |   |   |   |   |   |Spc|   |   |   |   |   | Vol+ |   |
     * |-----------------------------------------------------------|
     * |    |    |    |                        |    |Prev|Vol-|Next|
     * `-----------------------------------------------------------'
     */
    [_FN] = LAYOUT_all(
        KC_PSCR, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
        _______, KC_PAUS, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______, KC_MPLY,
        _______, _______, _______, _______, _______, _______, KC_SPC,  _______, _______, _______, _______, _______, KC_VOLU, _______,
        _______, _______, _______,                            _______,                            _______, KC_MPRV, KC_VOLD, KC_MNXT
    ),

};
