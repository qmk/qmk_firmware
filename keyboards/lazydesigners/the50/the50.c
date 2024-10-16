#include "the50.h"

#define THE50_LED_PIN B7

void the50_led_on(void) {
  gpio_set_pin_output(THE50_LED_PIN);
  gpio_write_pin_low(THE50_LED_PIN);
}

void the50_led_off(void) {
  gpio_set_pin_input(THE50_LED_PIN);
}
