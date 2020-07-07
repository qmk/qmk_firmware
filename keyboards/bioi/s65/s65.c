#include "s65.h"
void keyboard_pre_init_kb(void) {
    setPinOutput(F0);
    writePinHigh(F0);
    keyboard_pre_init_user();
}

bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        writePin(F0, !led_state.caps_lock);
    }
    return true;
}
