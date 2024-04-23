#include <stdio.h>
#include "led.h"
#include "host.h"

char host_led_state_str[22];

const char *read_host_led_state(void) {
  led_t led_state = host_keyboard_led_state();

  snprintf(host_led_state_str, sizeof(host_led_state_str), "Lock: %s%s%s",
           led_state.caps_lock ? "CAPL " : "",
           led_state.scroll_lock ? "SCRL " : "",
           led_state.num_lock ? "NUML" : "");

  return host_led_state_str;
}
