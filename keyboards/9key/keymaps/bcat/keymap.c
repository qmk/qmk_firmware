/* Copyright 2021 Jonathan Rascher
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

enum layer {
    LAYER_DEFAULT,
    LAYER_FUNCTION,
};

#define LY_FUNC MO(LAYER_FUNCTION)
#define KY_LOCK LCA(KC_L) /* Cinnamon lock screen */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [LAYER_DEFAULT] = LAYOUT(
        KC_MPLY,  KC_VOLU,  KC_MSTP,
        KC_MPRV,  KC_VOLD,  KC_MNXT,
        KY_LOCK,  KC_MUTE,  LY_FUNC
    ),
    [LAYER_FUNCTION] = LAYOUT(
        EEP_RST,  _______,  RESET,
        _______,  _______,  _______,
        _______,  _______,  _______
    ),
    // clang-format on
};
