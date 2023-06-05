#include <stdio.h>
#include "quantum.h"

char host_led_state_str[22];

const char *read_host_led_state(void) {
  uint8_t leds = host_keyboard_leds();

  snprintf(host_led_state_str, sizeof(host_led_state_str), "Lock: %s%s%s",
           (leds & (1 << USB_LED_CAPS_LOCK)) ? "CAPL " : "",
           (leds & (1 << USB_LED_SCROLL_LOCK)) ? "SCRL " : "",
           (leds & (1 << USB_LED_NUM_LOCK)) ? "NUML" : "");

  return host_led_state_str;
}
