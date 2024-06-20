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
    _LAY3,
    _LAY4,
    _LAY5
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAY0] = LAYOUT(
		KC_1,      KC_2,      KC_3,      KC_4,       KC_MPLY,
        KC_5,      KC_6,      KC_7,      KC_8,       TO(1),
        KC_9,      KC_0,      KC_UP,     KC_ENT,     KC_MUTE),
  [_LAY1] = LAYOUT(
		KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS, 
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    TO(2),
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS),
  [_LAY2] = LAYOUT(
		KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS, 
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    TO(3),
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS),
  [_LAY3] = LAYOUT(
		KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS, 
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    TO(4),
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS),
  [_LAY4] = LAYOUT(
		KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS, 
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    TO(5),
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS),
  [_LAY5] = LAYOUT(
		RGB_SPD,   RGB_SPI,   RGB_HUD,   RGB_HUI,    KC_TRNS, 
        RGB_SAD,   RGB_SAI,   RGB_VAD,   RGB_VAI,    TO(0),
        RGB_MOD,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS)

};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_LAY0] = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [_LAY1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_LAY2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_LAY3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_LAY4] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_LAY5] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif
