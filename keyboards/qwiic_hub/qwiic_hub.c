/* Copyright 2018 Jack Humbert
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

#include "qwiic_hub.h"

uint8_t *o_fb;

void matrix_init_kb(void) {
  ledDriverInit(1, GPIOA, 0b1000, &o_fb);
  testPatternFB(o_fb);

	matrix_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  return process_record_user(keycode, record);
}

void matrix_scan_kb(void) {

  testPatternFB(o_fb);
  matrix_scan_user();
}

const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_ortho_2x2(
  2,  3,
  0,  1
);
