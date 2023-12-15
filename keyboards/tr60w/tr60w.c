#include "quantum.h"

bool led_update_kb(led_t led_state) {
    bool runDefault = led_update_user(led_state);
    if (runDefault) {
      writePin(B1, !led_state.num_lock);
      writePin(B2, !led_state.caps_lock);
      writePin(B3, !led_state.scroll_lock);
    }
    return runDefault;
}
