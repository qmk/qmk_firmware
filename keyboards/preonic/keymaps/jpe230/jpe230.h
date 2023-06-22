/*
Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>

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

enum jpe230_keycodes {
  KC_LSRS = QK_KB_0,
  KC_LERS,
  KC_LSRE
};

#define LEFT_BAR 0, 9, 5
#define RIGHT_BAR 0, 9, 1

float song_lsrs[][2] = SONG(QWERTY_SOUND);
float song_lers[][2] = SONG(COLEMAK_SOUND);
float song_lsre[][2] = SONG(DVORAK_SOUND);