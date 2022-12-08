/*
Copyright 2022 imchipwood && deveth0

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

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
            BASE LAYER - Num Pad
    /-----------------------------------------------------`
    |             |    7    |    8    |    9    |    -    |
    |             |---------|---------|---------|---------|
    |             |    4    |    5    |    6    |    +    |
    |             |---------|---------|---------|---------|
    |             |    1    |    2    |    3    |    *    |
    |-------------|---------|---------|---------|---------|
    |    Mute     |  TT(1)  |    0    |         |  Enter  |
    \-----------------------------------------------------'
    */
    [0] = LAYOUT(
                    KC_P7,      KC_P8,    KC_P9,             KC_PMNS,
                    KC_P4,      KC_P5,    KC_P6,             KC_PPLS,
                    KC_P1,      KC_P2,    KC_P3,             KC_PAST,
        KC_MUTE,    TT(1),      KC_P0,    _______,           KC_ENTER
    ),
    /*
            SUB LAYER  - RGB controls, Modes on encoder
    /-----------------------------------------------------`
    |             | On/Off  | Bright- | Bright+ |  Reset  |
    |             |---------|---------|---------|---------|
    |             |         | Hue-    | Hue+    |         |
    |             |---------|---------|---------|---------|
    |             |         | Sat-    | Sat+    |         |
    |-------------|---------|---------|---------|---------|
    |             |  TT(1)  | Effect- | Effect+ |         |
    \-----------------------------------------------------'
    */
    [1] = LAYOUT(
                    RGB_TOG,    RGB_VAD,     RGB_VAI,      QK_BOOT,
                    KC_NO,      RGB_HUD,     RGB_HUI,      KC_NO,
                    KC_NO,      RGB_SAD,     RGB_SAI,      KC_NO,
        KC_NO,      _______,    RGB_SPD,     RGB_SPI,      KC_NO
    ),
};
// clang-format on

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        case 0:
            // main layer, volume
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
        default:
            // rgb control layer, effects
            if (clockwise) {
                rgblight_step();
            } else {
                rgblight_step_reverse();
            }
            break;
    }
    return false;
}
