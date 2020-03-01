#include "ixora.h"

void matrix_init_kb(void) {
    setPinOutput(A8);
    setPinOutput(A9);
    setPinOutput(A10);
    writePinLow(A8);
    writePinLow(A9);
    writePinLow(A10);
}

void led_set_kb(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinHigh(A10);
    } else {
        writePinLow(A10);
    }
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        writePinHigh(A9);
    } else {
        writePinLow(A9);
    }
    if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
        writePinHigh(A8);
    } else {
        writePinLow(A8);
    }
}
