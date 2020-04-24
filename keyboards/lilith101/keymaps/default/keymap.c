/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, oruint8_t encoder_mode = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (IS_LAYER_ON(1) && record->event.pressed) {
        switch (keycode) {
        case CUS_HUE:
            encoder_mode = 1;
            break;
        case CUS_SAT:
            encoder_mode = 2;
            break;
        case CUS_SPD:
            encoder_mode = 3;
            break;
        default:
            encoder_mode = 0;
        }
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (!(state & (1UL << 1))) {
        encoder_mode = 0;
    }
    return state;
}

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { // First encoder 
    if (IS_LAYER_ON(1)) {
      switch (encoder_mode) { 
      case 1:
        if (clockwise) {
          rgblight_increase_hue();
        } else {
          rgblight_decrease_hue();
        }
        break;
      case 2: 
        if (clockwise) {
          rgblight_increase_sat();
        } else {
          rgblight_decrease_sat();
        }
        break;
      case 3: 
        if (clockwise) {
          rgblight_increase_speed();
        } else {
          rgblight_decrease_speed();
        }
        break;
    }
  }
    else {
      if (clockwise) {
        tap_code(KC_DOWN);
      } else {
        tap_code(KC_UP);
      }
    }

  }
}
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "lilith101.h"

/*
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    {
    	{KC_CAPS}
    }, // test with KC_CAPS, KC_A, RESET
};
*/


enum custom_keycodes {
  CUS_HUE = SAFE_RANGE,
  CUS_SAT,
  CUS_VAL,
  CUS_SPD
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
		KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_DEL, KC_HOME, KC_PGUP, KC_PGDN, KC_END, 
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, 
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_P7, KC_P8, KC_P9, KC_MUTE, 
		KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_P4, KC_P5, KC_P6, KC_PPLS, 
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_P1, KC_P2, KC_P3, 
		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, KC_APP, MO(1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0, KC_PDOT, KC_PENT),
  [1] = LAYOUT( /* FN aka MO modifier layer */
    RESET, DF(0), DF(2), DF(3), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PAUS, KC_INS, KC_TRNS, KC_TRNS, KC_TRNS, LCTL(LSFT(KC_END)), 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SLCK, CUS_HUE, CUS_SAT, CUS_SPD, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, NK_TOGG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_VAI, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_RMOD, RGB_VAD, RGB_MOD, KC_TRNS, KC_TRNS, KC_TRNS),




};

/*

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { // First encoder
    if (clockwise) {
      tap_code(KC_UP);
    } else {
      tap_code(KC_DOWN);
    }
  } 
}
*/



uint8_t encoder_mode = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (IS_LAYER_ON(1) && record->event.pressed) {
        switch (keycode) {
        case CUS_HUE:
            encoder_mode = 1;
            break;
        case CUS_SAT:
            encoder_mode = 2;
            break;
        case CUS_SPD:
            encoder_mode = 3;
            break;
        default:
            encoder_mode = 0;
        }
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (!(state & (1UL << 1))) {
        encoder_mode = 0;
    }
    return state;
}

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { // First encoder 
    if (IS_LAYER_ON(1)) {
      switch (encoder_mode) { 
      case 1:
        if (clockwise) {
          rgblight_increase_hue();
        } else {
          rgblight_decrease_hue();
        }
        break;
      case 2: 
        if (clockwise) {
          rgblight_increase_sat();
        } else {
          rgblight_decrease_sat();
        }
        break;
      case 3: 
        if (clockwise) {
          rgblight_increase_speed();
        } else {
          rgblight_decrease_speed();
        }
        break;
    }
  }
    else {
      if (clockwise) {
        tap_code(KC_DOWN);
      } else {
        tap_code(KC_UP);
      }
    }

  }
}

