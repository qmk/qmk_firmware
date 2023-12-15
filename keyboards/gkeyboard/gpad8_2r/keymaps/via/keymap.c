/* Copyright 2023 gkeyboard
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

    [0] = LAYOUT(
        KC_MUTE,                RGB_TOG,
        KC_A,   KC_B,   KC_C,   KC_D,
        KC_E,   KC_F,   KC_G,   KC_H
    ),
    [1] = LAYOUT(
        KC_TRNS,                            KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    [2] = LAYOUT(
        KC_TRNS,                            KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    [3] = LAYOUT(
        KC_TRNS,                            KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    [4] = LAYOUT(
        KC_TRNS,                            KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    [5] = LAYOUT(
        KC_TRNS,                            KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    [6] = LAYOUT(
        KC_TRNS,                            KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    [7] = LAYOUT(
        KC_TRNS,                            KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),      ENCODER_CCW_CW(RGB_MOD, RGB_RMOD) },
    [1] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),      ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),      ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),      ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [4] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),      ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [5] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),      ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [6] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),      ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [7] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),      ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};
#endif
