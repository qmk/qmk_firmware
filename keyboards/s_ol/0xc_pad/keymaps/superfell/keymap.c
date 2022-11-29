/* Copyright 2022 Simon Fell
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

#define _NUMPAD 0
#define _CONTROL 1
#define _ADJUST 2

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_NUMPAD] = LAYOUT(
           TO(_CONTROL), KC_DOT,
             KC_7 , KC_8, KC_9,
           KC_4, KC_5, KC_6, KC_0,
            KC_1  , KC_2 , KC_3
    ),
    [_CONTROL] = LAYOUT(
                   TO(_ADJUST), _______,
              LGUI(KC_X), LGUI(KC_C), LGUI(KC_V),
        LGUI(KC_Q), LGUI(KC_W), LGUI(KC_N), LGUI(KC_S),
            KC_VOLD  , KC_MUTE , KC_VOLU
    ),
    [_ADJUST] = LAYOUT(
                TO(_NUMPAD), QK_BOOT,
               XXXXXXX, XXXXXXX, XXXXXXX,
           RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX,
              RGB_TOG, RGB_VAD, RGB_VAI
    ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (biton32(state)) {
        case _NUMPAD:
            rgblight_sethsv_noeeprom(170, 255, 128);
            rgblight_mode_noeeprom(2);
            break;
        case _CONTROL:
            rgblight_mode_noeeprom(3);
            break;
        case _ADJUST:
            rgblight_mode_noeeprom(4);
            break;
    }
    return state;
}