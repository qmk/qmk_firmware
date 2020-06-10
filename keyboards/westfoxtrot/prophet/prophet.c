#include "prophet.h"

void keyboard_pre_init_kb (void) {
  setPinOutput(B12);
  setPinOutput(B13);
}

bool led_update_kb(led_t led_state) {
  bool res = led_update_user(led_state);
  if(res) {
    writePin(B13, led_state.caps_lock);
  }
  return res;
}

__attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) {
  writePin(B12, layer_state_cmp(state, 1));
  return state;
}
