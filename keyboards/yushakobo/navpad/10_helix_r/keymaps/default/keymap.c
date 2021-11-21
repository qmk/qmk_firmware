/* Copyright 2021 yushakobo
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
    [_BASE] =LAYOUT (\
    KC_PSCR,   KC_SLCK,   KC_PAUS,   KC_MUTE,\
	  KC_INS,    KC_HOME,   KC_PGUP,   KC_ESC,    KC_PSLS,    KC_PAST,   KC_PMNS,                KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,  \
  	KC_DEL,    KC_END,    KC_PGDN,   KC_P7,     KC_P8,      KC_P9,     KC_PPLS,                KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
                                     KC_P4,     KC_P5,      KC_P6,     KC_PPLS,                KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  	S(KC_TAB), KC_UP,     KC_TAB,    KC_P1,     KC_P2,      KC_P3,     LT(1,KC_PENT), KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  \
  	KC_LEFT,   KC_DOWN,   KC_RGHT,   KC_P0,     KC_P0,      KC_PDOT,   LT(1,KC_PENT), KC_SPC,  KC_NO,   KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
    ),

    [_FN1] =LAYOUT (\
  	RESET,     EEP_RST,   KC_NO,     KC_NO,\
  	KC_NO,     KC_NO,     KC_NO,     KC_NLCK,   KC_QUOT,   KC_PEQL,    KC_NO,                  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    EEP_RST,\
  	KC_CAPS,   KC_NLCK,   KC_SLCK,   S(KC_9),   KC_UP,     S(KC_0),    S(KC_SPC),              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,\
                                     KC_LEFT,   KC_BTN3,   KC_RGHT,    S(KC_SPC),              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,\
  	KC_TRNS,   S(KC_ENT), KC_TRNS,   KC_BSPC,   KC_DOWN,   KC_DEL,     KC_TRNS,       KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT, \
  	KC_BTN1,   KC_ENT,    S(KC_SPC),LT(2,KC_SPC),KC_SPC,   KC_COMM,    KC_TRNS,       KC_SPC,  KC_NO,   KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT\
    ),

    [_FN2] =LAYOUT (\
  	RGB_TOG,   RGB_MOD,   RGB_RMOD,  KC_NO,\
  	RGB_HUI,   RGB_SAI,   RGB_VAI,   KC_NO,     KC_NO,     KC_NO,     KC_NO,                  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,\
  	RGB_HUD,   RGB_SAD,   RGB_VAD,   KC_NO,     KC_NO,     KC_NO,     KC_NO,                  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,\
                                     KC_NO,     KC_NO,     KC_NO,     KC_NO,                  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,\
  	KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,         KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,\
  	KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,         KC_SPC,  KC_NO,   KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
    ),

    [_FN3] =LAYOUT (\
  	KC_NO,     KC_NO,     KC_NO,     KC_NO,\
  	KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,                  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,\
  	KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,                  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,\
                                     KC_NO,     KC_NO,     KC_NO,     KC_NO,                  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,\
  	KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,         KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,\
  	KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,         KC_SPC,  KC_NO,   KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
    )
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* Navpad side encoder */
    if (IS_LAYER_ON(_BASE)){
      if (clockwise) {
        tap_code16(KC_VOLU);
      } else {
        tap_code16(KC_VOLD);
      }
    } else if (IS_LAYER_ON(_FN2)){
      if (clockwise) {
        rgblight_increase_sat();
      } else {
        rgblight_decrease_sat();
      }
    } else if (IS_LAYER_ON(_FN1)){
      if (clockwise) {
        rgblight_increase_hue();
      } else {
        rgblight_decrease_hue();
      }
    }
  }
  if (index == 1) { /* Helix side encoder */
    if (IS_LAYER_ON(_BASE)){
      if (clockwise) {
        tap_code16(KC_VOLU);
      } else {
        tap_code16(KC_VOLD);
      }
    } else if (IS_LAYER_ON(_FN2)){
      if (clockwise) {
        rgblight_increase_sat();
      } else {
        rgblight_decrease_sat();
      }
    } else if (IS_LAYER_ON(_FN1)){
      if (clockwise) {
        rgblight_increase_hue();
      } else {
        rgblight_decrease_hue();
      }
    }

  }
  return false;
}
#endif
