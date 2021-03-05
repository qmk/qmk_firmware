#include "acr60.h"
#include "led.h"

void led_init_ports(void) {
  // Set caps lock LED pin as output
  DDRB |= (1 << 2);
  // Default to off
  PORTB |= (1 << 2);
}

void led_set_kb(uint8_t usb_led) {
  // Code for caps lock LED as reported by the OS
  // Set this per keymap, instead of globally
  led_set_user(usb_led);
}
