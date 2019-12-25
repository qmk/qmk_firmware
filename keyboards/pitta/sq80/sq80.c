#include "sq80.h"
#include "led.h"

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
  // Set LED pin as output
  DDRD |= (1 << 0);
  DDRD |= (1 << 1);
  DDRD |= (1 << 2);
  // Default to off
  PORTD |= (1 << 0);
  PORTD |= (1 << 1);
  PORTD |= (1 << 2);
}
void led_set_user(uint8_t usb_led) {

    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        DDRD |= (1 << 0); PORTD &= ~(1 << 0);
    } else {
        DDRD &= ~(1 << 0); PORTD &= ~(1 << 0);
    }

    if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
        DDRD |= (1 << 1); PORTD &= ~(1 << 1);
    } else {
        DDRD &= ~(1 << 1); PORTD &= ~(1 << 1);
    }

    if (usb_led & (1 << USB_LED_NUM_LOCK)) {
        DDRD |= (1 << 2); PORTD &= ~(1 << 2);
    } else {
        DDRD &= ~(1 << 2); PORTD &= ~(1 << 2);
    }
}
