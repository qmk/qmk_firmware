// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void matrix_init_kb(void) {
  gpio_set_pin_output(GP9); //init gpio
  gpio_write_pin_low(GP9);
  gpio_set_pin_output(GP11); //init and turn off inverted power led
  gpio_write_pin_high(GP11);

  matrix_init_user();
}

//layer, capslock and numlock
__attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) {
	gpio_write_pin(GP9, layer_state_cmp(state, 1));
  return state;
}

bool led_update_kb(led_t led_state) {
  bool res = led_update_user(led_state);
  if(res) {
    led_state.num_lock = !led_state.num_lock;
    led_update_ports(led_state);
  }
  return res;
}
