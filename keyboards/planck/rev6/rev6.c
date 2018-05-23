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

void matrix_init_kb(void) {
  // rgblight_enable();
  // rgblight_mode(1);
  // rgblight_setrgb(0xFF, 0xFF, 0xFF);
  ws2812_init();
	matrix_init_user();
}

void matrix_scan_kb(void) {
	matrix_scan_user();

  int s = 0;
  for (int n = 0; n < WS2812_LED_N; n++) {
    int s0 = s + 10*n;
    ws2812_write_led(n, s0%255, (s0+85)%255, (s0+170)%255);
  }
  s += 10;
}
