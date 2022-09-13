#include "leons.h"

void keyboard_pre_init_kb(void) {
    setPinOutput(A1);
    setPinOutput(B6);

    keyboard_pre_init_user();
}

bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        writePin(A1, led_state.caps_lock);
        writePin(B6, led_state.scroll_lock);
    }
    return true;
}
