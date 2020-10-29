#include "idb_60.h"

void keyboard_pre_init_kb(void) {
    setPinOutput(C4);
    setPinOutput(C5);
}

void led_set_kb(uint8_t usb_led) {

    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
		_idb_60_caps_led_on();
		} else {
		_idb_60_caps_led_off();
    }

	led_set_user(usb_led);
}
