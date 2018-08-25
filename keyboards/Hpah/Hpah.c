#include "Hpah.h"

void matrix_init_kb(void) {
	matrix_init_user();
}


void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {
		DDRF |= (1 << 0); PORTF &= ~(1 << 0);
	} else {
		DDRF &= ~(1 << 0); PORTF &= ~(1 << 0);
	}

}