#include "decadepad.h"
void matrix_init_kb(void) {
  led_init_ports();
  matrix_init_user(); 
};

void led_init_ports(void) {
  setPinOutput(D4);
}

void led_set_kb(uint8_t usb_led) {
  if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
    // Turn NUM Lock LED on
    writePinLow(D4);
  } else {
    // Turn NUM Lock LED off
    writePinHigh(D4);
  }
    led_set_user(usb_led);
}
