#include "dk60.h"

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
		dk60_caps_led_on();
		} else {
		dk60_caps_led_off();
    }

	led_set_user(usb_led);
}