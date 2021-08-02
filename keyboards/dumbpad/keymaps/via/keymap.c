/* Copyright 2019 imchipwood
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
    |             |    4    |    5    |    6    |   Esc   |
    |             |---------|---------|---------|---------|
    |             |    1    |    2    |    3    |   Tab   |
    |-------------|---------|---------|---------|---------|
    | Left mouse  |  MO(1)  |    0    |    .    |  Enter  |
    \-----------------------------------------------------'
    */
    [0] = LAYOUT(
                    KC_7,      KC_8,    KC_9,             KC_BSPC,
                    KC_4,      KC_5,    KC_6,             KC_ESC,
                    KC_1,      KC_2,    KC_3,             KC_TAB,
        KC_BTN1,    MO(1),     KC_0,    KC_PDOT,          KC_ENTER
    ),
    /*
            SUB LAYER
    /-----------------------------------------------------`
    |             |         |         |         |  Reset  |
    |             |---------|---------|---------|---------|
    |             |         |         |         |    +    |
    |             |---------|---------|---------|---------|
    |             |         |         |         |    -    |
    |-------------|---------|---------|---------|---------|
    |    LOCK     |         |  MO(2)  |         |    =    |
    \-----------------------------------------------------'
    */
    [1] = LAYOUT(
                    _______,     _______,     _______,      RESET,
                    _______,     _______,     _______,      KC_KP_PLUS,
                    _______,     _______,     _______,      KC_KP_MINUS,
        KC_MUTE,    _______,      MO(2) ,     _______,      KC_EQL
    ),

    /*
        DEBUG LAYER
    /-----------------------------------------------------`
    |             |         |         |         |  Reset  |
    |             |---------|---------|---------|---------|
    |             |         |         |         |         |
    |             |---------|---------|---------|---------|
    |             |         |         |         |         |
    |-------------|---------|---------|---------|---------|
    |             |         |         |         |         |
    \-----------------------------------------------------'
    */
    [2] = LAYOUT(
                  _______,     _______,     _______,      RESET, 
                  _______,     _______,     _______,      _______, 
                  _______,     _______,     _______,      _______, 
      _______,    _______,     _______,      MO(3) ,      _______
    ),
    
    /*
        EXTRA LAYER
    /-----------------------------------------------------`
    |             |         |         |         |         |
    |             |---------|---------|---------|---------|
    |             |         |         |         |         |
    |             |---------|---------|---------|---------|
    |             |         |         |         |         |
    |-------------|---------|---------|---------|---------|
    |             |         |         |         |         |
    \-----------------------------------------------------'
    */
    [3] = LAYOUT(
                  _______,     _______,     _______,      _______, 
                  _______,     _______,     _______,      _______, 
                  _______,     _______,     _______,      _______, 
      _______,    _______,     _______,     _______,      _______
    ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    switch (get_highest_layer(layer_state)) {
      case 0:
        // sub layer - Scroll
        if (clockwise) {
          tap_code(KC_MS_WH_DOWN);
        } else {
          tap_code(KC_MS_WH_UP);
        }
        break;

      case 1:
        // main layer - Volume
        if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
        break;

      case 2:
        // debug layer - Change track
        if (clockwise) {
          tap_code(KC_MNXT);
        } else {
          tap_code(KC_MPRV);
        }
        break;

      default:
        // any other layer Scroll
        if (clockwise) {
          tap_code(KC_MS_WH_DOWN);
        } else {
          tap_code(KC_MS_WH_UP);
        }
        break;   
    }
  }
  else if (index == 1) {
      switch (get_highest_layer(layer_state)) {
      case 0:
        // sub layer - Volume
        if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
        break;

      case 1:
        // main layer - Scroll
        if (clockwise) {
          tap_code(KC_MS_WH_DOWN);
        } else {
          tap_code(KC_MS_WH_UP);
        }
        break;

      case 2:
        // debug layer - Brightness
        if (clockwise) {
          tap_code(KC_BRID);
        } else {
          tap_code(KC_BRIU);
        }
        break;

      default:
        // any other layer Scroll
        if (clockwise) {
          tap_code(KC_MS_WH_DOWN);
        } else {
          tap_code(KC_MS_WH_UP);
        }
        break;   
    }
  }
  return true;
}
