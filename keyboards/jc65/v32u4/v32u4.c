#include "v32u4.h"

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

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // output low
        DDRB |= (1<<2);
        PORTB &= ~(1<<2);
    } else {
        // Hi-Z
        DDRB &= ~(1<<2);
        PORTB &= ~(1<<2);
    }
	led_set_user(usb_led);
}
