/* Copyright 2022 DOIO
 * Copyright 2022 DOIO2022 <https://github.com/DOIO2022>
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

enum layer_names {
    _LAY0,
    _LAY1,
    _LAY2,
    _LAY3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAY0] = LAYOUT(
                KC_UP,          KC_1,       KC_2,       KC_3,       KC_MPLY,    KC_MUTE,
        KC_LEFT,    KC_RIGHT,   KC_4,       KC_5,       KC_6,
                KC_DOWN,        KC_7,       KC_8,       KC_9,
        TO(1),  LWIN(KC_D)),
    [_LAY1] = LAYOUT(
                KC_TRNS,        C(S(KC_S)), C(KC_H),    C(KC_G),    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    C(S(KC_A)), C(KC_J),    C(S(KC_G)),
                KC_TRNS,        C(KC_Z),    KC_DEL,     C(A(S(KC_E))),
        TO(2),  KC_TRNS),
    [_LAY2] = LAYOUT(
                KC_TRNS,        S(KC_I),    A(KC_EQL),  C(S(KC_M)), KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    S(KC_O),    A(KC_MINS), S(KC_M),
                KC_TRNS,        KC_C,       KC_V,       C(KC_M),
        TO(3),  KC_TRNS),
    [_LAY3] = LAYOUT(
                KC_TRNS,        RGB_SPI,    RGB_SPD,    RGB_HUI,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    RGB_SAI,    RGB_SAD,    RGB_HUD,
                KC_TRNS,        RGB_MOD,    RGB_VAI,    RGB_VAD,
        TO(0),  KC_TRNS)
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_LAY0] = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_LAY1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_LAY2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_LAY3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif
