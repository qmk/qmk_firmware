#include "z150_blackheart.h"

void matrix_init_kb(void) {
    setPinOutput(B0);
    setPinOutput(E6);
    setPinOutput(E7);
};

void led_set_kb(uint8_t usb_led) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        writePinHigh(E7);
    } else {
        writePinLow(E7);
    }

    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinHigh(B0);
    } else {
        writePinLow(B0);
    }

    if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
        writePinHigh(E6);
    } else {
        writePinLow(E6);
    }
}
