#include "dz60.h"

void matrix_init_kb(void) {
    matrix_init_user();
    led_init_ports();
};

void led_init_ports(void) {
    setPinOutput(B2);
    writePinHigh(B2);
}

void led_set_kb(uint8_t usb_led) {
    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        writePinLow(B2);
    } else {
        writePinHigh(B2);
    }

    led_set_user(usb_led);
}
