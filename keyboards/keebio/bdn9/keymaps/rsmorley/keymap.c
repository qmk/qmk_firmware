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
        | Hold: Layer 2     | Up   | Lock Screen        |
        | Left              | Down | Right              |
     */
    [0] = LAYOUT(
        KC_MUTE, KC_HOME, KC_MPLY,
        MO(1)  , KC_UP  , C(S(KC_L)),
        KC_LEFT, KC_DOWN, KC_RGHT
    ),
    /*
        | Knob 1: RGB Mode Cycle    |      | Knob 2: RGB Brightness |
        | RESET          | N/A  | Media Stop |
        | Held: Layer 2  | Home | Lock Screen|
        | Media Previous | End  | Media Next |
     */
    [1] = LAYOUT(
        RESET  , BL_STEP, KC_STOP,
        _______, KC_HOME, _______,
        KC_MPRV, KC_END , KC_MNXT
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    switch (index) {
        case 0:
            switch(biton32(layer_state)) {
                case 0: 
                    tap_code(clockwise ? KC_VOLD : KC_VOLU);
                    break;
                case 1: 
                    if (clockwise) {
                        rgblight_step();
                    } else {
                        rgblight_step_reverse();
                    }
                    break;
            }
            break;
        case 1:
            switch(biton32(layer_state)) {
                case 0: 
                    tap_code(clockwise ? KC_PGDN : KC_PGUP);
                    break;
                case 1:
                    if (clockwise) {
                        rgblight_increase_val();
                    } else {
                        rgblight_decrease_val();
                    }
                    break;
            }
            break;
    }
}