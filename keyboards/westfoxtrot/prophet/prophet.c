#include "quantum.h"

void keyboard_pre_init_kb(void) {
  gpio_set_pin_output(B12);

  keyboard_pre_init_user();
}

__attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) {
  gpio_write_pin(B12, layer_state_cmp(state, 1));
  return state;
}
