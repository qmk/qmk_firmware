/* Copyright 2020 yushakobo
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

#include "helix_5r.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {  5,  4,  3,  2,  1,  0, NO_LED },
  {  6,  7,  8,  9, 10, 11, NO_LED },
  { 17, 16, 15, 14, 13, 12, NO_LED },
  { 18, 19, 20, 21, 22, 23, 24 },
  { 31, 30, 29, 28, 27, 26, 25 },
  { 37, 36, 35, 34, 33, 32, NO_LED },
  { 38, 39, 40, 41, 42, 43, NO_LED },
  { 49, 48, 47, 46, 45, 44, NO_LED },
  { 50, 51, 52, 53, 54, 55, 56 },
  { 63, 62, 61, 60, 59, 58, 57 }
}, {
  // LED Index to Physical Position
  {86,0},{69,0},{52,0},{34,0},{17,0},{0,0},
  {0,16},{17,16},{34,16},{52,16},{69,16},{86,16},
  {86,32},{69,32},{52,32},{34,32},{17,32},{0,32},
  {0,48},{17,48},{34,48},{52,48},{69,48},{86,48},{103,48},
  {103,64},{86,64},{69,64},{52,64},{34,64},{17,64},{0,64},
  {138,0},{155,0},{172,0},{190,0},{207,0},{224,0},
  {224,16},{207,16},{190,16},{172,16},{155,16},{138,16},
  {138,32},{155,32},{172,32},{190,32},{207,32},{224,32},
  {224,48},{207,48},{190,48},{172,48},{155,48},{138,48},{121,48},
  {121,64},{138,64},{155,64},{172,64},{190,64},{207,64},{224,64}
}, {
  // LED Index to Flag
  4,4,4,4,4,4,
  4,4,4,4,4,4,
  4,4,4,4,4,4,
  4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,
  4,4,4,4,4,4,
  4,4,4,4,4,4,
  4,4,4,4,4,4,
  4,4,4,4,4,4,4,
  4,4,4,4,4,4,4
} };
#endif

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.

/*
void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

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

bool led_update_kb(led_t led_state) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

    return led_update_user(led_state);
}
*/
