/* Copyright 2020 William Ehman
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

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ortho_4x4(
    KC_F1,  KC_F2,  KC_F3,  KC_F4,
    KC_F5,  KC_F6,  KC_F7,  KC_F8,
    KC_F9,  KC_F10, KC_F11, KC_F12,
    KC_F13, KC_F14, KC_F15, TO(1)
  ),
  [1] = LAYOUT_ortho_4x4(
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  TO(2)
  ),
  [2] = LAYOUT_ortho_4x4(
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  TO(0)
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case 0:
            sethsv(HSV_WHITE, (LED_TYPE *)&led[0]);
            rgblight_set();
            break;
        case 1:
            sethsv(HSV_GREEN, (LED_TYPE *)&led[0]);
            rgblight_set();
            break;
        case 2:
            sethsv(HSV_BLUE, (LED_TYPE *)&led[0]);
            rgblight_set();
            break;
    }
    return state;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    /* With an if statement we can check which encoder was turned. */
    if (index == 0) { /* First encoder */
        /* And with another if statement we can check the direction. */
        if (clockwise) {
            /* This is where the actual magic happens: this bit of code taps on the
               Page Down key. You can do anything QMK allows you to do here.
               You'll want to replace these lines with the things you want your
               encoders to do. */
            tap_code(KC_AUDIO_VOL_UP);
        } else {
            /* And likewise for the other direction, this time Vol Down is pressed. */
            tap_code(KC_AUDIO_VOL_DOWN);
        }
    }
    return true;
}
