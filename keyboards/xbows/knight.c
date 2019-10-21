#include "knight.h"
void led_set_kb(uint8_t usb_led) {
	if (usb_led & (1 << USB_LED_NUM_LOCK)) {
		DDRD |= (1 << 1); PORTD &= ~(1 << 1);
	} else {
		DDRD &= ~(1 << 1); PORTD &= ~(1 << 1);
	}
	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		DDRE |= (1 << 2); PORTE &= ~(1 << 2);
	} else {
		DDRE &= ~(1 << 2); PORTE &= ~(1 << 2);
	}
    led_set_user(usb_led);
}

void matrix_init_kb(void) {
	matrix_init_user();
};


