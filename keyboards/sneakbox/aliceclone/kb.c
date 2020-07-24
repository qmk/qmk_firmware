#include "aliceclone.h"

void keyboard_pre_init_kb() {
    setPinOutput(D7);
    setPinOutput(D6);
    setPinOutput(D4);
    
    keyboard_pre_init_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(D7, led_state.num_lock);
        writePin(D6, led_state.caps_lock);
        writePin(D4, led_state.scroll_lock);
    }
    return res;
}
