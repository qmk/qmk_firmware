/* Copyright 2021 yfuku
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
    _BASE,
    _FN1,
    _FN2,
    _FN3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,  KC_NO, // for encoders
        KC_NO,   KC_NO,   KC_NO,  KC_NO, // for ext keys
        MO(1),   KC_BSPC, KC_SPC, KC_ENT,
        KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT
    ),
    [_FN1] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_1,    KC_2,    KC_3,   KC_4,
        KC_5,    KC_6,    KC_7,   KC_8
    ),
    [_FN2] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_1,    KC_2,    KC_3,   KC_4,
        KC_5,    KC_6,    KC_7,   KC_8
    ),
    [_FN3] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_NO,   KC_NO,   KC_NO,  KC_NO,
        KC_1,    KC_2,    KC_3,   KC_4,
        KC_5,    KC_6,    KC_7,   KC_8
    )
};

void encoder_update_user(uint8_t index, bool clockwise) {
    keypos_t key;

    if (index == 0) {
        if (clockwise) {
            key.row = 0;
            key.col = 13;
        } else {
            key.row = 0;
            key.col = 12;
        }
        uint8_t  layer   = layer_switch_get_layer(key);
        uint16_t keycode = keymap_key_to_keycode(layer, key);

        tap_code16(keycode);
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            key.row = 0;
            key.col = 15;
        } else {
            key.row = 0;
            key.col = 14;
        }
        uint8_t  layer   = layer_switch_get_layer(key);
        uint16_t keycode = keymap_key_to_keycode(layer, key);

        tap_code16(keycode);
    }
}
