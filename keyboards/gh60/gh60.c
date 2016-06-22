#include "gh60.h"
#include "led.h"

__attribute__ ((weak))
void matrix_init_user(void) {
	// leave this function blank - it can be defined in a keymap file
};

__attribute__ ((weak))
void matrix_scan_user(void) {
	// leave this function blank - it can be defined in a keymap file
}

__attribute__ ((weak))
bool process_action_user(keyrecord_t *record) {
	// leave this function blank - it can be defined in a keymap file
	return true;
}

__attribute__ ((weak))
void led_set_user(uint8_t usb_led) {
	// leave this function blank - it can be defined in a keymap file
}

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

bool process_action_kb(keyrecord_t *record) {
	// put your per-action keyboard code here
	// runs for every action, just before processing by the firmware

	return process_action_user(record);
}

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
	
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
		gh60_caps_led_on();
		} else {
		gh60_caps_led_off(); 
    }
	
    // if (usb_led & (1<<USB_LED_NUM_LOCK)) {
		// gh60_esc_led_on();
		// } else {
		// gh60_esc_led_off(); 
    // }
	
    // if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
		// gh60_fn_led_on();
		// } else {
		// gh60_fn_led_off(); 	
    // }

	led_set_user(usb_led);	
}
