#include "retro_refit.h"
#include "led.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    // Disable status LED on KB, enable status LED on Teensy (KB_STATUS = !TEENSY_STATUS)
    DDRD |= (1<<6);
    PORTD |= (1<<6);
};

void led_set_kb(uint8_t usb_led) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // output low
        DDRD |= (1<<0);
        PORTD &= ~(1<<0);
    } else {
        // Hi-Z
        DDRD &= ~(1<<0);
        PORTD &= ~(1<<0);
    }
    if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        // output low
        DDRD |= (1<<1);
        PORTD &= ~(1<<1);
    } else {
        // Hi-Z
        DDRD &= ~(1<<1);
        PORTD &= ~(1<<1);
    }
    if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
        // output low
        DDRC |= (1<<6);
        PORTC &= ~(1<<6);
    } else {
        // Hi-Z
        DDRC &= ~(1<<6);
        PORTC &= ~(1<<6);
    }
};
