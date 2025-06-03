/* Copyright 2024 Daniel Reisch (djreisch)
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

enum custom_keycodes { MACRO_GG = QK_USER };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
         Main
         ,-----------------------------------------.
         | ESC  |   1  |   2  |   3  |   4  |   5  |
         |------+------+------+------+------+------|
         | Tab  |   G  |   Q  |   W  |   E  |   R  |
         |------+------+------+------+------+------|
         |   LSHIFT    |   A  |   S  |   D  |   F  |
         |------+------+------+------+------+------|
         | LCTL |   B  |   Z  |   X  |   C  |   V  |-------|
         `-----------------------------------------/       /
                                  | LAlt |  FN  | / Space /
                                  |      |      |/       /
                                  `---------------------'
    */
    [0] = LAYOUT(KC_ESC,  KC_1,  KC_2, KC_3, KC_4, KC_5,
	             KC_TAB,  KC_G,  KC_Q, KC_W, KC_E, KC_R,
                 KC_LSFT, KC_A,  KC_S, KC_D, KC_F,
                 KC_LCTL, KC_B,  KC_Z, KC_X, KC_C, KC_V,
                 KC_LALT, MO(1), KC_SPACE),

    /*
         Alt
         ,-----------------------------------------.
         | ESC  |   0  |   9  |   8  |   7  |   6  |
         |------+------+------+------+------+------|
         |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |
         |------+------+------+------+------+------|
         |   LSHIFT    |   A  |   S  |   Y  |   H  |
         |------+------+------+------+------+------|
         | LCTL |   B  |   Z  |   X  |   C  |   M  |-------|
         `-----------------------------------------/       /
                                  | LAlt |  FN  | / Enter /
                                  |      |      |/       /
                                  `---------------------'
    */
    [1] = LAYOUT(KC_ESC, KC_0, KC_9, KC_8, KC_7, KC_6,
                 KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,
                 KC_LSFT, KC_A, KC_S, KC_Y, KC_H,
                 KC_LCTL, MACRO_GG, KC_Z, KC_X, KC_C, KC_M,
                 KC_LALT, KC_TRNS, KC_ENTER)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MACRO_GG:
            if (record->event.pressed) {
                // when keycode MACRO_GG is pressed, press shift+enter, send string "gg" and press enter
                SEND_STRING(SS_DOWN(X_LSFT) SS_DELAY(10) SS_TAP(X_ENTER) SS_UP(X_LSFT) "gg" SS_TAP(X_ENTER));
            }
            break;
    }

    return true;
}
