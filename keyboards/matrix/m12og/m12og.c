/**
 * m12og.c
 */

#include "m12og.h"

void matrix_init_user(void) {
	setPinOutput(C6);
	setPinOutput(B2);
	setPinOutput(B1);
}

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {
        writePinLow(B1);
	} else {
        writePinHigh(B1);
	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        writePinLow(C6);
	} else {
        writePinHigh(C6);
	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
        writePinLow(B2);
	} else {
        writePinHigh(B2);
	}
}
