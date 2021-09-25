/* Copyright 2020 rate
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE = 0,
    _FN,
    _RESERVE_0,
    _RESERVE_1
};

const keypos_t ENC_CW = {.row = 3, .col = 3};
const keypos_t ENC_CCW = {.row = 4, .col = 1};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_via(
                               KC_P0,KC_P1,KC_MPLY,
    LT(_FN, KC_NLCK),  KC_PSLS,  KC_PAST,  KC_PMNS,
    KC_P7,             KC_P8,    KC_P9,
    KC_P4,             KC_P5,    KC_P6,    KC_PPLS,
    KC_P1,             KC_P2,    KC_P3,
    KC_P0,                       KC_PDOT,  KC_PENT
    ),
    /* Fn */
    [_FN] = LAYOUT_via(
                    KC_P2,KC_P3,KC_NO,
    KC_NO,   KC_NO,   KC_NO,    KC_NO,
    RGB_HUI, RGB_SAI, RGB_VAI,
    RGB_HUD, RGB_SAD, RGB_VAD,  RGB_TOG,
    KC_NO,   KC_NO,   KC_NO,
    KC_NO,            KC_NO,    KC_NO
    ),
    /* Reserve */
    [_RESERVE_0] = LAYOUT_via(
                KC_VOLU,KC_VOLD,KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,          KC_TRNS,  KC_TRNS
    ),
    /* Reserve */
    [_RESERVE_1] = LAYOUT_via(
                KC_VOLU,KC_VOLD,KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,          KC_TRNS,  KC_TRNS
    ),
};
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    int l = get_highest_layer(layer_state);
    if (index == 0) {
        if (clockwise) {
            tap_code16(keymap_key_to_keycode(l, ENC_CW));
        } else {
            tap_code16(keymap_key_to_keycode(l, ENC_CCW));
        }
    }
    return true;
}
#endif
