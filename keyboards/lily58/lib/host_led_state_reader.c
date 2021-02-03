#include <stdio.h>
#include "led.h"
#include "host.h"
#include "lily58.h"

char host_led_state_str[24];

const char *read_host_led_state(void)
{
  snprintf(host_led_state_str, sizeof(host_led_state_str), "NL:%s CL:%s SL:%s",
           (IS_HOST_LED_ON(USB_LED_NUM_LOCK)) ? "on" : "- ",
           (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) ? "on" : "- ",
           (IS_HOST_LED_ON(USB_LED_SCROLL_LOCK)) ? "on" : "- ");

  return host_led_state_str;
}
