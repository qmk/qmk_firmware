/* Copyright 2018 Jack Humbert
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
#include "stanrc85.h"

#define _NUM 0
#define _NAV 1
#define _MED 2
#define _RGB 3
#define _FN1 4

enum keys {
  C_LAYR = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_NUM] = LAYOUT(
	KC_7,   KC_8, KC_9,
	KC_4,   KC_5, KC_6,
	KC_1,   KC_2, KC_3,
	C_LAYR, KC_0, KC_ENT),

  [_NAV] = LAYOUT(
	KC_HOME, KC_INS,  KC_PGUP,
	KC_END,  KC_UP,   KC_PGDN,
	KC_LEFT, KC_DOWN, KC_RGHT,
	C_LAYR,  TD_TWIN, KC_DOT),

  [_MED] = LAYOUT(
	KC_MUTE, KC_VOLD, KC_VOLU,
	CA_QUOT, KC_MPLY, CA_SCLN,
	LCTL(KC_C), LCTL(KC_V), KC_TRNS,
	C_LAYR,  KC_TRNS, KC_TRNS),

  [_RGB] = LAYOUT(
	RGB_SAI, RGB_VAI, RGB_HUI,
	RGB_SAD, RGB_VAD, RGB_HUD,
	RGB_TOG, RGB_MOD, KC_TRNS,
	C_LAYR,  KC_TRNS, KC_TRNS),

  [_FN1] = LAYOUT(
	KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, RESET,
	C_LAYR,  KC_LSFT, KC_MAKE)
};

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  keypos_t key;
  uint8_t current_layer;
  uint8_t next_layer;
  uint8_t max_layer;
  max_layer = sizeof(keymaps) / MATRIX_ROWS / MATRIX_COLS / 2;
  switch (keycode) {
  case C_LAYR: //Cycles layers from 0 to max_layer
    if (!record->event.pressed) {
      current_layer = layer_switch_get_layer(key);
      next_layer = current_layer + 1;
      if (current_layer < max_layer) {
        layer_on(next_layer);
      }
      else {
        layer_clear();
      }
    }
    break;
  }
  return true;
};
