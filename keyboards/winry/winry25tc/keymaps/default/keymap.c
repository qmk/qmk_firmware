/* Copyright 2021 Andrzej Ressel (andrzej.ressel@gmail.com)
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

enum my_layers {
    _FIRST_LAYER,
    _SECOND_LAYER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_FIRST_LAYER] = LAYOUT(
        KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS, KC_ESC,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS, UG_TOGG,
        KC_P4,   KC_P5,   KC_P6,   KC_PENT, UG_NEXT,
        KC_P1,   KC_P2,   KC_P3,   KC_UP,   MO(_SECOND_LAYER),
        KC_P0,   KC_PDOT, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_SECOND_LAYER] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_F11,  KC_F12,  KC_MUTE, KC_VOLD, KC_VOLU,
        KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT, _______,
        KC_RSFT, KC_RALT, KC_RGUI, KC_APP,  KC_RCTL
    ),
};
