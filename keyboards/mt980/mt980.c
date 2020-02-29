#include "mt980.h"

void keyboard_pre_init_kb(void) {
  /* Set NUMLOCK indicator pin as output */
  setPinOutput(C6);
  /* Set CAPSLOCK indicator pin as output */
  setPinOutput(C7);
  /* Set SCROLLOCK indicator pin as output */
  setPinOutput(B5);
}

void led_set_kb(uint8_t usb_led) {

  if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
    writePinLow(C6);
  }
  else {
    writePinHigh(C6);
  }

  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinLow(C7);
  }
  else {
    writePinHigh(C7);
  }

  if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
    writePinLow(B5);
  }
  else {
    writePinHigh(B5);
  }

  led_set_user(usb_led);
}
