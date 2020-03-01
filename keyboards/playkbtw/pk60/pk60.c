#include "pk60.h"
#include "led.h"

void matrix_init_kb (void) {
  led_init_ports();
}

void led_init_ports(void) {
  // Set capslock LED pin as pinout
  DDRF |= (1 << 4);
  PORTF |= (1 << 4);

}

void led_set_kb(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
      // Turn capslock on
      PORTF &= ~(1 << 4);
  } else {
      // Turn capslock off
      PORTF |= (1 << 4);
  }
}
