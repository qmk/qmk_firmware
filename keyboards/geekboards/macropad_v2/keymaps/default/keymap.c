/* Copyright 2020 Geekboards ltd. (geekboards.ru / geekboards.de)
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
#include "quantum.h"
#include "print.h"

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(	KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8)
};

void keyboard_post_init_user(void) 
{
	debug_enable=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
  #ifdef CONSOLE_ENABLE 
    uprintf("SW%u %s\n", record->event.key.col+1 + (4*record->event.key.row), record->event.pressed?"pressed":"released");
  #endif 
  return true;
}