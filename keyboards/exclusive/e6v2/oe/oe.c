#include "oe.h"

void led_init_ports(void) {
    setPinOutput(B2);
    setPinOutput(B6);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(B2, !led_state.caps_lock);
        writePin(B6, led_state.raw == 0);
    }
    return res;
}
