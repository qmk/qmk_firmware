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
					//PORTC |= (1<<6);
					writePinHigh(C6);
				else
					//PORTC &= ~(1<<6);
					writePinLow(C6);
				break;
			case 1:
				// Left hand B6
				if (on)
					//PORTB |= (1<<6);
					writePinHigh(B6);
				else
					//PORTB &= ~(1<<6);
					writePinLow(B6);
				break;
			case 2:
				// Left hand B5
				if (on)
					//PORTB |= (1<<5);
					writePinHigh(B5);
				else
					//PORTB &= ~(1<<5);
					writePinLow(B5);
				break;
			default:
				break;
		}
	} else {
		switch(id) {
			case 3:
				// Right hand F6
				if (on)
					//PORTF |= (1<<6);
					writePinHigh(F6);
				else
					//PORTF &= ~(1<<6);
					writePinLow(F6);
				break;
			case 4:
				// Right hand F7
				if (on)
					//PORTF |= (1<<7);
					writePinHigh(F7);
				else
					//PORTF &= ~(1<<7);
					writePinLow(F7);
				break;
			case 5:
				// Right hand C7
				if (on)
					//PORTC |= (1<<7);
					writePinHigh(C7);
				else
					//PORTC &= ~(1<<7);
					writePinLow(C7);
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

void set_layer_indicators(uint8_t layer) {
	
	switch (layer)
	{
		case 0:
			led_toggle(0, true);
			led_toggle(1, false);
			led_toggle(2, false);
			break;
		case 1:
			led_toggle(0, true);
			led_toggle(1, true);
			led_toggle(2, false);
			break;
		case 2:
			led_toggle(0, true);
			led_toggle(1, true);
			led_toggle(2, true);
			break;
		case 3:
			led_toggle(0, false);
			led_toggle(1, true);
			led_toggle(2, true);
			break;
		case 4:
			led_toggle(0, false);
			led_toggle(1, false);
			led_toggle(2, true);
			break;
		default:
			led_toggle(0, true);
			led_toggle(1, false);
			led_toggle(2, true);
			break;
	}
	
}

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	
	// Initialize indicator LEDs to output
	if (isLeftHand)
	{
		setPinOutput(C6);
		setPinOutput(B6);
		setPinOutput(B5);
		//DDRC |= (1<<6);
		//DDRB |= (1<<6);
		//DDRB |= (1<<5);
	}
	else
	{
		setPinOutput(F6);
		setPinOutput(F7);
		setPinOutput(C7);
		//DDRF |= (1<<6);
		//DDRF |= (1<<7);
		//DDRC |= (1<<7);
	}

	set_layer_indicators(0);
	
	matrix_init_user();
}

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
	
	if (is_keyboard_master()) {
	
		serial_m2s_buffer.nlock_led = IS_LED_ON(usb_led, USB_LED_NUM_LOCK);
		serial_m2s_buffer.clock_led = IS_LED_ON(usb_led, USB_LED_CAPS_LOCK);
		serial_m2s_buffer.slock_led = IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK);

		led_toggle(3, IS_LED_ON(usb_led, USB_LED_NUM_LOCK));
		led_toggle(4, IS_LED_ON(usb_led, USB_LED_CAPS_LOCK));
		led_toggle(5, IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK));
		
	}

	led_set_user(usb_led);
}

uint32_t layer_state_set_kb(uint32_t state) {
	
	if (is_keyboard_master())
	{
		serial_m2s_buffer.current_layer = biton32(state);
		
		// If left half, do the LED toggle thing
		if (isLeftHand)
		{
			set_layer_indicators(biton32(state));
		}
		
	}
	// NOTE: Do not set slave LEDs here.
	// This is not called on slave
	
	return layer_state_set_user(state);
}
