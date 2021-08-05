#include "rev3.h"
#include "led.h"

void led_init_ports(void) {
    // * Set our LED pins as output
    DDRE |= (1 << 6);

	//Set output high, so the capslock led is off
	PORTE |= (1 << 6);
}

void led_set_kb(uint8_t usb_led) {
    led_set_user(usb_led);
}
