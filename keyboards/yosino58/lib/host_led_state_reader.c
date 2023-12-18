#include <stdio.h>

char host_led_state_str[24];

const char *read_host_led_state(void)
{
  led_t led_state = host_keyboard_led_state();
  snprintf(host_led_state_str, sizeof(host_led_state_str), "NL:%s CL:%s SL:%s",
           led_state.num_lock ? "on" : "- ",
           led_state.caps_lock ? "on" : "- ",
           led_state.scroll_lock ? "on" : "- ");

  return host_led_state_str;
}
