/*
Copyright 2024 Joe Scotto

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(HYPR(KC_RIGHT), HYPR(KC_LEFT)), ENCODER_CCW_CW(HYPR(KC_UP), HYPR(KC_DOWN))  }
    //                  Encoder 1                                     Encoder 2
};
#endif

// Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        HYPR(KC_9),                         HYPR(KC_0),
        HYPR(KC_5), HYPR(KC_6), HYPR(KC_7), HYPR(KC_8),
        HYPR(KC_1), HYPR(KC_2), HYPR(KC_3), HYPR(KC_4)
    )
};
