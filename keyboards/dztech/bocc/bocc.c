#include "bocc.h"

void matrix_init_kb(void) {
    setPinOutput(E6);
    matrix_init_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(E6, !led_state.caps_lock);
    }
    return res;
}
