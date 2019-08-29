#include "satan.h"

void matrix_init_kb(void) {
  matrix_init_user();
  led_init_ports();
};

void matrix_scan_kb(void) {
  matrix_scan_user();
};

void led_init_ports(void) {
  setPinOutput(B2);
}

void led_set_kb(uint8_t usb_led) {
  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    // Turn Caps Lock LED on
    writePinLow(B2);
  } else {
    // Turn Caps Lock LED off
    writePinHigh(B2);
  }
}
