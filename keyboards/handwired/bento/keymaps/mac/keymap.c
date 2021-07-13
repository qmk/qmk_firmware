/* Copyright 2020 GhostSeven <work@ghost7.com>
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
#define _BASE 0  // Base layer
#define _CODE 1  // Code layer

enum encoder_names {
  _ENCODER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: Base Layer
    * Media Prev / Hold L1 | Media Next | Mute
    * Move Space Left | Mission Control | Move Space Right */
    [_BASE] = LAYOUT(
            LT(_CODE, KC_MPRV), KC_MNXT, KC_MUTE,
            C(KC_LEFT), C(KC_UP), C(KC_RIGHT)
    ),


    /* 1: Code layer
    * ---- | Shift+CMD+B (Build VS Code) | DFU Mode
    * Shift+CMD+C (FF Console) | Ctrl+Alt+U (Upload PIO) | Ctrl+Alt+S (Serial PIO) */
    [_CODE] = LAYOUT(
            _______, S(G(KC_B)), RESET,
            G(A(KC_C)), C(A(KC_U)), C(A(KC_S))
    ),
};


bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _ENCODER) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}
