#include "e7v1.h"

void matrix_init_kb(void) {
  setPinOutput(F0);
  matrix_init_user();
}

void matrix_scan_kb(void) {
  matrix_scan_user();
}

void led_set_kb(uint8_t usb_led) {
  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    writePinHigh(F0);
  } else {
    writePinLow(F0);
  }

  led_set_user(usb_led);
}

