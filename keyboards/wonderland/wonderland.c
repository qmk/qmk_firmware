#include "wonderland.h"

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	matrix_init_user();
	led_init_ports();
};

void matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)
	matrix_scan_user();
};

void led_init_ports(void) {
    // * Set our LED pins as output
    DDRB |= (1 << 1) | (1 << 2) | (1 << 3);
}

void led_set_kb(uint8_t usb_led) {
	if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        DDRB |= (1 << 1);
    } else {
        DDRB &= ~(1 << 1);
    }

    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        DDRB |= (1 << 2);
    } else {
        DDRB &= ~(1 << 2);
    }

    if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
        DDRB |= (1 << 3);
    } else {
        DDRB &= ~(1 << 3);
    }
	led_set_user(usb_led);
}
