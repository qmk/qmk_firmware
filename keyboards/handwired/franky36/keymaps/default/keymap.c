/* Copyright 2024-2025 Grigory Avdyushin
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┐
     * │ Q │ W │ E │ R │ T │         │ Y │ U │ I │ O │ P │
     * ├───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┤
     * │ A │ S │ D │ F │ G │         │ H │ J │ K │ L │ ; │
     * ├───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┤
     * │ Z │ X │ C │ V │ B │         │ N │ M │ , │ . │ / │
     * └───┴───┴───┴───┴───┘         └───┴───┴───┴───┴───┘
     *             ┌───┬───┬───┐ ┌───┬───┬───┐
     *             │CTL│ALT│SPC│ │ENT│ALT│SFT│
     *             └───┴───┴───┘ └───┴───┴───┘
     */
    [0] = LAYOUT_split_3x5_3(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
        _______, _______, KC_LCTL, KC_LALT, KC_SPC,  KC_ENT,  KC_RALT, KC_RSFT, _______, _______
    )
};
