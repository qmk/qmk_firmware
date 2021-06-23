
#include "kabedon98e.h"

void keyboard_pre_init_user(void) {
  setPinOutput(A13);
}

bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
		writePin(B5, !led_state.caps_lock);
    }
    return true;
}
