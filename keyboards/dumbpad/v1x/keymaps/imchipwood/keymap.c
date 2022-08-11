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
#include "imchipwood.h"

enum custom_layers {
    _BASE,
    _SUB,
};

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
     | Play/Pause  | TT(SUB) |    0    |    .    |  Enter  |
     \-----------------------------------------------------'
    */
    [_BASE] = LAYOUT(
                      KC_P7,      KC_P8,    KC_P9,     KC_BSPC,
                      KC_P4,      KC_P5,    KC_P6,     KC_KP_PLUS,
                      KC_P1,      KC_P2,    KC_P3,     KC_KP_ASTERISK,
      MEH_T(KC_MPLY), TT(_SUB),   KC_P0,    KC_PDOT,   KC_KP_ENTER
    ),
    /*
          SUB LAYER
     /-----------------------------------------------------`
     |             |   F7    |   F8    |   F9    | Del/NLK |
     |             |---------|---------|---------|---------|
     |             |   F4    |   F5    |   F6    |    -    |
     |             |---------|---------|---------|---------|
     |             |   F1    |   F2    |   F3    |    /    |
     |-------------|---------|---------|---------|---------|
     |    MUTE     |         |  LSFT   |  LCTL   |    =    |
     \-----------------------------------------------------'
    */
    [_SUB] = LAYOUT(
                   TD(ALT_F7),          KC_F8,          KC_F9, TD(DEL_NLCK),
                        KC_F4,     TD(CTL_F5),          KC_F6,  KC_KP_MINUS,
                        KC_F1,     TD(ALT_F2),          KC_F3,  KC_KP_SLASH,
        KC_MUTE,      _______,  OSM(MOD_LSFT),  OSM(MOD_LCTL),  KC_KP_EQUAL
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case _BASE:
                // main layer - volume up/down
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;

            case _SUB:
                // sub layer - next/previous track
                if (clockwise) {
                    tap_code(KC_MNXT);
                } else {
                    tap_code(KC_MPRV);
                }
                break;

            default:
                // default - volume up/down
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
        }
    }
    return true;
}
