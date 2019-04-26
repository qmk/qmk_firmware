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

const rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {
    {{0|(0<<4)},   {15*0, 0},  0},     // Esc
    {{0|(1<<4)},   {15*1, 0},  0},     // 1
    {{0|(2<<4)},   {15*2, 0},  0},     // 2
    {{0|(3<<4)},   {15*3, 0},  0},     // 3
    {{0|(4<<4)},   {15*4, 0},  0},     // 4
    {{0|(5<<4)},   {15*5, 0},  0},     // 5
    {{0|(6<<4)},   {15*6, 0},  0},     // 6
    {{0|(7<<4)},   {15*7, 0},  0},     // 7
    {{0|(8<<4)},   {15*8, 0},  0},     // 8
    {{0|(9<<4)},   {15*9, 0},  0},     // 9
    {{0|(10<<4)},  {15*10, 0}, 0},     // 0
    {{0|(11<<4)},  {15*11, 0}, 0},     // -
    {{0|(12<<4)},  {15*12, 0}, 0},     // =
    {{0|(13<<4)},  {15*13.5, 0}, 1},   // Backspace
    {{0|(14<<4)},  {15*15, 0},   1},   // Ins

    {{1|(0<<4)},   {15*0.5, 16},  1},  // Tab
    {{1|(1<<4)},   {15*1.5, 16},  0},  // Q
    {{1|(2<<4)},   {15*2.5, 16},  0},  // W
    {{1|(3<<4)},   {15*3.5, 16},  0},  // E
    {{1|(4<<4)},   {15*4.5, 16},  0},  // R
    {{1|(5<<4)},   {15*5.5, 16},  0},  // T
    {{1|(6<<4)},   {15*6.5, 16},  0},  // Y
    {{1|(7<<4)},   {15*7.5, 16},  0},  // U
    {{1|(8<<4)},   {15*8.5, 16},  0},  // I
    {{1|(9<<4)},   {15*9.5, 16},  0},  // O
    {{1|(10<<4)},  {15*10.5, 16}, 0},  // P
    {{1|(11<<4)},  {15*11.5, 16}, 0},  // [
    {{1|(12<<4)},  {15*12.5, 16},  0}, // ]
    {{1|(13<<4)},  {15*13.75, 16}, 1}, // 
    {{1|(14<<4)},  {15*15, 16},    1}, // Del

    {{2|(0<<4)},   {15*0.75, 32},  1}, // Capslock
    {{2|(1<<4)},   {15*1.75, 32},  0}, // A
    {{2|(2<<4)},   {15*2.75, 32},  0}, // S
    {{2|(3<<4)},   {15*3.75, 32},  0}, // D
    {{2|(4<<4)},   {15*4.75, 32},  0}, // F
    {{2|(5<<4)},   {15*5.75, 32},  0}, // G
    {{2|(6<<4)},   {15*6.75, 32},  0}, // H
    {{2|(7<<4)},   {15*7.75, 32},  0}, // J
    {{2|(8<<4)},   {15*8.75, 32},  0}, // K
    {{2|(9<<4)},   {15*9.75, 32},  0}, // L
    {{2|(10<<4)},  {15*10.75, 32}, 0}, // ;
    {{2|(11<<4)},  {15*11.75, 32}, 0}, // '
    {{2|(13<<4)},  {15*13.25, 32}, 1}, // Enter
    {{2|(14<<4)},  {15*15, 32},    1}, // Pgup

    {{3|(0<<4)},   {15*1.25, 48},  1}, // LShift
    {{3|(2<<4)},   {15*2, 48},  0},    // Z
    {{3|(3<<4)},   {15*3, 48},  0},    // X
    {{3|(4<<4)},   {15*4, 48},  0},    // C
    {{3|(5<<4)},   {15*5, 48},  0},    // V
    {{3|(6<<4)},   {15*6, 48},  0},    // B
    {{3|(7<<4)},   {15*7, 48},  0},    // N
    {{3|(8<<4)},   {15*8, 48},  0},    // M
    {{3|(9<<4)},   {15*9, 48},  0},    // ,
    {{3|(10<<4)},  {15*10, 48},  0},   // .
    {{3|(11<<4)},  {15*11, 48}, 0},    // /
    {{3|(12<<4)},  {15*12.75, 48}, 1}, // Shift
    {{3|(13<<4)},  {15*14, 48}, 1},    // Up
    {{3|(14<<4)},  {15*15, 48}, 1},    // Pgdn
    
    {{4|(0<<4)},   {15*0.25,  64}, 1}, // Ctrl
    {{4|(1<<4)},   {15*1.5,   64}, 1}, // GUI
    {{4|(2<<4)},   {15*2.25,  64}, 1}, // Alt
    {{4|(3<<4)},   {15*6.75,  64}, 0}, // Space
    {{4|(9<<4)},   {15*9,     64}, 1}, // RAlt
    {{4|(10<<4)},  {15*10.25, 64}, 1}, // FN
    {{4|(12<<4)},  {15*13,    64}, 1}, // Left
    {{4|(13<<4)},  {15*14,    64}, 1}, // Down
    {{4|(14<<4)},  {15*15,    64}, 1}, // Right
};
