#include "rev2.h"

void matrix_init_kb(void) {
    matrix_init_user();
    led_init_ports();
};

void led_init_ports(void) {
    setPinOutput(D4);
    writePinHigh(D4);
}

void led_set_kb(uint8_t usb_led) {
    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        writePinLow(D4);
    } else {
        writePinHigh(D4);
    }

    led_set_user(usb_led);
}
