#include "utd80.h"


void matrix_init_kb(void) {
  // Keyboard start-up code goes here
  // Runs once when the firmware starts up
  matrix_init_user();
  led_init_ports();
};

void matrix_scan_kb(void) {
  // Looping keyboard code goes here
  // This runs every cycle (a lot)
  matrix_scan_user();
};

void led_init_ports(void) {
    DDRB |= (1<<5) | (1<<6); // OUT
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
        PORTB |= (1<<5); // HI
    }
    else
    {
        PORTB &= ~(1<<5); // LO
    }

    led_set_user(usb_led);
}