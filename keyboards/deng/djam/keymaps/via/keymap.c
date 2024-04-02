/* Copyright 2022 Leo Deng (@myst729)
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

#define L1_SPC LT(1, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    *     ┌───┬───┬───┐           ┌───┬───┬───┐
    * ┌───┤ S │ D │ F │           │ J │ K │ L ├───┐
    * │ A ├───┼───┼───┤   DJAM    ├───┼───┼───┤ ; │
    * └───┤ Z │ X │ C │           │ N │ M │ , ├───┘
    * ┌───┼───┼───┴─┬─┴─┬───────┬─┴─┬─┴───┼───┼───┐
    * │ ← │ → │     │LSh│ SPACE │RSh│     │ ↑ │ ↓ │
    * └───┴───┘     └───┴───────┴───┘     └───┴───┘
    */
    [0] = LAYOUT(
                 KC_S,    KC_D,    KC_F,                               KC_J,    KC_K,    KC_L,
        KC_A,    KC_Z,    KC_X,    KC_C,                               KC_N,    KC_M,    KC_COMM, KC_SCLN,
        KC_LEFT, KC_RGHT,                   KC_LSFT, L1_SPC,  KC_RSFT,                   KC_UP,   KC_DOWN),

    [1] = LAYOUT(
                 RGB_HUI, RGB_SAI, RGB_VAI,                            RGB_SPI, _______, RGB_RMOD,
        _______, RGB_HUD, RGB_SAD, RGB_VAD,                            RGB_SPD, _______, RGB_MOD, RGB_TOG,
        _______, _______,                   BL_TOGG, _______, BL_STEP,                   _______, _______),

    [2] = LAYOUT(
                 _______, _______, _______,                            _______, _______, _______,
        _______, _______, _______, _______,                            _______, _______, _______, _______,
        _______, _______,                   _______, _______, _______,                   _______, _______),

    [3] = LAYOUT(
                 _______, _______, _______,                            _______, _______, _______,
        _______, _______, _______, _______,                            _______, _______, _______, _______,
        _______, _______,                   _______, _______, _______,                   _______, _______)
};
