#include "at101ish.h"

void keyboard_pre_init_user(void) {
  /* Configure LED driving pins as output pins */
  setPinOutput(NUMLOCKLEDPIN);
  setPinOutput(CAPSLOCKLEDPIN);
  setPinOutput(SCROLLLOCKLEDPIN);
}

void keyboard_post_init_user(void) {
  /* Customise these values to desired behaviour */
  //debug_enable = true;
  //debug_matrix = true;
  //debug_keyboard = true;
  //debug_mouse = true;
}

void led_set_user(uint8_t usb_led) {
  if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
    writePinHigh(NUMLOCKLEDPIN);
  } else {
    writePinLow(NUMLOCKLEDPIN);
  }

  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinHigh(CAPSLOCKLEDPIN);
  } else {
    writePinLow(CAPSLOCKLEDPIN);
  }

  if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
    writePinHigh(SCROLLLOCKLEDPIN);
  } else {
    writePinLow(SCROLLLOCKLEDPIN);
  }
}