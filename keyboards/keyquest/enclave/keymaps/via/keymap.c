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
    [0] = LAYOUT_ortho_3x3(
        KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK,
        KC_AUDIO_VOL_UP, KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN,
        _______, _______, _______
    ),

    [1] = LAYOUT_ortho_3x3(
        _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______
    ),

    [2] = LAYOUT_ortho_3x3(
        _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______
    ),

    [3] = LAYOUT_ortho_3x3(
        _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______
    )
};
