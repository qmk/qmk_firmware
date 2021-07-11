/**
 * Copyright (C) 2021 Jerrell, Jacob <@jjerrell>
 * 
 * This file is part of qmk_firmware.
 * 
 * qmk_firmware is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * qmk_firmware is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with qmk_firmware.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "jjerrell.h"

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

static uint16_t key_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (process_record_keymap(keycode, record)) {
        key_timer = timer_read();
        switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case KC_WORKMAN:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_WORKMAN);
            }
            return false;
            break;
        }
    }
    return true;
}


  // if (timer_elapsed(key_timer) < 100) {
  //   // do something if less than 100ms have passed
  // } else {
  //   // do something if 100ms or more have passed
  // }

  // case KC_CCCV:  // One key copy/paste
  //           if (record->event.pressed) {
  //               copy_paste_timer = timer_read();
  //           } else {
  //               if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {  // Hold, copy
  //                   tap_code16(LCTL(KC_C));
  //               } else {  // Tap, paste
  //                   tap_code16(LCTL(KC_V));
  //               }
  //           }
  //           break;
