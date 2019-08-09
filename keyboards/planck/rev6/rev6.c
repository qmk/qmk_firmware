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

const rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {
  /*{row | col << 4}
    |             {x=0..224, y=0..64}
    |              |                 modifier
    |              |                 | */
  {{2|(5<<4)},   {112, 39}, 0},
  {{7|(1<<4)},   {148, 60}, 0},
  {{3|(4<<4)},   {206, 53}, 0},
  {{4|(4<<4)},   {206, 3},  0},
  {{4|(1<<4)},   {150, 3},  0},
  {{0|(4<<4)},   {74,  3},  0},
  {{0|(1<<4)},   {18,  3},  0},
  {{3|(1<<4)},   {18,  54}, 0},
  {{7|(4<<4)},   {77,  60}, 0}
};


  uint8_t *o_fb;

uint16_t counterst = 0;

void matrix_init_kb(void) {
  // rgblight_enable();
  // rgblight_mode(1);
  // rgblight_setrgb(0xFF, 0xFF, 0xFF);

  //ledDriverInit(9, GPIOA, 0b00000010, &o_fb);
  //testPatternFB(o_fb);

	matrix_init_user();
}

void matrix_scan_kb(void) {
	matrix_scan_user();
  if (counterst == 0) {
    //testPatternFB(o_fb);
  }
  counterst = (counterst + 1) % 1024;
  //rgblight_task();
}
