#include "%KEYBOARD%.h"

__attribute__ ((weak))
void * matrix_init_user(void) {
	// leave this function blank - it can be defined in a keymap file
	return NULL;
};

__attribute__ ((weak))
void * matrix_scan_user(void) {
	// leave this function blank - it can be defined in a keymap file
	return NULL;
};

__attribute__ ((weak))
void * led_set_user(uint8_t usb_led) {
	// leave this function blank - it can be defined in a keymap file
	return NULL;
};

void * matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	
	if (matrix_init_user) {
		(*matrix_init_user)();
	}
	return NULL;
};

void * matrix_scan_kb(void) {
    // put your looping keyboard code here
    // runs every cycle (a lot)

	if (matrix_scan_user) {
		(*matrix_scan_user)();
	}
	return NULL;
};

void * led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

	if (led_set_user) {
		(*led_set_user)(usb_led);
	}
	return NULL;
};