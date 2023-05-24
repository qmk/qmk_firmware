/*
Copyright 2018 Cole Markham

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

LAYOUT(
    KC_A),


};


bool initialized = 0;

void matrix_init_user(void) {
  if (!initialized){
      dprintf("Initializing in matrix_scan_user");
      // Disable to set a known state
      rgblight_disable();
      rgblight_init();
      // None of the subsequent operations take effect if not enabled
      rgblight_enable();
      rgblight_sethsv(0,0,255);
      rgblight_mode(35);
      initialized = 1;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_A:
    if (record->event.pressed) {
      SEND_STRING("Howdy!!\n");
      rgblight_step();
      return false;
    }
  }
  return true;
}
