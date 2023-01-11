/* Copyright 2021 Ananya Kirti
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


bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_2x3(
        KC_MEDIA_STOP,  KC_MEDIA_PLAY_PAUSE, KC_MUTE,
        KC_MEDIA_REWIND,  KC_MEDIA_FAST_FORWARD,  KC_PGDN
    ),
    [1] = LAYOUT_ortho_2x3(
        _______,  _______,  _______,
        _______,  _______,  _______
    ),
    [2] = LAYOUT_ortho_2x3(
        _______,  _______, _______,
        _______,  _______, _______
    ),
    [3] = LAYOUT_ortho_2x3(
        _______,  _______, _______,
        _______,  _______, _______
    ),
};



// D4 D0
// C6 E6 D7

void matrix_scan_user(void) {
    writePin(C6, layer_state_is(1));
    writePin(E6, layer_state_is(2));
    writePin(D7, layer_state_is(3));
    writePin(D4, layer_state_is(4));
    writePin(D0, layer_state_is(5));
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
        unregister_code(KC_LWIN);
        is_alt_tab_active = false;
        }
  }
}

bool led_update_user(led_t led_state) {
    return false;
};



bool encoder_update_user(uint8_t index, bool clockwise) {
    if(IS_LAYER_ON(1)) { // on 1st layer
        if (clockwise) {
          if (!is_alt_tab_active) {
            is_alt_tab_active = true;
            register_code(KC_LWIN);
          }
          alt_tab_timer = timer_read();
          tap_code16(KC_TAB);
        } else {
          alt_tab_timer = timer_read();
          tap_code16(S(KC_TAB));
        }
    }
    // 2nd layer
    else if(IS_LAYER_ON(2)) { 
      if (clockwise) {
          tap_code(KC_DOWN);
      } else {
          tap_code(KC_UP);
      }
    }
    else if(IS_LAYER_ON(3)) { 
      if (clockwise) {
          tap_code(KC_BRIU);
      } else {
          tap_code(KC_BRID);
      }
    }
    // default layer
    else if(IS_LAYER_ON(0)) { 
      if (clockwise) {
        tap_code(KC_VOLU);
      } else {
          tap_code(KC_VOLD);
      }
    }
    return false;
}
