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

enum layers { _MAIN };

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    if (clockwise) {
      tap_code(KC_KB_VOLUME_UP); // MacOS Volume Up
    } else {
      tap_code(KC_KB_VOLUME_DOWN); // MacOS Volume Down
    }
  }
    return false;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { //button closest to USB is first
  [_MAIN] = LAYOUT(
     KC_MUTE, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, G(KC_SPC), KC_MNXT
  )
};
