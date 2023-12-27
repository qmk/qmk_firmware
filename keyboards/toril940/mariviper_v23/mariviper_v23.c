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

const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *    driver
 *    |  LED address
 *    |  | */
	{ 0, C1_1 }, { 0, C2_1 }, { 0, C3_1 }, // Lock Indicator
	{ 0, C4_1 }, { 0, C5_1 }, { 0, C6_1 }, { 0, C7_1 }, { 0, C8_1 } // Layer Indicator
};



void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up

	led_matrix_enable();
	matrix_init_user();
}

bool led_matrix_indicators_kb(void) {
	led_t led_state = host_keyboard_led_state();
	bool res = led_update_user(led_state);
	if (res)
	{
		led_matrix_set_value(0, led_state.caps_lock ? 255 : 0);
		led_matrix_set_value(1, led_state.num_lock ? 255 : 0);
		led_matrix_set_value(2, led_state.scroll_lock ? 255 : 0);
	}
	return res;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
	// if on layer 0, turn on L1 LED, otherwise off.
	if (get_highest_layer(state) == 0)
	{
		led_matrix_set_value(3, 0xFF);
	}
	else
	{
		led_matrix_set_value(3, 0x00);
	}
	// if on layer 1, turn on L2 LED, otherwise off.
	if (get_highest_layer(state) == 1)
	{
		led_matrix_set_value(4, 0xFF);
	}
	else
	{
		led_matrix_set_value(4, 0x00);
	}

	// if on layer 2, turn on L3 LED, otherwise off.
	if (get_highest_layer(state) == 2)
	{
		led_matrix_set_value(5, 0xFF);
	}
	else
	{
		led_matrix_set_value(5, 0x00);
	}

	// if on layer 3, turn on L4 LED, otherwise off.
	if (get_highest_layer(state) == 3)
	{
		led_matrix_set_value(6, 0xFF);
	}
	else
	{
		led_matrix_set_value(6, 0x00);
	}

	// if on layer 4, turn on L5 LED, otherwise off.
	if (get_highest_layer(state) == 3)
	{
		led_matrix_set_value(7, 0xFF);
	}
	else
	{
		led_matrix_set_value(7, 0x00);
	}

	return layer_state_set_user(state);
}

void suspend_power_down_kb(void) {
	led_matrix_disable();
	suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
	led_matrix_enable();
	suspend_wakeup_init_user();
}
