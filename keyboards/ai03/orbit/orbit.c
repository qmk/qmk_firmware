/* Copyright 2018 Ryota Goto
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
#include "orbit.h"
#include "split_util.h"
#include "transport.h"


// Call led_toggle to set LEDs easily
// LED IDs:
// 
// (LEFT) 0 1 2   |   3 4 5 (RIGHT)

void led_toggle(int id, bool on) {
	
	if (isLeftHand) {
		switch(id) {
			case 0:
				// Left hand C6
				if (on)
					PORTC |= (1<<6);
				else
					PORTC &= ~(1<<6);
				break;
			case 1:
				// Left hand B6
				if (on)
					PORTB |= (1<<6);
				else
					PORTB &= ~(1<<6);
				break;
			case 2:
				// Left hand B5
				if (on)
					PORTB |= (1<<5);
				else
					PORTB &= ~(1<<5);
				break;
			default:
				break;
		}
	} else {
		switch(id) {
			case 3:
				// Right hand F6
				if (on)
					PORTF |= (1<<6);
				else
					PORTF &= ~(1<<6);
				break;
			case 4:
				// Right hand F7
				if (on)
					PORTF |= (1<<7);
				else
					PORTF &= ~(1<<7);
				break;
			case 5:
				// Right hand C7
				if (on)
					PORTC |= (1<<7);
				else
					PORTC &= ~(1<<7);
				break;
			default:
				break;
		}
	}
}

// Set all LEDs at once using an array of 6 booleans
// LED IDs:
// 
// (LEFT) 0 1 2   |   3 4 5 (RIGHT)
// 
// Ex. set_all_leds({ false, false, false, true, true, true }) would turn off left hand, turn on right hand

void set_all_leds(bool leds[6]) {
	for (int i = 0; i < 6; i++) {
		led_toggle(i, leds[i]);
	}
}

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	
	// Initialize indicator LEDs to output
	if (isLeftHand)
	{
		DDRC |= (1<<6);
		DDRB |= (1<<6);
		DDRB |= (1<<5);
	}
	else
	{
		DDRF |= (1<<6);
		DDRF |= (1<<7);
		DDRC |= (1<<7);
	}
	
	if(is_keyboard_master()) 
	{
		bool allLeds[] = { true, true, true, true, true, true };
		set_all_leds(allLeds);
	}

	matrix_init_user();
}

uint8_t get_current_layer(void) {
	return current_layer;
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
	
	serial_m2s_buffer.nlock_led_status = IS_LED_ON(usb_led, USB_LED_NUM_LOCK);
	serial_m2s_buffer.clock_led_status = IS_LED_ON(usb_led, USB_LED_CAPS_LOCK);
	serial_m2s_buffer.slock_led_status = IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK);

	led_set_user(usb_led);
}

uint32_t layer_state_set_kb(uint32_t state) {
	// keymap-unrelated LED toggles
	
	//current_layer = biton32(state);
	serial_m2s_buffer.active_layer = biton32(state);
	
	return layer_state_set_user(state);
}


