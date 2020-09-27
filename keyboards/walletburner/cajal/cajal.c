#include "cajal.h"

void matrix_init_kb(void) {
    setPinOutput(B5);
    writePinLow(B5);
    setPinOutput(B6);
    writePinLow(B6);
    setPinOutput(B7);
    writePinLow(B7);
    matrix_init_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(B5, led_state.caps_lock);
        writePin(B6, led_state.num_lock);
        writePin(B7, led_state.scroll_lock);
    }
    return res;
}

