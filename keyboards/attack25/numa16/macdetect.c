#include QMK_KEYBOARD_H
#include <macdetect.h>

bool macos_check(void) {
  wait_ms(1600);
  bool mac_mode = true;
  tap_code(KC_NLCK);
  wait_ms(100);
  if (host_keyboard_leds() & (1 << USB_LED_NUM_LOCK))
  {
    mac_mode = false;
  }
  tap_code(KC_NLCK);
  wait_ms(100);
  if (host_keyboard_leds() & (1 << USB_LED_NUM_LOCK))
  {
    mac_mode = false;
  }
  return mac_mode;
}