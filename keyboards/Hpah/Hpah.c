#include "hpah.h"

void matrix_init_kb(void) {
	setPinOutput(F0);
	matrix_init_user();
}


void led_set_user(uint8_t usb_led) {
	if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
		writePinLow(F0);
	} else {
		writePinHigh(F0);
	}
}