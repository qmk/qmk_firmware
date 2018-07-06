#include "h87a.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    led_init_ports();
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


void led_init_ports(void) {
	DDRD |= (1<<5); // OUT
	DDRE |= (1<<6); // OUT
}

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		DDRD |= (1 << 5); PORTD &= ~(1 << 5);
	} else {
		DDRD &= ~(1 << 5); PORTD &= ~(1 << 5);
	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
		DDRE |= (1 << 6); PORTE &= ~(1 << 6);
	} else {
		DDRE &= ~(1 << 6); PORTE &= ~(1 << 6);
	}

}