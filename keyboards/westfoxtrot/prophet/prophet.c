#include "quantum.h"

void keyboard_pre_init_kb (void) {
  gpio_set_pin_output(B12);
  gpio_set_pin_output(B13);
}

bool led_update_kb(led_t led_state) {
  bool res = led_update_user(led_state);
  if(res) {
    gpio_write_pin(B13, led_state.caps_lock);
  }
  return res;
}

__attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) {
  gpio_write_pin(B12, layer_state_cmp(state, 1));
  return state;
}
