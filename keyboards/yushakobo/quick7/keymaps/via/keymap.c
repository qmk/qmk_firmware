/* Copyright 2020 yushakobo
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
    _FUNC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_MUTE,   MO(_FUNC), RGB_MOD,
        S(KC_TAB), KC_UP,     KC_TAB,
        KC_LEFT,   KC_DOWN,   KC_RGHT
    ),
    [_FUNC] = LAYOUT(
        QK_BOOT, KC_TRNS, RGB_TOG,
        KC_HOME, KC_VOLU, KC_END,
        KC_MPRV, KC_VOLD, KC_MNXT
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(RGB_HUI, RGB_HUD) },
    [_FUNC] = { ENCODER_CCW_CW(RGB_HUI, RGB_HUD),ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};
#endif
