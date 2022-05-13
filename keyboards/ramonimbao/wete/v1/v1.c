#include "v1.h"

void keyboard_pre_init_user(void) {
    // Initialize indicator LED pins
    setPinOutput(A14); // Num Lock
    setPinOutput(A15); // Scroll Lock
    setPinOutput(B3); // Caps Lock
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        writePin(A14, !led_state.num_lock);
        writePin(A15, !led_state.scroll_lock);
        writePin(B3, !led_state.caps_lock);
    }

    return res;
}
