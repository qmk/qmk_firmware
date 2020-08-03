#include "selene.h"

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(A2, led_state.num_lock);
        writePin(A1, led_state.caps_lock);
        writePin(A0, led_state.scroll_lock);
    }
    return res;
}
