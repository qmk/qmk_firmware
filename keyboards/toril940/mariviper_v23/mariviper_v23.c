// Copyright <year> <name> <email> @<github_username>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "quantum.h"

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.

const is31_led PROGMEM g_is31_leds[LED_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *    driver
 *    |  LED address
 *    |  | */
{ 0, C1_1 },
{ 0, C2_1 },
{ 0, C3_1 },
{ 0, C4_1 },
{ 0, C5_1 },
{ 0, C6_1 },
{ 0, C7_1 },
{ 0, C8_1 }
};

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up

	led_matrix_enable();
	matrix_init_user();
}

bool led_matrix_indicators_kb(void) {
	bool res = led_update_user(host_keyboard_led_state());
	if (res) {
		led_matrix_set_value(0, host_keyboard_led_state().caps_lock * 255);
		led_matrix_set_value(1, host_keyboard_led_state().num_lock * 255);
		led_matrix_set_value(2, host_keyboard_led_state().scroll_lock * 255);
	}
	return res;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
	switch (get_highest_layer(state)) {
		case 1:
			led_matrix_set_value(3, 255);
			led_matrix_set_value(4, 0);
			led_matrix_set_value(5, 0);
			led_matrix_set_value(6, 0);
			led_matrix_set_value(7, 0);
			break;
		case 2:
			led_matrix_set_value(3, 0);
			led_matrix_set_value(4, 255);
			led_matrix_set_value(5, 0);
			led_matrix_set_value(6, 0);
			led_matrix_set_value(7, 0);
			break;
		case 3:
			led_matrix_set_value(3, 0);
			led_matrix_set_value(4, 0);
			led_matrix_set_value(5, 255);
			led_matrix_set_value(6, 0);
			led_matrix_set_value(7, 0);
			break;
		case 4:
			led_matrix_set_value(3, 0);
			led_matrix_set_value(4, 0);
			led_matrix_set_value(5, 0);
			led_matrix_set_value(6, 255);
			led_matrix_set_value(7, 0);
			break;
		case 5:
			led_matrix_set_value(3, 0);
			led_matrix_set_value(4, 0);
			led_matrix_set_value(5, 0);
			led_matrix_set_value(6, 0);
			led_matrix_set_value(7, 255);
			break;
		default:
			led_matrix_set_value(3, 255);
			led_matrix_set_value(4, 255);
			led_matrix_set_value(5, 255);
			led_matrix_set_value(6, 255);
			led_matrix_set_value(7, 255);
			break;
	}
	return layer_state_set_user(state);
}

void suspend_power_down_kb(void) {
	led_matrix_set_value(0, 0);
	led_matrix_set_value(1, 0);
	led_matrix_set_value(2, 0);
	led_matrix_set_value(3, 0);
	led_matrix_set_value(4, 0);
	led_matrix_set_value(5, 0);
	led_matrix_set_value(6, 0);
	led_matrix_set_value(7, 0);


	suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
	led_matrix_set_value(0, 255);
	led_matrix_set_value(1, 255);
	led_matrix_set_value(2, 255);
	led_matrix_set_value(3, 255);
	led_matrix_set_value(4, 255);
	led_matrix_set_value(5, 255);
	led_matrix_set_value(6, 255);
	led_matrix_set_value(7, 255);

	suspend_wakeup_init_user();
}
