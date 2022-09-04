/* Copyright 2021 keyquest
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

/* what each layer does */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     *    M = Macro
     * ┌────┬────┬────┐
     * │ M1 │ M2 │ M3 │
     * ├────┼────┼────┤
     * │ M4 │ M5 │ M6 │
     * ├────┼────┼────┤
     * │ M7 │ M8 │ M9 │
     * └────┴────┴────┘
     */
    [0] = LAYOUT(
        KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK,
        C(KC_C), C(KC_V), G(KC_V),
        KC_AUDIO_VOL_UP, KC_AUDIO_VOL_DOWN, MO(1)
    ),

    [1] = LAYOUT(
        _______, _______, _______,
        _______, _______, _______,
        _______, MO(2), _______
    ),

    [2] = LAYOUT(
        _______, _______, _______,
        _______, _______, _______,
        MO(3), _______, _______
    ),

    [3] = LAYOUT(
        RGB_TOG, RGB_MODE_PLAIN, RGB_MODE_BREATHE,
        RGB_MODE_RAINBOW, RGB_MODE_SWIRL, RGB_MODE_GRADIENT,
        _______, _______, _______
    )
};
