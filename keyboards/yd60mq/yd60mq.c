#include "yd60mq.h"

void led_set_kb(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        setPinOutput(F4);
        writePinLow(F4);
    } else {
        setPinInput(F4);
        writePinLow(F4);
	}

    led_set_user(usb_led);
}
