#include "crkbd.h"

char host_led_state[40];

char *read_host_led_state(void)
{
  snprintf(host_led_state, sizeof(host_led_state), "\n%s  %s  %s",
           (host_keyboard_leds() & (1 << USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
           (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
           (host_keyboard_leds() & (1 << USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");

  return host_led_state;
}
