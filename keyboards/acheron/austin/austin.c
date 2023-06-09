#include "quantum.h"

void keyboard_pre_init_kb(void) {
    setPinOutput(A0);
    setPinOutput(A1);
    setPinOutput(A2);

    keyboard_pre_init_user();
}

bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        writePin(A2, led_state.num_lock);
        writePin(A0, led_state.caps_lock);
        writePin(A1, led_state.scroll_lock);
    }
    return true;
}
