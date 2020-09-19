/* Copyright 2020 Dennis Nguyen <u/nguyedt>
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
    /*
        |                  |          | Knob 2: Vol Up/Dn |
        |  Toggle Layer 1  |    Up    |    Press: Mute    |
        |      Left        |   Down   |      Right        |
     */
    [0] = LAYOUT(
         MO(1) , KC_UP  , KC_MUTE,
        KC_LEFT, KC_DOWN, KC_RGHT 
    ),
    /*
        |               |   Increase Brightness  |     Mute    |
        |   RGB Cycle   |   Decrease Brightness  |  Hue Cycle  |
     */
    [1] = LAYOUT(
        _______, RGB_VAI, KC_MUTE,
        RGB_MOD, RGB_VAD, RGB_HUI
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGUP);
        } else {
            tap_code(KC_PGDN);
        }
    }
}
