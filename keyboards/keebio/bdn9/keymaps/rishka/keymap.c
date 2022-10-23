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
        | Knob 1: Vol Dn/Up |      | Knob 2: Page Dn/Up |
        | Press: Mute       | Home | Press: Play/Pause  |
        | Hold: Layer 2     | Up   | RGB Mode           |
        | Left              | Down | Right              |
     */
    [0] = LAYOUT(
        KC_MUTE, KC_UP, TO(0),
        KC_F12  , _______  , KC_F1,
        KC_LEFT, KC_DOWN, KC_RGHT
    ),
    /*
        | QK_BOOT          | N/A  | Media Stop |
        | Held: Layer 2  | Home | RGB Mode   |
        | Media Previous | End  | Media Next |
     */
    [1] = LAYOUT(
        QK_BOOT, KC_HOME, _______,
        _______, _______, _______,
        KC_MPRV, KC_END , KC_MNXT
    ),
};
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
    else if (index == 1) {
        int mod = 0;
        if (clockwise) {
            mod = 1;
        } else {
            mod = -1;
        }
        int n = 2; //sizeof(PROGMEM);
        int new_layer = ((layer_state + mod) % n + n) % n;
        uprintf("new: %d\n", new_layer);
        layer_on(new_layer);
        for(int i=0; i < n; i++) {
            if (new_layer != i) {
                layer_off(i);
            }
        }
    }
    return true;
}
