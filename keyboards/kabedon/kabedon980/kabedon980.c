#include "kabedon980.h"

void keyboard_pre_init_user(void) {
  /* Set CAPSLOCK indicator pin as output */
  setPinOutput(E6);
}
void led_set_keymap(uint8_t usb_led) {}

void led_set_kb(uint8_t usb_led) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinLow(E6);
  }
  else {
    writePinHigh(E6);
  }
   led_set_keymap(usb_led);
    //led_set_user(usb_led);
}



