#include "s65_plus.h"
#include "led.h"

void led_set_kb(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
    // Turn capslock on
    PORTB &= ~(1<<7);
  } else {
    // Turn capslock off
    PORTB |= (1<<7);
  }
}
