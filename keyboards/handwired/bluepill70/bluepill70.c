#include "bluepill70.h"

void led_set_kb(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        writePinLow(C13);
    } else {
        writePinHigh(C13);
    }

    led_set_user(usb_led);
}
