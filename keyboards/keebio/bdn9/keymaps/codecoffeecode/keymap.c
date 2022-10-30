/* Copyright 2019 Danny Nguyen <danny@keeb.io>
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
        | Knob 1: Scrl Dn/Up |      | Knob 2: Vol Dn/Up  |
        | Press: Mute        | Up   | Press: Play/Pause  |
        | Left               | Down | Right              |
        | Media Previous     | MO(1)| Media Next         |
     */
    [0] = LAYOUT(
        KC_MUTE, KC_UP,   KC_MPLY,
        KC_LEFT, KC_DOWN, KC_RIGHT,
        KC_MPRV, MO(1),   KC_MNXT
    ),
    /*
        |       QK_BOOT        | Home |    Media Stop      |
        |                    | End  |                    |
        |      CTRL_END      |      |    CTRL_HOME       |
     */
    [1] = LAYOUT(
        QK_BOOT,      KC_HOME, KC_STOP,
        _______,      KC_END,  _______,
        LCTL(KC_END), _______, LCTL(KC_HOME)
    ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_MS_WH_UP);
        } else {
            tap_code(KC_MS_WH_DOWN);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}
