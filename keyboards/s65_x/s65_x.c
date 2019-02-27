#include "s65_x.h"
#include "led.h"

void matrix_init_kb(void) {
  // put your keyboard start-up code here
  // runs once when the firmware starts up
  matrix_init_user();
};

void matrix_scan_kb(void) {
  // put your looping keyboard code here
  // runs every cycle (a lot)
  matrix_scan_user();
};

void led_set_kb(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
    // Turn capslock on
    PORTB &= ~(1<<7);
  } else {
    // Turn capslock off
    PORTB |= (1<<7);
  }
}
