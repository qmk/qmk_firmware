/* Copyright 2022 Olly Hayes (@ollyhayes)
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

enum layers {
    BASE,
    QWERTY,
    GAMES,
    NUM,
    FUNCTIONS,
    ARR,
    PUNC,
    DUBPUNC,
    MEDIA,
};

enum custom_keycodes {
  DOWN4 = SAFE_RANGE,
  UP4,
  NUM_SWITCH,
  ALTTAB,
  A_UMLAUT,
  O_UMLAUT,
  U_UMLAUT,
};

extern uint16_t key_presses;
