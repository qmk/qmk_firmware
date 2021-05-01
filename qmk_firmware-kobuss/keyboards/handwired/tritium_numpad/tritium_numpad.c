#include "tritium_numpad.h"
#include "led.h"

void keyboard_pre_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	keyboard_pre_init_user();
	led_init_ports();
};

void matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)
	matrix_scan_user();
};

void led_init_ports(void) {
    // * Set our LED pins as output
    // Numlock LED
    setPinOutput(D5);
}

void led_set_kb(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        writePinLow(D5);
    } else {
        writePinHigh(D5);
    }
}
