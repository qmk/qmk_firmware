#include "rev1.h"

void led_set_kb(uint8_t usb_led) {
#ifndef CONVERT_TO_PROTON_C
    /* Map RXLED to USB_LED_NUM_LOCK */
    if (usb_led & (1 << USB_LED_NUM_LOCK)) {
        DDRB |= (1 << 0); PORTB &= ~(1 << 0);
    } else {
        DDRB &= ~(1 << 0); PORTB &= ~(1 << 0);
    }

    /* Map TXLED to USB_LED_CAPS_LOCK */
    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        DDRD |= (1 << 5); PORTD &= ~(1 << 5);
    } else {
        DDRD &= ~(1 << 5); PORTD &= ~(1 << 5);
    }
#endif
}
