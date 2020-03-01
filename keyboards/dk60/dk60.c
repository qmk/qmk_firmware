#include "dk60.h"

extern inline void dk60_caps_led_on(void);
extern inline void dk60_esc_led_on(void);

extern inline void dk60_caps_led_off(void);
extern inline void dk60_esc_led_off(void);

extern inline void dk60_led_all_on(void);
extern inline void dk60_led_all_off(void);


void dk60_blink_all_leds(void)
{
    dk60_led_all_off();
    dk60_led_all_on();
    _delay_ms(500);
    dk60_led_all_off();
}

void matrix_init_kb(void) {
    led_init_ports();
    dk60_blink_all_leds();
}

void led_init_ports(void) {
    // * Set our LED pins as output
    DDRE |= (1<<6);
    DDRF |= (1<<0);
}

void led_set_kb(uint8_t usb_led) {
	if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
		// Turn capslock on
		dk60_caps_led_on();
	} else {
		// Turn capslock off
		dk60_caps_led_off();
	}
}
