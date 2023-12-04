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
		KC_NUM,     KC_PSLS,     KC_PAST,     KC_PMNS,     MO(5),
		KC_P7,      KC_P8,       KC_P9,       KC_PPLS,     TO(1),
		KC_P4,      KC_P5,       KC_P6,
		KC_P1,      KC_P2,       KC_P3,       KC_PENT,
        KC_P0,      KC_PDOT,     KC_MUTE),
  [_LAY1] = LAYOUT(
		KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,
		KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     TO(2),
		KC_TRNS,    KC_TRNS,     KC_TRNS,
        KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,
		KC_TRNS,    KC_TRNS,     KC_TRNS),
  [_LAY2] = LAYOUT(
		KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,
		KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     TO(3),
		KC_TRNS,    KC_TRNS,     KC_TRNS,
        KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,
		KC_TRNS,    KC_TRNS,     KC_TRNS),
  [_LAY3] = LAYOUT(
		KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,
		KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     TO(4),
		KC_TRNS,    KC_TRNS,     KC_TRNS,
        KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,
		KC_TRNS,    KC_TRNS,     KC_TRNS),
  [_LAY4] = LAYOUT(
		KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,
		KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     TO(5),
		KC_TRNS,    KC_TRNS,     KC_TRNS,
        KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,
		KC_TRNS,    KC_TRNS,     KC_TRNS),
  [_LAY5] = LAYOUT(
		RGB_SPI,    RGB_SPD,     KC_TRNS,     KC_TRNS,     KC_TRNS,
		RGB_SAI,    RGB_SAD,     KC_TRNS,     KC_TRNS,     TO(0),
		RGB_TOG,    RGB_MOD,     RGB_HUI,
        KC_TRNS,    RGB_VAI,     RGB_HUD,     RGB_VAD,
		KC_TRNS,    KC_TRNS,     KC_TRNS)

};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_LAY0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_LAY1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_LAY2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_LAY3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_LAY4] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_LAY5] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif
