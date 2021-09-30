/* Copyright 2020 imchipwood
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
            BASE LAYER
    /-----------------------------------------------------`
    |             |    7    |    8    |    9    |  Bkspc  |
    |             |---------|---------|---------|---------|
    |             |    4    |    5    |    6    |    +    |
    |             |---------|---------|---------|---------|
    |             |    1    |    2    |    3    |    *    |
    |-------------|---------|---------|---------|---------|
    | Play/pause  |  TT(1)  |    0    |    .    |  Enter  |
    \-----------------------------------------------------'
    */
    [0] = LAYOUT(
                    KC_P7,     KC_P8,   KC_P9,    KC_BSPC,
                    KC_P4,     KC_P5,   KC_P6,    KC_KP_PLUS,
                    KC_P1,     KC_P2,   KC_P3,    KC_KP_ASTERISK,
        KC_MPLY,    TT(1),     KC_P0,   KC_PDOT,  KC_KP_ENTER
    ),
    /*
            SUB LAYER
    /-----------------------------------------------------`
    |             |         |         |         | Numlock |
    |             |---------|---------|---------|---------|
    |             |         |         |         |    -    |
    |             |---------|---------|---------|---------|
    |             |         |         |         |    /    |
    |-------------|---------|---------|---------|---------|
    |    MUTE     |         |         |         |    =    |
    \-----------------------------------------------------'
    */
    [1] = LAYOUT(
                    _______,     _______,     _______,      KC_NLCK,
                    _______,     _______,     _______,      KC_KP_MINUS,
                    _______,     _______,     _______,      KC_KP_SLASH,
        KC_MUTE,    _______,     _______,     _______,      KC_KP_EQUAL
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    /*  Custom encoder control - handles CW/CCW turning of encoder
     *  Default behavior:
     *    main layer:
     *       CW: volume up
     *      CCW: volume down
     *    other layers:
     *       CW: next track
     *      CCW: previous track
     */
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case 0:
                // main layer - volume up (CW) and volume down (CCW)
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;

            default:
                // other layers - media next (CW) and media previous (CCW)
                if (clockwise) {
                    tap_code(KC_MNXT);
                } else {
                    tap_code(KC_MPRV);
                }
                break;
        }
    }
}
