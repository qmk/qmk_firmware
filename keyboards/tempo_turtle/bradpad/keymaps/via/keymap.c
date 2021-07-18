/*
Copyright 2021 v3ritas <v3ritas@tempoturtle.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum layers {
    _LAYER0,
    _LAYER1,
    _LAYER2,
    _LAYER3,
};
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAYER0] = LAYOUT(
        KC_KP_7,    KC_KP_8,     KC_KP_9,   KC_KP_MINUS,    \
        KC_KP_4,    KC_KP_5,     KC_KP_6,   KC_KP_PLUS,     \
        KC_KP_1,    KC_KP_2,     KC_KP_3,   KC_KP_SLASH,    \
        KC_NUMLOCK, KC_KP_0,     KC_KP_DOT, KC_KP_ASTERISK, \
                    KC_KP_ENTER, KC_EQUAL),
    [_LAYER1] = LAYOUT(
        KC_TRNS,    KC_TRNS,     KC_TRNS,   KC_TRNS, \
        KC_TRNS,    KC_TRNS,     KC_TRNS,   KC_TRNS, \
        KC_TRNS,    KC_TRNS,     KC_TRNS,   KC_TRNS, \
        KC_TRNS,    KC_TRNS,     KC_TRNS,   KC_TRNS, \
                    KC_TRNS,     KC_TRNS),
    [_LAYER2] = LAYOUT(
        KC_TRNS,    KC_TRNS,     KC_TRNS,   KC_TRNS, \
        KC_TRNS,    KC_TRNS,     KC_TRNS,   KC_TRNS, \
        KC_TRNS,    KC_TRNS,     KC_TRNS,   KC_TRNS, \
        KC_TRNS,    KC_TRNS,     KC_TRNS,   KC_TRNS, \
                    KC_TRNS,     KC_TRNS),
    [_LAYER3] = LAYOUT(
        KC_TRNS,    KC_TRNS,     KC_TRNS,   KC_TRNS, \
        KC_TRNS,    KC_TRNS,     KC_TRNS,   KC_TRNS, \
        KC_TRNS,    KC_TRNS,     KC_TRNS,   KC_TRNS, \
        KC_TRNS,    KC_TRNS,     KC_TRNS,   KC_TRNS, \
                    KC_TRNS,     KC_TRNS)
};
// clang-format on
