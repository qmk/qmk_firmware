/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ares.h"

#ifdef RGBLIGHT_ENABLE

#include <string.h>
#include "i2c_master.h"
#include "rgblight.h"

extern rgblight_config_t rgblight_config;

void matrix_init_kb(void) {
  i2c_init();
  // call user level keymaps, if any
  matrix_init_user();
}

// custom RGB driver
void rgblight_set(void) {
  if (!rgblight_config.enable) {
    memset(led, 0, 3 * RGBLED_NUM);
  }

  i2c_transmit(0xb0, (uint8_t*)led, 3 * RGBLED_NUM, 100);
}

bool rgb_init = false;

void matrix_scan_kb(void) {
  // if LEDs were previously on before poweroff, turn them back on
  if (rgb_init == false && rgblight_config.enable) {
    i2c_transmit(0xb0, (uint8_t*)led, 3 * RGBLED_NUM, 100);
    rgb_init = true;
  }

  rgblight_task();
  matrix_scan_user();
}

#endif

#ifdef BACKLIGHT_ENABLE
void backlight_init_ports(void) {
    setPinOutput(D0);
    setPinOutput(D1);
    setPinOutput(D4);
    setPinOutput(D6);
}

void backlight_set(uint8_t level) {
	if (level == 0) {
		// Turn out the lights
		writePinLow(D0);
		writePinLow(D1);
		writePinLow(D4);
		writePinLow(D6);
	} else {
		// Turn on the lights
		writePinHigh(D0);
		writePinHigh(D1);
		writePinHigh(D4);
		writePinHigh(D6);
	}
}
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
void led_set_kb(uint8_t usb_led) {
  // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
  led_set_user(usb_led);
}
*/