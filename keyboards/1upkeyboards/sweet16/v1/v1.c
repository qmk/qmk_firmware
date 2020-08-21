#include "v1.h"

void led_set_kb(uint8_t usb_led) {
#ifndef CONVERT_TO_PROTON_C
    /* Map RXLED to USB_LED_NUM_LOCK */
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        setPinOutput(B0);
        writePinLow(B0);
    } else {
        setPinInput(B0);
    }

    /* Map TXLED to USB_LED_CAPS_LOCK */
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        setPinOutput(D5);
        writePinLow(D5);
    } else {
        setPinInput(D5);
    }
#endif
}
