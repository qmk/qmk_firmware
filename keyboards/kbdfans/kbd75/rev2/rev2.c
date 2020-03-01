#include "rev2.h"

void led_set_kb(uint8_t usb_led) {
  // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinLow(B2);
  } else {
    writePinHigh(B2);
  }
}

void matrix_init_kb(void) {
  setPinOutput(B2);
}
