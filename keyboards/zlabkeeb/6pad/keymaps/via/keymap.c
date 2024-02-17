/*
Copyright 2024 zlabkeeb (zlabkeeb@gmail.com)

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


uint16_t underglow_timer = 0;
bool underglow_on = true;
uint8_t prev_rgb_mode; // variable to store the previous RGB mode

layer_state_t layer_state_set_user(layer_state_t state) {
    prev_rgb_mode = rgblight_get_mode(); // store the current RGB mode before changing it
    switch (get_highest_layer(state)) {
    case 0:
        rgblight_setrgb (0x00,  0x00, 0xFF); // LED blue for layer 0
        underglow_timer = timer_read();
        underglow_on = false;
        break;
    case 1:
        rgblight_setrgb (0xFF,  0x00, 0x00); // LED red for layer 1
        underglow_timer = timer_read();
        underglow_on = false;
        break;
    case 2:
        rgblight_setrgb (0xFF,  0xFF, 0x00); // LED yellow for layer 2
        underglow_timer = timer_read();
        underglow_on = false;
        break;
    case 3:
        rgblight_setrgb (0x00,  0xFF, 0x00); // LED green for layer 3
        underglow_timer = timer_read();
        underglow_on = false;
        break;
    default: //  for any other layers, or the default layer
        rgblight_setrgb (0x00,  0x00, 0x00);
        underglow_timer = timer_read();
        underglow_on = false;
        break;
    }
  return state;
}

void matrix_scan_user(void) {
    if (!underglow_on && timer_elapsed(underglow_timer) > 3000) { // 3000ms = 3 seconds
        rgblight_mode_noeeprom(prev_rgb_mode); // restore the previous RGB mode
        underglow_on = true;
    }
}
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌─────────┌─────────┌─────────┐
     * │    1    │    2    │    3    │
     * ├─────────┼─────────┼─────────|
     * │    4    │    5    │    6    |
     * ├─────────┼─────────┼─────────┘
     */
    [0] = LAYOUT(
        KC_1, KC_2, KC_3,
        KC_4, KC_5, KC_6
        ),
    [1] = LAYOUT(
        KC_A, KC_B, KC_C,
        KC_D, KC_E, KC_F
        ),
    [2] = LAYOUT(
        _______, _______, _______,
        _______, _______, _______
        ),
    [3] = LAYOUT(
        _______, _______, _______,
        _______, _______, _______
        )
        };
#if defined (ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = { ENCODER_CCW_CW(KC_PGDN, KC_PGUP)},
    [2] = { ENCODER_CCW_CW(_______, _______)},
    [3] = { ENCODER_CCW_CW(_______, _______)},
};
#endif
