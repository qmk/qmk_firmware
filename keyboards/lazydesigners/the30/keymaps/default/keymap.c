/* Copyright 2019 Erovia
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

enum custom_layers {
	_QWERTY,
	_FN
};

/* Press for Enter, hold for FN layer */
#define FN_ENT LT(_FN, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 *  ,-------------------------------------------------.
 *  | Q  | W  | E  | R  | T  | Y  | U  | I  | O  | P  |
 *  |-------------------------------------------------|
 *  | A  | S  | D  | F  | G  | H  | J  | K  | L  |ENT |
 *  |-------------------------------------------------|
 *  | Z  | X  | C  | V  | B  | N  | M  | ,  | .  | /  |
 *  `-------------------------------------------------'
 */
    [_QWERTY] = LAYOUT_ortho_3x10(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    FN_ENT,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH
    ),
/*
 *  ,-------------------------------------------------.
 *  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 0  |
 *  |-------------------------------------------------|
 *  |    |    |    |    |    |    |    |    |    |    |
 *  |-------------------------------------------------|
 *  |RST |ERST|    |    |SPC |    |    |    |    |    |
 *  `-------------------------------------------------'
 */
    [_FN] = LAYOUT_ortho_3x10(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        QK_BOOT, EE_CLR,  _______, _______, KC_SPC,  _______, _______, _______, _______, _______
    ),

};
