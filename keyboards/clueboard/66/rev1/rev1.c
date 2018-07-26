#include "rev1.h"

void led_init_ports() {
    // * Set our LED pins as output
    DDRF |= (1<<0);
}

void led_set_kb(uint8_t usb_led) {
    DDRF |= (1<<0);
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // Turn capslock on
        PORTF |= (1<<0);
    } else {
        // Turn capslock off
        PORTF &= ~(1<<0);
    }
}
