/* Copyright 2020 Joshua Moses Diamond
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

enum layers {
    _NUMPAD,
    _RGB,
    _MACRO
};

enum custom_keycodes {
    HELLO = SAFE_RANGE,
    CH_CPNL,  // AL Control Panel
    CH_ASST,  // AL Context-aware Desktop Assistant
    CH_SUSP,  // Suspend
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_NUMPAD] = LAYOUT(
                KC_KP_7, KC_KP_8, KC_KP_9, TO(_NUMPAD),
                KC_KP_4, KC_KP_5, KC_KP_6, TO(_RGB),
                KC_KP_1, KC_KP_2, KC_KP_3, TO(_MACRO),
                KC_KP_0, KC_PDOT, KC_PENT
                ),

    [_RGB] = LAYOUT(
                RGB_HUI,  RGB_SAI, RGB_VAI, KC_TRNS,
                RGB_HUD,  RGB_SAD, RGB_VAD, KC_TRNS,
                KC_NO,    KC_NO,   KC_NO,   KC_TRNS,
                RGB_RMOD, RGB_TOG, RGB_MOD
                ),


    [_MACRO] = LAYOUT(
                HELLO,   DEBUG,   RESET,   KC_TRNS,
                KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
                KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
                CH_CPNL, CH_ASST, CH_SUSP
                ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case CH_CPNL: host_consumer_send(AL_CONTROL_PANEL); return false;
            case CH_ASST: host_consumer_send(AL_ASSISTANT); return false;
            case CH_SUSP: tap_code16(LGUI(LSFT(KC_L))); return true;
            case HELLO:   SEND_STRING("Hello, world!"); return true;
        }
    }
    
    return true;
};  

void encoder_update_user(uint8_t index, bool clockwise) {

  switch (get_highest_layer(layer_state)) {
    case _RGB:
      if (index == 0) {
        if (clockwise) {
          rgblight_increase_hue();
        } else {
          rgblight_decrease_hue();
        }
      } else if (index == 1) {
        if (clockwise) {
          rgblight_increase_sat();
        } else {
          rgblight_decrease_sat();
        }
      } else if (index == 2) {
        if (clockwise) {
          rgblight_increase_val();
        } else {
          rgblight_decrease_val();
        }
      }
      break;

    default:
      if (index == 0) {
        if (clockwise) {
          tap_code(KC_BRIU);
        } else {
          tap_code(KC_BRID);
        }
      } else if (index == 1) {
        if (clockwise) {
          tap_code(KC_DOWN);
        } else {
          tap_code(KC_UP);
        }
      } else if (index == 2) {
        if (clockwise) {
          tap_code(KC_VOLU); 
        } else {
          tap_code(KC_VOLD);
        }
      }
      break;

  }
}
