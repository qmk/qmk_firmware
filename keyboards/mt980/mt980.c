#include "mt980.h"

void keyboard_pre_init_user(void) {
  /* Set NUMLOCK indicator pin as output */
  setPinOutput(C6);
  /* Set CAPSLOCK indicator pin as output */
  setPinOutput(C7);
  /* Set SCROLLOCK indicator pin as output */
  setPinOutput(B5);
}

void led_set_user(uint8_t usb_led) {

  if (usb_led & (1 << USB_LED_NUM_LOCK)) {
    writePinLow(C6);
  }
  else {
    writePinHigh(C6);
  }

  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    writePinLow(C7);
  }
  else {
    writePinHigh(C7);
  }

  if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
    writePinLow(B5);
  }
  else {
    writePinHigh(B5);
  }

}
