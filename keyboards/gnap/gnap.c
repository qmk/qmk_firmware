#include "gnap.h"
#include <stdint.h>
#include "protocol/serial.h"

//GNAP keymap functions
void gnaplight_step(void) {
	serial_send(101);
}

void gnaplight_toggle(void) {
	serial_send(100);
}

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up

	matrix_init_user();

       serial_init();
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
