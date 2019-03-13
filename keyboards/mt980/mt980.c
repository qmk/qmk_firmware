#include "mt980.h"

__attribute__ ((weak))
void matrix_init_keymap(void) {}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}
__attribute__ ((weak))
uint32_t layer_state_set_keymap (uint32_t state) {
  return state;
}
__attribute__ ((weak))
void led_set_keymap(uint8_t usb_led) {}

void matrix_init_user(void) {
  matrix_init_keymap();
}

void matrix_scan_user(void) {
  matrix_scan_keymap();
}

void keyboard_pre_init_user(void) {
  /* Set NUMLOCK indicator pin as output */
  setPinOutput(C6);
  /* Set CAPSLOCK indicator pin as output */
  setPinOutput(C7);
  /* Set SCROLLOCK indicator pin as output */
  setPinOutput(B5);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return process_record_keymap(keycode, record);
}

void led_set_user(uint8_t usb_led) {

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

  led_set_keymap(usb_led);
}
