#include "pk60.h"

void led_set_kb(uint8_t usb_led) {
    
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        PORTF |= (1<<4);
    } else {
        PORTF &= ~(1<<4);
    }
    led_set_user(usb_led);

}