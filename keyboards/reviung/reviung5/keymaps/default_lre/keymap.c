/* Copyright 2021 gtips
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
    _LOWER,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_reviung5(
        TG(_LOWER),       KC_MPRV,       KC_MPLY,       KC_MNXT,    KC_MUTE
    ),
    [_LOWER] = LAYOUT_reviung5(
        _______,       LCTL(KC_X),    LCTL(KC_C),    LCTL(KC_V),    RGB_TOG
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (IS_LAYER_ON(_LOWER)) {
          tap_code16((clockwise == true) ? KC_WH_D : KC_WH_U);
        } else {
          tap_code((clockwise == true) ? KC_VOLD : KC_VOLU);
        }
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _LOWER:
        rgblight_setrgb (RGB_GOLD);
        break;
    default: //  for any other layers, or the default layer
        rgblight_setrgb (RGB_TEAL);
        break;
    }
  return state;
}
