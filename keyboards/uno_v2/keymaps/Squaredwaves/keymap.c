/* Copyright 2020 Snipeye
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





enum layer_names {
 _LR,
 _UD 
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [_LR] = LAYOUT(
            TO(_UD)
          ),
      [_UD] = LAYOUT(
            TO(_LR)
          )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _UD:
        rgblight_sethsv (HSV_PURPLE);
        break;
    case _LR:
        rgblight_sethsv (HSV_WHITE);
    }
 return state;
};




void encoder_update_user(uint8_t index, bool clockwise) {
if (index == 0){    
    if(IS_LAYER_ON(_LR)) {
        if (clockwise) {
            tap_code(KC_LEFT);
        } 
        else {
            tap_code(KC_RIGHT);
        }
    }
    if(IS_LAYER_ON(_UD)) {
        if (clockwise) {
             tap_code(KC_UP);
        } else {
            tap_code(KC_DOWN);
        }
    }
}

};

