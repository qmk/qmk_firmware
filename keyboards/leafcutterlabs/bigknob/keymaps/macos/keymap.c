/* Copyright 2021 Craig Gardner
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

 /*
    Modifications 1/2023 by Kassandra Karan for MacOS support
    * Changed Volume up and down to mac scan codes
    * MacOS doesnt support Stop, so changed default to spotlight search
 */

#include QMK_KEYBOARD_H

#define _MAIN 0

enum custom_keycodes{
  APPLE_SEARCH
};

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    if (clockwise) {
      tap_code(KC_KB_VOLUME_UP); // MacOS Volume Up
    } else {
      tap_code(KC_KB_VOLUME_DOWN); // MacOS Volume Down
    }
  }
    return true;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case APPLE_SEARCH:
            if (record->event.pressed) {
                // when keycode APPLE_SEARCH is pressed
                register_code(KC_LCMD);  // press the Command key
                register_code(KC_SPACE);  // press the Space key
            } else {
                // when keycode APPLE_SEARCH is released
                unregister_code(KC_LCMD);  // Release the Command key
                unregister_code(KC_SPACE);  // release the Space key
            }
            break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { //button closest to USB is first
  [_MAIN] = LAYOUT(
     KC_MUTE, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, APPLE_SEARCH, KC_MNXT
  )
};
