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
#include "rev6.h"
#include "rgblight.h"

  uint8_t *o_fb;

void matrix_init_kb(void) {
  // rgblight_enable();
  // rgblight_mode(1);
  // rgblight_setrgb(0xFF, 0xFF, 0xFF);

  ledDriverInit(2, GPIOA, 0b00000010, &o_fb);
  testPatternFB(o_fb);

	matrix_init_user();
}

void matrix_scan_kb(void) {
	matrix_scan_user();
  testPatternFB(o_fb);
}
