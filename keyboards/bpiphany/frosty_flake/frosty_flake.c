#include "frosty_flake.h"

void led_set_kb(uint8_t usb_led) {
    DDRB |= (1<<7);
    DDRC |= (1<<5) | (1<<6);

    print_dec(usb_led);

    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        PORTC &= ~(1<<5);
    else
        PORTC |=  (1<<5);

    if (usb_led & (1<<USB_LED_NUM_LOCK))
        PORTB &= ~(1<<7);
    else
        PORTB |=  (1<<7);

    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
        PORTC &= ~(1<<6);
    else
        PORTC |=  (1<<6);
}
