#include "do60.h"


extern inline void do60_caps_led_on(void);
extern inline void do60_bl_led_on(void);

extern inline void do60_caps_led_off(void);
extern inline void do60_bl_led_off(void);


void led_set_kb(uint8_t usb_led) {
	if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
		do60_caps_led_on();
	} else {
		do60_caps_led_off();
	}

	led_set_user(usb_led);
}
