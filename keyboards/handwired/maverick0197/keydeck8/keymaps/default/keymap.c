/* Copyright 2023 Maverick0197 <>
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
  _HOME = 0,
  _FN1,
  _FN2,
  _FN3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	 /*
     * ┌────┬────┬────┐
     * │ D0 │ D1 │ D4 │
     * ├────┼────┼────┤
     * │ C6 │ D7 │ E6 │
     * ├────┼────┼────┤
     * │ B4 │ B5 │ B6 │
     * └────┴────┴────┘
     */
	[_HOME] = LAYOUT(
	 KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK,
	 KC_1, KC_2, KC_3,
	 KC_4, KC_5, KC_6),
	[_FN1] = LAYOUT(
	KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS),
	[_FN2] = LAYOUT(
	KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS),
	[_FN3] = LAYOUT(
	KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS)
};
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [_HOME] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
        [_FN1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
        [_FN2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
        [_FN3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};
#endif
