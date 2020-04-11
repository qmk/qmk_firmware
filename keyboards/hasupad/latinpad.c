/* Copyright 2020 latincompass
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
#include "latinpad.h"   
#ifdef RGB_MATRIX_ENABLE
  led_config_t g_led_config = {
  {
    {   1,  2,  3,  4 },  
    {   5,  6,  7,  8 },
    {   9, 10, 11, 12 },
	{   13, 14, 15, 16 },
    {  17, 18, NO_LED, NO_LED }
  },{
    { 74, 21 }, { 37, 21 }, { 24, 21 }, { 18, 21 },
    { 74, 10 }, { 37, 10 }, { 28, 10 }, { 18, 10 },
    { 74, 7 }, { 37, 7 }, { 20, 7 }, { 18, 7 },
    { 74, 5 }, { 37, 5 }, { 22, 5 }, { 18, 5 },
	{ 74, 5 }, { 37, 5 },
  },{
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1,
	1, 1, 1, 1,
    1, 1
  }
  };
#endif
// void matrix_init_kb(void) {
//   // put your keyboard start-up code here
//   // runs once when the firmware starts up

//   matrix_init_user();
// }

// void matrix_scan_kb(void) {
//   // put your looping keyboard code here
//   // runs every cycle (a lot)

//   matrix_scan_user();
// }

// bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
//   // put your per-action keyboard code here
//   // runs for every action, just before processing by the firmware

//   return process_record_user(keycode, record);
// }

//void led_set_kb(uint8_t usb_led) {
  // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

  //led_set_user(usb_led);
//}
