#include "oe.h"

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
	DDRB |= (1<<6);
	if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
			// output low
			DDRB |= (1<<2);
			PORTB &= ~(1<<2);
		} else {
			// Hi-Z
			DDRB &= ~(1<<2);
			PORTB &= ~(1<<2);
		}
	// DDRB |= (1<<7);
	// DDRB |= (1<<1);
	// DDRB |= (1<<3);
	// DDRE |= (1<<6);
	if (usb_led == 0){
		PORTB |= (1<<6);
		// PORTB |= (1<<7);
		// PORTB |= (1<<1);
		// PORTB |= (1<<3);
		// PORTE |= (1<<6);
	}
	else{
		PORTB &= ~(1<<6);
		// PORTB &= ~(1<<7);
	}
    
	led_set_user(usb_led);
}
