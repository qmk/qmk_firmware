#include "evil80.h"
void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    led_init_ports();
}

void led_init_ports(void) {
    DDRB |= (1<<6) | (1<<7); // OUT
}

void led_set_kb(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
    {
        PORTB |= (1<<6); // HI
    }
    else
    {
        PORTB &= ~(1<<6); // LO
    }

    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
    {
        PORTB |= (1<<7); // HI
    }
    else
    {
        PORTB &= ~(1<<7); // LO
    }
}
