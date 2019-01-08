/* Copyright 2016 Jack Humbert
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
#ifdef HID_KEYCODES_ENABLE
#include "process_hid_keycodes.h"

bool process_hid_keycodes(uint16_t keycode, keyrecord_t *record) {
  if IS_SYSTEM(keycode) {
    host_system_send(KEYCODE2SYSTEM(keycode));
  }
  else if IS_CONSUMER(keycode) {
    host_consumer_send(KEYCODE2CONSUMER(keycode));
  }
  #if TAP_CODE_DELAY > 0
    wait_ms(TAP_CODE_DELAY);
  #endif
  if IS_SYSTEM(keycode) {
    host_system_send(0);
  }
  else if IS_CONSUMER(keycode) {
    host_consumer_send(0);
  }
  return true;
}

#endif
