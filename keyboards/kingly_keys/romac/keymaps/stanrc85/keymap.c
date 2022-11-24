/* Copyright 2019 Stanrc85
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

enum keys {
  U_LAYR = SAFE_RANGE,
  D_LAYR
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_NUMPAD] = LAYOUT(
	KC_7,   KC_8, KC_9,
	KC_4,   KC_5, KC_6,
	KC_1,   KC_2, KC_3,
	U_LAYR, KC_0, KC_ENT),

  [_NAVKEY] = LAYOUT(
	KC_HOME, KC_INS,  KC_PGUP,
	KC_END,  KC_UP,   KC_PGDN,
	KC_LEFT, KC_DOWN, KC_RGHT,
	U_LAYR,  TD_TWIN, D_LAYR),

  [_MEDIA] = LAYOUT(
	KC_MUTE, KC_VOLD, KC_VOLU,
	CA_QUOT, KC_MPLY, CA_SCLN,
	CA_COPY, CA_PSTE, KC_NO,
	U_LAYR,  KC_NO,   D_LAYR),

  [_RGB] = LAYOUT(
	RGB_SAI, RGB_VAI, RGB_HUI,
	RGB_SAD, RGB_VAD, RGB_HUD,
	RGB_TOG, RGB_MOD, KC_NO,
	U_LAYR,  KC_NO,   D_LAYR),

  [_FN1PAD] = LAYOUT(
	KC_NO, KC_NO,   KC_NO,
	KC_NO, KC_NO,   QK_BOOT,
	KC_NO, KC_NO,   KC_MAKE,
	KC_NO, KC_LSFT, D_LAYR)
};

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  keypos_t key;
  uint8_t current_layer;
  uint8_t next_layer;
  switch (keycode) {
  case U_LAYR: //cycles up the layers
    if (!record->event.pressed) {
      current_layer = layer_switch_get_layer(key);
      next_layer = current_layer+1;
      layer_move(next_layer);
    }
    break;
  case D_LAYR: //cycles down the layers
    if (!record->event.pressed) {
      current_layer = layer_switch_get_layer(key);
      next_layer = current_layer-1;
      layer_move(next_layer);
    }
    break;
  }
  return true;
};
