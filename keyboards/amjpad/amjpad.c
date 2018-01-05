#include "amjpad.h"
#include "led.h"

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
    DDRD |= (1<<6);
}

void led_set_kb(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        // Turn numlock on
        PORTD &= ~(1<<6);
    } else {
        // Turn numlock off
        PORTD |= (1<<6);
    }
}
