#include "rev2.h"
#include "led.h"

void led_init_ports(void) {
    // * Set our LED pins as output
    DDRB &= ~(1<<5);

	//Set output high, so the capslock led is off
	PORTB |= (1 << 5);
}

void led_set_kb(uint8_t usb_led) {
	if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // Turn capslock on
        PORTF |= (1<<5);
    } else {
        // Turn capslock off
        PORTF &= ~(1<<5);
    }
	led_set_user(usb_led);
}
