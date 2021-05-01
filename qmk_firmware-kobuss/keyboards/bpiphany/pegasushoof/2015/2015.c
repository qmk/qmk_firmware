/*
Copyright 2016 Daniel Svensson <dsvensson@gmail.com>

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

#include "2015.h"


extern inline void ph_caps_led_on(void);
extern inline void ph_caps_led_off(void);

extern inline void ph_sclk_led_on(void);
extern inline void ph_sclk_led_off(void);

__attribute__ ((weak))
void matrix_init_user(void) {
};

__attribute__ ((weak))
void matrix_scan_user(void) {
}

__attribute__ ((weak))
bool process_action_user(keyrecord_t *record) {
    return true;
}

__attribute__ ((weak))
void led_set_user(uint8_t usb_led) {
}

void matrix_init_kb(void) {
	matrix_init_user();
}

void matrix_scan_kb(void) {
	matrix_scan_user();
}

bool process_action_kb(keyrecord_t *record) {
	return process_action_user(record);
}

void led_set_kb(uint8_t usb_led) {
	led_set_user(usb_led);
}
