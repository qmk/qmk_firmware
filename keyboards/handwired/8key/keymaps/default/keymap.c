 /* Copyright 2022 Marcus Young
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

#define _MAIN 0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAIN] = LAYOUT(
    KC_MEDIA_PREV_TRACK,  KC_AUDIO_VOL_DOWN,  KC_AUDIO_VOL_UP,      KC_MEDIA_NEXT_TRACK,
    KC_MEDIA_STOP,        KC_AUDIO_MUTE,      KC_MEDIA_PLAY_PAUSE,  KC_MEDIA_SELECT
  )
};
