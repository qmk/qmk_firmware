#include <stdio.h>
#include "led.h"
#include "host.h"
#include "ergoluna.h"

char host_led_state_str[24];

const char *read_host_led_state(void)
{
  led_t led_state = host_keyboard_led_state();
  snprintf(host_led_state_str, sizeof(host_led_state_str), "NL:%s CL:%s SL:%s",
           (led_state.num_lock) ? "on " : "off",
           (led_state.caps_lock) ? "on " : "off",
           (led_state.scroll_lock) ? "on " : "off");
  return host_led_state_str;
}
