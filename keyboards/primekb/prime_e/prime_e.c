/* Copyright 2019 Holten Campbell
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
#include "prime_e.h"
/*
void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	 // set CapsLock LED to output and low

//	matrix_init_user();
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
	if (usb_led & (1<<USB_LED_NUM_LOCK)) {
    PORTB |= (1<<2);
  } else {
    PORTB &= ~(1<<2);
  }
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
    PORTB |= (1<<1);
  } else {
    PORTB &= ~(1<<1);
  }
  
  if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
    PORTB |= (1<<3);
  } else {
    PORTB &= ~(1<<3);
  }
  

	led_set_user(usb_led);
}

//function for layer indicator LED. if (biton32(state) == X) where X=layer number to indicate. In this example the scroll lock indicator is used as defined above.
uint32_t layer_state_set_user(uint32_t state)
{
    if (biton32(state) == 1) {
        PORTB |= (1<<3);
	} else {
		PORTB &= ~(1<<3);
    }
    return state;
}

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	 // set CapsLock LED to output and low
  DDRB |= (1 << 1);
  PORTB &= ~(1 << 1);
  // set NumLock LED to output and low
  DDRB |= (1 << 2);
  PORTB &= ~(1 << 2);
  // set ScrollLock LED to output and low
  DDRB |= (1 << 3);
  PORTB &= ~(1 << 3);

	matrix_init_user();
}*/