/* Copyright 2019 MechMerlin
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
#include "rgb.h"

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.



void matrix_init_kb(void) {
  // put your keyboard start-up code here
  // runs once when the firmware starts up
  setPinOutput(E6);
  matrix_init_user();
}

void matrix_scan_kb(void) {
  // put your looping keyboard code here
  // runs every cycle (a lot)

  matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  // put your per-action keyboard code here
  // runs for every action, just before processing by the firmware

  return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinLow(E6);
  } else {
    writePinHigh(E6);
  }
	led_set_user(usb_led);
}

#define NUMBER_OF_COLS 15
#define NUMBER_OF_ROWS 5
#define colCalc(col)  ((224/(NUMBER_OF_COLS - 1) * col))
#define rowCalc(row)  ((64/(NUMBER_OF_ROWS - 1) * row))

const rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {
    {{0|(0<<4)},   {colCalc(0), rowCalc(0)},  0},
    {{0|(1<<4)},   {colCalc(1), rowCalc(0)},  0},
    {{0|(2<<4)},   {colCalc(2), rowCalc(0)},  0},
    {{0|(3<<4)},   {colCalc(3), rowCalc(0)},  0},
    {{0|(4<<4)},   {colCalc(4), rowCalc(0)},  0},
    {{0|(5<<4)},   {colCalc(5), rowCalc(0)},  0},
    {{0|(6<<4)},   {colCalc(6), rowCalc(0)},  0},
    {{0|(7<<4)},   {colCalc(7), rowCalc(0)},  0},
    {{0|(8<<4)},   {colCalc(8), rowCalc(0)},  0},
    {{0|(9<<4)},   {colCalc(9), rowCalc(0)},  0},
    {{0|(10<<4)},  {colCalc(10), rowCalc(0)}, 0},
    {{0|(11<<4)},  {colCalc(11), rowCalc(0)}, 0},
    {{0|(12<<4)},  {colCalc(12), rowCalc(0)}, 0},
    {{0|(13<<4)},  {colCalc(13), rowCalc(0)}, 1},
    {{0|(14<<4)},  {colCalc(14), rowCalc(0)}, 1},

    {{1|(0<<4)},   {colCalc(0), rowCalc(1)},  1},
    {{1|(1<<4)},   {colCalc(1), rowCalc(1)},  0},
    {{1|(2<<4)},   {colCalc(2), rowCalc(1)},  0},
    {{1|(3<<4)},   {colCalc(3), rowCalc(1)},  0},
    {{1|(4<<4)},   {colCalc(4), rowCalc(1)},  0},
    {{1|(5<<4)},   {colCalc(5), rowCalc(1)},  0},
    {{1|(6<<4)},   {colCalc(6), rowCalc(1)},  0},
    {{1|(7<<4)},   {colCalc(7), rowCalc(1)},  0},
    {{1|(8<<4)},   {colCalc(8), rowCalc(1)},  0},
    {{1|(9<<4)},   {colCalc(9), rowCalc(1)},  0},
    {{1|(10<<4)},  {colCalc(10), rowCalc(1)}, 0},
    {{1|(11<<4)},  {colCalc(11), rowCalc(1)}, 0},
    {{1|(12<<4)},  {colCalc(12), rowCalc(1)}, 0},
    {{1|(13<<4)},  {colCalc(13), rowCalc(1)}, 1},
    {{1|(14<<4)},  {colCalc(14), rowCalc(1)}, 1},

    {{2|(0<<4)},   {colCalc(0), rowCalc(2)},  1},
    {{2|(1<<4)},   {colCalc(1), rowCalc(2)},  0},
    {{2|(2<<4)},   {colCalc(2), rowCalc(2)},  0},
    {{2|(3<<4)},   {colCalc(3), rowCalc(2)},  0},
    {{2|(4<<4)},   {colCalc(4), rowCalc(2)},  0},
    {{2|(5<<4)},   {colCalc(5), rowCalc(2)},  0},
    {{2|(6<<4)},   {colCalc(6), rowCalc(2)},  0},
    {{2|(7<<4)},   {colCalc(7), rowCalc(2)},  0},
    {{2|(8<<4)},   {colCalc(8), rowCalc(2)},  0},
    {{2|(9<<4)},   {colCalc(9), rowCalc(2)},  0},
    {{2|(10<<4)},  {colCalc(10), rowCalc(2)}, 0},
    {{2|(11<<4)},  {colCalc(11), rowCalc(2)}, 0},
    {{2|(13<<4)},  {colCalc(12), rowCalc(2)}, 1},
    {{2|(14<<4)},  {colCalc(13), rowCalc(2)}, 1},

    {{3|(0<<4)},   {colCalc(0), rowCalc(3)},  1},
    {{3|(2<<4)},   {colCalc(1), rowCalc(3)},  0},
    {{3|(3<<4)},   {colCalc(2), rowCalc(3)},  0},
    {{3|(4<<4)},   {colCalc(3), rowCalc(3)},  0},
    {{3|(5<<4)},   {colCalc(4), rowCalc(3)},  0},
    {{3|(6<<4)},   {colCalc(5), rowCalc(3)},  0},
    {{3|(7<<4)},   {colCalc(6), rowCalc(3)},  0},
    {{3|(8<<4)},   {colCalc(7), rowCalc(3)},  0},
    {{3|(9<<4)},   {colCalc(8), rowCalc(3)},  0},
    {{3|(10<<4)},  {colCalc(9), rowCalc(3)},  0},
    {{3|(11<<4)},  {colCalc(10), rowCalc(3)}, 0},
    {{3|(12<<4)},  {colCalc(11), rowCalc(3)}, 1},
    {{3|(13<<4)},  {colCalc(12), rowCalc(3)}, 1},
    {{3|(14<<4)},  {colCalc(13), rowCalc(3)}, 1},
    
    {{4|(0<<4)},   {colCalc(0), rowCalc(4)}, 1},
    {{4|(1<<4)},   {colCalc(1), rowCalc(4)}, 1},
    {{4|(2<<4)},   {colCalc(2), rowCalc(4)}, 1},
    {{4|(3<<4)},   {colCalc(3), rowCalc(4)}, 0},
    {{4|(9<<4)},   {colCalc(4), rowCalc(4)}, 1},
    {{4|(10<<4)},  {colCalc(5), rowCalc(4)}, 1},
    {{4|(12<<4)},  {colCalc(6), rowCalc(4)}, 1},
    {{4|(13<<4)},  {colCalc(7), rowCalc(4)}, 1},
    {{4|(14<<4)},  {colCalc(8), rowCalc(4)}, 1},
};
