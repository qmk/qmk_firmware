/* Copyright 2023 Brian McKenna
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
        KC_ESC, KC_F11, KC_NO, KC_MSTP,
        KC_NO, KC_NO, KC_MRWD, KC_MFFD,
        KC_NO, KC_MPLY, KC_MPLY, KC_MNXT,

        KC_MUTE, KC_NO, KC_NO, RGB_TOG
    )
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
        ENCODER_CCW_CW(RGB_HUD, RGB_HUI),
        ENCODER_CCW_CW(RGB_VAD, RGB_VAI),
        ENCODER_CCW_CW(RGB_MODE_REVERSE, RGB_MODE_FORWARD)
    },
};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
