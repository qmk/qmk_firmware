#include "kc60.h"

void led_set_kb(uint8_t usb_led)
{
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // output low
        DDRB |= (1<<2);
        PORTB &= ~(1<<2);
    } else {
        // Hi-Z
        DDRB &= ~(1<<2);
        PORTB &= ~(1<<2);
    }

     led_set_user(usb_led);
}