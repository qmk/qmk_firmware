/* Copyright 2018 Jack Humbert <jack.humb@gmail.com>
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

#include "thk.h"

extern bool dip_switch[4];

void matrix_init_kb(void) {

  //DDRD |= (1<<5);
    //PORTD |= (1<<5);
  matrix_init_user();
}

void matrix_scan_kb(void) {
  matrix_scan_user();
}

static uint8_t keys_pressed = 0;

bool react_to_keys = false;

void dip_update_kb(uint8_t index, bool active) {
  if (index == 0)
    react_to_keys = active;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    keys_pressed++;
  } else {
    keys_pressed--;
  }

  if (react_to_keys){
    if (keys_pressed) {
      PORTD |= (1<<5);
    } else {
      PORTD &= ~(1<<5);
    }
  }
  return process_record_user(keycode, record);
}
