#include "le.h"

void led_set_kb(uint8_t usb_led) {
	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		DDRB |= (1 << 7); 
		PORTB &= ~(1 << 7);
	} else {
		DDRB &= ~(1 << 7); 
		PORTB &= ~(1 << 7);
	}
}

