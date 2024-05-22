/* Copyright 2021 recompile keys
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,
        MO(_FN), KC_LCTL, KC_LALT,                   KC_SPC,  KC_ENT
    ),
    [_FN] = LAYOUT(
        QK_BOOT,           _______, _______, _______, _______, _______, _______,
        RGB_TOG, RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI, _______, _______, _______,
        _______, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, _______,
        _______, _______,  _______, _______, _______, _______, _______,
        _______, _______,  _______, _______, _______, _______, _______,
        _______, _______, _______,                    _______, _______
    )
};
