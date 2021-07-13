#include "rev1.h"

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.
  // Set our LED pins as output
  setPinOutput(D5);
  setPinOutput(D3);
  setPinOutput(D2);
  setPinOutput(D1);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(D5, led_state.num_lock);
        writePin(D3, led_state.caps_lock);
        writePin(D2, led_state.scroll_lock);
    }
    return res;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    switch (get_highest_layer(state)) {
      case 1:
        writePinHigh(D1);
        break;
      default: //  for any other layers, or the default layer
        writePinLow(D1);
        break;
      }
    return layer_state_set_user(state);
}
