#include "dz60.h"
#include "led.h"

void matrix_init_kb(void) {
  // Keyboard start-up code goes here
  // Runs once when the firmware starts up
  led_init_ports();
};

void led_init_ports(void) {
  // Set caps lock LED pin as output
  DDRB |= (1 << 2);
  // Default to off
  PORTB |= (1 << 2);
}

void led_set_kb(uint8_t usb_led) {
    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        PORTB &= ~(1 << 2);
    } else {
        PORTB |= (1 << 2);
    }
}
