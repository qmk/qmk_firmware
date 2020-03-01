#include "e7v1.h"

void matrix_init_kb(void) {
  setPinOutput(F0);
}

void led_set_kb(uint8_t usb_led) {
  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    writePinHigh(F0);
  } else {
    writePinLow(F0);
  }
}

